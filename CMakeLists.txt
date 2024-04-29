cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(SHAPES ${SRC}/shapes)
set(ACTORS ${SRC}/actors)
set(ACTORS ${SRC}/actors)
set(PROJECT_NAME simulator)
# set the project name and version
project(${PROJECT_NAME} VERSION 0.1.2)


file(GLOB SOURCE_FILES
	${SRC}/main.cpp
	)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/build)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})


add_library(point 	        SHARED ${SHAPES}/TPoint.cpp)
add_library(line 			SHARED ${SHAPES}/TLine.cpp)
add_library(circle 			SHARED ${SHAPES}/TCircle.cpp)
add_library(vector 			SHARED ${SHAPES}/TVector.cpp)
add_library(polygon 		SHARED ${SHAPES}/TPolygon.cpp)
add_library(segment 		SHARED ${SHAPES}/Segment.cpp)

add_library(ai 		        SHARED ${ACTORS}/ai.cpp)
add_library(object 			SHARED ${ACTORS}/object.cpp)
add_library(obstacle		SHARED ${ACTORS}/obstacle.cpp)
add_library(player 			SHARED ${ACTORS}/player.cpp)
add_library(vehicle 		SHARED ${ACTORS}/vehicle.cpp)


target_link_libraries(vector point)
target_link_libraries(line point vector)
target_link_libraries(circle point line)
target_link_libraries(segment point line)




set(CMAKE_CXX_FLAGS "-std=c++17 -g")

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} Threads::Threads
                        point line circle vector polygon segment
						Qt5::Widgets
					)

enable_testing()
add_executable(line_to_line ${TEST}/shapes/line_line.cpp)
add_executable(line_to_circle ${TEST}/shapes/line_circle.cpp)
add_executable(segment_to_line ${TEST}/shapes/segment_line.cpp)
add_executable(interface_test ${TEST}/general/ui.cpp)

target_link_libraries(line_to_line point line)
target_link_libraries(line_to_line point line circle)
target_link_libraries(segment_to_line point line circle segment)
target_link_libraries(interface_test Qt5::Widgets Qt5::Core)

# LINE TO LINE TESTS
add_test(NAME "l2l1" COMMAND line_to_line 0 4 4 3 0 0 8 4)
set_property (TEST "l2l1"
              PROPERTY PASS_REGULAR_EXPRESSION "0\\.000000 \\(5\\.33333, 2\\.66667\\)")

add_test(NAME "l2l2" COMMAND line_to_line 0 4 4 3 0 3 4 2)
set_property (TEST "l2l2"
              PROPERTY PASS_REGULAR_EXPRESSION "0\\.970143 \\(inf, 0\\)")

add_test(NAME "l2l3" COMMAND line_to_line 0 4 4 3 0 3 0 5)
set_property (TEST "l2l3"
	PROPERTY PASS_REGULAR_EXPRESSION "0\\.000000 \\(0, 4\\)")

# LINE TO CIRCLE TESTS
add_test(NAME "l2c1" COMMAND line_to_circle 0 4 4 3 4 1 8)
set_property (TEST "l2c1"
	PROPERTY PASS_REGULAR_EXPRESSION "0 \\(-3\\.05882, 4\\.76471\\) \\(12, 1\\)")

add_test(NAME "l2c2" COMMAND line_to_circle 0 3 4 3 4 2 8)
set_property (TEST "l2c2"
	PROPERTY PASS_REGULAR_EXPRESSION "0 \\(-3\\.93725, 3\\) \\(11\\.9373*, 3\\)")


add_test(NAME "l2c3" COMMAND line_to_circle 0 3 3 3 4 2 1)
set_property (TEST "l2c3"
	PROPERTY PASS_REGULAR_EXPRESSION "0 \\(4, 3\\)")


add_test(NAME "l2c4" COMMAND line_to_circle 0 0 5 4 4 2 1)
set_property (TEST "l2c4"
	PROPERTY PASS_REGULAR_EXPRESSION "0 \\(3\\.14194, 2\\.51355\\) \\(3\\.68733, 2\\.94986\\)")

# SEGMENT TO LINE TESTS

add_test(NAME "s2l1" COMMAND segment_to_line 0 0 4 2 2 2 4 1)
set_property (TEST "s2l1"
	PROPERTY PASS_REGULAR_EXPRESSION "0 \\(3, 1\\.5\\) \\+ t\\(-0\\.447214, -0\\.894427\\) \\(3, 1\\.5\\)")

add_test(NAME "uit1" COMMAND interface_test)