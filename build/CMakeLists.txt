cmake_minimum_required(VERSION 3.10.0)

# Set project name
set(PROJECT_NAME NetDesign)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)          # Using C++23 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Enforce the standard
set(CMAKE_CXX_EXTENSIONS OFF)       # Disable compiler-specific extensions

cmake_policy(SET CMP0167 NEW)       # Set the policy to suppress the warning

# Project paths
set(INCLUDE_DIR     ${CMAKE_SOURCE_DIR}/../include)
set(SRC_DIR         ${CMAKE_SOURCE_DIR}/../src)
set(MODEL_DIR       ${SRC_DIR}/model)
set(VIEW_DIR        ${SRC_DIR}/view)
set(CONTROLLER_DIR  ${SRC_DIR}/controller)

# Project source files
set(SRCS
    "${CONTROLLER_DIR}/ProjectController.cpp"
    "${CONTROLLER_DIR}/EditController.cpp"
    "${CONTROLLER_DIR}/InfoController.cpp"
    "${CONTROLLER_DIR}/MenuController.cpp"
    "${VIEW_DIR}/MainWindow.cpp"
    "${SRC_DIR}/Main.cpp"
)

# Include directories
include_directories(${INCLUDE_DIR})

# Connect Qt & Boost libraries
find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)
find_package(Boost REQUIRED COMPONENTS system filesystem)

# Create the executable
add_executable(${PROJECT_NAME} ${SRCS})

set(CXXFLAGS
    "-Wall"         # Enable all compiler's warning messages
    "-Wextra"       # Enable additional warning messages not covered by -Wall
    "-Werror"       # Treat all warnings as errors
    "-Wpedantic"    # Enable strict ISO C++ compliance warnings
    "-Wconversion"  # Enable warnings for implicit type conversions
    "-fanalyzer"    # Enable the static analyzer in the compiler
    "-std=c++23"    # Use the C++23 standard
    "-O2"           # Optimize the code for performance (level 2 optimization)
    "-g"            # Generate debug information
)

# Set compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE ${CXXFLAGS})

# Link the Qt & Boost libraries to the executable
target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::Charts)
target_link_libraries(${PROJECT_NAME} Boost::system Boost::filesystem)