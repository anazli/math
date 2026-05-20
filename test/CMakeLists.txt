include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

set(TEST_EXECUTABLE math-tests)

add_executable(${TEST_EXECUTABLE} mat2_test.cpp
                                  mat3_test.cpp
                                  mat4_test.cpp
                                  point3_test.cpp
                                  vec2_test.cpp
                                  vec3_test.cpp
                                  vec4_test.cpp)
target_link_libraries(${TEST_EXECUTABLE} PRIVATE math gtest_main gtest gmock)
gtest_discover_tests(${TEST_EXECUTABLE})