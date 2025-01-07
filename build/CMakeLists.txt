cmake_minimum_required(VERSION 3.10.0)

# setting project name
set(PROJECT_NAME NetDesign)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)          # using C++23 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON) # enforcing the standard
set(CMAKE_CXX_EXTENSIONS OFF)       # disabling compiler-specific extensions

cmake_policy(SET CMP0167 NEW)       # setting the policy to suppress the warning

# setting project paths
set(INCLUDE_DIR     ${CMAKE_SOURCE_DIR}/../include)
set(SRC_DIR         ${CMAKE_SOURCE_DIR}/../src)
set(MENU_DIR        ${SRC_DIR}/menu)
set(TABS_DIR        ${SRC_DIR}/tabs)

# setting project source files
set(SRCS
    "${TABS_DIR}/RouterSettings.cpp"
    "${TABS_DIR}/NodeSettings.cpp"
    "${TABS_DIR}/SettingsTab.cpp"
    "${TABS_DIR}/GraphTab.cpp"
    "${MENU_DIR}/Project.cpp"
    "${MENU_DIR}/Edit.cpp"
    "${MENU_DIR}/Info.cpp"
    "${SRC_DIR}/ProjectParser.cpp"
    "${SRC_DIR}/MainWindow.cpp"
    "${SRC_DIR}/Utils.cpp"
    "${SRC_DIR}/Main.cpp"
)

# setting include directories
include_directories(${INCLUDE_DIR})

# connecting Qt & Boost libraries
find_package(Qt6 REQUIRED COMPONENTS Widgets Charts Core Xml)
find_package(Boost REQUIRED COMPONENTS system filesystem)

# creating the executable
add_executable(${PROJECT_NAME} ${SRCS})

set(CXXFLAGS
    "-Wall"         # enable all compiler's warning messages
    "-Wextra"       # enable additional warning messages not covered by -Wall
    "-Werror"       # treat all warnings as errors
    "-Wpedantic"    # enable strict ISO C++ compliance warnings
    "-Wconversion"  # enable warnings for implicit type conversions
    "-std=c++23"    # use the C++23 standard
    "-O2"           # optimize the code for performance (level 2 optimization)
    "-g"            # generate debug information
)

# setting compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE ${CXXFLAGS})

# linking the Qt & Boost libraries to the executable
target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::Charts Qt6::Core Qt6::Xml)
target_link_libraries(${PROJECT_NAME} Boost::system Boost::filesystem)