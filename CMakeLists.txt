cmake_minimum_required(VERSION 3.20)
project (ChanlunX LANGUAGES CXX)
set (ChanlunX_VERSION_MAJOR 1)
set (ChanlunX_VERSION_MINOR 0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================================
# 1. 核心算法静态库：chanlunx_core (插件自包含 /MT)
# ============================================================
set(CORE_SRCS
    Bi.cpp
    Duan.cpp
    ZhongShu.cpp
    KxianChuLi.cpp
    BiChuLi.cpp
)
add_library(chanlunx_core STATIC ${CORE_SRCS})
target_include_directories(chanlunx_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ============================================================
# 2. 插件 DLL：ChanlunX (依赖 chanlunx_core，/MT 静态 CRT)
# ============================================================
set(DLL_SRCS Main.cpp)
add_library(ChanlunX SHARED ${DLL_SRCS})
target_link_libraries(ChanlunX PRIVATE chanlunx_core)

# ============================================================
# 3. GoogleTest 测试框架 (FetchContent，无外部依赖)
# ============================================================
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()
# chanlunx_test 不链接 chanlunx_core，而是直接编译算法源文件
# 这样测试用 /MD + GoogleTest /MD，插件用 /MT，两条链路完全独立
add_executable(chanlunx_test tests/chanlunx_test.cpp ${CORE_SRCS})
target_link_libraries(chanlunx_test PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(chanlunx_test)

# ============================================================
# MSVC: CRT 运行时选择
# - chanlunx_core / ChanlunX: /MT (插件自包含，不依赖宿主 CRT)
# - chanlunx_test: /MD (与 GoogleTest 动态 CRT 保持一致)
# ============================================================
if (MSVC)
    foreach(lib chanlunx_core ChanlunX)
        target_compile_options(${lib} PRIVATE /MT /utf-8)
    endforeach()
    target_compile_options(chanlunx_test PRIVATE /MD /utf-8)
endif()
