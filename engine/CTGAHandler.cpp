#include "CTGAHandler.h"
#include <fstream>
#include <iostream>

using std::ifstream;
using std::ios;
namespace base
{
	namespace io
	{ 
		
	GLbyte *gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
	{
    FILE *pFile;			// File pointer
	TGAHEADER tgaHeader;		// TGA file header
    unsigned long lImageSize;		// Size in bytes of image
    short sDepth;			// Pixel depth;
    GLbyte	*pBits = NULL;          // Pointer to bits
    
    // Default/Failed values
    *iWidth = 0;
    *iHeight = 0;
    *eFormat = GL_RGB;
    *iComponents = GL_RGB;
    
    // Attempt to open the file
    pFile = fopen(szFileName, "rb");
    if(pFile == NULL)
        return NULL;
	
    // Read in header (binary)
    fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);
    
    // Do byte swap for big vs little endian
#ifdef __APPLE__
   /* LITTLE_ENDIAN_WORD(&tgaHeader.colorMapStart);
    LITTLE_ENDIAN_WORD(&tgaHeader.colorMapLength);
    LITTLE_ENDIAN_WORD(&tgaHeader.xstart);
    LITTLE_ENDIAN_WORD(&tgaHeader.ystart);
    LITTLE_ENDIAN_WORD(&tgaHeader.width);
    LITTLE_ENDIAN_WORD(&tgaHeader.height);*/
#endif
	
	
    // Get width, height, and depth of texture
    *iWidth = tgaHeader.width;
    *iHeight = tgaHeader.height;
    sDepth = tgaHeader.bits / 8;
    
    // Put some validity checks here. Very simply, I only understand
    // or care about 8, 24, or 32 bit targa's.
    if(tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
	{
		std::cout<<tgaHeader.bits<<std::endl;
		return NULL;
	}
   
	
    // Calculate size of image buffer
    lImageSize = tgaHeader.width * tgaHeader.height * sDepth;
    
    // Allocate memory and check for success
    pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
    if(pBits == NULL)
        return NULL;
    
    // Read in the bits
    // Check for read error. This should catch RLE or other 
    // weird formats that I don't want to recognize
    if(fread(pBits, lImageSize, 1, pFile) != 1)
		{
        free(pBits);
        return NULL;
		}
    
    // Set OpenGL format expected
    switch(sDepth)
		{
#ifndef OPENGL_ES
        case 3:     // Most likely case
            *eFormat = GL_BGR_EXT;
            *iComponents = GL_RGB;
            break;
#endif
        case 4:
            *eFormat = GL_BGRA_EXT;
            *iComponents = GL_RGBA;
            break;
        case 1:
            *eFormat = GL_LUMINANCE;
            *iComponents = GL_LUMINANCE;
            break;
        default:        // RGB
            // If on the iPhone, TGA's are BGR, and the iPhone does not 
            // support BGR without alpha, but it does support RGB,
            // so a simple swizzle of the red and blue bytes will suffice.
            // For faster iPhone loads however, save your TGA's with an Alpha!
#ifdef OPENGL_ES
    for(int i = 0; i < lImageSize; i+=3)
        {
        GLbyte temp = pBits[i];
        pBits[i] = pBits[i+2];
        pBits[i+2] = temp;
        }
#endif
        break;
		}
	
    
    
    // Done with File
    fclose(pFile);
	
    // Return pointer to image data
    return pBits;
	}

	CImage* CTGAHandler::readFile(const char * filename, unsigned int * textureID)
		{
			TGAHEADER header;
			ifstream file(filename);
			ifstream::pos_type size;
			char *memblock;
			if(file.is_open())
			{
				std::cout<<"FILE:: "<<filename<<" opened succesfully\n";
				file.seekg(0,ios::end); //we seek move the seek pointer to the end of the file
				size = file.tellg(); //get the size of the file
				file.seekg(0,ios::beg);
				memblock = new char[size];
				
				file.read((char *)&header,sizeof(TGAHEADER));
				
				std::cout<<"BITS: "<<header.bits<<std::endl;
				std::cout<<"COLOR MAP BITS: "<<header.colorMapBits<<std::endl;
				std::cout<<"COLOR MAP LENGTH: "<<header.colorMapLength<<std::endl;
				std::cout<<"COLOR MAP START: "<<header.colorMapStart<<std::endl;
				std::cout<<"COLOR MAP TYPE:"<<header.colorMapType<<std::endl;
				std::cout<<"DESCRIPTOR: "<<header.descriptor<<std::endl;
				std::cout<<"HEIGHT: "<<header.height<<std::endl;
				std::cout<<"IMAGE TYPE: "<<header.imageType<<std::endl;
				std::cout<<"INDENT TYPE: "<<header.identsize<<std::endl;
				std::cout<<"WIDTH: "<<header.width<<std::endl;
				std::cout<<"X START: "<<header.xstart<<std::endl;
				std::cout<<"y START: "<<header.ystart<<std::endl;

				if(header.bits !=8 && header.bits != 24 && header.bits != 32)
					std::cout<<"SOMETHING IS WRONG";
				
				file.close();
			}
			else{
				std::cout<<"FILE:: "<<filename <<" could NOT be opened\n";
			}
			//	Image *image =  new Image();
			//	return image;
			//}
			//else return NULL;

			/*FILE *pFile;
			unsigned long lImageSize;
			short sDepth;
			GLbyte *pBits = NULL;

			pFile = fopen(filename,"rb");
			if(pFile==NULL)
				return NULL;

			fread(&header,18,1,pFile);
			 if(header.bits != 8 && header.bits != 24 && header.bits != 32)
				std::cout<<"WRONG"<<std::endl;
			else
				std::cout<<header.bits<<std::endl;*/
			int w,h,i;
			GLenum e;
			GLbyte *data = gltReadTGABits(filename,&w,&h,&i,&e);
			Image *image   =  new Image();
			image->width = w;
			image->height = h;
			image->data  = data;
			image->component = i;
			image->format = e;
			return image;
		}

	}
}
