cmake_minimum_required(VERSION 3.10.0)

# set project name
set(PROJECT_NAME NetDesign)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)          # use C++23 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON) # enforce the standard
set(CMAKE_CXX_EXTENSIONS OFF)       # disable compiler-specific extensions

cmake_policy(SET CMP0167 NEW)       # set the policy to suppress the warning

# set project paths
set(INCLUDE_DIR     ${CMAKE_SOURCE_DIR}/../include)
set(SRC_DIR         ${CMAKE_SOURCE_DIR}/../src)
set(MODEL_DIR       ${SRC_DIR}/model)
set(VIEW_DIR        ${SRC_DIR}/view)
set(CONTROLLER_DIR  ${SRC_DIR}/controller)
set(UTILS_DIR       ${SRC_DIR}/utils)

# set project source files
set(SRCS
    "${CONTROLLER_DIR}/ProjectController.cpp"
    "${CONTROLLER_DIR}/RouterController.cpp"
    "${CONTROLLER_DIR}/NodeController.cpp"
    "${CONTROLLER_DIR}/MenuController.cpp"
    "${CONTROLLER_DIR}/InfoController.cpp"
    "${CONTROLLER_DIR}/TabController.cpp"
    "${VIEW_DIR}/SettingsView.cpp"
    "${VIEW_DIR}/RouterView.cpp"
    "${VIEW_DIR}/MenuView.cpp"
    "${VIEW_DIR}/NodeView.cpp"
    "${VIEW_DIR}/TabView.cpp"
    "${VIEW_DIR}/MainWindow.cpp"
    "${UTILS_DIR}/Utils.cpp"
    "${SRC_DIR}/Main.cpp"
)

# set include directories
include_directories(${INCLUDE_DIR})

# connect Qt & Boost libraries
find_package(Qt6 REQUIRED COMPONENTS Widgets Charts Core Xml)
find_package(Boost REQUIRED COMPONENTS system filesystem)

# create the executable
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

# set compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE ${CXXFLAGS})

# link the Qt & Boost libraries to the executable
target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::Charts Qt6::Core Qt6::Xml)
target_link_libraries(${PROJECT_NAME} Boost::system Boost::filesystem)