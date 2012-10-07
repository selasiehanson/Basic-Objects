#include "CFileReader.h"

namespace base
{

	namespace io
	{
		CFileReader::CFileReader()
		{
			
		}

		//CFileReader::CFileReader(const char * fileSrc)
		//{
		//	this->file  = file;
		//}

		//CFileReader::~CFileReader()
		//{
		//
		//}

		//unsigned long CFileReader::getFileLength()
		//{
		//	if(!file.good())
		//		return 0;
		//	file.seekg(0,ios::end); //move file pointer to the end of the file
		//	unsigned long length = file.tellg(); //get the size
		//	file.seekg(0,ios::beg); // move file pointer back to the beggining of the file
		//	return length;
		//}

		//ifstream CFileReader::getFile()
		//{
		//	return file;
		//}

		/*bool CFileReader::open(const char * fileSrc)
		{
			if(fileSrc == NULL)
				return false;
			file.open(fileSrc);
			if(!file.good())
				return false;
			return true;
		}*/



	}
}
