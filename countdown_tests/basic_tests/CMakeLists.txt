include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runBasicCountdownTests
        basic_chack.cpp)
target_link_libraries(runBasicCountdownTests gtest gtest_main)
target_link_libraries(runBasicCountdownTests countdown)
