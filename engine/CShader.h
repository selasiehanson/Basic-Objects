#ifndef __CSHADER
#define __CSHADER

//#include "CFileReader.h"
//#define GLEW_STATIC
#include <GL/glew.h>
#define FREEGLUT_STATIC
#include <GL/glut.h>
#include <fstream>
#include "CAttribLocationsTypes.h"
using std::ifstream;
namespace base
{
	namespace objects
	{
		class CShader
		{
			public :
				CShader();
				CShader(const char *vertexShaderFile, const char*fragmentShaderFile);
				~CShader();

				void loadShadersVF();
				char * loadShader(const char * filename);
				void unloadShaderSrc(GLubyte * shaderSrc);
				void link();
				void bindLocations();
				//void enableLocations();
				void reflectLocations();
				
				GLuint getProgram();
			private: 
				//void loadShader(io::FilReader file);
				unsigned long getFileLength(ifstream &file);
				
				char * vertexSrcProgram;
				char * fragmentSrcProgram;
			
				GLuint vertexShader ;
				GLuint fragmentShader ;
				GLuint shaderProgram ;

				void reset();
				
		};

		typedef class CShader Shader;
	}
}
#endif