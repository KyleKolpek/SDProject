#ifndef STDGLEXT_H
#define STDGLEXT_H

/***************************************************************************//**
 * Manages cross-platform OpenGL extension includes.
 *
 ******************************************************************************/

/* Windows specific includes */
#ifdef WIN32
    /* May need #include <windows.h> here */
    #include "windows/GL/wglext.h"

/* *nix and MacOSX includes */
#elif defined MACOSX || defined _NIX
    #include "nix/GL/glxext.h"
#endif

#include "common/GL/glext.h"

#endif
