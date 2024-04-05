cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)	
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)	
set(SHAPES ${SRC}/shapes)	
set(PROJECT_NAME simulator)
# set the project name and version
project(${PROJECT_NAME} VERSION 0.1.2)


file(GLOB SOURCE_FILES
	${SRC}/main.cpp
	)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/build)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

							
add_library(point 	        SHARED ${SHAPES}/TPoint.cpp)
add_library(line 			SHARED ${SHAPES}/TLine.cpp)
add_library(circle 			SHARED ${SHAPES}/TCircle.cpp)
add_library(vector 			SHARED ${SHAPES}/TVector.cpp)
add_library(polygon 		SHARED ${SHAPES}/TPolygon.cpp)
add_library(segment 		SHARED ${SHAPES}/Segment.cpp)


target_link_libraries(vector point)
target_link_libraries(line point vector)
target_link_libraries(circle point line)
target_link_libraries(segment point line)




set(CMAKE_CXX_FLAGS "-std=c++17 -g")

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} Threads::Threads 
                        point line circle vector polygon segment
					)