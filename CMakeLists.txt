cmake_minimum_required (VERSION 3.5)
project (SAT_exercise3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

find_package(MiniSat 2.2 REQUIRED)

add_executable(sat_exercise_3
    main.cpp
    solver.cpp
    solver.hpp
)
target_link_libraries(sat_exercise_3 MiniSat::libminisat)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT sat_exercise_3)
