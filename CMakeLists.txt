cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
project( DisplayImage )
find_package( OpenCV REQUIRED )
message(STATUS "OpenCV_LIBS = ${OpenCV_LIBS}")
message(STATUS "OpenCV_INCLUDE_DIRS = ${OpenCV_INCLUDE_DIRS}")
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( /home/pi/rpi-rgb-led-matrix/include )
link_directories( /home/pi/rpi-rgb-led-matrix/lib )
add_executable( DisplayImage
        src/display_rpi.cpp
        src/display_desktop.cpp
        main.cpp)
target_link_libraries( DisplayImage pthread;rgbmatrix )
target_link_libraries( DisplayImage ${OpenCV_LIBS} )
