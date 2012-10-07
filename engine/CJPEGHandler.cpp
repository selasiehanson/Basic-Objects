#include "CJPEGHandler.h"

namespace base
{
	namespace io
	{
		CImage * CJPEGHandler::readFile( const char * filename, unsigned int * textureID)
		{
			unsigned char * big_buff;
			struct jpeg_decompress_struct cinfo;
			struct my_error_mgr jerr;

			FILE * infile;		
			JSAMPARRAY buffer;	
			int row_stride;		

			if ((infile = fopen(filename, "rb")) == NULL)
			{
				fprintf(stderr, "can't open %s\n", filename);
				exit(1);
				//return 0;
			}

			cinfo.err = jpeg_std_error(&jerr.pub);
			jerr.pub.error_exit = my_error_exit;

			if (setjmp(jerr.setjmp_buffer)) 
			{
				jpeg_destroy_decompress(&cinfo);
				fclose(infile);
				fprintf(stderr, "jpeg error\n");
				exit(1); //please remember to change me to something appropriate
				//return 0;
			}
			jpeg_create_decompress(&cinfo);

			jpeg_stdio_src(&cinfo, infile);

			(void) jpeg_read_header(&cinfo, TRUE);
			(void) jpeg_start_decompress(&cinfo);
			row_stride = cinfo.output_width * cinfo.output_components;

			buffer = (*cinfo.mem->alloc_sarray)
				((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
			big_buff = (unsigned char *)malloc(cinfo.output_height * cinfo.output_width * cinfo.output_components);

			while (cinfo.output_scanline < cinfo.output_height)
			{
				JDIMENSION read_now = jpeg_read_scanlines(&cinfo, buffer, 1);
				memcpy(&big_buff[(cinfo.output_scanline - read_now) * cinfo.output_width * cinfo.output_components], buffer[0], row_stride);
			}

			CImage *image = new CImage();
			image->data  =  big_buff;
			image->height = cinfo.output_height;
			image->width = cinfo.output_width;

		
			/*
			* We no longer need the buffer since opengl has a copy now
			*/
			//free(big_buff);	

			(void) jpeg_finish_decompress(&cinfo);
			jpeg_destroy_decompress(&cinfo);
			//fclose(infile);
			return image;
		}
	}
}
