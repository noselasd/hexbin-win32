@set PATH="c:\Program Files (x86)\Windows Installer XML v3.6\bin\";%PATH%
candle installer.wxs
@if %errorlevel% neq 0 pause

light -o Hexbin.msi installer.wixobj
@if %errorlevel% neq 0 pause

