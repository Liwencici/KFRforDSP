#pragma once
#ifndef LOAD_H_
#define LOAD_H_
#include<string>
#include<kfr.h>
using namespace kfr;

template <typename T>
class loadfile
{
private:
	size_t size;//文件大小
	float samplerate;//采样率
	loadfile readfile;//对象
	static data[];
public:

	/*template <typename T = void> 
	inline std::shared_ptr<file_reader<T>>open_file_for_reading(const filepath& path)
	{
		return std::make_shared<file_reader<T>>(fopen_portable(path.c_str(), KFR_FILEPATH("rb")));
	}*/
	 loadfile_voltage();
};

#endif