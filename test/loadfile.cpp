#include"loadfile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <kfr.h>
#include <vector>
#include <stdarg.h>
#include<string>
using namespace kfr;
//loadfile之后 return 结构体

template<typename T>
loadfile<T>::loadfile_voltage( )   //协议未拟好
{
	reader_file<float> reader(open_file_for_reading("文件名"));//读取文件
	readfile.samplerate = reader.format().samplerate;
	readfile.samplerate = reader.format().channels;
	unsigned char* temp;					// 存放读取内容的缓冲区

	ifstream ifs_read;
	CStdioFile file;
	String filepath;					
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
	CFileDialog fileDlg(FALSE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	if (IDOK == fileDlg.DoModal())
	{
		filepath = fileDlg.GetPathName();
		file.Open(filepath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
			
		ifs_read.open(filepath, ios::in | ios::binary);
		if (ifs_read.is_open() == true)
		{
			ifs_read.seekg(0, ifs_read.end);
			streamoff size = ifs_read.tellg();
			ifs_read.seekg(0, ifs_read.beg);
			temp = new char[sizeof(uint32_t)*size];//分配内存
			char* hex_sigle[9];
			memcpy(hex_sigle, 0, 9);
			int byteBeenRead = 0;

			while (isFound == false)
			{	
				while (ifs_read.read((char*)&hex_sigle, 1))
				{
					if (byteBeenRead % 16 == 0)
					{
						memcpy(hex_single, 0, 9);
					}
					byteBeenRead++;
				}
			}
		
				
		
			
		}
		file.Close();
	}
	return readfile;
}


