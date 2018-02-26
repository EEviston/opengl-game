#include "myCubeMap.h";

Skybox::Skybox()
{
	// create cube...
	points[0] = vec3(-10.0f, 10.0f, -10.0f); // side0
	points[1] = vec3(-10.0f, -10.0f, -10.0f);
	points[2] = vec3(10.0f, -10.0f, -10.0f);
	points[3] = vec3(10.0f, -10.0f, -10.0f);
	points[4] = vec3(10.0f, 10.0f, -10.0f);
	points[5] = vec3(-10.0f, 10.0f, -10.0f);

	points[6] = vec3(-10.0f, -10.0f, 10.0f), // side1
	points[7] = vec3(-10.0f, -10.0f, -10.0f);
	points[8] = vec3(-10.0f, 10.0f, -10.0f);
	points[9] = vec3(-10.0f, 10.0f, -10.0f);
	points[10] = vec3(-10.0f, 10.0f, 10.0f);
	points[11] = vec3(-10.0f, -10.0f, 10.0f);

	points[12] = vec3(10.0f, -10.0f, -10.0f); // side2
	points[13] = vec3(10.0f, -10.0f, 10.0f);
	points[14] = vec3(10.0f, 10.0f, 10.0f);
	points[15] = vec3(10.0f, 10.0f, 10.0f);
	points[16] = vec3(10.0f, 10.0f, -10.0f);
	points[17] = vec3(10.0f, -10.0f, -10.0f);

	points[18] = vec3(-10.0f, -10.0f, 10.0f); // side3
	points[19] = vec3(-10.0f, 10.0f, 10.0f);
	points[20] = vec3(10.0f, 10.0f, 10.0f);
	points[21] = vec3(10.0f, 10.0f, 10.0f);
	points[22] = vec3(10.0f, -10.0f, 10.0f);
	points[23] = vec3(-10.0f, -10.0f, 10.0f);

	points[24] = vec3(-10.0f, 10.0f, -10.0f); // side4
	points[25] = vec3(10.0f, 10.0f, -10.0f);
	points[26] = vec3(10.0f, 10.0f, 10.0f);
	points[27] = vec3(10.0f, 10.0f, 10.0f);
	points[28] = vec3(-10.0f, 10.0f, 10.0f);
	points[29] = vec3(-10.0f, 10.0f, -10.0f);

	points[30] = vec3(-10.0f, -10.0f, -10.0f); // side5
	points[31] = vec3(-10.0f, -10.0f, 10.0f);
	points[32] = vec3(10.0f, -10.0f, -10.0f);
	points[33] = vec3(10.0f, -10.0f, -10.0f);
	points[34] = vec3(-10.0f, -10.0f, 10.0f);
	points[35] = vec3(10.0f, -10.0f, 10.0f);
}

void Skybox::create_sky(
	GLuint skyLoc,
	const char* front,
	const char* back,
	const char* top,
	const char* bottom,
	const char* left,
	const char* right,
	GLuint* tex_cube) // tex_cube is the texture array... pass in a global
{
	glGenBuffers(1, &cube_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), &points, GL_STATIC_DRAW);

	glGenVertexArrays(1, &cube_vao);
	glBindVertexArray(cube_vao);
	glEnableVertexAttribArray(skyLoc);
	glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
	glVertexAttribPointer(skyLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, tex_cube);
	// load each image and copy into a side of the cube-map texture
	load_sky_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);
	load_sky_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
	load_sky_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
	load_sky_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
	load_sky_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
	load_sky_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);
	// format cube map texture
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

bool Skybox::load_sky_side(GLuint texture, GLenum side_target, const char* file_name)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int x, y;
	int force_channels = 4;

	unsigned char* img = SOIL_load_image(file_name, &x, &y, 0, force_channels); // force_channels as last parameter?
	if (!img) {
		fprintf(stderr, "ERROR: could not load %s\n", file_name);
		return false;
	}

	
	// non-power-of-2 dimensions check
	if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
		fprintf(stderr,
			"WARNING: image %s is not power-of-2 dimensions\n",
			file_name);
	}
	
	// copy image data into 'target' side of cube map
	glTexImage2D(
		side_target,
		0,
		GL_RGBA,
		x,
		y,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		img);
	
	free(img);
	return true;
}


