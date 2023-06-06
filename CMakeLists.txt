cmake_minimum_required(VERSION 3.4)
project(pysparse)

set(CMAKE_CXX_STANDARD 17)

set(PYTHON_MODULE_NAME pysparse)

file(GLOB SOURCES
        "source/*.hpp"
        "source/*.tcc"
        )

file(GLOB PY_SOURCES
        "python_objects/*.hpp"
        )

add_subdirectory(pybind11)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

#add_executable(${PROJECT_NAME} main.cc
#        ${SOURCES} ${PY_SOURCES}
#        )
#target_link_libraries(${PROJECT_NAME} PRIVATE ${PYBIND11_LIBRARIES})
#target_include_directories(${PROJECT_NAME} PRIVATE "./pybind11/include/")
#target_link_libraries(${PROJECT_NAME} PRIVATE ${PYTHON_LIBRARIES})


pybind11_add_module(${PYTHON_MODULE_NAME} pybind.cc ${SOURCES} ${PY_SOURCES})
