/**
 *  forward references
 */
typedef struct TextSpan TextSpan;
typedef struct TextLine TextLine;
typedef struct TextLineList TextLineList;
typedef struct SourceFile SourceFile;
typedef struct TextLocation TextLocation;
typedef struct SyntaxTrivia SyntaxTrivia;
typedef struct SyntaxTriviaList SyntaxTriviaList;
typedef struct SyntaxTokenValue SyntaxTokenValue;
typedef struct SyntaxToken SyntaxToken;
typedef struct SimpleToken SimpleToken;
typedef struct Diagnostic Diagnostic;
typedef struct DiagnosticBag DiagnosticBag;
typedef struct Result Result;
typedef struct Scanner Scanner;
typedef struct TypeAnnotationSyntax TypeAnnotationSyntax;
typedef struct ArrayInitializerExpressionSyntax ArrayInitializerExpressionSyntax;
typedef struct ArrayCreationExpressionSyntax ArrayCreationExpressionSyntax;
typedef struct IdentifierNameSyntax IdentifierNameSyntax;
typedef struct GenericNameSyntax GenericNameSyntax;
typedef struct QualifiedNameSyntax QualifiedNameSyntax;
typedef struct SimpleNameSyntax SimpleNameSyntax;
typedef struct NameSyntax NameSyntax;
typedef struct ExpressionItemSyntax ExpressionItemSyntax;
typedef struct ExpressionListSyntax ExpressionListSyntax;
typedef struct AssignmentExpressionSyntax AssignmentExpressionSyntax;
typedef struct BinaryExpressionSyntax BinaryExpressionSyntax;
typedef struct BlockExpressionSyntax BlockExpressionSyntax;
typedef struct CallExpressionSyntax CallExpressionSyntax;
typedef struct ForExpressionSyntax ForExpressionSyntax;
typedef struct GroupExpressionSyntax GroupExpressionSyntax;
typedef struct IfExpressionSyntax IfExpressionSyntax;
typedef struct IndexExpressionSyntax IndexExpressionSyntax;
typedef struct LiteralExpressionSyntax LiteralExpressionSyntax;
typedef struct MemberAccessExpressionSyntax MemberAccessExpressionSyntax;
typedef struct NewExpressionSyntax NewExpressionSyntax;
typedef struct UnaryExpressionSyntax UnaryExpressionSyntax;
typedef struct UnitExpressionSyntax UnitExpressionSyntax;
typedef struct WhileExpressionSyntax WhileExpressionSyntax;
typedef struct ExpressionSyntax ExpressionSyntax;
typedef struct FunctionBodySyntax FunctionBodySyntax;
typedef struct ParameterSyntax ParameterSyntax;
typedef struct TypeArgumentItemSyntax TypeArgumentItemSyntax;
typedef struct TypeArgumentListSyntax TypeArgumentListSyntax;
typedef struct UsingDirectiveSyntax UsingDirectiveSyntax;
typedef struct TemplateSyntax TemplateSyntax;
typedef struct ObjectDeclarationSyntax ObjectDeclarationSyntax;
typedef struct ClassDeclarationSyntax ClassDeclarationSyntax;
typedef struct FunctionDeclarationSyntax FunctionDeclarationSyntax;
typedef struct VariableDeclarationStatementSyntax VariableDeclarationStatementSyntax;
typedef struct BreakStatementSyntax BreakStatementSyntax;
typedef struct ContinueStatementSyntax ContinueStatementSyntax;
typedef struct ExpressionStatementSyntax ExpressionStatementSyntax;
typedef struct StatementSyntax StatementSyntax;
typedef struct GlobalStatementSyntax GlobalStatementSyntax;
typedef struct MemberSyntax MemberSyntax;
typedef struct NamespaceDeclarationSyntax NamespaceDeclarationSyntax;
typedef struct CompilationUnitSyntax CompilationUnitSyntax;
typedef struct Declaration Declaration;
typedef struct Node Node;
typedef struct TokenList TokenList;
typedef struct Parser Parser;
typedef struct SyntaxTree SyntaxTree;
typedef struct ScopeParent ScopeParent;
typedef struct Scope Scope;
typedef struct Symbol Symbol;
typedef struct SymbolResult SymbolResult;
typedef struct Binder Binder;
typedef struct Type Type;
typedef struct UnionType UnionType;
typedef struct ArrayType ArrayType;
typedef struct IntersectionType IntersectionType;
typedef struct PrimitiveType PrimitiveType;
typedef struct TypeVariable TypeVariable;
typedef struct FunctionType FunctionType;
typedef struct RecordType RecordType;
typedef struct RecordTypeField RecordTypeField;
typedef struct SymbolLinks SymbolLinks;
typedef struct NodeLinks NodeLinks;
typedef struct Checker Checker;
typedef struct Emitter Emitter;
typedef struct Compilation Compilation;

/**
 *  types
 */
struct TextSpan {
  int start;
  int length;
  int end;
};

struct TextLine {
  int start;
  int length;
  int length_with_line_breaks;
  int end;
  TextSpan span;
};

struct TextLineList {
  int _size;
  array_TextLine _items;
};

struct SourceFile {
  string content;
  string file_name;
  array_TextLine _lines;
  int line_count;
  int length;
};

struct TextLocation {
  SourceFile source_file;
  TextSpan span;
  string file_name;
  int start_line;
  int start_character;
  int end_line;
  int end_character;
};

struct SyntaxTrivia {
  int kind;
  int start;
  string text;
};

struct SyntaxTriviaList {
  array_SyntaxTrivia _items;
  int _size;
};

struct SyntaxTokenValue {
  int kind;
  array_bool boolValue;
  array_string stringValue;
  array_char characterValue;
  array_int numberValue;
};

struct SyntaxToken {
  SourceFile source_file;
  int kind;
  int start;
  string text;
  SyntaxTokenValue value;
  array_SyntaxTrivia leading;
  array_SyntaxTrivia trailing;
  TextSpan span;
  TextLocation location;
};

struct SimpleToken {
  int kind;
  int start;
  string text;
  SyntaxTokenValue value;
};

struct Diagnostic {
  TextLocation location;
  string message;
};

struct DiagnosticBag {
  int _size;
  array_Diagnostic _items;
};

struct Result {
  bool is_success;
  any value;
};

struct Scanner {
  SourceFile source_file;
  DiagnosticBag diagnostics;
  int _position;
  bool debug;
};

struct TypeAnnotationSyntax {
  SyntaxToken colonToken;
  NameSyntax type;
};

struct ArrayInitializerExpressionSyntax {
  SyntaxToken openBrace;
  ExpressionListSyntax expressions;
  SyntaxToken closeBrace;
};

struct ArrayCreationExpressionSyntax {
  SyntaxToken newKeyword;
  NameSyntax name;
  SyntaxToken openBracket;
  array_ExpressionSyntax arrayRank;
  SyntaxToken closeBracket;
  array_ArrayInitializerExpressionSyntax initializer;
};

struct IdentifierNameSyntax {
  SyntaxToken identifier;
};

struct GenericNameSyntax {
  SyntaxToken identifier;
  TypeArgumentListSyntax typeArgumentlist;
};

struct QualifiedNameSyntax {
  NameSyntax left;
  SyntaxToken dotToken;
  SimpleNameSyntax right;
};

struct SimpleNameSyntax {
  int kind;
  array_GenericNameSyntax genericName;
  array_IdentifierNameSyntax identifierName;
};

struct NameSyntax {
  int kind;
  array_QualifiedNameSyntax qualifiedName;
  array_SimpleNameSyntax simpleName;
};

struct ExpressionItemSyntax {
  ExpressionSyntax expression;
  array_SyntaxToken separatorToken;
};

struct ExpressionListSyntax {
  array_ExpressionItemSyntax expressions;
};

struct AssignmentExpressionSyntax {
  ExpressionSyntax left;
  SyntaxToken equals;
  ExpressionSyntax right;
};

struct BinaryExpressionSyntax {
  ExpressionSyntax left;
  SyntaxToken operator;
  ExpressionSyntax right;
};

struct BlockExpressionSyntax {
  SyntaxToken openBrace;
  array_StatementSyntax statements;
  array_ExpressionSyntax expression;
  SyntaxToken closeBrace;
};

struct CallExpressionSyntax {
  ExpressionSyntax name;
  SyntaxToken openParen;
  ExpressionListSyntax arguments;
  SyntaxToken closeParen;
};

struct ForExpressionSyntax {
  SyntaxToken forKeyword;
  SyntaxToken openParen;
  SyntaxToken identifier;
  SyntaxToken arrow;
  ExpressionSyntax fromExpr;
  SyntaxToken toKeyword;
  ExpressionSyntax toExpr;
  SyntaxToken closeParen;
  ExpressionSyntax body;
};

struct GroupExpressionSyntax {
  SyntaxToken openParen;
  ExpressionSyntax expression;
  SyntaxToken closeParen;
};

struct IfExpressionSyntax {
  SyntaxToken ifKeyword;
  SyntaxToken openParen;
  ExpressionSyntax condition;
  SyntaxToken closeParen;
  ExpressionSyntax then;
  SyntaxToken elseKeyword;
  ExpressionSyntax elseExpr;
};

struct IndexExpressionSyntax {
  ExpressionSyntax left;
  SyntaxToken openBracket;
  ExpressionSyntax index;
  SyntaxToken closeBracket;
};

struct LiteralExpressionSyntax {
  SyntaxToken token;
  SyntaxTokenValue value;
};

struct MemberAccessExpressionSyntax {
  ExpressionSyntax left;
  SyntaxToken dotToken;
  IdentifierNameSyntax right;
};

struct NewExpressionSyntax {
  SyntaxToken newKeyword;
  NameSyntax identifier;
  SyntaxToken openParen;
  ExpressionListSyntax arguments;
  SyntaxToken closeParen;
};

struct UnaryExpressionSyntax {
  SyntaxToken operator;
  ExpressionSyntax expression;
};

struct UnitExpressionSyntax {
  SyntaxToken openParen;
  SyntaxToken closeParen;
};

struct WhileExpressionSyntax {
  SyntaxToken whileKeyword;
  SyntaxToken openParen;
  ExpressionSyntax left;
  SyntaxToken closeParen;
  ExpressionSyntax body;
};

struct ExpressionSyntax {
  int kind;
  array_ArrayCreationExpressionSyntax arrayCreationExpression;
  array_AssignmentExpressionSyntax assignmentExpression;
  array_BinaryExpressionSyntax binaryExpression;
  array_BlockExpressionSyntax blockExpression;
  array_CallExpressionSyntax callExpression;
  array_ForExpressionSyntax forExpression;
  array_GroupExpressionSyntax groupExpression;
  array_IdentifierNameSyntax identifierName;
  array_IfExpressionSyntax ifExpression;
  array_IndexExpressionSyntax indexExpression;
  array_LiteralExpressionSyntax literalExpression;
  array_MemberAccessExpressionSyntax memberAccessExpression;
  array_NewExpressionSyntax newExpression;
  array_UnaryExpressionSyntax unaryExpression;
  array_UnitExpressionSyntax unitExpression;
  array_WhileExpressionSyntax whileExpression;
  int id;
};

struct FunctionBodySyntax {
  SyntaxToken equalToken;
  ExpressionSyntax expression;
};

struct ParameterSyntax {
  SyntaxToken identifier;
  TypeAnnotationSyntax typeAnnotation;
  array_SyntaxToken commaToken;
};

struct TypeArgumentItemSyntax {
  NameSyntax name;
  array_SyntaxToken separator;
};

struct TypeArgumentListSyntax {
  SyntaxToken lessThanToken;
  array_TypeArgumentItemSyntax arguments;
  SyntaxToken greaterThanToken;
};

struct UsingDirectiveSyntax {
  SyntaxToken usingKeyword;
  NameSyntax name;
};

struct TemplateSyntax {
  SyntaxToken openBrace;
  array_MemberSyntax members;
  SyntaxToken closeBrace;
};

struct ObjectDeclarationSyntax {
  SyntaxToken objectKeyword;
  SyntaxToken identifier;
  TemplateSyntax template;
};

struct ClassDeclarationSyntax {
  SyntaxToken classKeyword;
  SyntaxToken identifier;
  SyntaxToken openParenToken;
  array_ParameterSyntax parameters;
  SyntaxToken closeParenToken;
  array_TemplateSyntax template;
};

struct FunctionDeclarationSyntax {
  SyntaxToken defKeyword;
  SyntaxToken identifier;
  SyntaxToken openParenToken;
  array_ParameterSyntax parameters;
  SyntaxToken closeParenToken;
  array_TypeAnnotationSyntax typeAnnotation;
  array_FunctionBodySyntax body;
};

struct VariableDeclarationStatementSyntax {
  SyntaxToken valOrVarKeyword;
  SyntaxToken identifier;
  array_TypeAnnotationSyntax typeAnnotation;
  SyntaxToken equalToken;
  ExpressionSyntax expression;
};

struct BreakStatementSyntax {
  SyntaxToken breakKeyword;
};

struct ContinueStatementSyntax {
  SyntaxToken continueKeyword;
};

struct ExpressionStatementSyntax {
  ExpressionSyntax expression;
};

struct StatementSyntax {
  int kind;
  array_VariableDeclarationStatementSyntax variableDeclarationStatement;
  array_BreakStatementSyntax breakStatement;
  array_ContinueStatementSyntax continueStatement;
  array_ExpressionStatementSyntax expressionStatement;
};

struct GlobalStatementSyntax {
  StatementSyntax statement;
};

struct MemberSyntax {
  int kind;
  array_ObjectDeclarationSyntax objects;
  array_ClassDeclarationSyntax classes;
  array_FunctionDeclarationSyntax functions;
  array_GlobalStatementSyntax statements;
};

struct NamespaceDeclarationSyntax {
  SyntaxToken namespaceKeyword;
  NameSyntax name;
};

struct CompilationUnitSyntax {
  array_NamespaceDeclarationSyntax namespaceDeclaration;
  array_UsingDirectiveSyntax usings;
  array_MemberSyntax members;
  SyntaxToken endToken;
  int kind;
};

struct Declaration {
  int kind;
  string name;
  TextLocation location;
  array_ObjectDeclarationSyntax object_declaration;
  array_ClassDeclarationSyntax class_declaration;
  array_FunctionDeclarationSyntax function_declaration;
  array_ParameterSyntax parameter_declaration;
  array_VariableDeclarationStatementSyntax local_declaration;
  array_SyntaxToken token_declaration;
  int id;
};

struct Node {
  array_Declaration declaration;
  array_ExpressionSyntax expression;
};

struct TokenList {
  array_SyntaxToken _items;
  int _size;
};

struct Parser {
  SourceFile source_file;
  DiagnosticBag diagnostics;
  array_SyntaxToken _tokens;
  int _position;
};

struct SyntaxTree {
  SourceFile file;
  CompilationUnitSyntax root;
  array_Diagnostic diagnostics;
};

struct ScopeParent {
  int kind;
  array_Symbol symbol;
  array_Scope scope;
};

struct Scope {
  ScopeParent parent;
  string note;
  int _symbol_count;
  array_Symbol _symbols;
  int _scope_count;
  array_Scope _scopes;
};

struct Symbol {
  int kind;
  string name;
  TextLocation location;
  array_Symbol _parent;
  array_Declaration _declarations;
  int _declaration_count;
  int id;
  Scope members;
};

struct SymbolResult {
  int kind;
  array_Symbol symbol;
};

struct Binder {
  Symbol root;
  DiagnosticBag diagnostics;
  string ns;
  array_Symbol _parent;
};

struct Type {
  int kind;
  bool resolved;
  array_Symbol symbol;
  array_UnionType union;
  array_IntersectionType intersection;
  array_PrimitiveType primitive;
  array_TypeVariable typeVariable;
  array_FunctionType function;
  array_RecordType record;
  array_ArrayType array;
};

struct UnionType {
  Type left;
  Type right;
};

struct ArrayType {
  Type inner;
};

struct IntersectionType {
  Type left;
  Type right;
};

struct PrimitiveType {
  string name;
};

struct TypeVariable {
  string name;
  int hash;
};

struct FunctionType {
  array_Type parameters;
  Type returnType;
};

struct RecordType {
  array_RecordTypeField fields;
};

struct RecordTypeField {
  string name;
  Type type;
};

struct SymbolLinks {
  bool typing;
  array_Type _type;
};

struct NodeLinks {
  array_Symbol _symbol;
  array_Type _type;
};

struct Checker {
  Symbol root;
  Type BoolType;
  Type CharType;
  Type IntType;
  Type ErrorType;
  Type StringType;
  Type UnitType;
  Type AnyType;
  int last_symbol_id;
  array_SymbolLinks symbol_links;
  int last_node_id;
  array_NodeLinks node_links;
  int rt;
};

struct Emitter {
  array_SyntaxTree syntaxTrees;
  Symbol root;
  string file;
  array_string sections;
  string indent;
  string symbol_prefix;
  Symbol container;
  bool container_has_this;
  Checker checker;
  string nl;
};

struct Compilation {
  array_SyntaxTree syntaxTrees;
  Symbol root;
  array_Diagnostic diagnostics;
};


/**
 *  DECLARATIONS
 */
// emitting root with 112 symbols


/**
 *  METHODS
 */
