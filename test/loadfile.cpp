#include"loadfile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <kfr.h>
#include <vector>
#include <stdarg.h>
#include<string>
using namespace kfr;
//loadfile֮�� return �ṹ��

template<typename T>
loadfile<T>::loadfile_voltage( )   //Э��δ���
{
	reader_file<float> reader(open_file_for_reading("�ļ���"));//��ȡ�ļ�
	readfile.samplerate = reader.format().samplerate;
	readfile.samplerate = reader.format().channels;
	unsigned char* temp;					// ��Ŷ�ȡ���ݵĻ�����

	ifstream ifs_read;
	CStdioFile file;
	String filepath;					
	TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");
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
			temp = new char[sizeof(uint32_t)*size];//�����ڴ�
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


