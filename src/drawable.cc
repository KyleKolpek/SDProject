#include "drawable.h"

Drawable::~Drawable()
{
}

void Drawable::setProgram(ShaderManager *shaderManager)
{
    this->shaderManager = shaderManager;
}
