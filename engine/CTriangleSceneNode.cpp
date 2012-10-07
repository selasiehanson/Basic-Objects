#include "CTriangleSceneNode.h"
#include <iostream>
#include "CSceneManager.h"



namespace base 
{
	namespace objects 
	{
		CTriangleSceneNode::CTriangleSceneNode(CSceneManager *sceneManager, CMesh2 *mesh)
		{
			this->mesh = mesh;
		}

		void CTriangleSceneNode::init()
		{
			mesh->bufferData();
		}

		void CTriangleSceneNode ::render () 
		{
			mesh->draw();
		}

		void CTriangleSceneNode::exit()
		{
		
		}
	}

}

