#ifndef __CModelMesh
#define __CModelMesh

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
		class CModelMesh
		{
		private:
			
			//int nVertices;
			//int nNormals;
			//int nTexCoords;
		public:
			CModelMesh ();
			~CModelMesh();
			CModelMesh(std::string filename);
			
			std::vector<glm::vec3> vertices;
			std::vector<glm::vec2> textureCoordinates;
			std::vector<glm::vec3>normals;

			std::vector<GLushort>indices;

			int getVertexCount();
			int getNormalCount();
			int getTexCoordCount();
		};

		typedef class CModelMesh Mesh;
	}
}


#endif