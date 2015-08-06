# Try to find CpperoMQ include path.
# Once done this will define:
#
# CPPEROMQ_FOUND
# CPPEROMQ_INCLUDE_DIR

FIND_PATH(CPPEROMQ_INCLUDE_DIR
              CpperoMQ/All.hpp
          PATH_SUFFIXES
              include
          PATHS
              ${CPPEROMQDIR}
              $ENV{CPPEROMQDIR}
              ~/Library/Frameworks
              /Library/Frameworks
              /usr/local/
              /usr/
              /sw          # Fink
              /opt/local/  # DarwinPorts
              /opt/csw/    # Blastwave
              /opt/
)

SET(CPPEROMQ_FOUND TRUE)

IF(NOT CPPEROMQ_INCLUDE_DIR)
    SET(CPPEROMQ_FOUND FALSE)
    SET(FIND_CPPEROMQ_MISSING "${FIND_CPPEROMQ_MISSING} CPPEROMQ_INCLUDE_DIR")
ENDIF()

IF(NOT CPPEROMQ_FOUND)
    SET(FIND_CPPEROMQ_ERROR "Could NOT find CpperoMQ (missing: ${FIND_CPPEROMQ_MISSING})")
    IF(CPPEROMQ_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR ${FIND_CPPEROMQ_ERROR})
    ELSEIF(NOT CPPEROMQ_FIND_QUIETLY)
        MESSAGE("${FIND_CPPEROMQ_ERROR}")
    ENDIF()
ENDIF()

IF(CPPEROMQ_FOUND)
    MESSAGE("Found CpperoMQ: ${CPPEROMQ_INCLUDE_DIR}")
ENDIF()
