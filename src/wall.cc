#include "SOIL/SOIL.h"
#include "wall.h"

Wall::Wall(float x1, float y1, float x2, float y2):
	x1(x1),
	y1(y1),
	x2(x2),
	y2(y2),
	vertexCount(4)
{
	
	float tmpVertexData[] = {x1, 0.0, y1,
							 x1, 4.0, y1,
							 x2, 4.0, y2,
							 x2, 0.0, y2};
    // Prepare vertex buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(float), tmpVertexData,
		GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Load texture data
	texture = SOIL_load_OGL_texture(
		 "../assets/models/wall/stoneWall.jpg",
		 SOIL_LOAD_AUTO,
		 SOIL_CREATE_NEW_ID,
		 SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
		 SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT |
		 SOIL_FLAG_TEXTURE_REPEATS);
}

Wall::~Wall()
{
	//Nothing to do yet.
}

void Wall::draw()
{
	
}

