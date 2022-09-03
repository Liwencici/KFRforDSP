#pragma once
#ifndef DATA_PREPROCESS_H_
#define DATA_PREPROCESS_H_
#include <kfr.h>
#include "loadfile.h"
#include "dft.hpp"

using namespace kfr;

//dec_num为输入的实际采样点，根据采样频率计算得出时域序列
//计算时域上的RMS值
//计算频域上每个频率对应的幅值和采样点个数（结构体）,计算除前五个谐波和DC之外的所有频率分量的RMS幅度

template <typename T >
class Data_preprocess :
{
private:
	loadfile samplerate;
	loadfile dec_num;
	loadfile data; //loadfile 类对象
	int RMS_time; //时域上的RMS值
	univector<complex<double>, dec_num> freq; //freq为大小dec_num的无符号double容器
	univector<complex<double>, dec_num> data_val;
	//频域信号的Real Part（实部），Imag Part（虚部），Mag（幅值），Angle（相位角）
	//U8 char ;U16 short int; U32 int U64 
public:
	loadfile get_num();
	loadfile get_samplerate();
	loadfile get_data();
	int Time_dom(Data_preprocess &data);
	int Freq_dom(Data_preprocess &data);
};

template <typename T> // data type, float or double
struct dft_plan
{
	dft_plan(size_t size);
	void execute(complex<T>* out,
		const complex<T>* in,
		u8* temp,
		bool inverse = false) const;
	void execute(univector<complex<T>, N>& out,
		const univector<const complex<T>, N>& in,
		univector<u8, N2>& temp,
		bool inverse = false) const;
};
#endif

