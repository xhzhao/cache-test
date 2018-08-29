#===============================================================================
# Copyright 2016-2017 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#===============================================================================


#set(APP_NAME "gtest")

# TODO: enable me!
#file(GLOB API_TEST_CASES_SRC api_tests/*.cpp)
file(GLOB PRIM_TEST_CASES_SRC test_*.cpp)
#file(GLOB PRIM_TEST_CASES_SRC
#                            test_cache_line1.c
#                              ) #temporary


foreach(TEST_FILE ${PRIM_TEST_CASES_SRC} ${MKL_PRIM_TEST_CASES_SRC})
    set(CMAKE_C_FLAGS "-O3")
    set(CMAKE_CXX_FLAGS "-std=c++11 -O3")
    #set(CMAKE_C_FLAGS "-O2")
    #set(CMAKE_CXX_FLAGS "-std=c++11 -O2")
    include_directories("/opt/intel/mkl/include/")
    get_filename_component (TEST_FILE_WE ${TEST_FILE} NAME_WE)
    set(CURR_APP_NAME ${TEST_FILE_WE})
    add_executable(${CURR_APP_NAME} ${MAIN_SRC_GTEST} ${TEST_FILE})
    target_link_libraries(${CURR_APP_NAME} mkl_rt)
    #add_test(${CURR_APP_NAME} ${CURR_APP_NAME})
endforeach()

