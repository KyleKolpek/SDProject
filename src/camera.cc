
Camera::Camera():
	viewMatrix(1.0);
{
}

glm::mat4 getViewMatrix()
{
	return viewMatrix;
}

void Camera::resetMatrix()
{
	viewMatrix = glm::mat4(1.0);
}

void Camera::lookAt(glm::vec3 const eye,
					glm::vec3 const at,
					glm::vec3 const up)
{
	/*glm::vec3 fN  = glm::normalize(at - eye);
	glm::vec3 upN = glm::normalize(up);
	glm::vec3 s   = glm::cross(f, up);
	glm::vec3 u   = glm::cross(s, f);
	glm::mat4 M   = glm::mat4(1.0);
	M[0][0] =  s[0];
	M[0][1] =  u[0];
	M[0][2] = -f[0];
	M[1][0] =  s[1];
	M[1][1] =  u[1];
	M[1][2] = -f[1];
	M[2][0] =  s[2];
	M[2][1] =  u[2];
	M[2][2] = -f[2];*/
	viewMatrix *= glm::lookAt(eye, at, up);
}

void Camera::frustum(float left, float right
					 float bottom, float top,
					 float zNear, float zFar)
{
	viewMatrix *= glm::frustum(left, right, bottom, top, zNear, zFar);
}

void Camera::rotate(glm::vec3 axis, float radians)
{
}

void Camera::translate(glm::vec3 delta)
{
}
