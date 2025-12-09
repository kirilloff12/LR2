cmake_minimum_required(VERSION 3.10)
project(stack C)

# Опция для включения покрытия кода
option(ENABLE_COVERAGE "Enable code coverage reporting" ON)

if(ENABLE_COVERAGE)
    # Устанавливаем флаги для gcov
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage -lgcov")

    message(STATUS "Code coverage enabled")
endif()

add_library(stack stack.c)

add_executable(main main.c)
target_link_libraries(main stack)

add_executable(stack_test test_stack.c)
target_link_libraries(stack_test stack)

add_executable(benchmark benchmark.c)
target_link_libraries(benchmark stack)

#add_executable(benchmark benchmark.c)
#target_link_libraries(benchmark stack)

# Enable testing
enable_testing()
add_test(NAME stack_test COMMAND stack_test)

