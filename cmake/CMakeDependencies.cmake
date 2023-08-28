message(STATUS "Searching for librairy dependencies")

if(NOT DEFINED BUILD_OCL_BACKEND)
set(BUILD_OCL_BACKEND ON)
endif()
if(NOT DEFINED BUILD_CUDA_BACKEND)
set(BUILD_CUDA_BACKEND ON)
endif()

set(CLE_OPENCL false)
set(CLE_CUDA false)

# find GPU Framework (OpenCL, CUDA)
if (BUILD_OCL_BACKEND)
    message(STATUS "Search OpenCL librairy")
    if (DEFINED OpenCL_LIBRARIES AND DEFINED OpenCL_INCLUDE_DIRS)
        set(OpenCL_FOUND true)
    else()
        find_package(OpenCL)
    endif()
    if (OpenCL_FOUND)
        set(CLE_OPENCL true)
        message(STATUS "OpenCL librairy : ${OpenCL_LIBRARIES}")
        message(STATUS "OpenCL includes : ${OpenCL_INCLUDE_DIRS}")
    endif()
endif()

if (BUILD_CUDA_BACKEND)
    message(STATUS "Search CUDAToolkit librairy")
    if (NOT CUDAToolkit_FOUND)
        find_package(CUDAToolkit)
    endif()
    if (CUDAToolkit_FOUND)
        set(CLE_CUDA true)
        message(STATUS "CUDAToolkit librairy : ${CUDAToolkit_LIBRARY_DIR}")
        message(STATUS "CUDAToolkit includes : ${CUDAToolkit_INCLUDE_DIRS}")
    endif()
endif()

if (NOT OpenCL_FOUND AND NOT CUDAToolkit_FOUND)
    # we need at least one of the two
    message(FATAL_ERROR "No GPU framework found (OpenCL, CUDA). Please provide one of these GPU framework in order to compile the librairy.")
endif()

# add the variables to the compile definitions for the source code
add_compile_definitions(
    $<$<BOOL:${CLE_CUDA}>:CLE_CUDA>
    $<$<BOOL:${CLE_OPENCL}>:CLE_OPENCL>
)

if(CLE_OPENCL)
    message(STATUS "\tOpenCL backend is enabled")
else()
    message(STATUS "\tOpenCL backend is disabled")
endif()
if(CLE_CUDA)
    message(STATUS "\tCUDA backend is enabled")
else()
    message(STATUS "\tCUDA backend is disabled")
endif()

