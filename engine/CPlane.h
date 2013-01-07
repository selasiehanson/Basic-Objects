#ifndef __CPLANE
#define __CPLANE

//#define GLEW_STATIC
#include <GL/glew.h>
#define FREEGLUT_STATIC
#include <GL/glut.h>
#include"CBase.h"
#include "CSceneNode.h"
#include "CShader.h"
#include "CMesh.h"
namespace base
{
	namespace objects
	{
		class CPlane : public CSceneNode
		{
			public:
				CPlane(CSceneManager *sceneManager,CMesh *mesh, GLenum drawType = NULL);
				~CPlane();
				void init();
				void render();
				void exit();

			 private :
				base::objects::Shader *shader ;
				CMesh *mesh;
		};

		typedef class CPlane Plane;
	}
}

#endif