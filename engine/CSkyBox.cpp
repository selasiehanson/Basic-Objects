//#include <GL/glew.h>
#include "CSkyBox.h"
#include "CJPEGHandler.h"
#include "CTGAHandler.h"
#include "Globals.h"
#include "CSceneManager.h"
#include <string>
#include <iostream>
namespace base
{
	namespace objects
	{
		

		CSkyBox::CSkyBox()
		{
			// use defaults
		}
		CSkyBox::CSkyBox(const char ** image, base::objects::CSceneManager *smgr ,float len)
		{
			length = len;
			this->images =  new char* [6];
			this->images[0] = const_cast<char *>  (image[0]);
			this->images[1] = const_cast<char *>  (image[1]);
			this->images[2] = const_cast<char *>  (image[2]);
			this->images[3] = const_cast<char *>  (image[3]);
			this->images[4] = const_cast<char *>  (image[4]);
			this->images[5] = const_cast<char *>  (image[5]);

			this->smgr = smgr; 
			
			types = new GLenum[6];
			types[0] = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
			types[1] = GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
			types[2] = GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
			types[3] = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
			types[4] = GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
			types[5] = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z ;
		}


		CSkyBox::~CSkyBox()
		{
		
		}

		void CSkyBox::init(){
			//ASSETS directory;
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_CUBE_MAP,textureId);
			base::io::TGAHandler *tgaHandler = new base::io::TGAHandler();
			
			for (int i=0; i < 6; i++)
			{
				//std::string str = Images + std::string(images[i] );
				std::string str = ASSETS::IMAGE(images[i]);
				base::io::Image *image  = tgaHandler->readFile(str.c_str( ), 0);		
				glTexImage2D( types[i],0,image->component,image->width,image->height,0, image->format,GL_UNSIGNED_BYTE,image->data);
			}

			 // Set up texture maps        
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);       
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
			//cube =  new base::objects::Cube(this->smgr,20.0f,false);
			//cube->init();
			
			float v[72] = {
						-length, -length,  length,
						 length, -length,  length,
						 length,  length,  length,
						-length,  length, length,

						// Back Face
						-length, -length, -length,
						-length,  length, -length,
						 length,  length, -length,
						 length, -length, -length,
						
						 // Top Face
						-length,  length, -length,
						-length,  length,  length,
						 length,  length,  length,
						 length,  length, -length,

						// Bottom Face
						-length, -length, -length,
						 length, -length, -length,
						 length, -length,  length,
						-length, -length,  length,

						// Right face
						length, -length, -length,
						length,  length, -length,
						length,  length,  length,
						length, -length,  length,

						// Left Face
						-length, -length, -length,
						-length, -length,  length,
						-length,  length,  length,
						-length,  length, -length
			};

			//for each (float x in  v){
			//	std::cout << x <<std::endl;
			//}
			float * verts = &v[0];
			
			
			glGenBuffersARB(1,&vertId);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB,vertId);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB,72 * sizeof(float),verts,GL_DYNAMIC_DRAW_ARB);

			auto skyV = "assets/shaders/skybox.vp";
			auto skyF = "assets/shaders/skybox.fp";
			shader  = new base::objects::Shader(skyV, skyF);
			
			glBindAttribLocation(shader->getProgram(),0,"vVertex");
			locMVP = glGetUniformLocation (shader->getProgram(),"locMVP");
			shader->link();
		}

		
		void CSkyBox::render()
		{
			
			//glDepthMask(GL_FALSE);
			auto program = shader->getProgram();
			auto m =  glm::mat4(1.0f);
			auto v =  smgr->getViewMatrix().top();
			auto mv = v * m;

			glUseProgram(program);
			auto  MVP = smgr->getProjectionMatrix() * mv;
			glUniformMatrix4fv(locMVP,1,GL_FALSE,glm::value_ptr(MVP));
			
			
			//glBindAttribLocation(program,1,"nNormal");
			//draw the cube
			glBindBufferARB(GL_ARRAY_BUFFER_ARB,vertId);
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3,GL_FLOAT,0,0);

			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
			glDrawArrays(GL_QUADS,0,72);

			glDisableClientState(GL_VERTEX_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);
			glUseProgram(0);
			//glDepthMask(GL_TRUE);
			
		}

		void CSkyBox::exit()  {
			
		}

		
	}
}