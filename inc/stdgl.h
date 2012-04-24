#ifndef STDGL_H
#define STDGL_H

/***************************************************************************//**
 * Manages cross-platform OpenGL includes.
 * SFML provides this functionality, but there may be times when you want to
 * write platform-independent code without the bulk of SFML.
 *
 ******************************************************************************/

/* Windows specific includes */
#ifdef WIN32
    #include <windows.h>
    #include "windows/GL/gl.h"
    #include "windows/GL/glu.h"
#endif

/* OSX specific includes */
#ifdef MACOSX
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#endif

/* *nix specific includes */
#ifdef _NIX
	#include <GL/glew.h>
	#include <GL/glext.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#endif
