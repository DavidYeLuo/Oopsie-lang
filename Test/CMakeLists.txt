project(Tests)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# TESTS
add_executable(Tests)
target_sources(Tests PRIVATE ${CMAKE_CURRENT_LIST_DIR}/LexerTests.cpp)
target_sources(Tests PRIVATE ${CMAKE_CURRENT_LIST_DIR}/ParserTests.cpp)
target_sources(Tests PRIVATE ${CMAKE_CURRENT_LIST_DIR}/AstPrinterTests.cpp)
target_sources(Tests PRIVATE ${CMAKE_CURRENT_LIST_DIR}/AstEvaluatorTests.cpp)

include(GoogleTest)
gtest_discover_tests(Tests)
