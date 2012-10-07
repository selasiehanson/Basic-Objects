#ifndef __CTRIANGLE_SCENENODE
#define __CTRIANGLE_SCENENODE

//#define GLEW_STATIC
#include <GL/glew.h>
#define FREEGLUT_STATIC
#include<GL/glut.h>
#include"CBase.h"
#include "CSceneNode.h"
#include "CShader.h"
#include "CMesh2.h"

namespace base
{
	namespace objects
	{
		class CTriangleSceneNode : public CSceneNode
		{
			public:
				CTriangleSceneNode(CSceneManager *sceneManager, CMesh2 *mesh);
				void init();
				void render();
				void exit();
			private :
				int nVert;
				int nTextures;
				GLuint vaoHandle;
				GLuint buffers[2];
				//Vertexf *pVertices;
				float angle;
				base::objects::Shader *shader ;
				CMesh2 *mesh;
		};

		typedef class CTriangleSceneNode TriangleSceneNode;
	}
}


#endif