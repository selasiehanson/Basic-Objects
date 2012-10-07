#include "CPlane.h"
#include <iostream>
#include "CSceneManager.h"

namespace base
{
	namespace objects
	{
		CPlane::CPlane(CSceneManager *sceneManager)
		{
			nVert  = 324;
			this->sceneManager = sceneManager;
		}

		CPlane::CPlane(CSceneManager *sceneManager,int nVert)
		{
			this->nVert  = nVert;
			this->sceneManager = sceneManager;
		}

		CPlane::~CPlane()
		{
			delete  pVertices;
			pVertices = NULL;
		}

		void CPlane::init()
		{
			float _x = -20.0f;
			pVertices = new Vertexf[nVert];
			int size = 0;
			float y = -0.55f;
			float z = 20.0f;
			for(int i=0; i < nVert ; i+=4) //note the 4, since we ar bulding a quad
			{
				pVertices[i].x = _x;
				pVertices[i].y = y;
				pVertices[i].z = z;

				pVertices[i+1].x = _x;
				pVertices[i+1].y = y;
				pVertices[i+1].z = -z;

				pVertices[i+2].x = z;
				pVertices[i+2].y = y;
				pVertices[i+2].z = _x;

				pVertices[i+3].x = -z;
				pVertices[i+3].y = y;
				pVertices[i+3].z = _x;
			
				_x += 0.5f; 
				size+=4;
			}

			vec4 colorData = glm::vec4(0.0f);
			
			
			
			//setup shaders
			
			auto basicVs = "assets/shaders/flat_shader.vp";
			auto basicFs = "assets/shaders/flat_shader.fp";
			shader=  new base::objects::Shader(basicVs,basicFs);

			shader->bindLocations();
			shader->link();

			glGenBuffersARB(2, buffers);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB,buffers[0]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB,nVert * 3 * sizeof(float),&pVertices[0],GL_DYNAMIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER,buffers[1]);
			glBufferDataARB(GL_ARRAY_BUFFER,sizeof(glm::vec4),NULL,GL_DYNAMIC_DRAW_ARB);
		}

		void CPlane::render()
		{
			
			glUseProgram(shader->getProgram());

			glGenVertexArrays(1,&vaoHandle);
			glBindVertexArray(vaoHandle);

			shader->enableLocations();
			//map index 0 to vertex data
			glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
			glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(GLubyte *)NULL);


			//map index 1 to color data
			glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
			glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,(GLubyte *)NULL);


			//all uniform stuff fgoes here
			auto pos = this->getPosition();
			mat4 model = translate(mat4(1.0f),vec3(pos.x,pos.y,pos.z));
			
			
			glm::mat4 view = sceneManager->getViewMatrix().top();
			glm::mat4 mv = view * model;
			auto MVP =  sceneManager->getProjectionMatrix() * mv;

			auto  locMVP  = glGetUniformLocation(shader->getProgram(),"locMVP");
			glUniformMatrix4fv(locMVP,1,GL_FALSE,glm::value_ptr(MVP));
			
			auto colorLocation = glGetUniformLocation(shader->getProgram(),"color");
			glUniform4f(colorLocation,0.7f,0.4f,0.6f,0.5f);

			glBindVertexArray(vaoHandle);
			//glDrawArrays(GL_QUADS,0,nVert);
			//glDrawArrays(GL_TRIANGLE_FAN,0,nVert);
			
			//keep this for future when we decide to use wireframe rendering
			glDrawArrays(GL_LINES, 0,nVert);
			glBindVertexArray(0);

			//glPopMatrix();
			glUseProgram(0); //disable the shader
			
		}

		void CPlane::exit()
		{
		
		}
	}
}