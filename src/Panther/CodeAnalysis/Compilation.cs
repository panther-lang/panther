using System;
using System.Collections.Generic;
using System.Collections.Immutable;
using System.IO;
using System.Linq;
using System.Threading;
using Microsoft.CodeAnalysis.CSharp;
using Mono.Cecil;
using Panther.CodeAnalysis.Binding;
using Panther.CodeAnalysis.CSharp;
using Panther.CodeAnalysis.Emit;
using Panther.CodeAnalysis.Lowering;
using Panther.CodeAnalysis.Symbols;
using Panther.CodeAnalysis.Syntax;
using Panther.IO;
using CASyntaxTree = Microsoft.CodeAnalysis.SyntaxTree;

namespace Panther.CodeAnalysis
{
    public class Compilation
    {
        public bool IsScript { get; }
        public Compilation? Previous { get; }
        public ImmutableArray<SyntaxTree> SyntaxTrees { get; }
        public ImmutableArray<AssemblyDefinition> References { get; }
        public ImmutableArray<Symbol> Types => BoundAssembly.Types;

        private BoundAssembly? _boundAssembly;
        private BoundAssembly BoundAssembly
        {
            get
            {
                if (_boundAssembly == null)
                {
                    var bindAssembly = Binder.BindAssembly(IsScript, SyntaxTrees, Previous?.BoundAssembly,  References);
                    Interlocked.CompareExchange(ref _boundAssembly, bindAssembly, null);
                }

                return _boundAssembly!;
            }
        }


        private Compilation(ImmutableArray<AssemblyDefinition> references, bool isScript, Compilation? previous, params SyntaxTree[] syntaxTrees)
        {
            References = references;
            IsScript = isScript;
            Previous = previous;
            SyntaxTrees = syntaxTrees.ToImmutableArray();
        }

        public static (ImmutableArray<Diagnostic> diagnostics, Compilation? compilation) Create(string[] references, params SyntaxTree[] syntaxTrees)
        {
            var bag = new DiagnosticBag();
            var assemblies = ImmutableArray.CreateBuilder<AssemblyDefinition>();
            foreach (var reference in references)
            {
                try
                {
                    var asm = AssemblyDefinition.ReadAssembly(reference);
                    assemblies.Add(asm);
                }
                catch (BadImageFormatException)
                {
                    bag.ReportInvalidReference(reference);
                }
            }

            if (bag.Any())
            {
                return (bag.ToImmutableArray(), null);
            }

            return (ImmutableArray<Diagnostic>.Empty, Create(assemblies.ToImmutable(), syntaxTrees));
        }

        public static Compilation Create(ImmutableArray<AssemblyDefinition> references, params SyntaxTree[] syntaxTrees) =>
            new Compilation(references, false, null, syntaxTrees);

        public static Compilation CreateScript(ImmutableArray<AssemblyDefinition> references, Compilation? previous, params SyntaxTree[] syntaxTrees) =>
            new Compilation(references, isScript: true, previous, syntaxTrees);

        public IEnumerable<Symbol> GetSymbols()
        {
            Compilation? compilation = this;
            var symbolNames = new HashSet<string>();

            while (compilation != null)
            {
                foreach (var type in compilation.Types.Where(type => symbolNames.Add(type.Name)))
                {
                    yield return type;

                    foreach (var member in type.Members)
                    {
                        yield return member;
                    }
                }

                compilation = compilation.Previous;
            }
        }

        public void EmitTree(TextWriter writer)
        {
            var entryPoint = BoundAssembly.EntryPoint?.Symbol;
            foreach (var type in BoundAssembly.Types)
            {
                // TODO: print type symbol
                foreach (var function in type.Methods)
                {
                    // emit entry point last
                    if (entryPoint == function)
                        continue;

                    if (BoundAssembly.MethodDefinitions.TryGetValue(function, out var body))
                    {
                        EmitTree(function,  body, writer);
                        writer.WriteLine();
                    }
                }
            }


            if (entryPoint != null)
            {
                EmitTree(entryPoint, writer);
                writer.WriteLine();
            }
        }

        public void EmitTree(Symbol method, TextWriter writer)
        {
            BoundAssembly? assembly = BoundAssembly;

            while (assembly != null)
            {
                if (assembly.MethodDefinitions.TryGetValue(method, out var block))
                {
                    EmitTree(method, block, writer);

                    return;
                }

                assembly = assembly.Previous;
            }

            method.WriteTo(writer);
        }

        private static void EmitTree(Symbol method, BoundBlockExpression block, TextWriter writer)
        {
            method.WriteTo(writer);
            writer.WritePunctuation(" = ");
            writer.WriteLine();
            block.WriteTo(writer);
        }

        public IEmitResult EmitVM(string outputPath) =>
           VMEmitter.Emit(BoundAssembly, outputPath);

        public EmitResult Emit(string moduleName, string outputPath) =>
            Emitter.Emit(BoundAssembly, moduleName, outputPath);

        public (bool Success, ImmutableArray<Diagnostic>) EmitCSharp(string moduleName, string outputPath)
        {
            var diagnostics = BoundAssembly.Diagnostics;
            if (!diagnostics.IsEmpty)
                return (false, diagnostics);

            return CSharpEmitter.ToCSharp(moduleName, outputPath, SyntaxTrees.ToArray());
        }

        internal EmitResult Emit(string moduleName, string outputPath, Dictionary<Symbol, FieldReference> previousGlobals, Dictionary<Symbol, MethodReference> previousMethods) =>
            Emitter.Emit(BoundAssembly, moduleName, outputPath, previousGlobals, previousMethods);
    }
}