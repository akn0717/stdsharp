#
# Project details
#
project(${CMAKE_PROJECT_NAME}Tests LANGUAGES CXX)

verbose_message("Adding tests under ${CMAKE_PROJECT_NAME}...")

#
# Set the sources for the unit tests and add the executable(s)
#
set(
    src
    src/tests.cpp
    src/pattern_match_test.cpp
    src/concurrent_object_test.cpp
    src/algorithm/algorithm_test.cpp
    src/utility/utility_test.cpp
    src/containers/containers_test.cpp
    src/containers/actions_test.cpp
    src/type_traits/value_sequence_test.cpp
    src/type_traits/type_sequence_test.cpp
    src/type_traits/member_test.cpp
    src/tuple/tuple_test.cpp
    src/functional/pipeable_test.cpp
    src/functional/symmetric_operations_test.cpp
    src/filesystem/filesystem_test.cpp
)

config_lib(${PROJECT_NAME}Lib INTERFACE)
config_exe(${PROJECT_NAME} EXE_SRC ${src})

target_compile_options(
    ${PROJECT_NAME}
    PUBLIC $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:-Werror>
           $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)

find_package(Catch2 CONFIG REQUIRED)
include(Catch)
target_link_libraries(${PROJECT_NAME} PRIVATE stdsharp Catch2::Catch2WithMain ${PROJECT_NAME}Lib)

#
# Configure clang-tidy
#
option(ENABLE_CLANG_TIDY "Enable clang-tidy" ON)

if(${ENABLE_CLANG_TIDY})
    message(STATUS "clang-tidy is enabled")
    target_enable_clang_tidy(${PROJECT_NAME})
endif()

catch_discover_tests(${PROJECT_NAME})