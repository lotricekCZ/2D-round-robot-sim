cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(SHAPES ${SRC}/shapes)
set(ACTORS ${SRC}/actors)
set(INTERFACE ${SRC}/user_interface)
set(RENDERABLE ${SRC}/renderable)
set(PROJECT_NAME simulator)
# set the project name and version
project(${PROJECT_NAME} VERSION 0.1.2)


file(GLOB SOURCE_FILES
	${SRC}/main.cpp
	)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(Doxygen
			 REQUIRED dot
			 OPTIONAL_COMPONENTS mscgen dia)

find_package(Qt5 COMPONENTS 
				LinguistTools           RemoteObjects
				Help                    QuickWidgets
				Location                RepParser
				Multimedia              Scxml
				MultimediaWidgets       Network                 
				OpenGL                  Svg
				OpenGLExtensions        Test
				Positioning             TextToSpeech
				PositioningQuick        UiPlugin
				PrintSupport            UiTools
				Qml                     WebChannel
				Quick                   WebSockets
				Concurrent              QuickCompiler           
				WebView 				Core
				QuickControls2          Widgets
				Gamepad                 QuickTemplates2
				Xml						Gui             
				QuickTest               XmlPatterns
				REQUIRED)
include_directories(${Qt5UiTools_INCLUDE_DIRS})


# Qt5::Variant
# Qt5::Action
# Qt5::Application
# Qt5::ComboBox
# Qt5::CommandLinkButton
# Qt5::FormLayout
# Qt5::GridLayout
# Qt5::GroupBox
# Qt5::HBoxLayout
# Qt5::HeaderView
# Qt5::Label
# Qt5::LineEdit
# Qt5::MainWindow
# Qt5::Menu
# Qt5::MenuBar
# Qt5::OpenGLWidget
# Qt5::StatusBar
# Qt5::TabWidget
# Qt5::TableWidget
# Qt5::ToolButton
# Qt5::VBoxLayout
# Qt5::Widget

set(DOXYGEN_GENERATE_HTML NO)
set(DOXYGEN_GENERATE_MAN YES)

doxygen_add_docs(
    doxygen
    ${PROJECT_SOURCE_DIR}
    COMMENT "Generate man pages"
)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/build)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})


add_library(point 	        SHARED ${SHAPES}/TPoint.cpp)
add_library(line 			SHARED ${SHAPES}/TLine.cpp)
add_library(circle 			SHARED ${SHAPES}/TCircle.cpp)
add_library(vector 			SHARED ${SHAPES}/TVector.cpp)
add_library(polygon 		SHARED ${SHAPES}/TPolygon.cpp)
add_library(segment 		SHARED ${SHAPES}/Segment.cpp)

add_library(ai 		        SHARED ${ACTORS}/ai.cpp)
add_library(obstacle		SHARED ${ACTORS}/obstacle.cpp)
add_library(player 			SHARED ${ACTORS}/player.cpp)
add_library(vehicle 		SHARED ${ACTORS}/vehicle.cpp)

add_library(interface 		SHARED ${INTERFACE}/interface.cpp)
add_library(viewport		SHARED ${INTERFACE}/gl_viewport.cpp)
add_library(serializer		SHARED ${INTERFACE}/serializer.cpp)

add_library(renderable		SHARED ${RENDERABLE}/renderable.cpp)
add_library(renderer		SHARED ${RENDERABLE}/renderer.cpp)

target_link_libraries(vector point)
target_link_libraries(line point vector)
target_link_libraries(circle point line)
target_link_libraries(segment point line)
target_link_libraries(renderable circle point line vector segment)
target_link_libraries(vehicle Qt5::OpenGL renderable circle point line)
target_link_libraries(obstacle Qt5::OpenGL renderable circle point segment line)
target_link_libraries(viewport Qt5::Widgets Qt5::Gui Qt5::OpenGL vehicle obstacle renderable)
target_link_libraries(renderer vehicle obstacle renderable)
target_link_libraries(serializer Qt5::Widgets Qt5::Core vehicle player renderer obstacle)

set_target_properties(interface PROPERTIES AUTOMOC TRUE)
target_link_libraries(interface serializer Qt5::Widgets Qt5::Core Qt5::UiTools renderer viewport player vehicle ai)





set(CMAKE_CXX_FLAGS "-std=c++17 -g")

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} Threads::Threads
                        point line circle vector polygon segment
						Qt5::Widgets interface viewport
					)

enable_testing()
add_executable(line_to_line 		${TEST}/shapes/line_line.cpp)
add_executable(line_to_circle 		${TEST}/shapes/line_circle.cpp)
add_executable(segment_to_line 		${TEST}/shapes/segment_line.cpp)
add_executable(segment_to_segment 	${TEST}/shapes/segment_segment.cpp)
add_executable(segment_to_point 	${TEST}/shapes/segment_point.cpp)
add_executable(interface_test 		${TEST}/general/ui.cpp)
add_executable(interface_test_final	${TEST}/general/final_ui.cpp)
add_executable(jsontest				${TEST}/general/jsontest.cpp)

target_link_libraries(line_to_line point line)
target_link_libraries(line_to_line point line circle)
target_link_libraries(segment_to_line point line circle segment)
target_link_libraries(segment_to_segment point line circle segment)
target_link_libraries(segment_to_point point line circle segment)
target_link_libraries(interface_test Qt5::Widgets Qt5::Core)
target_link_libraries(interface_test_final interface viewport)
target_link_libraries(jsontest serializer)

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

add_test(NAME "s2l2" COMMAND segment_to_line -6 0 0 6 6 4 1 0 0.25)
set_property (TEST "s2l2"
	PROPERTY PASS_REGULAR_EXPRESSION "4\\.94975")


add_test(NAME "s2l3" COMMAND segment_to_line -6 0 0 6 6 4 1 0.5 0.25)
set_property (TEST "s2l3"
	PROPERTY PASS_REGULAR_EXPRESSION "4\\.65685")

add_test(NAME "s2l4" COMMAND segment_to_line -6 0 0 6 6 4 1 0.360 0.25)
set_property (TEST "s2l4"
	PROPERTY PASS_REGULAR_EXPRESSION "4\\.66129")

# SEGMENT TO POINT TESTS

add_test(NAME "s2p1" COMMAND segment_to_point 0 3 3 2 2 0.25 0.375)
set_property (TEST "s2p1"
	PROPERTY PASS_REGULAR_EXPRESSION "1\\.63899")

add_test(NAME "s2p2" COMMAND segment_to_point 0 3 -3 3 -2 6)
set_property (TEST "s2p2"
	PROPERTY PASS_REGULAR_EXPRESSION "2\\.84605")

add_test(NAME "s2p3" COMMAND segment_to_point 0 3 -3 -2 -2 1)
set_property (TEST "s2p3"
	PROPERTY PASS_REGULAR_EXPRESSION "2\\.82843")

# SEGMENT TO SEGMENT TESTS

add_test(NAME "s2s1" COMMAND segment_to_segment 0 4 2 6 3 2 2.5 5)
set_property (TEST "s2s1"
	PROPERTY PASS_REGULAR_EXPRESSION "1\\.06066 \\(2\\.75, 3\\.5\\) \\+ t\\(0\\.986394, 0\\.164399\\)")

add_test(NAME "s2s2" COMMAND segment_to_segment 0 4 1 5.5 3 2 1 0 0.375)
set_property (TEST "s2s2"
	PROPERTY PASS_REGULAR_EXPRESSION "2\\.62497 \\(0\\.5, 4\\.75\\) \\+ t\\(0\\.83205, -0\\.5547\\)")

add_test(NAME "s2s3" COMMAND segment_to_segment 3 2 5 2 1 3 -0.25 0.375 0 0.375)
set_property (TEST "s2s3"
	PROPERTY PASS_REGULAR_EXPRESSION "4\\.65685")


# add_test(NAME "uit1" COMMAND interface_test)