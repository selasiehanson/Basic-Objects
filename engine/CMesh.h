#ifndef __CMesh
#define __CMesh

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include "../glm/glm.hpp"

#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "EMeshBuffer.h"
#include "EMeshType.h"
#include "CShader.h"
namespace base
{
	namespace objects
	{
		class CMesh
		{
			public:
				CMesh(EMESH_TYPE type, GLfloat length = 1.0f);
				std::vector<glm::vec3> vertices;
				std::vector<glm::vec2> textureCoordinates;
				std::vector<glm::vec3>normals;
				std::vector<glm::vec3>colors;
				
				std::vector<GLushort>indices;

				//not really necessarry
				GLuint getTextureId();
				void setTextureId(GLuint textureId);
				void bufferData();
				void draw(GLenum type = NULL);
			private:
				GLuint vao;
				GLuint buffers[EMESH_BUFFER::EMESH_BUFFER_COUNT];
				base::objects::Shader *shader ;
				GLuint textureId;

		};
	}
}

#endif