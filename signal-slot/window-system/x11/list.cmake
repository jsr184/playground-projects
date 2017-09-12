INCLUDE( ${CMAKE_CURRENT_LIST_DIR}/../common/list.cmake )

SET( WINDOW_SYSTEM_SOURCES ${WINDOW_SYSTEM_SOURCES}
        ${CMAKE_CURRENT_LIST_DIR}/window-factory-x11.cpp
        ${CMAKE_CURRENT_LIST_DIR}/window-factory-x11.h
        ${CMAKE_CURRENT_LIST_DIR}/window-x11.cpp
        ${CMAKE_CURRENT_LIST_DIR}/window-x11.h
        )