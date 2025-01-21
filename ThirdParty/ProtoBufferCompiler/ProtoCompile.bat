SET PROTOC="C:\Users\user\Desktop\4Q\4Q_TeamProject\ThirdParty\ProtoBufferCompiler\protoc.exe"
SET SOLUTION_DIR="..\..\4Q_Solution\
SET OUT_DIR=%SOLUTION_DIR%Packet"

if not exist %OUT_DIR% mkdir %OUT_DIR%

for %%f in (*.proto) do (
	%PROTOC% --cpp_out=%OUT_DIR% %%f
	echo %%f Compile Complete!
)

IF ERRORLEVEL 1 PAUSE

pause