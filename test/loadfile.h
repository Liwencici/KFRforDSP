#pragma once
#ifndef LOAD_H_
#define LOAD_H_
#include<kfr.h>
#include<vector>
using namespace kfr;

template <typename T >
class loadfile
{
private:
	static int dec_num;//���������
	size_t size;//�ļ���С

	//loadfile readfile;//����
	std::vector<int> DecArr = { 0 };
	std::vector<int> DEC; 
	// static int DEC[dec_num]; //ʮ��������,dec_num��������
	std::vector<int> data;
public:

	/*template <typename T = void> 
	inline std::shared_ptr<file_reader<T>>open_file_for_reading(const filepath& path)
	{
		return std::make_shared<file_reader<T>>(fopen_portable(path.c_str(), KFR_FILEPATH("rb")));
	}*/

	int loadfile_voltage();
	int Hex_Conversion_Dec(T *aHex ,int len);//����ת��, T=std::string
};
#endif

