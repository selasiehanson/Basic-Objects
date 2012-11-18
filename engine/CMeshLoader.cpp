#include "CMeshLoader.h"

#include <sstream>

using std::string;
using std::ifstream;
using std::stringstream;
using std::vector;
using std::ios;
using std::cout;
using std::endl;

namespace base
{
	namespace objects
	{
		

		CModelMesh * CMeshLoader::loadMesh(string filename)
		{

			EMODEL_TYPE type = getType(filename);
			Mesh * mesh = new Mesh;
			
			switch(type)
			{
				case EMODEL_TYPE::OBJ:
					 loadAsOBJ(filename,mesh);
					break; 
				default :
					mesh = NULL;
			}
			return mesh;
		}
		
		EMODEL_TYPE CMeshLoader::getType(string filename)
		{
			//get file extension and use that to return the type
			char *tok = strtok(strdup(filename.c_str()),".");
			char *ext = "";

			while(tok)
			{
				ext = tok;
				tok = strtok(0,".");
			}
			
			if(strcmp((const char *)(strlwr(ext)),"obj")==0)
				return EMODEL_TYPE::OBJ;

			return EMODEL_TYPE::NONE;
		}

		bool CMeshLoader::getSimilarVertex (PackedVertex &packedVertex,std::map<PackedVertex,unsigned short> &vertexToOutIndex, 
			unsigned short &result)
		{
			std::map<PackedVertex,unsigned short>::iterator it = vertexToOutIndex.find( packedVertex);
			if(it == vertexToOutIndex.end())
			{
				return false;
			}
			else
			{
				result = it->second;
				return true;
			}

			
		}

		void CMeshLoader::indexVBO (vector<vec3> &inVertices, vector<vec2> &inTexCoords, vector<vec3> & inNormals, 
			vector<unsigned short> & outIndices,vector<vec3> &outVertices, vector<vec2> &outTexCoords, vector<vec3> &outNormals) 
		{
			map<PackedVertex, unsigned short>vertexToOutIndex;
			for(unsigned int i=0; i < inVertices.size(); i++)
			{
				PackedVertex packed = {inVertices[i],inTexCoords[i],inNormals[i]};

				unsigned short index;
				bool found = getSimilarVertex(packed, vertexToOutIndex,index);
				if(found)
				{
					outIndices.push_back(index);
				}
				else 
				{
					outVertices.push_back(inVertices[i]);
					outTexCoords.push_back(inTexCoords[i]);
					outNormals.push_back(inNormals[i]);

					unsigned short  newIndex = (unsigned short)(outVertices.size() - 1);
					outIndices.push_back(newIndex);
					vertexToOutIndex[packed] = newIndex;
				}
			}
		}

		void CMeshLoader::loadAsOBJ(string filename,Mesh *mesh)
		{
			vector<string> tempFaces;
			vector<short> tempVertexIndices;
			vector<short> tempUVIndices;
			vector<short> tempNormalIndices;
			vector<glm::vec3> tempVertices;
			vector<glm::vec3> tempNormals;
			vector<glm::vec2> tempTexture;
			vector<int> faces;

			float x,y,z;
			float u,v;
			float nx, ny,nz;
		
			char *memblock;
			ifstream::pos_type size; 

			ifstream inFile(filename);
			if(!inFile)
				return ;
			if(inFile.is_open())
			{
				while(inFile.good())
				{
					string line;
					string str;
					char* tok = 0;
					int vertexCounter = 0;
					int normalCounter = 0;
					int texCoordCounter = 0;
					int faceCounter = 0;
					float vx, vy, vz;
					float nx, ny, nz;
					float u,v;
					short v1,v2,v3, t1,t2,t3, n1,n2,n3;
					char slash;

					char type;
					getline(inFile,line); //read line to string
					str = (char *)line.c_str();
					//cout<<str<<endl;
					istringstream iss (str);
					string token;
					if(str!= " ")
					{
						getline(iss,token, ' ');
						//cout<<iss.str()<<endl;
						if(strcmp(token.c_str(),"v")==0) 
						{
							//iss>> type;
							iss>>vx >> vy >> vz;

							tempVertices.push_back( vec3(vx, vy,vz));
						}
						if(strcmp(token.c_str(),"vt")==0) 
						{
							iss >> u >> v;
							tempTexture.push_back(vec2(u,v));
						}

						if(strcmp(token.c_str(),"vn")==0)  
						{
							iss >> nx >> ny >> nz;
							tempNormals.push_back(vec3(nx,ny,nz));
						}

						if(strcmp(token.c_str(),"f")==0)  
						{
							iss >> v1 >> slash >> t1 >> slash >> n1 ;
							iss >> v2 >> slash >> t2 >> slash >> n2;
							iss >> v3 >> slash >> t3 >> slash >> n3;

							tempVertexIndices.push_back(v1);
							tempVertexIndices.push_back(v2);
							tempVertexIndices.push_back(v3);
							
							mesh->indices.push_back(v1);
							mesh->indices.push_back(v2);
							mesh->indices.push_back(v3);

							tempUVIndices.push_back(t1);
							tempUVIndices.push_back(t2);
							tempUVIndices.push_back(t3);

							tempNormalIndices.push_back(n1);
							tempNormalIndices.push_back(n2);
							tempNormalIndices.push_back(n3);
							//mesh->indices.push_back(
						}
						

					}
				}
		
				inFile.close();
			}

			//mesh->indices =  &tempVertexIndices[0];
			vector<vec3> vertices;
			vector<vec2> uvs;
			vector<vec3> normals;
			for(int i=0; i < tempVertexIndices.size(); i++)
			{
				//find the rize vertex index 
				int vertexIndex = tempVertexIndices[i]-1 ; //c++ 0 based arrays
				int uvIndex = tempUVIndices[i] - 1  ;
				int normalIndex = tempNormalIndices[i] -1 ;
				/*vertices.push_back(tempVertices[vertexIndex]);
				uvs.push_back(tempTexture[uvIndex]);
				normals.push_back(tempNormals[normalIndex]);*/

				mesh->vertices.push_back(tempVertices[vertexIndex]);
				mesh->textureCoordinates.push_back(tempTexture[uvIndex]);
				mesh->normals.push_back(tempNormals[normalIndex]);

				//mesh->indices.push_back(vertexIndex);
			}
	
			

			// the new method
			indexVBO(vertices, uvs, normals, mesh->indices,
				mesh->vertices,mesh->textureCoordinates, mesh->normals);
		}

	}
}
