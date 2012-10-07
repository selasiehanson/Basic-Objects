#ifndef __CJPEGHANDLER
#define __CJPEGHANDLER
//#include<stdlib.h>

#include <windows.h>
#define FREEGLUT_STATIC
#include <GL\glut.h>
#include <stdio.h>
#include <setjmp.h>
#include "../jpeg-8/jpeglib.h"


#include "IImage.h"

namespace  base
{
	namespace io
	{
		class CJPEGHandler : public IImage
		{
			public:
				struct my_error_mgr
				{
					struct jpeg_error_mgr pub;
					jmp_buf setjmp_buffer;
				}; 
				METHODDEF(void) my_error_exit(j_common_ptr cinfo)
				{
					my_error_ptr myerr = (my_error_ptr) cinfo->err;
					(*cinfo->err->output_message) (cinfo);
					longjmp(myerr->setjmp_buffer, 1);
				}
				virtual CImage * readFile( const  char * filename, unsigned int * textureID);

			private:
				typedef struct my_error_mgr * my_error_ptr;

		};

		typedef class CJPEGHandler JPEGHandler;
	}
}

#endif