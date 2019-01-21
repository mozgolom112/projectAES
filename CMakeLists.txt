cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 14)
project(prjCrypto)
set (CMAKE_PREFIX_PATH "H:\\Qt\\5.11.2\\msvc2017_64\\")
set (OPENSSL_ROOT_DIR "C:\\Program Files\\OpenSSL-Win64\\lib\\")
set (QT_ROOT_DIR "H:\\Qt\\5.11.2\\msvc2017_64\\include\\")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(OpenSSL)

# Populate a CMake variable with the sources
set(crypto_prog_SRCS
main.cpp

main_window.h
main_window.cpp
main_window.ui

set_path_window.h
set_path_window.cpp
set_path_window.ui

ialgorithm.h

algorithm_aes.cpp
algorithm_aes.h

resourses.qrc
)
# Tell CMake to create the program_for_crypt executable
add_executable(program_for_crypt ${crypto_prog_SRCS})
# Use the Widgets module from Qt 5
target_link_libraries(program_for_crypt Qt5::Widgets)
target_link_libraries(program_for_crypt Qt5::Core)
target_link_libraries(program_for_crypt ${OPENSSL_LIBRARIES})

include_directories(${OPENSSL_INCLUDE_DIR})
include_directories(${QtWidgets_INCLUDE_DIR})
