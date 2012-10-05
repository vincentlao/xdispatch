FIND_PATH(
	ODE_INCLUDE_DIRS
	NAMES
	ode/ode.h
	HINTS
	$ENV{HOME}/include
	/usr/local/include
	/usr/include
	$ENV{ProgramFiles}/ode/include
)

FIND_LIBRARY(
	ODE_LIBRARY_DEBUG
	NAMES
	oded debugdll/ode
	HINTS
	$ENV{HOME}/lib
	/usr/local/lib
	/usr/lib
	$ENV{ProgramFiles}/ode/lib
)

FIND_LIBRARY(
	ODE_LIBRARY_RELEASE
	NAMES
	ode releasedll/ode
	HINTS
	$ENV{HOME}/lib
	/usr/local/lib
	/usr/lib
	$ENV{ProgramFiles}/ode/lib
)

IF (ODE_LIBRARY_DEBUG AND NOT ODE_LIBRARY_RELEASE)
	SET(ODE_LIBRARIES ${ODE_LIBRARY_DEBUG})
ENDIF (ODE_LIBRARY_DEBUG AND NOT ODE_LIBRARY_RELEASE)

IF (ODE_LIBRARY_RELEASE AND NOT ODE_LIBRARY_DEBUG)
	SET(ODE_LIBRARIES ${ODE_LIBRARY_RELEASE})
ENDIF (ODE_LIBRARY_RELEASE AND NOT ODE_LIBRARY_DEBUG)

IF (ODE_LIBRARY_DEBUG AND ODE_LIBRARY_RELEASE)
	SET(ODE_LIBRARIES debug ${ODE_LIBRARY_DEBUG} optimized ${ODE_LIBRARY_RELEASE})
ENDIF (ODE_LIBRARY_DEBUG AND ODE_LIBRARY_RELEASE)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(
	ODE
	DEFAULT_MSG
	ODE_INCLUDE_DIRS
	ODE_LIBRARIES
)

MARK_AS_ADVANCED(
	ODE_INCLUDE_DIRS
	ODE_LIBRARIES
	ODE_LIBRARY_DEBUG
	ODE_LIBRARY_RELEASE
) 