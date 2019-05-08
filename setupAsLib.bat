call setupLibs.bat

@REM VS does not really have any good way to change between configuration types, so just replace the type in the project file
powershell -Command "(gc ScapeGameEngine\ScapeGameEngine.vcxproj) -replace '<ConfigurationType>Application', '<ConfigurationType>StaticLibrary' | Out-File ScapeGameEngine\ScapeGameEngine.vcxproj"
powershell -Command "(gc ScapeGameEngine\ScapeGameEngine.vcxproj) -replace '<PreprocessorDefinitions>', '<PreprocessorDefinitions>SGE_MAKE_LIBRARY;' | Out-File ScapeGameEngine\ScapeGameEngine.vcxproj"