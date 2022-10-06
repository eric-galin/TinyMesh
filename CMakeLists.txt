cmake_minimum_required (VERSION 3.1)

project(AppTinyMesh)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui OpenGL OpenGLWidgets)
if (Qt6Widgets_FOUND)
    if (Qt6Widgets_VERSION VERSION_LESS 6.3.0)
        message(FATAL_ERROR "Minimum Qt version is 6.3.0")
    endif()
endif()
qt_standard_project_setup()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_RELEASE "-Ox")
endif()

# Add dependencies
find_package(OpenMP)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# ------------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(APP AppTinyMesh)
set(SRC_DIR AppTinyMesh/Source)
set(INC_DIR AppTinyMesh/Include)
include_directories(${INC_DIR})
aux_source_directory(${SRC_DIR} SRC_FILES)
add_executable(${APP} WIN32
        ${SRC_FILES}
        ${INC_DIR}/box.h
        ${INC_DIR}/camera.h
        ${INC_DIR}/color.h
        ${INC_DIR}/GL.h
        ${INC_DIR}/glew.h
        ${INC_DIR}/implicits.h
        ${INC_DIR}/mathematics.h
        ${INC_DIR}/mesh.h
        ${INC_DIR}/meshcolor.h
        ${INC_DIR}/qte.h
        ${INC_DIR}/ray.h
        ${INC_DIR}/realtime.h
        ${INC_DIR}/shader-api.h
        ${INC_DIR}/cylinder.h
        ${INC_DIR}/sphere.h)
set_target_properties(${APP} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})

# window target exe
if (WIN32)
    find_library(GLEW_LIBRARIES
            NAMES glew32
            HINTS "./Libs/"
            )
    target_link_libraries(${APP}
            ${GLEW_LIBRARIES}
            glu32.lib
            opengl32
            Qt6::Core
            Qt6::Widgets
            Qt6::Gui
            Qt6::OpenGL
            Qt6::OpenGLWidgets
            )
    # linux target exe
else()
    include_directories()

    find_package(GLEW REQUIRED)
    target_link_libraries(${APP}
            ${GLEW_LIBRARIES}
            /usr/local/lib/libGLEW.dylib
            /usr/local/lib/libGLU.dylib
            /usr/local/lib/libglut.dylib
            Qt6::Core
            Qt6::Widgets
            Qt6::Gui
            Qt6::OpenGL
            Qt6::OpenGLWidgets
            )
endif()


# shader folder copy on post build (all platforms)
set(DATA_DIR AppTinyMesh/Shaders)
add_custom_command(
        TARGET ${APP} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/${DATA_DIR}
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Shaders
)

# windeployqt execution for copying all Qt (dll, platforms)
if (WIN32)
    # find qmake executable
    get_target_property(_qmake_executable Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)

    # run windeployqt
    add_custom_command(
            TARGET ${APP} POST_BUILD
            COMMAND "${_qt_bin_dir}/windeployqt.exe" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AppTinyMesh.exe
    )

    # copy glew32.dll
    add_custom_command(
            TARGET ${APP} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/Libs/glew32.dll
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
    )
endif()
