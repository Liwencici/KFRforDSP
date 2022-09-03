#pragma once
#ifndef LOAD_H_
#define LOAD_H_
#include<kfr.h>
using namespace kfr;

template <typename T >
class loadfile
{
private:
	const int MAX = 100;
	static int dec_num;//采样点个数
	size_t size;//文件大小
	float samplerate;//采样率
	//loadfile readfile;//对象
	int DecArr[MAX] = { 0 };
	static int DEC[dec_num]; //十进制数据,dec_num个采样点
	std::vector<int> data;
public:

	/*template <typename T = void> 
	inline std::shared_ptr<file_reader<T>>open_file_for_reading(const filepath& path)
	{
		return std::make_shared<file_reader<T>>(fopen_portable(path.c_str(), KFR_FILEPATH("rb")));
	}*/
	int loadfile_voltage();
	int Hex_Conversion_Dec(T &aHex);//进制转换, T=std::string
};
#endif

