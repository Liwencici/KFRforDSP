#include"loadfile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <kfr.h>
#include <vector>
#include <stdarg.h>


using namespace kfr;
//loadfile֮�� return �ṹ��
template <typename T >
int loadfile<T>::loadfile_voltage()   //Э��δ���
{
	//reader_file<float> reader(open_file_for_reading("�ļ���"));//��ȡ�ļ�
	//readfile.samplerate = reader.format().samplerate;
	//readfile.samplerate = reader.format().channels;
	//unsigned char* temp;					// ��Ŷ�ȡ���ݵĻ�����
	ifstream ifs_read;
	dec_num = 0;

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
			ifs_read.seekg(0, ifs_read.beg);//size��¼���ļ��е��ַ�������size/5���ǵ�ĸ���

			char ch;//�ַ�
			int Dec_num = size / 5;//num Ϊ�������
			char single_hex[5];
			int i = 0;
			int temp_dex;//18λ��ת��λʮ����
			while (!ifs_read.eof())
			{
				ifs_read >> ch;
				single_hex[i] = ch;
				i++;
				if (i == 5)
				{
					temp_dex = Hex_Conversion_Dec(single_hex, 5);
					cout << temp_dex;
					DEC[dec_num] = temp_dex;
					dec_num++;
				}
			}
		}
		ifs_read.close();
	}
	file.Close();
	data = rms(make_univector(DEC)); //���ݴ��ݵ�KFR����??????
	return data;
}

template <typename T >
int loadfile<T>::Hex_Conversion_Dec(T  *aHex ,int len)
{
	int Dec = 0;
	int DecCount = 0;
	int count_len = len;
	//�ж�
	while (count_len--)
	{
		if (aHex[count_len] < '0' || (aHex[count_len] > '9' && aHex[count_len] < 'A') || (aHex[count_len] > 'F'&&aHex[count_len] < 'a') || aHex[count_len]>'f')
		{
			{
				std::cout << "�����������룡" << std::endl;
				return 0;
			}
		}
		//����
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
		for (int i = 0; i < 5; i++)
		{
			Dec = Dec + pow(16, (4 - i))*DecArr[i];
		}
		return Dec;
	}
}

