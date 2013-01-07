#include "CTriangleSceneNode.h"
#include <iostream>
#include "CSceneManager.h"



namespace base 
{
	namespace objects 
	{
		CTriangleSceneNode::CTriangleSceneNode(CSceneManager *sceneManager, CMesh *mesh, GLenum drawType)
		{
			this->mesh = mesh;
			this->drawType = drawType;
		}

		void CTriangleSceneNode::init()
		{
			mesh->bufferData();
			//move this to the scene node
			auto basicVs = ASSETS::SHADER("basic.vp");
			auto basicFs = ASSETS::SHADER("basic.fp");
			shader =  new base::objects::Shader(basicVs.c_str(),basicFs.c_str());
			
			//bind indices to shader inputs
			shader->bindLocations();
			shader->link();
		}

		void CTriangleSceneNode ::render () 
		{
			glUseProgram(shader->getProgram());
			auto rotationMatrix = glm::rotate(glm::mat4(1.0f),90.0f,glm::vec3(0.0f,0.0f,1.0f));

			auto location =  glGetUniformLocation(shader->getProgram(),"rotationMatrix");

			if(location >= 0)
			{
				glUniformMatrix4fv(location,1,GL_FALSE	,&rotationMatrix[0][0]);
			}
			
			mesh->draw(drawType);
			glUseProgram(0);
		}

		void CTriangleSceneNode::exit()
		{
		
		}
	}

}

