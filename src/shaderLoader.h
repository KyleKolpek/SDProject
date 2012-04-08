// Adapted source for ShaderLoader from
// http://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/loading.php
#include <stdgl.h>

class ShaderLoader
{
public:

	// Constructor
	ShaderLoader();
	ShaderLoader(char const *const filename);

	// Destructor
	~ShaderLoader();

	int loadShader(char const *const filename);

	void unloadShader();
	int getStringCount();
	const GLchar **getShaderSource();

private:
	GLchar **shaderSource;
	int stringCount;
};
