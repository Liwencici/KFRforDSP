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
	loadfile samplerate; //采样率
	loadfile dec_num;  //采样点个数
	loadfile<T> data; 
	int RMS_time; //时域上的RMS值
	int snr_pre;//频域上的除前5个谐波和DC之外的所有其他分量的RMS
	univector<complex<double>, dec_num> freq; //freq为大小dec_num的无符号double容器
	univector<complex<double>, dec_num> data_val; //data-->data_val
	
	//频域信号的Real Part（实部），Imag Part（虚部），Mag（幅值），Angle（相位角）
	//U8 char ;U16 short int; U32 int U64 
public:
	loadfile get_num();
	loadfile get_samplerate();
	loadfile get_data(T *data);
	int Time_dom(T *data_val, loadfile<T> dec_num);//返回值为时域上的RMS值
	int Freq_dom(T *data_val, loadfile<T> dec_num);//返回值为频域上的计算出的freq[i]=振幅
	int Freq_cacul(univector<double> *freq, loadfile<T> dec_num);
	template<typename T>
};

template <typename T> // data type, float or double
struct dft_plan
{
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

