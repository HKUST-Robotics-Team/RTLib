#[[

This file is part of RTLib.

Copyright (C) 2017 waicool20 <waicool20@gmail.com>
Copyright (C) 2018 Derppening <david.18.19.21@gmail.com>

RTLib is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RTLib is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with RTLib.  If not, see <http://www.gnu.org/licenses/>.

]]

# Get Build Information
execute_process(COMMAND make --version OUTPUT_VARIABLE MAKE_OUTPUT)
string(REGEX REPLACE "GNU Make ([0-9]\\.[0-9]\\.*[0-9]*).+" "\\1" MAKE_VERSION ${MAKE_OUTPUT})

message("-----------Build Information------------")
message(STATUS "Host    : ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "Make    : ${MAKE_VERSION}")
message(STATUS "CC      : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "CXX     : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Build   : ${CMAKE_BUILD_TYPE}")

# Additional Flags
set(ADDITIONAL_C_FLAGS "-fmessage-length=0 -fno-strict-aliasing -ffunction-sections -fdata-sections -fsigned-char")
set(ADDITIONAL_CXX_FLAGS "-fno-exceptions -fno-rtti")
set(ADDITIONAL_LINKER_FLAGS "-Wl,-Map,${CMAKE_PROJECT_NAME}_${CMAKE_BUILD_TYPE}.map,--cref,--gc-sections")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra ${TARGET_FLAGS} ${ADDITIONAL_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra ${TARGET_FLAGS} ${ADDITIONAL_CXX_FLAGS}")
set(LINKER_FLAGS "${LINKER_FLAGS} -nostartfiles -lc -lnosys --specs=rdimon.specs ${ADDITIONAL_LINKER_FLAGS}")

message("------------Additional Flags------------")
message(STATUS "C   : ${ADDITIONAL_C_FLAGS}")
message(STATUS "CXX : ${ADDITIONAL_CXX_FLAGS}")
message(STATUS "LD  : ${ADDITIONAL_LINKER_FLAGS}")

# Build-dependent flags
set(CMAKE_C_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_C_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-Og")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Og")

# Collect sources and includes
find_file(RTLIB_SRC "src" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/RTLib" "${CMAKE_CURRENT_SOURCE_DIR}")
if (RTLIB_SRC STREQUAL "RTLIB_SRC-NOTFOUND")
    message(FATAL_ERROR "Could not find RTLib sources")
endif ()

file(GLOB_RECURSE RTLIB_SOURCE_FILES "${RTLIB_SRC}/*.c" "${RTLIB_SRC}/*.cpp")
include_directories(${RTLIB_SRC})

# Dump all the flags at this point
if (LOG_VERBOSE)
    string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)

    message("-------------Full Flag List-------------")
    message(STATUS "C   : ${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_${BUILD_TYPE}}")
    message(STATUS "CXX : ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${BUILD_TYPE}}")
    message(STATUS "LD  : ${LINKER_FLAGS}")
endif()
