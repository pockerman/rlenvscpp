CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

SET(EXECUTABLE  example_1)
SET(SOURCE ${EXECUTABLE}.cpp)

ADD_EXECUTABLE(${EXECUTABLE} ${SOURCE})
TARGET_LINK_LIBRARIES(${EXECUTABLE} rlenvscpplib)
TARGET_LINK_LIBRARIES(${EXECUTABLE} CppController)
