#ifndef __UTILITIES
#define __UTILITIES

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

#include <iostream>
using  namespace glm;

namespace base
{
	namespace math
	{
		mat3 getRotataionMatrix(mat4 matrix, bool normalize = false)
		{
			float rotMatrix[3][3];
			
			float  *_mat = glm::value_ptr (matrix);
			auto i = _mat[0];
			//we pick the upper 3x3 matrix from out 4x4 matrix
			

			if(normalize)
			{
				auto v  = glm::normalize(vec3(_mat[0],_mat[1],_mat[2]));
				rotMatrix[0][0] = v.x;
				rotMatrix[0][1] = v.y;
				rotMatrix[0][2] = v.z;

				v  = glm::normalize(vec3(_mat[4],_mat[5],_mat[6]));
				rotMatrix[1][0] = v.x;
				rotMatrix[1][1] = v.y;
				rotMatrix[1][2] = v.z;

				v  = glm::normalize(vec3(_mat[8],_mat[9],_mat[10]));
				rotMatrix[2][0] = v.x;
				rotMatrix[2][1] = v.y;
				rotMatrix[2][2] = v.z;
				
			}
			else 
			{
				rotMatrix[0][0] = _mat[0];
				rotMatrix[0][1] = _mat[1];
				rotMatrix[0][2] = _mat[2];

				rotMatrix[1][0] = _mat[4];
				rotMatrix[1][1] = _mat[5];
				rotMatrix[1][2] = _mat[6];

				rotMatrix[2][0] = _mat[8];
				rotMatrix[2][1] = _mat[9];
				rotMatrix[2][2] = _mat[10];
			}

			return mat3(rotMatrix);

		}

		

		mat3 getNormalizedMatrix(mat4 matrix)
		{
			mat3 normalizedMat;
			getRotataionMatrix(matrix,true);
			return normalizedMat;
		}
	}
}

#endif