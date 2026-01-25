cmake_minimum_required(VERSION 3.20)
project(Client VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_definitions(_ITERATOR_DEBUG_LEVEL=0)
set_property(GLOBAL PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

include(FetchContent)

FetchContent_Declare(
    libhat
    GIT_REPOSITORY https://github.com/BasedInc/libhat.git
    GIT_TAG        v0.9.0
)
FetchContent_MakeAvailable(libhat)

FetchContent_Declare(
    minhook
    GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
    GIT_TAG master
)
FetchContent_MakeAvailable(minhook)

FetchContent_Declare(
    EnTT
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG        fe8d7d78c4823e8a66a050bf86f5c6318cf76ce7
)
FetchContent_MakeAvailable(EnTT)

add_library(Client SHARED main.cpp)
add_subdirectory(src)

target_link_libraries(Client PRIVATE minhook libhat::libhat EnTT::EnTT)