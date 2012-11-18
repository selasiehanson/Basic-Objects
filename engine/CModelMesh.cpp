#include "CModelMesh.h"

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
		CModelMesh::CModelMesh()
		{

		}

		CModelMesh::~CModelMesh()
		{

		}

		CModelMesh::CModelMesh(string filename)
		{
			//load(filename);
		}


		int CModelMesh::getVertexCount()
		{
			return (vertices.size() /3);
		}

		int CModelMesh::getNormalCount()
		{
			return (normals.size() / 3);
		}

		int CModelMesh::getTexCoordCount()
		{
			return (textureCoordinates.size() / 3);
		}

		
	}
}