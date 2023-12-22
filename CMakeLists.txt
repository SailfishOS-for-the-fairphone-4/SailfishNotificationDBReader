cmake_minimum_required(VERSION 3.18)
project(SailFishNotificationDBReader)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib)

add_executable(SailFishNotificationDBReader main.cpp
        lib/I2CDevice/I2CDevice.cpp
        NotificationSerializer.cpp
        NotificationSerializer.h
        Notification.cpp
        Notification.h
        SQLite3Item.cpp
        SQLite3Item.h
        SQLite3Result.cpp
        SQLite3Result.h
        Serializer.cpp
        Serializer.h)
target_link_libraries(SailFishNotificationDBReader I2CDevice sqlite3)

install(TARGETS SailFishNotificationDBReader DESTINATION bin)