#ifndef __CTRIANGLE_MESH_DATA
#define __CTRIANGLE_MESH_DATA

#include "CMesh.h"

namespace base 
{

	namespace objects 
	{
		class CTriangleDataMesh 
		{
			public:
				CTriangleDataMesh(CMesh *mesh, float f)
				{
					mesh->vertices.push_back(glm::vec3(-f, -f, 0.0f));
					mesh->vertices.push_back(glm::vec3( f, -f, 0.0f));
					mesh->vertices.push_back(glm::vec3( 0.0f,  f, 0.0f));
					
					mesh->textureCoordinates.push_back(glm::vec2(0.5f, 0.0f));
					mesh->textureCoordinates.push_back(glm::vec2(1.0f, 1.0f));
					mesh->textureCoordinates.push_back(glm::vec2(0.0f, 1.0f));

					mesh->colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
					mesh->colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
					mesh->colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));

				}
				
				~CTriangleDataMesh(){};
				
		};

		//CTriangleDataMesh:: CTriangleDataMesh(CMesh2 *mesh, float f)
				
	}

}

#endif;

