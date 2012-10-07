#define FREEGLUT_STATIC
#include<GL/glut.h>

#ifndef __CBASE
#define __CBASE

namespace base
{
	struct SVertexf
	{
		float x;
		float y;
		float z;
		SVertexf(){};
		SVertexf (float x,float y, float z)
		{
			this->x = x ;
			this->y  = y;
			this->z = z;
		}
	
		/*bool SVertex::operator ==()const
		{
		
		}*/
		bool SVertexf::operator == (const SVertexf &other) const 
		{
			if((x == other.x) && (y == other.y) && (z==other.z))
				return true;
			return false;
		}
		bool SVertexf::operator!=(const SVertexf &other) const 
		{
			return !(*this == other);
		}
	};


	struct STexCoordf
	{
		float u;
		float v;
	};
	typedef struct SVertexf Vertexf;
	typedef struct STexCoordf TexCoordf;
}


#endif