SET(CMAKE_MIN_REQ_VERSION 2.4)
cmake_minimum_required(VERSION ${CMAKE_MIN_REQ_VERSION})

INCLUDE("variables.cmake")
INCLUDE("CMakeSettings.txt")

FBX_PROJECT(GenNullFbx .)
SET(FBX_TARGET_SOURCE
    src/GenNullFbx.h
    src/GenNullFbx.cxx
    src/Common.h
    src/Common.cxx
)
ADD_LIBRARY(
   ${FBX_TARGET_NAME}
   SHARED
   ${FBX_TARGET_SOURCE}
)
SET_SAMPLES_GLOBAL_FLAGS()

TARGET_COMPILE_FEATURES(${FBX_TARGET_NAME} PUBLIC cxx_std_17)
INSTALL(TARGETS ${FBX_TARGET_NAME} DESTINATION ${FBX_INSTALL_PATH})

IF(WIN32)
    FBX_PROJECT(SaveFbxTest .)
    ADD_EXECUTABLE(
        SaveFbxTest
        test/SaveFbxTest.cxx
    )
    TARGET_LINK_LIBRARIES(SaveFbxTest GenNullFbx)
    ADD_TEST(
        NAME SaveFbxTest
        COMMAND $<TARGET_FILE:SaveFbxTest>
    )
ENDIF()
