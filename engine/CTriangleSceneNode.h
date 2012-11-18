#ifndef __CTRIANGLE_SCENENODE
#define __CTRIANGLE_SCENENODE

//#define GLEW_STATIC
#include <GL/glew.h>
#define FREEGLUT_STATIC
#include<GL/glut.h>
#include"CBase.h"
#include "CSceneNode.h"
#include "CShader.h"
#include "CMesh.h"

namespace base
{
	namespace objects
	{
		class CTriangleSceneNode : public CSceneNode
		{
			public:
				CTriangleSceneNode(CSceneManager *sceneManager, CMesh *mesh,GLenum drawType = NULL);
				void init();
				void render();
				void exit();
			private :
				float angle;
				base::objects::Shader *shader ;
				CMesh *mesh;
		};

		typedef class CTriangleSceneNode TriangleSceneNode;
	}
}


#endif