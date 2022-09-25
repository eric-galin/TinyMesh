# Installation notes
First, you must install Qt6 (**version must be > 6.3.0**) (https://www.qt.io/download, use the open source version). On Windows, choose the msvc2019_64 compiler. The following sections show you how to compile the provided code on Windows or Linux after installing Qt.

## Windows
### Visual Studio
Two options for Visual Studio:
- Use the provided solution files (AppTinyMesh.sln) with Visual Studio 2022 Community. You have to set the "QTDIR64" environment variable to your Qt installation folder (example: "E:\Code\Qt\6.3.0\msvc2019_64"). Then, run the Script/AppTinyMeshDeploy.bat. Finally, open the solution and press F5 to build and execute the program.
- Use CMake (https://cmake.org/) with the provided CMakeLists.txt to generate the visual studio solution files (or for another IDE of your choice). You will have to set the Qt6 installation folder in the CMake interface. Then open the solution and press F5 to build and execute the program.

### Qt Creator
Open Qt Creator (make sure you are using Qt6) and click on "File > Open project" and select the CMakeLists.txt file at project root folder. Make sure the correct version of Qt is selected and hit "configure project", and finally compile and execute the program directly.

## Unix
After installing Qt6 (**version must be > 6.3.0**), you must have the following package installed (depending on your Linux installation, other dependencies might be required):
```
sudo apt-get install g++ libglew-dev freeglut3-dev
```
After installing the dependencies, open Qt Creator (make sure you are using Qt6) and click on "File > Open project" and select the CMakeLists.txt file at project root folder. Make sure the correct version of Qt is selected and hit click "configure project", and finally compile and execute the program directly.

# Additional notes
Optionnally, you can use your own code (without Qt) to do the windowing and rendering part. In this case, you can extract the following files, which don't have any dependencies apart from the C++ standard library:
 - box.h/.cpp
 - camera.h/.cpp
 - color.h
 - implicits.h/.cpp
 - mathematics.h
 - mesh.h/.cpp
 - meshcolor.h/.cpp
 - ray.h/.cpp
 
