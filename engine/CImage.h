#ifndef __CIMAGE
#define __CIMAGE

#define FREEGLUT_STATIC
#include<GL/glut.h>
namespace base
{
	namespace io
	{
		class CImage
		{
		public: 
			//virtual CImage* getImageData() = 0;
			GLint width;
			GLint height;
			GLint component;
			GLenum format;
			//unsigned char *data;
			const void *data;
		};

		typedef class CImage Image; 
	}
}

#endif
