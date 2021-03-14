find_package(PkgConfig)
pkg_check_modules(HICSS hicss)

set(VERSION_OK TRUE)

if (HICSS_VERSION)
    if (HICSS_FIND_VERSION_EXACT)
        if (NOT("${HICSS_FIND_VERSION}" VERSION_EQUAL "${HICSS_VERSION}"))
            set(VERSION_OK FALSE)
        endif ()
    else ()
        if ("${HICSS_VERSION}" VERSION_LESS "${HICSS_FIND_VERSION}")
            set(VERSION_OK FALSE)
        endif ()
    endif ()
endif ()

if (NOT HICSS_INCLUDE_DIRS)
    set(HICSS_INCLUDE_DIRS ${HICSS_INCLUDEDIR})
endif ()

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(HICSS DEFAULT_MSG HICSS_INCLUDE_DIRS HICSS_LIBRARIES VERSION_OK)

