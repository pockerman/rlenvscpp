CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

SET(EXECUTABLE  ray_example_2)
SET(SOURCE ${EXECUTABLE}.cpp)

ADD_EXECUTABLE(${EXECUTABLE} ${SOURCE})
TARGET_LINK_LIBRARIES(${EXECUTABLE} rlenvscpplib)

IF(RLENVSCPP_RAY)
	TARGET_LINK_LIBRARIES(${EXECUTABLE} ray_api)
ENDIF()
