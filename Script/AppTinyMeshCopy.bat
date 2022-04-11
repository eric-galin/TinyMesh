cls

:: x64 Debug
XCOPY /Y "%QTDIR64%\bin\Qt6Cored.dll"	 					"..\Out\x64\Debug\" 
XCOPY /Y "%QTDIR64%\bin\Qt6Guid.dll" 						"..\Out\x64\Debug\" 
XCOPY /Y "%QTDIR64%\bin\Qt6Widgetsd.dll" 					"..\Out\x64\Debug\" 
XCOPY /Y "%QTDIR64%\bin\Qt6Opengld.dll" 					"..\Out\x64\Debug\" 
XCOPY /Y "%QTDIR64%\bin\Qt6PrintSupportd.dll" 				"..\Out\x64\Debug\" 
XCOPY /Y "%QTDIR64%\bin\Qt6OpenGLWidgetsd.dll" 				"..\Out\x64\Debug\" 
XCOPY /Y "%QTDIR64%\bin\icudt53.dll" 						"..\Out\x64\Debug\" 
XCOPY /Y "%QTDIR64%\bin\icuin53.dll" 						"..\Out\x64\Debug\" 
XCOPY /Y "%QTDIR64%\bin\icuuc53.dll" 						"..\Out\x64\Debug\" 
XCOPY /Y "%QTDIR64%\plugins\platforms\qwindowsd.dll" 		"..\Out\x64\Debug\platforms\" 
	
XCOPY /Y "..\Libs\glew32.dll" 								"..\Out\x64\Debug\" 

:: x64 Release
XCOPY /Y "%QTDIR64%\bin\Qt6Core.dll"	 					"..\Out\x64\Release\" 
XCOPY /Y "%QTDIR64%\bin\Qt6Gui.dll" 						"..\Out\x64\Release\" 
XCOPY /Y "%QTDIR64%\bin\Qt6Widgets.dll" 					"..\Out\x64\Release\" 
XCOPY /Y "%QTDIR64%\bin\Qt6Opengl.dll" 						"..\Out\x64\Release\" 
XCOPY /Y "%QTDIR64%\bin\Qt6PrintSupport.dll" 				"..\Out\x64\Release\" 
XCOPY /Y "%QTDIR64%\bin\Qt6OpenGLWidgets.dll" 				"..\Out\x64\Release\" 
XCOPY /Y "%QTDIR64%\bin\icudt53.dll" 						"..\Out\x64\Release\" 
XCOPY /Y "%QTDIR64%\bin\icuin53.dll" 						"..\Out\x64\Release\" 
XCOPY /Y "%QTDIR64%\bin\icuuc53.dll" 						"..\Out\x64\Release\" 
XCOPY /Y "%QTDIR64%\plugins\platforms\qwindows.dll" 		"..\Out\x64\Release\platforms\" 
	
XCOPY /Y "..\Libs\glew32.dll" 								"..\Out\x64\Release\" 