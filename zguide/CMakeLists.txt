SET(EXE_SOURCES
    hwclient.cpp
    hwserver.cpp
    tasksink.cpp
    taskvent.cpp
    taskwork.cpp
    wuclient.cpp
    wuserver.cpp
    version.cpp
)

FOREACH(CUR_SOURCE_FILE ${EXE_SOURCES})
    STRING(REPLACE ".cpp" "" EXE_NAME ${CUR_SOURCE_FILE})
    ADD_EXECUTABLE(${EXE_NAME} ${CUR_SOURCE_FILE})
    TARGET_LINK_LIBRARIES(${EXE_NAME} ${ZEROMQ_LIBRARIES})

    INSTALL(TARGETS ${EXE_NAME} RUNTIME DESTINATION bin)
ENDFOREACH()
