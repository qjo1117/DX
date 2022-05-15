@ECHO OFF
 
SET CURR=%CD%
ECHO Current dir: %CURR%
 
FOR /D %%i IN (%CURR%\*) DO (
  PUSHD %%i
  ECHO Check sub-dir in %%i
 
  FOR /D %%k IN (%%i\*) DO (
    PUSHD %%k
 
    ECHO Now in %%k
 
    IF EXIST "*.vcxproj" (
      ECHO Build the project in %%k
       
      msbuild /t:Rebuild /p:Configuration=Release
      copy .\x64\release\*.exe .
      rmdir x64 /S /Q
       
    ) ELSE (
      ECHO No project in %%k
    )   
 
    POPD 
  )
 
  POPD 
)