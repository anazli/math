cmake_minimum_required(VERSION 3.16)
project(math LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(math INTERFACE)

target_include_directories(math INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Make headers available when using FetchContent
target_sources(math INTERFACE
  FILE_SET headers
  TYPE HEADERS
  FILES
    src/mat2.h
    src/mat3.h
    src/mat4.h
    src/math.h
    src/normal3.h
    src/orthonormal.h
    src/point3.h
    src/ray.h
    src/types.h
    src/vec2.h
    src/vec3.h
    src/vec4.h
)

option(ENABLE_TESTING "Enable tests" ON)
if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()

# Export target for FetchContent
install(TARGETS math
  EXPORT mathTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  FILE_SET headers DESTINATION include
)

install(EXPORT mathTargets
  FILE mathTargets.cmake
  NAMESPACE math::
  DESTINATION lib/cmake/math
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/mathConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/mathConfig.cmake"
  INSTALL_DESTINATION lib/cmake/math
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/mathConfig.cmake"
  DESTINATION lib/cmake/math
)
