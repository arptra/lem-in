cmake_minimum_required(VERSION 3.14)

project(libut)

add_library(ut STATIC dllutils.h dllutils.c dllutils2.c)