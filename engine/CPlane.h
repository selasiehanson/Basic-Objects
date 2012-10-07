#ifndef __CPLANE
#define __CPLANE

//#define GLEW_STATIC
#include <GL/glew.h>
#define FREEGLUT_STATIC
#include<GL/glut.h>
#include"CBase.h"
#include "CSceneNode.h"
#include "CShader.h"
namespace base
{
	namespace objects
	{
		class CPlane : public CSceneNode
		{
			public:
				CPlane(CSceneManager *sceneManager);
				CPlane(CSceneManager *sceneManager,int nVert);
				~CPlane();
				void init();
				void render();
				void exit();

			 private :
				int nVert;
				int nTextures;
				GLuint bufferId;
				GLuint buffers[2];
				GLuint vaoHandle;
				Vertexf *pVertices;
				base::objects::Shader *shader ;
		};

		typedef class CPlane Plane;
	}
}

#endif