cls

:: x64 Debug
XCOPY /Y "%QTDIR64%\bin\Qt5Cored.dll"	 					"..\Out\x64\Debug\" 
XCOPY /Y "%QTDIR64%\bin\Qt5Guid.dll" 						"..\Out\x64\Debug\" 
XCOPY /Y "%QTDIR64%\bin\Qt5Widgetsd.dll" 					"..\Out\x64\Debug\" 
XCOPY /Y "%QTDIR64%\bin\Qt5Opengld.dll" 					"..\Out\x64\Debug\" 
XCOPY /Y "%QTDIR64%\bin\Qt5PrintSupportd.dll" 				"..\Out\x64\Debug\" 
XCOPY /Y "%QTDIR64%\bin\icudt53.dll" 						"..\Out\x64\Debug\" 
XCOPY /Y "%QTDIR64%\bin\icuin53.dll" 						"..\Out\x64\Debug\" 
XCOPY /Y "%QTDIR64%\bin\icuuc53.dll" 						"..\Out\x64\Debug\" 
	
XCOPY /Y "%PLATFORMDIR%\LibGL\x64\bin\glew32.dll" 			"..\Out\x64\Debug\" 

:: x64 Release
XCOPY /Y "%QTDIR64%\bin\Qt5Core.dll"	 					"..\Out\x64\Release\" 
XCOPY /Y "%QTDIR64%\bin\Qt5Gui.dll" 						"..\Out\x64\Release\" 
XCOPY /Y "%QTDIR64%\bin\Qt5Widgets.dll" 					"..\Out\x64\Release\" 
XCOPY /Y "%QTDIR64%\bin\Qt5Opengl.dll" 						"..\Out\x64\Release\" 
XCOPY /Y "%QTDIR64%\bin\Qt5PrintSupport.dll" 				"..\Out\x64\Release\" 
XCOPY /Y "%QTDIR64%\bin\icudt53.dll" 						"..\Out\x64\Release\" 
XCOPY /Y "%QTDIR64%\bin\icuin53.dll" 						"..\Out\x64\Release\" 
XCOPY /Y "%QTDIR64%\bin\icuuc53.dll" 						"..\Out\x64\Release\" 
	
XCOPY /Y "%PLATFORMDIR%\LibGL\x64\bin\glew32.dll" 			"..\Out\x64\Release\" 