cmake_minimum_required(VERSION 3.10.0)

# setting project name
set(PROJECT_NAME NetDesign)
project(${PROJECT_NAME})

set(CMAKE_C_STANDARD 23)          # using C23 standard
set(CMAKE_C_STANDARD_REQUIRED ON) # enforce the standard
set(CMAKE_C_EXTENSIONS OFF)       # disable compiler-specific extensions

# project paths
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../include)
set(SRC_DIR     ${CMAKE_SOURCE_DIR}/../src)
set(MENU_DIR    ${SRC_DIR}/menu)

# project source files
set(SRCS
    "${MENU_DIR}/estimate.c"
    "${MENU_DIR}/project.c"
    "${MENU_DIR}/edit.c"
    "${MENU_DIR}/info.c"
    "${SRC_DIR}/load_matrix.c"
    "${SRC_DIR}/parser.c"
    "${SRC_DIR}/utils.c"
    "${SRC_DIR}/main.c"
    "${SRC_DIR}/app.c"
)

# finding the GTK package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# setting include directories
include_directories(${INCLUDE_DIR} ${GTK3_INCLUDE_DIRS})

# adding the executable
add_executable(${PROJECT_NAME} ${SRCS})

# setting compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE
    "-Wall"         # enable all compiler's warning messages
    "-Wextra"       # enable additional warning messages not covered by -Wall
    "-Werror"       # treat all warnings as errors
    "-Wpedantic"    # enable strict ISO C compliance warnings
    "-Wconversion"  # enable warnings for implicit type conversions
    "-fanalyzer"    # enable the static analyzer in the compiler
    "-std=c23"      # use the C23 standard
    "-O2"           # optimize the code for performance (level 2 optimization)
    "-g"            # generate debug information
)

# linking the GTK libraries
target_link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES})