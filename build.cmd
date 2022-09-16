@echo off
@REM SET PNC=dotnet pnc
SET PNC="D:\code\Panther2\src\Panther\bin\Debug\net6.0\pnc.exe"
mkdir bin 2>NUL
copy support\dotnet\* bin\ >NUL
del bin\panther.dll 2>NUL
%PNC% src\compiler\math.pn src\compiler\text.pn src\compiler\syntax.pn src\compiler\scanner.pn src\compiler\ast.pn src\compiler\parser.pn src\compiler\program.pn /o bin\panther.dll /r ".\support\dotnet\Panther.StdLib.dll" /r ".\support\dotnet\System.Runtime.dll" /r ".\support\dotnet\System.Runtime.Extensions.dll"
if not exist .\bin\panther.dll exit /b
cls
dotnet .\bin\panther.dll src\compiler\math.pn src\compiler\text.pn src\compiler\syntax.pn src\compiler\scanner.pn src\compiler\ast.pn src\compiler\parser.pn src\compiler\program.pn