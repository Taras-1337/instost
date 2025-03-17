cmake_minimum_required(VERSION 3.21)

set(CMAKE_C_STANDARD 23)
# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(instost
        VERSION      0.6.1
        DESCRIPTION "Insurgency internal toster"
        LANGUAGES   C
)

file(GLOB_RECURSE SOURCES src/*.c)
add_library(${CMAKE_PROJECT_NAME}
            SHARED
            ${SOURCES}
)

target_include_directories(${CMAKE_PROJECT_NAME}
                           PUBLIC
                           "src/third_party"
)

target_compile_options(${CMAKE_PROJECT_NAME}
                       PUBLIC
                       -Wall
                       -Wextra
                       -m32
                       -O2
)

target_link_options(${CMAKE_PROJECT_NAME}
                    PUBLIC
                    -m32
)
