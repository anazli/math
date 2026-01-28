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

file(GLOB TEST_SOURCES "*.cpp")
add_executable(${TEST_EXECUTABLE} ${TEST_SOURCES})
target_link_libraries(${TEST_EXECUTABLE} PRIVATE math gtest_main gtest gmock)
gtest_discover_tests(${TEST_EXECUTABLE})