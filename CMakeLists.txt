cmake_minimum_required(VERSION 3.16)

project(FinalBrownTaskE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Рекурсивно добавляем все .cpp и .h файлы
file(GLOB_RECURSE SOURCES "./TransportationGuide_E/*.cpp" "./TransportationGuide_E/*.h")

add_executable(FinalBrownTaskE ${SOURCES})

include(GNUInstallDirs)
install(TARGETS FinalBrownTaskE
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
