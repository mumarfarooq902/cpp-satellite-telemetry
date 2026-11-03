cmake_minimum_required(VERSION 3.16)

project(SatelliteTelemetry VERSION 1.0 LANGUAGES CXX)

# Use modern C++ (C++17) as required.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Threads (std::thread) support.
find_package(Threads REQUIRED)

add_executable(telemetry
    src/main.cpp
    src/TelemetryPacket.cpp
    src/TelemetryGenerator.cpp
    src/TelemetryProcessor.cpp
)

target_include_directories(telemetry PRIVATE include)
target_link_libraries(telemetry PRIVATE Threads::Threads)

# Enable common warnings.
if(MSVC)
    target_compile_options(telemetry PRIVATE /W4)
else()
    target_compile_options(telemetry PRIVATE -Wall -Wextra -Wpedantic)
endif()
