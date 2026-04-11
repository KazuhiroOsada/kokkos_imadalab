cmake_minimum_required(VERSION 3.16)
project(KokkosGPUSample CXX)

# ---- C++ ----
set(CMAKE_CXX_STANDARD 20)

# ---- Kokkos ----
set(Kokkos_ROOT "$ENV{HOME}/kokkos-install")
find_package(Kokkos REQUIRED)

# ---- Output Directories ----
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})

# ---- Executables ----
add_executable(sample sample.cpp)
target_link_libraries(sample Kokkos::kokkos)
