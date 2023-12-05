project(mpr)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEFINED_IN_CMAKELISTS")
include_directories(${PROJECT_SOURCE_DIR}/include)

# add_subdirectory(${PROJECT_SOURCE_DIR}/external/gflags)

set(gflags_DIR ${PROJECT_SOURCE_DIR}/external/gflags/build)
set(glog_DIR ${PROJECT_SOURCE_DIR}/external/glog/build)
find_package(gflags 2.2.2 REQUIRED)
find_package(glog 0.6.0 REQUIRED)
find_package(OpenMP REQUIRED)

add_compile_options(-Wall -Wextra -pedantic -Werror -Wno-error=maybe-uninitialized -Wno-error=unused-parameter -Wno-error=switch -w -g -O3 -std=c++17 -march=native -pthread -lpthread -lglog)


# include(ExternalProject)

# ExternalProject_Add(
#     mimalloc
#     PREFIX ${CMAKE_BINARY_DIR}/mimalloc
#     GIT_REPOSITORY git@github.com:microsoft/mimalloc.git
#     GIT_TAG master
#     CONFIGURE_COMMAND ""
#     BUILD_COMMAND make
#     INSTALL_COMMAND ""
# )
add_executable(mpr
    ${PROJECT_SOURCE_DIR}/src/trace_list.cpp
    ${PROJECT_SOURCE_DIR}/src/tracereader.cpp
    ${PROJECT_SOURCE_DIR}/src/pattern_list.cpp
    ${PROJECT_SOURCE_DIR}/src/pc_meta.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/macro.cpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    /home/wangguidong/mimalloc/out/release/mimalloc.o
)

# # 链接到 mimalloc 库
# add_dependencies(mpr mimalloc)
# target_link_libraries(mpr PRIVATE ${CMAKE_BINARY_DIR}/mimalloc/src/mimalloc-build/libmimalloc.a
# -static-libgcc -static-libstdc++ -lpthread -lstdc++
# glog::glog
# gflags
# )
include(CheckCXXSourceCompiles)
check_cxx_source_compiles("#include <filesystem>\nint main() {return 0;}" HAS_FILESYSTEM)
if(NOT HAS_FILESYSTEM)
    target_link_libraries(mpr stdc++fs)
endif()

target_link_options(mpr PRIVATE -static-libgcc -static-libstdc++ -lpthread )
target_link_libraries(mpr glog::glog)
target_link_libraries(mpr gflags)
target_link_libraries(mpr stdc++fs)

add_executable(pattern2line
    ${PROJECT_SOURCE_DIR}/src/utils/pattern2line.cpp
    ${PROJECT_SOURCE_DIR}/src/pc_meta.cpp
)
target_link_libraries(pattern2line stdc++fs)
target_link_options(pattern2line PRIVATE -static-libgcc -static-libstdc++)
target_link_libraries(pattern2line glog::glog)

add_executable(perf-parse
    ${PROJECT_SOURCE_DIR}/src/utils/perf-parse.cpp
)
target_link_options(perf-parse PRIVATE -static-libgcc -static-libstdc++)
target_link_libraries(perf-parse gflags)
target_link_libraries(perf-parse glog::glog)

add_executable(analyze-other
    ${PROJECT_SOURCE_DIR}/src/utils/analyze-other.cpp
)
target_link_options(analyze-other PRIVATE -static-libgcc -static-libstdc++)

add_executable(analyze-gem5-prefetch
    ${PROJECT_SOURCE_DIR}/src/utils/analyze-gem5-prefetch.cpp
    ${PROJECT_SOURCE_DIR}/src/pc_meta.cpp
)
target_link_libraries(analyze-gem5-prefetch stdc++fs)
target_link_options(analyze-gem5-prefetch PRIVATE -static-libgcc -static-libstdc++)
# target_link_libraries(analyze-gem5-prefetch stdc++fs)
target_link_libraries(analyze-gem5-prefetch glog::glog)

add_executable(analyze-gem5-missinfo
    ${PROJECT_SOURCE_DIR}/src/utils/analyze-gem5-missinfo.cpp
    ${PROJECT_SOURCE_DIR}/src/pc_meta.cpp
)
target_link_options(analyze-gem5-missinfo PRIVATE -static-libgcc -static-libstdc++)
target_link_libraries(analyze-gem5-missinfo glog::glog)
target_link_libraries(analyze-gem5-missinfo gflags)
target_link_libraries(analyze-gem5-missinfo stdc++fs)

add_executable(merge-result
    ${PROJECT_SOURCE_DIR}/src/utils/merge-result.cpp
    ${PROJECT_SOURCE_DIR}/src/pc_meta.cpp
    ${PROJECT_SOURCE_DIR}/src/trace_list.cpp
    ${PROJECT_SOURCE_DIR}/src/pattern_list.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/macro.cpp
    ${PROJECT_SOURCE_DIR}/src/tracereader.cpp
)
target_link_libraries(merge-result stdc++fs)
target_link_options(merge-result PRIVATE -static-libgcc -static-libstdc++)
target_link_libraries(merge-result glog::glog)
target_link_libraries(merge-result gflags)
target_link_libraries(merge-result OpenMP::OpenMP_CXX)
# target_link_libraries(merge-result stdc++fs)


add_executable(parse-merged-result
    ${PROJECT_SOURCE_DIR}/src/utils/parse-merged-result.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/macro.cpp
)
target_link_libraries(parse-merged-result stdc++fs)
target_link_options(parse-merged-result PRIVATE -static-libgcc -static-libstdc++)
target_link_libraries(parse-merged-result glog::glog)
target_link_libraries(parse-merged-result gflags)

add_executable(choose_ckp
    ${PROJECT_SOURCE_DIR}/src/utils/choose_ckp.cpp
)
target_link_libraries(choose_ckp stdc++fs)
target_link_options(choose_ckp PRIVATE -static-libgcc -static-libstdc++)
target_link_libraries(choose_ckp glog::glog)
target_link_libraries(choose_ckp gflags)
target_link_libraries(choose_ckp OpenMP::OpenMP_CXX)

