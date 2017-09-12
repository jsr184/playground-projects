INCLUDE( ${CMAKE_CURRENT_LIST_DIR}/../common/list.cmake )
SET( WINDOW_SYSTEM_SOURCES ${WINDOW_SYSTEM_SOURCES}
        ${CMAKE_CURRENT_LIST_DIR}/window-factory-sdl2.cpp
        ${CMAKE_CURRENT_LIST_DIR}/window-factory-sdl2.h
        ${CMAKE_CURRENT_LIST_DIR}/window-sdl2.cpp
        ${CMAKE_CURRENT_LIST_DIR}/window-sdl2.h
        )