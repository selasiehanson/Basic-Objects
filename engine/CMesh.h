#ifndef __CMESH
#define __CMESH

//#define GLEW_STATIC
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <Gl/glew.h>
#include "../glm/glm.hpp"

#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
namespace base
{
	namespace objects
	{
		class CMesh
		{
		private:
			
			//int nVertices;
			//int nNormals;
			//int nTexCoords;
		public:
			CMesh ();
			~CMesh();
			CMesh(std::string filename);
			
			std::vector<glm::vec3> vertices;
			std::vector<glm::vec2> textureCoordinates;
			std::vector<glm::vec3>normals;

			std::vector<GLushort>indices;

			int getVertexCount();
			int getNormalCount();
			int getTexCoordCount();
		};

		typedef class CMesh Mesh;
	}
}


#endif