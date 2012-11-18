#ifndef __CCOMPLEX_MODEL_SCENE_NODE
#define __CCOMPLEX_MODEL_SCENE_NODE

//#define GLEW_STATIC
#include <GL/glew.h>
#define FREEGLUT_STATIC
#include<GL/glut.h>
#include "CSceneNode.h"
#include "CModelMesh.h"
#include "CShader.h"
#include "CImage.h"
#include  <string>
using std::string;
namespace base
{
	namespace objects
	{
		class CComplexModelSceneNode : public CSceneNode
		{
			public:
				//CComplexModelSceneNode();
				CComplexModelSceneNode( CSceneManager *sceneManager);
				CComplexModelSceneNode(CSceneManager *sceneManager, string filname, string texture);
				void init ();
				void render();
				void exit();
			
			private:
				CModelMesh *mesh;
				//GLuint bufferId[2];
				GLuint vertexId;
				GLuint texCoordId;
				GLuint indexBufferId;
				Vertexf *pVertices;
				void reset();
				base::objects::Shader *shader ;
				void setUpTexturing(base::io::CImage* image);
				bool isTexturedEnabled;
				GLuint textureId[1];
				string texture;
				GLint textureUnit;
				GLint vVertex;
				GLint vTexCoords;
				
		};

		typedef class CComplexModelSceneNode ModelSceneNode;
	}
}

#endif