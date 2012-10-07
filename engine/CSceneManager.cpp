#include "CSkyBox.h"
#include "CSceneManager.h"
#include <iostream>

namespace base
{
	namespace objects
	{
		CSceneManager::CSceneManager()
		{
			this->skybox = NULL;
		}
		
		void CSceneManager::addNode(SceneNode *node)
		{
			nodes.push_back(node);
		}

		std::vector<SceneNode *> CSceneManager::getNodes()
		{
			return nodes;
		}

		int CSceneManager::getNumNodes()
		{
			return nodes.size();
		}

		void CSceneManager::render()
		{
			std::vector<SceneNode *>::iterator it = nodes.begin();
			//std::cout<<"there are "<< nodes.size()<<" objects to be drawn" <<std::endl;
			for(it = nodes.begin(); it != nodes.end(); it++)
			{
				(*it)->render();
			}

			if(this->skybox ){
				skybox->render();
			}	
		}

		
		void CSceneManager::init()
		{
			std::vector<SceneNode *>::iterator it;
			for(it = nodes.begin(); it != nodes.end(); it++)
			{
				(*it)->init();
			}		

			if(skybox)
				skybox->init();
		}

		void CSceneManager::exit()
		{
			std::vector<SceneNode *>::iterator it = nodes.begin();
			for(it = nodes.begin(); it != nodes.end(); it++)
			{
				(*it)->exit();
			}
		}

		void CSceneManager::setProjectionMatrix(glm::mat4 projectionMatrix)
		{
			this->projectionMatrix = projectionMatrix;
		}

		void CSceneManager::setViewMatrix(glm::mat4 viewMatrix)
		{
			this->viewMatrix.push(viewMatrix);
		}
		
		//void CSceneManager::addModelViewMatrix(glm::mat4 modelViewMatrix)
		//{
		//	this->modelViewMatrix.push(modelViewMatrix); //similar to abod
		//}

		std::stack<glm::mat4> CSceneManager::getViewMatrix()
		{
			return viewMatrix;
		}

		glm::mat4 CSceneManager::getProjectionMatrix()
		{
			return projectionMatrix;
		}

		void CSceneManager::setSkyBox(SkyBox* skyBox)
		{
			this->skybox = skyBox;
		}

		CSkyBox * CSceneManager::getSkyBox()
		{
			return this->skybox;
		}
	}
}