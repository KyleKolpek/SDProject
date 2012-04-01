// Adapted source for ShaderLoader from
// http://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/loading.php
#include <GL/gl.h>

class ShaderLoader
{
public:

    // Constructor
    ShaderLoader();
    ShaderLoader(
        char *filename);

    // Destructor
    ~ShaderLoader();

    int loadShader(
        char *filename);

    void unloadShader();
    int getStringCount();
    const GLchar **getShaderSource();

private:
    GLchar **shaderSource;
    int stringCount;
};
