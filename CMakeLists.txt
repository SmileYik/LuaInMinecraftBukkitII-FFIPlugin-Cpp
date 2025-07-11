cmake_minimum_required(VERSION 3.15)
project(ffi-plugin VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(ENABLE_DEBUG)
    message(STATUS "Enable Debug")
    add_compile_definitions(ENABLE_DEBUG)
endif()

find_package(JNI REQUIRED)
if (JNI_FOUND)
    message(STATUS "JNI Found:") 
    message(STATUS "  JAVA_INCLUDE_PATH: ${JAVA_INCLUDE_PATH}")
    message(STATUS "  JAVA_INCLUDE_PATH_2: ${JAVA_INCLUDE_PATH2}")
else()
    message(FATAL_ERROR "Not found JNI, make sure you already installed JDK and configured PATH or JAVA_HOME environment variables.")
endif()

set(PROJECT_SOURCES
    src/ffi_init.cpp
    src/plugin.cpp
    src/bridge.cpp
    src/jni_bridge.cpp
)
set(PROJECT_INCLUDE_DIRECTORIES
    src
    ${JAVA_INCLUDE_PATH}
    ${JAVA_INCLUDE_PATH2}
)

add_library(ffi-plugin SHARED ${PROJECT_SOURCES})
target_include_directories(ffi-plugin PRIVATE ${PROJECT_INCLUDE_DIRECTORIES})
