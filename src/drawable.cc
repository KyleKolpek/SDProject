#include "drawable.h"

Drawable::~Drawable()
{
}

void Drawable::setProgram(GLuint program)
{
    this->program = program;
}
