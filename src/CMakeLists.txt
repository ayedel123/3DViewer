cmake_minimum_required(VERSION 3.23)
project(3DViewer_by_bebra)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets)


include_directories(ui)
include_directories(gifRecorder)
include_directories(savingFile)
include_directories(viewModel)
include_directories(utils)

add_library(libegif.a STATIC IMPORTED)
set_target_properties(libegif.a PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/gifRecorder/gifEncoder/build/libegif.a)


add_executable(3DViewer_by_bebra
        main.cpp

        ui/glWindow/gl_window.h
        ui/glWindow/gl_window.cpp

        ui/mainWindow/mainwindow.cpp
        ui/mainWindow/mainwindow.h
        ui/mainWindow/mainwindow.ui
        ui/mainWindow/mainWindowBackend.cpp

        gifRecorder/gifRecorder.cpp
        gifRecorder/gifRecorderThread.h
        gifRecorder/gifRecorderThread.cpp

        savingFile/SavedParams.cpp
        savingFile/GlWindowParamsSaver.h
        savingFile/SavingFile.cpp

        viewModel/affine/affine.c
        viewModel/affine/matrix/matrix.c
        viewModel/affine/affine.h
        viewModel/affine/matrix/matrix.h

        viewModel/common.h
        viewModel/parser.c
        viewModel/parser.h
        viewModel/s21_model.c
        viewModel/s21_model.c

        utils/cores.h
        utils/untils.cpp
        utils/utils.h
        utils/edges_counter.cpp
        utils/edges_counter.h

        )



target_link_libraries(3DViewer_by_bebra PRIVATE  Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGL Qt${QT_VERSION_MAJOR}::OpenGLWidgets ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(3DViewer_by_bebra PRIVATE libegif.a)



project(count_edges_test)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)


find_package(Qt6 REQUIRED COMPONENTS Core)


include_directories(viewModel)


add_executable(count_edges_test

        viewModel/common.h
        viewModel/parser.c
        viewModel/parser.h
        viewModel/s21_model.c

        utils/edges_counter.cpp
        utils/edges_counter.h

        tests/edges_counter_test.cpp

        )


target_link_libraries(count_edges_test PRIVATE  Qt${QT_VERSION_MAJOR}::Core check)
