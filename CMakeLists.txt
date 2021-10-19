cmake_minimum_required(VERSION 3.16.3)
project(cmake_test)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)

include_directories(include /home/stuart/cmake-test/rootfs/opt/vc/src/hello_pi/hello_fft /home/stuart/cmake-test/rootfs/usr/include)

file(GLOB SOURCES 
  "src/*.cpp"
  "/home/stuart/cmake-test/rootfs/opt/vc/src/hello_pi/hello_fft/*.c"
)
add_executable(cmake_test ${SOURCES})

find_library(PTHREAD pthread PATH $ENV{HOME}/cmake-test/rootfs/ PATH_SUFFIXES .a)
find_library(ALSA asound $ENV{HOME}/cmake-test/rootfs/)
find_library(DL dl PATH $ENV{HOME}/cmake-test/rootfs/ PATH_SUFFIXES .a)
find_library(LM m PATH $ENV{HOME}/cmake-test/rootfs/)
target_link_libraries(cmake_test PUBLIC ${PTHREAD} ${DL} ${LM})
target_include_directories(cmake_test PUBLIC /home/stuart/cmake-test/rootfs/opt/vc/src/hello_pi/hello_fft)
# target_compile_options(cmake_test PUBLIC -mfloat-abi=hard)