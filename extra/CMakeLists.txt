SET(EXE_SOURCES
    multipartpublisher.cpp
    multipartsubscriber.cpp
    pubsubcontroller.cpp
    pubsubpublisher.cpp
    pubsubqueue.cpp
    pubsubsubscriber.cpp
    sendrecvpublisher.cpp
    sendrecvsubscriber.cpp
)

SET(CXX_FEATURES
    cxx_auto_type
    cxx_defaulted_functions
    cxx_delegating_constructors
    cxx_deleted_functions
    cxx_final
    cxx_noexcept
    cxx_nullptr
    cxx_override
    cxx_rvalue_references
    cxx_static_assert
    cxx_trailing_return_types
    cxx_variadic_templates
)

FOREACH(CUR_SOURCE_FILE ${EXE_SOURCES})
    STRING(REPLACE ".cpp" "" EXE_NAME ${CUR_SOURCE_FILE})
    ADD_EXECUTABLE(${EXE_NAME} ${CUR_SOURCE_FILE})
    TARGET_LINK_LIBRARIES(${EXE_NAME} ${ZEROMQ_LIBRARIES})

    IF (NOT MSVC)
        TARGET_COMPILE_FEATURES(${EXE_NAME} PRIVATE ${CXX_FEATURES})
    ENDIF()

    INSTALL(TARGETS ${EXE_NAME} RUNTIME DESTINATION bin)
ENDFOREACH()
