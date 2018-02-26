#ifndef SKY_H
#define	SKY_H

#include "maths_funcs.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "SOIL.h"
#include <stdio.h>

class Skybox
{
public:
	static const double TO_RADS;

	Skybox();

	GLuint cube_vao;

	void create_sky(
		GLuint skyLoc,
		const char* front,
		const char* back,
		const char* top,
		const char* bottom,
		const char* left,
		const char* right,
		GLuint* tex_cube);

	bool load_sky_side(
		GLuint texture, GLenum side_target, const char* file_name);
private:
	vec3 pos;
	GLuint cube_vbo;
	// now of type vec 3 to add camera pos to each element of the array!!! may not be needed now...
	vec3 points[36];
};

#endif	/* SKY_H */
