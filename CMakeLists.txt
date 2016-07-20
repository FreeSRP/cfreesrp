cmake_minimum_required(VERSION 2.8.4)
project(cfreesrp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# cfreesrp Library
find_package(libusb-1.0 REQUIRED)

include_directories(${LIBUSB_1_INCLUDE_DIR})

file(GLOB_RECURSE CFREESRP_SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/*.hpp
    ${PROJECT_SOURCE_DIR}/src/*.h
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.c
)

file(GLOB_RECURSE CFREESRP_INCLUDE_FILES
    ${PROJECT_SOURCE_DIR}/include/*.hpp
    ${PROJECT_SOURCE_DIR}/include/*.h
)

add_library(
    cfreesrp
    SHARED
    ${CFREESRP_SRC_FILES}
    ${CFREESRP_INCLUDE_FILES}
)

include_directories(${PROJECT_SOURCE_DIR}/include)

target_link_libraries(cfreesrp freesrp)

# Test app
set(EXAMPLE_TEST_SOURCE_FILES ${PROJECT_SOURCE_DIR}/examples/test/test.c)
add_executable(cfreesrp-test ${EXAMPLE_TEST_SOURCE_FILES})
target_link_libraries(cfreesrp-test cfreesrp)

# Install library
install(TARGETS cfreesrp LIBRARY DESTINATION lib)
install(FILES ${CFREESRP_INCLUDE_FILES} DESTINATION include)
