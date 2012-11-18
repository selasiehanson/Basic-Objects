#ifndef __SKYBOX
#define __SKYBOX

#include "CCube.h"
//#define FREEGLUT_STATIC
//#include<GL/glut.h>

using namespace std;
class base::objects::CSceneManager;
namespace base
{
	namespace objects
	{

		class CSkyBox  
		{
			public:
				CSkyBox();
				CSkyBox(const char ** images, base::objects::CSceneManager *smgr , float length=100.0f);
				~CSkyBox();
				void init();
				void render();
				void exit();
			private:
				char ** images ;
				GLuint textureId;
				base::objects::Cube *cube;
				base::objects::CSceneManager *smgr;
				base::objects::Shader *shader;

				GLuint vertId;
				GLenum *types;
				GLint locMVP;
				float length;
		};

		typedef class CSkyBox SkyBox;
	}
}
#endif