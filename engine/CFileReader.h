#ifndef __CFILEREADER
#define __CFILEREADER

#include <fstream>

using std::ifstream;
using std::ios;
namespace base
{
	namespace io
	{
		class CFileReader
		{
		public:
			CFileReader();
			//CFileReader(const char * fileSrc);
			//~CFileReader();
			
			//ifstream getFile();
			//void  setFile(const  ifstream file);
			//unsigned long getFileLength();  //not sure if file size sounds better

			//bool open(const char * fileSrc);
			//void *read();
			//bool close();
		private:
			//ifstream file;
		};

		typedef class CFileReader FilReader;
	}
}
#endif