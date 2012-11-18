#include "CCamera.h"


namespace base
{
	namespace objects
	{
		Camera::CCamera()
		{
			reset();
			matrix = glm::mat4(1.0f);
		}

		Camera::CCamera(base::Vertexf position)
		{
			this->pos = position;
			target.x  = 0;
			target.y = 0;
			target.z  = 0;
			matrix = glm::mat4(1.0f);
		}

		Camera::CCamera(base::Vertexf pos, base::Vertexf target)
		{
			this->pos = pos;
			this->target = target;
			matrix = glm::mat4(1.0f);
		}

		Camera::~CCamera()
		{

		}

		void Camera::constructMatrix()
		{
			//up vector
			up.x = 0.0f;
			up.y = 1.0f;
			up.z = 0.0f;

			//forward
			//				B(x2,y2)
			//				 /
			//			    /	
			//			   /
			//			  /	
			//			 /	
			//			/
			//     A(x1,y1)
			forward.x = target.x - pos.x;
			forward.y = target.y - pos.y;
			forward.z = target.z - pos.z;

			//normalise the vector
			forward =  glm::normalize(forward);
			
			//compute side side vector : cross product if forward vector and up vectio
			side = glm::normalize( glm::cross(forward,up) );

			//note: you may choose to recompute the up vector. I dont see the sense for this yet
			/*matrix =  glm::mat4(side.x,up.x,-forward.x,0.0f,
								side.y,up.y,-forward.y,0.0f,
								side.z,up.z,-forward.z,1.0f);
			*/

		}

		void Camera::reset()
		{
			//defaults
			//position defaults to origin;
			pos.x = 0;
			pos.y = 0;
			pos.z = 0;

			//target or line of sight
			target.x = 0;
			target.y = 0;
			target.z = 0;
		}


		void Camera::move(int direction, float amount)
		{
			pos.x = pos.x + (direction * target.x * amount);
			pos.z = pos.z + (direction * target.z * amount);
		}

		void Camera::rotateXZ(float degrees) 
		{
			target.x = sin(degrees);
			target.y = 0;
			target.z = -cos (degrees);
			view();
		}

		void Camera::rotateXY(float degrees)
		{
			
		}

		void Camera::rotateYZ(float degrees)
		{
			target.y =  sin(degrees);
			target.z = cos(degrees);
			target.x = 0;
			view();
		}

		void Camera::lookAt(base::Vertexf lineOfSight)
		{
			target = lineOfSight;
			this->view();
		}

		void Camera::view()
		{
			//glLoadIdentity();
			//matrix = glm::mat4(1.0f);
				matrix = glm::translate(matrix,glm::vec3(pos.x,pos.y,pos.z));
				matrix = glm::lookAt( glm::vec3(pos.x,pos.y,pos.z),
									  glm::vec3(pos.x + target.x, pos.y + target.y, pos.z + target.z),
									glm::vec3(0.0f,1.0f,0.0f));

			/*matrix = glm::mat4(1.0f);
			matrix = glm::translate(matrix,glm::vec3(pos.x,pos.y,pos.z));*/

		}

		base::Vertexf Camera::getPosition()
		{
			return pos;
		}

		void Camera::setPosition(base::Vertexf _position)
		{
			pos = _position;
		}

		//new stuff
		void Camera::translate(float x, float y, float z)
		{
			pos.x = x;
			pos.y = y;
			pos.z = z;
		}

		glm::mat4 Camera::getMatrix()
		{
			return matrix;
		}

		void Camera::setMatrix(glm::mat4 mat) {
			matrix = mat;
		}

		
	}
}


