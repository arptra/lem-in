cmake_minimum_required(VERSION 3.14)
project(lem-in C)

set(CMAKE_C_STANDARD 99)

add_executable(lem-in
                input.c
                error_management.c
                graph.c
                lem-in.c
        graph.h
                graph2.c
                ssp_finder.c
                queue.c
                queue.h
                all_disjoint_paths.c
                graph3.c
                paths.c
                path.h
                mergesort.c
                ants.c
                output.c parser.c algorithm.c)

add_subdirectory(libft)


target_link_libraries(lem-in ft)