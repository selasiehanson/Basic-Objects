#ifndef __CCAMERA
#define __CCAMERA

#include <math.h>
#include "CBase.h"
#include <stdlib.h>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

namespace base
{
	namespace objects
	{
		class CCamera 
		{
		public:
			CCamera();
			CCamera(base::Vertexf position);
			CCamera(base::Vertexf position, base::Vertexf target);
			~CCamera();
			void rotateXZ(float degrees); //about the Y axis
			void rotateXY(float degrees); //about the Z axis
			void rotateYZ(float degrees); //about the X axis
			void move(int direction, float amount);//denotes moving in the xz plane
			void lookAt(base::Vertexf lineOfSight);
			void view();
			void reset();
			void setPosition(base::Vertexf _position);
			base::Vertexf getPosition();

			//new stuff
			void translate(float x, float y, float z);
			glm::mat4 getMatrix();
			void setMatrix(glm::mat4) ;

		private:
			base::Vertexf pos;
			base::Vertexf target;

			//new stuff 
			glm::mat4 matrix;

			glm::vec3 forward;
			glm::vec3 up;
			glm::vec3 side;
			void constructMatrix();

		};

		typedef class CCamera Camera;	
	}
}

#endif