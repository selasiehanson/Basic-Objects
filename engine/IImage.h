#ifndef __IIMAGE
#define __IIMAGE
	
#include "CImage.h"
namespace  base
{
	namespace io
	{
		class IImage //interface to define Image functions
		{
			public:
				virtual CImage  *readFile (const char * filename, unsigned int * textureID) = 0;
			
		};
	}	
}

#endif