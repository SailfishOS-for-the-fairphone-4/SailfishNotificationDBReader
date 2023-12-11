cmake_minimum_required(VERSION 3.18)
project(SailFishNotificationDBReader)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib)

add_executable(SailFishNotificationDBReader main.cpp
        lib/I2CDevice/I2CDevice.cpp)
target_link_libraries(SailFishNotificationDBReader I2CDevice sqlite3)

install(TARGETS SailFishNotificationDBReader DESTINATION bin)