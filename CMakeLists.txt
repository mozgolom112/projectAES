cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 14)
project(prjAES)
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
set(cipherAES_SRCS
aes_main.cpp
aes_main.h
main.cpp
cipher.cpp
cipher.h
setpath.cpp
setpath.h
aes_main.ui
setpath.ui
resourses.qrc
)
# Tell CMake to create the cipherAES executable
add_executable(cipherAES ${cipherAES_SRCS})
# Use the Widgets module from Qt 5
target_link_libraries(cipherAES Qt5::Widgets)
target_link_libraries(cipherAES Qt5::Core)
target_link_libraries(cipherAES ${OPENSSL_LIBRARIES})

include_directories(${OPENSSL_INCLUDE_DIR})
include_directories(${QtWidgets_INCLUDE_DIR})
