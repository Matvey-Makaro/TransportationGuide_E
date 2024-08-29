cmake_minimum_required(VERSION 3.5)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INSTALL_RPATH "$ORIGIN")

option(REMOTE_CONFIG "Turn remote configuration" ON)
if (REMOTE_CONFIG)
    add_definitions(-DREMOTE_CONFIG)
endif()

set(SMC_INCLUDE ${CMAKE_SOURCE_DIR}/External/SMC)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(LIBS_LIST ${CONAN_LIBS_DEBUG})
  elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
    set(LIBS_LIST ${CONAN_LIBS_RELEASE})
  elseif(${CMAKE_BUILD_TYPE} MATCHES "RelWithDebInfo")
    set(LIBS_LIST ${CONAN_LIBS_RELWITHDEBINFO})
  elseif(${CMAKE_BUILD_TYPE} MATCHES "MinSizeRel")
    set(LIBS_LIST ${CONAN_LIBS_MINSIZEREL})
endif()
        
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

file(GLOB_RECURSE SOURCES_LIST *.h *.cpp *.qrc *.ui *.sm)
get_filename_component(MAIN_CPP ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ABSOLUTE)
list(REMOVE_ITEM SOURCES_LIST ${MAIN_CPP})

add_library(${CONAN_PACKAGE_NAME}-core STATIC ${SOURCES_LIST})
target_link_libraries(${CONAN_PACKAGE_NAME}-core PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets ${LIBS_LIST})

add_executable(${CONAN_PACKAGE_NAME} ${MAIN_CPP})
target_link_libraries(${CONAN_PACKAGE_NAME} PRIVATE ${CONAN_PACKAGE_NAME}-core Qt5::Core Qt5::Gui Qt5::Widgets ${LIBS_LIST})

target_include_directories(${CONAN_PACKAGE_NAME}-core PRIVATE ${SMC_INCLUDE})

set_target_properties(${CONAN_PACKAGE_NAME} 
    PROPERTIES DEBUG_POSTFIX -d
    BUILD_RPATH "$ORIGIN:$ORIGIN/../lib:$ORIGIN/../../lib")
target_compile_definitions(${CONAN_PACKAGE_NAME} 
    PRIVATE 
    PROD_NAME="${CONAN_PACKAGE_NAME}"
    PROD_VERSION="${CONAN_PACKAGE_VERSION}")

install(TARGETS ${CONAN_PACKAGE_NAME}
        CONFIGURATIONS ${CMAKE_BUILD_TYPE}
        RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin)
