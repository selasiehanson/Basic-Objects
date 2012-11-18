#include "CMesh.h"

namespace base 
{

	namespace objects 
	{
		class CPlaneMesh 
		{
			public :
				CPlaneMesh(CMesh *mesh)	
				{
					
					float _x = -20.0f;
					int nVert = 324;
					
					float y = -1.0f;
					float z = 20.0f;
					for(int i=0; i < nVert ; i+=4) //note the 4, since we ar bulding a quad
					{
						mesh->vertices.push_back(glm::vec3(_x, y, z));
						mesh->vertices.push_back(glm::vec3(_x, y, -z));
						mesh->vertices.push_back(glm::vec3(z, y, _x));
						mesh->vertices.push_back(glm::vec3(-z, y, _x));
						_x += 0.5f; 
					}

					
					mesh->textureCoordinates.push_back(glm::vec2(0.5f, 0.0f));
					
					mesh->colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
					
				}
			
		};
		
	}
}