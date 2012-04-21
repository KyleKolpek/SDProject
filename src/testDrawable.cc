#include "TestDrawable.h"
#include "objLoader.h"

using namespace std;

TestDrawable::TestDrawable(Camera *camera):
	vertexCount(0),
	vertexData(NULL),
	vertexBuffer(NULL),
	camera(camera)
{
    // Prepare vertex buffer
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	float tmpVertData[] = {-0.25, -0.25, 0.75,
							 0.0,   0.0,  1.0,
						    0.25, -0.25, 0.75,
							 0.0,   0.0,  1.0,
							 0.0,  0.25, 0.75,
							 0.0,   0.0,  1.0};
	vertexCount = 3;

    // Add vertedData to a buffer
    glBufferData(GL_ARRAY_BUFFER, vertexCount * 6 * sizeof(float), tmpVertData,
        GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

TestDrawable::~TestDrawable()
{
	delete[] vertexData;
}

void TestDrawable::draw()
{
	// TODO: Store a ShaderManager over a program
	glUseProgram(shaderManager->getProgram(2, "phong.vert", "phong.frag"));

	// Set up uniforms
	GLint mvLoc = glGetUniformLocation(program, "modelView");
	GLint nmvLoc = glGetUniformLocation(program, "normalModelView");
	GLint projLoc = glGetUniformLocation(program, "projection");

	glm::mat4 MV = getModelMatrix() * camera->getViewMatrix();
	glm::mat4 proj = camera->getProjectionMatrix();

	if(mvLoc != -1)
	{
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &MV[0][0]);
	}
	else
	{
		cout << "Error" << endl;
		return;
	}

	if(nmvLoc != -1)
	{
		glUniformMatrix4fv(nmvLoc, 1, GL_FALSE,
			&glm::transpose(glm::inverse(MV))[0][0]);
	}
	else
	{
		cout << "Error" << endl;
		return;
	}
	
	if(projLoc != -1)
	{
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);
	}
	else
	{
		cout << "Error" << endl;
		return;
	}

	GLuint vertexPosLoc = glGetAttribLocation(program, "vertexPosition");
	GLuint vertexNormalLoc = glGetAttribLocation(program, "vertexNormal");

	if(vertexPosLoc == -1)
	{
		cout << "Error" << endl;
		return;
	}
	if(vertexNormalLoc == -1)
	{
		cout << "Error" << endl;
		return;
	}

	glEnableVertexAttribArray(vertexPosLoc);
	glEnableVertexAttribArray(vertexNormalLoc);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(vertexPosLoc, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(float), 0);
	glVertexAttribPointer(vertexNormalLoc, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(float), (void *)( 3 * sizeof(float)));

	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	glDisableVertexAttribArray(vertexPosLoc);
	glDisableVertexAttribArray(vertexNormalLoc);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

glm::mat4 TestDrawable::getModelMatrix()
{
	return glm::mat4(1.0, 0.0,   0.0, 0.0,
					 0.0, 1.0,   0.0, 0.0,
					 0.0, 0.0,   1.0, 0.0,
					 0.0, 0.0, -17.0, 1.0);
}
