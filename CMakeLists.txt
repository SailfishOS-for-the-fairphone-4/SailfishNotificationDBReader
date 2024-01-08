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
        SQLite/SQLite3Item.cpp
        SQLite/SQLite3Item.h
        SQLite/SQLite3Result.cpp
        SQLite/SQLite3Result.h
        Serializer.cpp
        Serializer.h
        SQLite/SQLite3.cpp
        SQLite/SQLite3.h)
target_link_libraries(SailFishNotificationDBReader I2CDevice sqlite3)

install(TARGETS SailFishNotificationDBReader DESTINATION bin)