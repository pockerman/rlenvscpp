CMAKE_MINIMUM_REQUIRED(VERSION 3.6)

INCLUDE_DIRECTORIES(${PROJECT_INCL_DIR}) 
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIR})

IF( USE_PYTORCH )
	LIST(APPEND CMAKE_PREFIX_PATH /home/alex/MySoftware/libtorch)
	FIND_PACKAGE(Torch REQUIRED CONFIG)
	INCLUDE_DIRECTORIES(${TORCH_INCLUDE_DIRS})
ENDIF()

SET(CMAKE_CXX_COMPILER /usr/bin/g++-11)
SET(CMAKE_C_COMPILER /usr/bin/gcc-11)
SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED True) 

IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
	SET(CMAKE_CXX_FLAGS "-g -Wall -Wextra")
ELSEIF(CMAKE_BUILD_TYPE STREQUAL "Release")
	SET(CMAKE_CXX_FLAGS "-O2")
ENDIF()

SET(CMAKE_LINKER_FLAGS "-pthread")


IF(GTEST_INCLUDE_DIRS MATCHES " ")

	# find gtest
	FIND_PACKAGE(GTest REQUIRED)

	IF(GTest_FOUND)
		INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})
		SET(GTEST_LIB_DIR "/usr/local/lib")
	ENDIF()

ELSE()
	INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})
	SET(GTEST_LIB_DIR "/usr/local/lib")
ENDIF()

# use the Boost link directories
LINK_DIRECTORIES(${Boost_LIBRARY_DIR})
LINK_DIRECTORIES(${CMAKE_INSTALL_PREFIX})
LINK_DIRECTORIES(${GTEST_LIB_DIR})

ADD_SUBDIRECTORY(test_frozen_lake)
ADD_SUBDIRECTORY(test_black_jack)
ADD_SUBDIRECTORY(test_cliff_world)
ADD_SUBDIRECTORY(test_cart_pole)
#ADD_SUBDIRECTORY(test_mountain_car)
#ADD_SUBDIRECTORY(test_taxi)
#ADD_SUBDIRECTORY(test_tiled_cart_pole)
ADD_SUBDIRECTORY(test_grid_world)
ADD_SUBDIRECTORY(test_acrobot)
#ADD_SUBDIRECTORY(test_vector_env_wrapper)
#ADD_SUBDIRECTORY(test_vector_time_step)
ADD_SUBDIRECTORY(test_generic_line)
ADD_SUBDIRECTORY(test_rest_api_server_wrapper)

