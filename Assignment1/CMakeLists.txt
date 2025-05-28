cmake_minimum_required(VERSION 3.25)
project(DogShelterSim C)

set(CMAKE_C_STANDARD 99)

add_executable(DogShelterSim dogShelterSimulation.c
        Dog.h
        Dog.c
        list.c
        list.h
        queue.h
        queue.c)