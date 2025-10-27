# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

#set(RMAKER_PATH $ENV{IDF_PATH}/esp-rainmaker)
set(RMAKER_PATH $ENV{HOME}/trabajo/antiguo/esp-rainmaker)

message(STATUS "RMAKER_PATH está definido: ${RMAKER_PATH}")


# Add RainMaker components and other common application components
set(EXTRA_COMPONENT_DIRS ${RMAKER_PATH}/components ${RMAKER_PATH}/examples/common)

set(PROJECT_VER "1.3")
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(thermostat_rainmaker)
