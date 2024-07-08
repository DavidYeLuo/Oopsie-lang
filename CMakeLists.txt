cmake_minimum_required(VERSION 3.21)

project(
  "Oopsie Lang"
  VERSION 0.1
  DESCRIPTION "A custom language for learning purposes.")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(Lexer)
add_subdirectory(Test)
