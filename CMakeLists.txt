cmake_minimum_required(VERSION 3.20)
project(Client VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_definitions(_ITERATOR_DEBUG_LEVEL=0)
set_property(GLOBAL PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

include(FetchContent)

# MinHook
FetchContent_Declare(
    minhook
    GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
    GIT_TAG master
)
FetchContent_MakeAvailable(minhook)

#EnTT
FetchContent_Declare(
    EnTT
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG f931687ff04d435871ac9664bb299f71f2a8fafc
)
FetchContent_MakeAvailable(EnTT)

#libhat
FetchContent_Declare(
    libhat
    GIT_REPOSITORY https://github.com/BasedInc/libhat
    GIT_TAG 37ee990ef49e07571e9a948f78cd597c84a639d9
)
FetchContent_MakeAvailable(libhat)

add_library(Client SHARED)                                      # Set as DLL
target_sources(Client PRIVATE main.cpp)                         # DLL entry point

target_link_libraries(Client PRIVATE minhook EnTT::EnTT libhat) # Target link libraries; MinHook, EnTT, libhat

# External sub folders
add_subdirectory(Client)
add_subdirectory(Utils)
add_subdirectory(Mem)
add_subdirectory(SDK)