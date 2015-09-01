# Try to find Sodium library and include path.
# Once done this will define:
#
# SODIUM_FOUND
# SODIUM_INCLUDE_DIR
# SODIUM_LIBRARIES

FIND_PATH(SODIUM_INCLUDE_DIR
              sodium.h
          PATH_SUFFIXES
              include
          PATHS
              ${SODIUMDIR}
              ${SODIUMDIR}/src/libsodium
              $ENV{SODIUMDIR}
              $ENV{SODIUMDIR}/src/libsodium
              ~/Library/Frameworks
              /Library/Frameworks
              /usr/local/
              /usr/
              /sw          # Fink
              /opt/local/  # DarwinPorts
              /opt/csw/    # Blastwave
              /opt/
)

SET(SODIUM_FOUND TRUE)
SET(FIND_SODIUM_LIB_PATHS
        ${SODIUMDIR}
        $ENV{SODIUMDIR}
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw
        /opt/local
        /opt/csw
        /opt
)

FIND_LIBRARY(SODIUM_LIBRARY_DEBUG
             NAMES
                 sodium
                 libsodium
             PATH_SUFFIXES
                 lib64
                 lib
             PATHS
                 ${FIND_SODIUM_LIB_PATHS}
                 ${SODIUMDIR}/bin/Win32/Debug/v120/dynamic
                 $ENV{SODIUMDIR}/bin/Win32/Debug/v120/dynamic
)

FIND_LIBRARY(SODIUM_LIBRARY_RELEASE
             NAMES
                 sodium
                 libsodium
             PATH_SUFFIXES
                 lib64
                 lib
             PATHS
                 ${FIND_SODIUM_LIB_PATHS}
                 ${SODIUMDIR}/bin/Win32/Release/v120/dynamic
                 $ENV{SODIUMDIR}/bin/Win32/Release/v120/dynamic
)

IF (SODIUM_LIBRARY_DEBUG OR SODIUM_LIBRARY_RELEASE)
    SET(SODIUM_FOUND TRUE)

    IF (SODIUM_LIBRARY_DEBUG AND SODIUM_LIBRARY_RELEASE)
        SET(SODIUM_LIBRARY debug ${SODIUM_LIBRARY_DEBUG} optimized ${SODIUM_LIBRARY_RELEASE})
    ENDIF()

    IF (SODIUM_LIBRARY_DEBUG AND NOT SODIUM_LIBRARY_RELEASE)
        SET(SODIUM_LIBRARY_RELEASE ${SODIUM_LIBRARY_DEBUG})
        SET(SODIUM_LIBRARY         ${SODIUM_LIBRARY_DEBUG})
    ENDIF()
    IF (SODIUM_LIBRARY_RELEASE AND NOT SODIUM_LIBRARY_DEBUG)
        SET(SODIUM_LIBRARY_DEBUG ${SODIUM_LIBRARY_RELEASE})
        SET(SODIUM_LIBRARY       ${SODIUM_LIBRARY_RELEASE})
    ENDIF()
ELSE()
    SET(SODIUM_FOUND FALSE)
    SET(SODIUM_FOUND FALSE)
    SET(SODIUM_LIBRARY "")
    SET(FIND_SODIUM_MISSING "${FIND_SODIUM_MISSING} SODIUM_LIBRARY")
ENDIF()

MARK_AS_ADVANCED(SODIUM_LIBRARY
                 SODIUM_LIBRARY_RELEASE
                 SODIUM_LIBRARY_DEBUG
)

SET(SODIUM_LIBRARIES ${SODIUM_LIBRARIES} "${SODIUM_LIBRARY}")

IF (NOT SODIUM_FOUND)
    SET(FIND_SODIUM_ERROR "Could NOT find Sodium (missing: ${FIND_SODIUM_MISSING})")
    IF(SODIUM_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR ${FIND_SODIUM_ERROR})
    ELSEIF(NOT SODIUM_FIND_QUIETLY)
        MESSAGE("${FIND_SODIUM_ERROR}")
    ENDIF()
ENDIF()

IF(SODIUM_FOUND)
    MESSAGE("Found Sodium: ${SODIUM_INCLUDE_DIR}")
ENDIF()
