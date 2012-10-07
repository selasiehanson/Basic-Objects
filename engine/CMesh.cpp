#include "CMesh.h"

using std::string;
using std::ifstream;
using std::vector;
using std::ios;
using std::cout;
using std::endl;
namespace base
{
	namespace objects
	{
		CMesh::CMesh()
		{

		}

		CMesh::~CMesh()
		{

		}

		CMesh::CMesh(string filename)
		{
			//load(filename);
		}


		int CMesh::getVertexCount()
		{
			return (vertices.size() /3);
		}

		int CMesh::getNormalCount()
		{
			return (normals.size() / 3);
		}

		int CMesh::getTexCoordCount()
		{
			return (textureCoordinates.size() / 3);
		}

		
	}
}