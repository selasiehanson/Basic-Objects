#include "CPlane.h"
#include <iostream>
#include "CSceneManager.h"

namespace base
{
	namespace objects
	{
		CPlane::CPlane(CSceneManager *sceneManager,CMesh *mesh, GLenum drawType)
		{
			this->sceneManager = sceneManager;
			this->mesh = mesh;
			this->drawType = drawType;
		}

		CPlane::~CPlane()
		{
			//this->mesh->vertices.empty();
		}

		void CPlane::init()
		{
			mesh->bufferData();
			//setup shaders
		
			auto basicVs = ASSETS::SHADER("flat_shader.vp");
			auto basicFs = ASSETS::SHADER("flat_shader.fp");
			shader =  new base::objects::Shader(basicVs.c_str(),basicFs.c_str());
			
			//bind indices to shader inputs
			shader->bindLocations();
			shader->link();

		}

		void CPlane::render()
		{
			glUseProgram(shader->getProgram());

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

			
			//keep this for future when we decide to use wireframe rendering
			//glDrawArrays(GL_LINES, 0,nVert);
			mesh->draw(drawType);
			glUseProgram(0);
			
		}

		void CPlane::exit()
		{
		
		}
	}
}