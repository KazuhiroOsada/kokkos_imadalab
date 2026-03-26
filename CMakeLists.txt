cmake_minimum_required(VERSION 3.16)
project(KokkosGPUSample CXX)

find_package(Kokkos REQUIRED)

add_executable(sample sample.cpp)
target_link_libraries(sample Kokkos::kokkos)
set_target_properties(sample PROPERTIES CXX_STANDARD 17)
