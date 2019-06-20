@REM Does the reverse of setupAsLib.bat

call setupLibs.bat
powershell -Command "(gc ScapeGameEngine\ScapeGameEngine.vcxproj) -replace '<ConfigurationType>StaticLibrary', '<ConfigurationType>Application' | Out-File ScapeGameEngine\ScapeGameEngine.vcxproj"
powershell -Command "(gc ScapeGameEngine\ScapeGameEngine.vcxproj) -replace 'SGE_MAKE_LIB;', '' | Out-File ScapeGameEngine\ScapeGameEngine.vcxproj"