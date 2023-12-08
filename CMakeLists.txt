cmake_minimum_required(VERSION 3.26)
project(SailFishNotificationDBReader)

set(CMAKE_CXX_STANDARD 11)

add_executable(SailFishNotificationDBReader main.cpp)
target_link_libraries(SailFishNotificationDBReader sqlite3)

install(TARGETS SailFishNotificationDBReader DESTINATION bin)