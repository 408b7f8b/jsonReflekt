cmake_minimum_required(VERSION 2.4)
project(jsonReflekt)

set(CMAKE_C_STANDARD 99)

add_executable(jsonReflekt main.c)

set(JSON-C_LIBRARY_PATH /usr/local/lib CACHE PATH "Pfad zur Bibliothek JSON-C")
set(SCHLL_PATH /home/dbb/Desktop/git/schll)
set(EINFL_PATH /home/dbb/Desktop/git/einfl)

include_directories(${SCHLL_PATH} ${EINFL_PATH})

link_directories(
        ${JSON-C_LIBRARY_PATH}
)


target_link_libraries(jsonReflekt json-c)