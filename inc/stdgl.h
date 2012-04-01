#ifndef STDGL_H
#define STDGL_H

// Windows specific includes
#ifdef WIN32
    #include <windows.h>
    #include "windows/GL/gl.h"
    #include "windows/GL/glu.h"
#endif

// OSX specific includes
#ifdef MACOSX
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#endif

// *nix specific includes
#ifdef _NIX
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#endif
