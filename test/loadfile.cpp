#include"loadfile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <kfr.h>
#include <vector>
#include <stdarg.h>


using namespace kfr;
//loadfile之后 return 结构体
template <typename T >
int loadfile<T>::loadfile_voltage()   //协议未拟好
{
	//reader_file<float> reader(open_file_for_reading("文件名"));//读取文件
	//readfile.samplerate = reader.format().samplerate;
	//readfile.samplerate = reader.format().channels;
	//unsigned char* temp;					// 存放读取内容的缓冲区
	ifstream ifs_read;
	dec_num = 0;

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
			char* hex_sigle[16];
			memcpy(hex_sigle, 0, 16);
			
			int ByteBeenRead = 0;
			int flag = 0;//标志位
			unsigned char x; //单个字母
			uint32_t dex_single;//单个字母转成的十进制
			while (isFound == false)
				while (x=ifs_read.read((char*)&hex_sigle, 2))//每次传入2个字节
				{
					dex_single = Hex_Conversion_Dec(hex_sigle);
					DEC[dec_num] = dex_single;
					ByteBeenRead = ByteBeenRead + 2;
					dec_num++;
				}
		}
		ifs_read.close();
	}
	file.Close();
	data = rms(make_univector(DEC)); //数据传递到KFR函数
	return data;
}

template <typename T >
int loadfile<T>::Hex_Conversion_Dec(T  &aHex)
{
	int Dec = 0;
	int DecCount = 0;
	int len = aHex.length();//字符串的字符个数
	int count = len; 
	//判断
	while (count--)
	{
		if (aHex[count] < '0' || (aHex[count] > '9' && aHex[count] < 'A') || (aHex[count] > 'F'&&aHex[count] < 'a') || aHex[count]>'f')
		{
			std::cout << "有乱码有乱码！" << std::endl;
			return 0;
		}
	}
	//计数
	int count = 0;
	while (len--)
	{
		if (aHex[count] >= '0' && aHex[count] <= '9')
			DecArr[DecCount++] = aHex[count] - '0';
		else if (aHex[count] >= 'A' && aHex[count] <= 'F')
			DecArr[DecCount++] = aHex[count] - 'A' + 10;
		else if (aHex[count] >= 'a' && aHex[count] <= 'f')
			DecArr[DecCount++] = aHex[count] - 'a' + 10;
		count++;
	}
	int j = 0;
	for (int i = DecCount-1; i >= 0; i--)
	{
		Dec = Dec + DecArr[i] * 16 ^ i;
	}
	return Dec;
}

