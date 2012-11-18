#ifndef __CUBE
#define __CUBE

//#define GLEW_STATIC
#include <GL/glew.h>
#define FREEGLUT_STATIC
#include<GL/glut.h>
#include "CShader.h"
#include "CImage.h"
#include "CSceneNode.h"
#include <vector>

namespace base
{
	namespace objects
	{	
		struct Vertex{
			glm::vec3 vertrices;
			glm::vec2 texCoords;

			Vertex (){}

			Vertex (glm::vec3 vertices, glm::vec2 texCoords){
				this->vertrices = vertices;
				this->texCoords = texCoords;
			}
		};

		class CCube : public CSceneNode
		{
		public:
			CCube();
			CCube(CSceneManager *sceneManager);
			//CCube(GLfloat length);
			CCube(CSceneManager *sceneManager,GLfloat length,string texture,bool useTexCoords = true);
			~CCube();
			
			void setLength( GLfloat length);
			GLfloat getLength();
			
			void setTextures(const char *[]);
			
			void init();
			void render();
			void exit();

		private:
			GLfloat length; //the length of each side
			bool useTexCoords;
			GLuint textureId[1];
			string texture;
			void setUpTexturing(base::io::CImage* image);
			void  tetxuring(base::io::CImage * image );
			base::objects::Shader *shader;
			GLuint vertexId;
			GLuint texCoordId;
			GLuint indexBufferId;

			GLint textureUnit;
			GLint vVertex;
			GLint vTexCoords;
			//GLint;

			
			

			static const int vertCount = 3*4*6;
			static const int texcoordSize  = 2*4*6;
			static const int normalSize = 18;

			float *verts; //  3(x,y,z) * 4 points * 6 faces
			float *normals ;
			float *texCoords; 
		};
		
		typedef class CCube Cube;
	}

	
}

#endif

