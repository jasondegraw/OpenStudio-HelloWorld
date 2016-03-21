CMAKE_MINIMUM_REQUIRED( VERSION 2.8.11 )

SET( target_name HelloWorld )
 
PROJECT( ${target_name} )

# High level project configuration

SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Products" )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Products" )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Products" )

# Build with Multiple Processes

IF(MSVC)
  OPTION( BUILD_WITH_MULTIPLE_PROCESSES "/MP compiler flag for full processor utilization" ON )
  MARK_AS_ADVANCED( BUILD_WITH_MULTIPLE_PROCESSES )
ENDIF()

# Required dependencies 

## OpenStudio

SET( OPENSTUDIO_BUILD_DIR "" CACHE PATH "Build or install directory for OpenStudio build to link against")

INCLUDE ( "${OPENSTUDIO_BUILD_DIR}/OSCore-prefix/src/OSCore-build/OpenStudioCoreConfig.cmake" )

IF(MSVC)
  file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/Products/Debug")
  file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/Products/Release")
  file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/Products/RelWithDebInfo")
  LIST( APPEND CMAKE_LIBRARY_PATH ${OPENSTUDIO_LIB_DIR} )

  file(GLOB DEBUG_DLLS "${OPENSTUDIO_BUILD_DIR}/OSCore-prefix/src/OSCore-build/Products/Debug/*.dll")
  file(GLOB RELEASE_DLLS "${OPENSTUDIO_BUILD_DIR}/OSCore-prefix/src/OSCore-build/Products/Release/*.dll")
  file(GLOB RELDBG_DLLS "${OPENSTUDIO_BUILD_DIR}/OSCore-prefix/src/OSCore-build/Products/RelWithDebInfo/*.dll")

  file(COPY ${DEBUG_DLLS} DESTINATION "${CMAKE_BINARY_DIR}/Products/Debug/")
  file(COPY ${RELEASE_DLLS} DESTINATION "${CMAKE_BINARY_DIR}/Products/Release/")
  file(COPY ${RELDBG_DLLS} DESTINATION "${CMAKE_BINARY_DIR}/Products/RelWithDebInfo/")
ENDIF()

INCLUDE_DIRECTORIES( ${OpenStudioCore_INCLUDE_DIRS} )

link_directories(${OpenStudioCore_LIBRARY_DIRS})

## Boost
IF(APPLE)
  set(Boost_USE_STATIC_LIBS ON)  
ENDIF()
IF (WIN32)
  set(Boost_USE_STATIC_LIBS ON)  
ENDIF (WIN32)

find_package(Boost 1.55.0 COMPONENTS filesystem regex program_options system thread chrono date_time log QUIET)

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

## Qt
find_package(Qt5Widgets) #Qt5Core, Qt5Gui, Qt5Widgets
find_package(Qt5Sql) #Qt5Core, Qt5Sql
find_package(Qt5Network) #Qt5Core, Qt5Network
find_package(Qt5Xml) #Qt5Core, Qt5Xml
#find_package(Qt5WebKit) #Qt5Core, Qt5Gui, Qt5Network, Qt5WebKit
#find_package(Qt5WebKitWidgets) #Qt5Core, Qt5Gui, Qt5Multimedia, Qt5MultimediaWidgets, Qt5Network, Qt5OpenGL, Qt5Positioning, Qt5PrintSupport, Qt5Qml, Qt5Quick, Qt5Sensors, Qt5WebKit, Qt5WebKitWidgets, Qt5Widgets
#find_package(Qt5WinExtras) #Qt5Core, Qt5Gui, Qt5WinExtras
find_package(Qt5Concurrent) #Qt5Core, Qt5Concurrent
find_package(Qt5PrintSupport)  #Qt5Core, Qt5Gui, Qt5PrintSupport, Qt5Widgets
find_package(Qt5WebEngine) #Qt5Core, Qt5Gui, Qt5Network, Qt5Qml, Qt5Quick, Qt5WebEngine
find_package(Qt5WebEngineWidgets) #Qt5Core, Qt5Gui, Qt5Network, Qt5Qml, Qt5Quick, Qt5WebEngine, Qt5WebEngineWidgets, Qt5Widgets

mark_as_advanced(
  Qt5Concurrent_DIR
  Qt5Core_DIR
  Qt5Gui_DIR
  Qt5Gui_EGL_LIBRARY
  Qt5Location_DIR
  Qt5Multimedia_DIR
  Qt5MultimediaWidgets_DIR
  Qt5Network_DIR
  Qt5OpenGL_DIR
  Qt5Positioning_DIR
  Qt5PrintSupport_DIR
  Qt5Qml_DIR
  Qt5Quick_DIR
  Qt5Sensors_DIR
  Qt5Sql_DIR
  Qt5WebEngine_DIR
  Qt5WebEngineWidgets_DIR
  Qt5Widgets_DIR
  #Qt5WinExtras_DIR
  Qt5Xml_DIR
)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Dependencies
SET( ${target_name}_depends
  openstudio_utilities
  ${Boost_LIBRARIES}
  #${QT_LIBS}
)

# HelloWorld

SET( HELLOWORLD_SRC
  main.cpp
  MainWindow.hpp
)

ADD_EXECUTABLE( HelloWorld
  WIN32
  MACOSX_BUNDLE
  ${HELLOWORLD_SRC}
  #${HELLOWORLD_QRCS}
  ${ICON_SRC}
)

TARGET_LINK_LIBRARIES( HelloWorld
  ${${target_name}_depends}
)

