cmake_minimum_required(VERSION 3.8)
project(signal_slot)

set(CMAKE_CXX_STANDARD 14)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

SET( PLATFORM               x11 )
SET( WINDOW_SYSTEM          x11 )
SET( GRAPHICS               glx )
INCLUDE( ${CMAKE_CURRENT_LIST_DIR}/platform/${PLATFORM}/list.cmake )
INCLUDE( ${CMAKE_CURRENT_LIST_DIR}/window-system/${WINDOW_SYSTEM}/list.cmake )
INCLUDE( ${CMAKE_CURRENT_LIST_DIR}/graphics/${GRAPHICS}/list.cmake )

# add window

set(SOURCE_FILES main.cpp
        system/common/signal.h

        ${PLATFORM_SOURCES}

        ${WINDOW_SYSTEM_SOURCES}

        ${GRAPHICS_SOURCES}

        # public
        dali/public-api/application.h
        dali/public-api/signal.h
        dali/public-api/window.h
        )
add_executable(signal_slot ${SOURCE_FILES})
target_link_libraries( signal_slot SDL2 GL X11)