SET PROTOC="protoc.exe"
SET OUT_DIR="./ProtoCpp"

if not exist %OUT_DIR% mkdir %OUT_DIR%

for %%f in (*.proto) do (
	%PROTOC% --cpp_out=%OUT_DIR% %%f
	echo %%f Compile Complete!
)

IF ERRORLEVEL 1 PAUSE

pause