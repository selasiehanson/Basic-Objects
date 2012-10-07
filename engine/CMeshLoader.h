#ifndef __CMESH_LOADER
#define __CMESH_LOADER

#include "CMesh.h"
#include "EModelType.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include  <map>

using namespace std;
using namespace glm;
namespace base
{
	namespace objects
	{
		

		struct PackedVertex {
			vec3 vertex;
			vec2 uv;
			vec3 normal;
			bool operator<(const PackedVertex that) const{
				return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
			};
		};

		class CMeshLoader
		{
			public:
				CMeshLoader(){};
				~CMeshLoader(){};
				CMesh * loadMesh(string filename);
			private:
				void loadAsOBJ(string filename,Mesh *mesh);
				bool  getSimilarVertex(PackedVertex &packedVertex,map<PackedVertex,unsigned short> &vertexToOutIndex, 
						unsigned short &result);

				void indexVBO (vector<vec3> &inVertices, vector<vec2> &inTexCoords, vector<vec3> & inNormals, 
			vector<unsigned short> & outIndices,vector<vec3> &outVertices, vector<vec2> &outTexCoords, vector<vec3> &outNormals) ;
				EMODEL_TYPE getType(string filename);
		};

		typedef class CMeshLoader MeshLoader;
	}
}
#endif;