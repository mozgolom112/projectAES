cmake_minimum_required(VERSION 3.1.0)

project(testproject)
#set (CMAKE_PREFIX_PATH "H:\\Qt\\5.11.2\\msvc2017_64\\")
#set (OpenSSL_DIR "C:\\Program Files\\OpenSSL-Win64\\")
set (OPENSSL_ROOT_DIR "C:\\Program Files\\OpenSSL-Win64\\lib\\")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(OpenSSL)

# Populate a CMake variable with the sources
set(helloworld_SRCS
aes_main.cpp
aes_main.h
main.cpp
cipher.cpp
cipher.h
setpath.cpp
setpath.h
aes_main.ui
setpath.ui
)
# Tell CMake to create the helloworld executable
add_executable(helloworld ${helloworld_SRCS})
# Use the Widgets module from Qt 5
target_link_libraries(helloworld Qt5::Widgets)
target_link_libraries(helloworld Qt5::Network)
target_link_libraries(helloworld ${OPENSSL_LIBRARIES})
include_directories(${OPENSSL_INCLUDE_DIR})