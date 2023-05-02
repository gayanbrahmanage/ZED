cmake_minimum_required(VERSION 2.8)
project(ZED)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)

if(COMPILER_SUPPORTS_CXX17)
   
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread ")
elseif(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -pthread ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread ")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

set(CMAKE_CXX_FLAGS "${C_CXX_FLAGS_DEFAULT} ${CMAKE_CXX_FLAGS} --std=c++11")

include_directories( ${PROJECT_SOURCE_DIR}/include)

#configuration for openCV
find_package( OpenCV REQUIRED )


			
add_executable(main
		src/main.cpp)

target_link_libraries(main
			${OpenCV_LIBS})

