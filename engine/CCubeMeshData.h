#ifndef __CCUBE_MESH_DATA
#define __CCUBE_MESH_DATA
#include "CMesh.h"
namespace base
{
	namespace objects 
	{
		class CCubeMeshData
		{
			public:
				CCubeMeshData(CMesh *mesh, GLfloat length)
				{
					//VERTICES	
					//TOP FACE
					mesh->vertices.push_back(glm::vec3(length, length, length));
					mesh->vertices.push_back(glm::vec3(length, length, -length));
					mesh->vertices.push_back(glm::vec3(-length, length, -length));
					mesh->vertices.push_back(glm::vec3(length, length, length));
					mesh->vertices.push_back(glm::vec3(-length, length, -length));
					mesh->vertices.push_back(glm::vec3(-length, length, length));
					
					//BOTTOM FACE
					mesh->vertices.push_back(glm::vec3(-length, -length, -length ));
					mesh->vertices.push_back(glm::vec3( length, -length, -length));
					mesh->vertices.push_back(glm::vec3( length, -length, length));
					mesh->vertices.push_back(glm::vec3(-length, -length, length));
					mesh->vertices.push_back(glm::vec3(-length, -length, -length));
					mesh->vertices.push_back(glm::vec3(length, -length, length));

					//LEFT FACE
					mesh->vertices.push_back(glm::vec3(-length, length, length));
					mesh->vertices.push_back(glm::vec3(-length, length, -length));
					mesh->vertices.push_back(glm::vec3(-length, -length, -length));
					mesh->vertices.push_back(glm::vec3(-length, length, length));
					mesh->vertices.push_back(glm::vec3(-length, -length, -length));
					mesh->vertices.push_back(glm::vec3( -length, -length, length));


					//RIGHT FACE
					mesh->vertices.push_back(glm::vec3(length, -length, -length ));
					mesh->vertices.push_back(glm::vec3(length, length, -length ));
					mesh->vertices.push_back(glm::vec3(length, length, length ));
					mesh->vertices.push_back(glm::vec3(length, length, length));
					mesh->vertices.push_back(glm::vec3(length, -length, length));
					mesh->vertices.push_back(glm::vec3(length, -length, -length ));


					//FRONT FACE
					mesh->vertices.push_back(glm::vec3(length, -length, length));
					mesh->vertices.push_back(glm::vec3(length, length, length));
					mesh->vertices.push_back(glm::vec3(-length, length, length));
					mesh->vertices.push_back(glm::vec3(-length, length, length));
					mesh->vertices.push_back(glm::vec3(-length, -length, length));
					mesh->vertices.push_back(glm::vec3(length, -length, length));

					//BACK FACE
					mesh->vertices.push_back(glm::vec3(length, -length, -length));
					mesh->vertices.push_back(glm::vec3(-length, -length, -length ));
					mesh->vertices.push_back(glm::vec3(-length, length, -length));
					mesh->vertices.push_back(glm::vec3(-length, length, -length));
					mesh->vertices.push_back(glm::vec3(length, length, -length));
					mesh->vertices.push_back(glm::vec3(length, -length, -length));




					//NORMALS
					//TOP FACE
					mesh->normals.push_back(glm::vec3(0.0f, length, 0.0f ));
					mesh->normals.push_back(glm::vec3(0.0f, length, 0.0f ));
					mesh->normals.push_back(glm::vec3(0.0f, length, 0.0f ));
					mesh->normals.push_back(glm::vec3(0.0f, length, 0.0f));
					mesh->normals.push_back(glm::vec3(0.0f, length, 0.0f ));
					mesh->normals.push_back(glm::vec3(0.0f, length, 0.0f));

					//BOTTOM FACE
					mesh->normals.push_back(glm::vec3(0.0f, -length, 0.0f));
					mesh->normals.push_back(glm::vec3(0.0f, -length, 0.0f));
					mesh->normals.push_back(glm::vec3(0.0f, -length, 0.0f));
					mesh->normals.push_back(glm::vec3(0.0f, -length, 0.0f));
					mesh->normals.push_back(glm::vec3(0.0f, -length, 0.0f));
					mesh->normals.push_back(glm::vec3(0.0f, -length, 0.0f));

					//LEFT FACE
					mesh->normals.push_back(glm::vec3(-length, 0.0f, 0.0f ));
					mesh->normals.push_back(glm::vec3(-length, 0.0f, 0.0f ));
					mesh->normals.push_back(glm::vec3(-length, 0.0f, 0.0f ));
					mesh->normals.push_back(glm::vec3(-length, 0.0f, 0.0f ));
					mesh->normals.push_back(glm::vec3(-length, 0.0f, 0.0f ));
					mesh->normals.push_back(glm::vec3(-length, 0.0f, 0.0f ));

					//RIGHT FACE
					mesh->normals.push_back(glm::vec3(length, 0.0f, 0.0f));
					mesh->normals.push_back(glm::vec3(length, 0.0f, 0.0f));
					mesh->normals.push_back(glm::vec3(length, 0.0f, 0.0f));
					mesh->normals.push_back(glm::vec3(length, 0.0f, 0.0f));
					mesh->normals.push_back(glm::vec3(length, 0.0f, 0.0f));
					mesh->normals.push_back(glm::vec3(length, 0.0f, 0.0f));

					//FRONT FACE
					mesh->normals.push_back(glm::vec3(0.0f, 0.0f, length));
					mesh->normals.push_back(glm::vec3(0.0f, 0.0f, length));
					mesh->normals.push_back(glm::vec3(0.0f, 0.0f, length));
					mesh->normals.push_back(glm::vec3(0.0f, 0.0f, length));
					mesh->normals.push_back(glm::vec3(0.0f, 0.0f, length));
					mesh->normals.push_back(glm::vec3(0.0f, 0.0f, length));

					//BACK FACE
					mesh->normals.push_back(glm::vec3(0.0f, 0.0f, -length));
					mesh->normals.push_back(glm::vec3(0.0f, 0.0f, -length));
					mesh->normals.push_back(glm::vec3(0.0f, 0.0f, -length));
					mesh->normals.push_back(glm::vec3(0.0f, 0.0f, -length));
					mesh->normals.push_back(glm::vec3(0.0f, 0.0f, -length));
					mesh->normals.push_back(glm::vec3(0.0f, 0.0f, -length));


					//TEXTURE COORDINATES
					//TOP
					mesh->textureCoordinates.push_back(glm::vec2(length, length));
					mesh->textureCoordinates.push_back(glm::vec2(length, 0.0f));
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, 0.0f));
					mesh->textureCoordinates.push_back(glm::vec2(length, length));
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, 0.0f));
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, length));

					//BOTTOM
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, 0.0f));
					mesh->textureCoordinates.push_back(glm::vec2(length, 0.0f));
					mesh->textureCoordinates.push_back(glm::vec2(length, length));
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, length));
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, 0.0f));
					mesh->textureCoordinates.push_back(glm::vec2(length, length));

					//LEFT
					mesh->textureCoordinates.push_back(glm::vec2(length, length));
					mesh->textureCoordinates.push_back(glm::vec2(length, 0.0f));
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, 0.0f));
					mesh->textureCoordinates.push_back(glm::vec2(length, length));
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, 0.0f));
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, length));

					//RIGHT
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, 0.0f));
					mesh->textureCoordinates.push_back(glm::vec2(length, 0.0f));
					mesh->textureCoordinates.push_back(glm::vec2(length, length));
					mesh->textureCoordinates.push_back(glm::vec2(length, length));
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, length));
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, 0.0f));

					//FRONT
					mesh->textureCoordinates.push_back(glm::vec2(length, 0.0f));
					mesh->textureCoordinates.push_back(glm::vec2(length, length));
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, length));
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, length));
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, 0.0f));
					mesh->textureCoordinates.push_back(glm::vec2(length, 0.0f));

					//BACK
					mesh->textureCoordinates.push_back(glm::vec2(length, 0.0f));
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, 0.0f));
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, length));
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, length));
					mesh->textureCoordinates.push_back(glm::vec2(length, length));
					mesh->textureCoordinates.push_back(glm::vec2(length, 0.0f));


				}
				~CCubeMeshData(){};
		};
	}
}

#endif