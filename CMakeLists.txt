# A very minimal config just to get started

cmake_minimum_required(VERSION 3.23)
project(riscv-emulator LANGUAGES CXX ASM)

add_executable(riscv-emulator "./src/main.cpp")
