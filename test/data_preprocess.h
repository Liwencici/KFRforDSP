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
class Data_preprocess 
{
private:
	loadfile<T> samplerate; //采样率
	loadfile<T> dec_num;  //采样点个数
	loadfile<T> DEC; //十进制文件（补0）
	int N=0; //2的n次幂的倍数采样点
	loadfile<T> data; //没补0的值
	loadfile<T> freq_basic; //基波频率
	int RMS_time; //时域上的RMS值
	float snr_pre;//频域上的除前5个谐波和DC之外的所有其他分量的RMS
	float snr_fund_freq;//基波(一次谐波)的RMS
	univector<complex<double>> freq; //freq为大小dec_num的无符号double容器
	univector<complex<double>> data_val; //data-->data_val
	
	//频域信号的Real Part（实部），Imag Part（虚部），Mag（幅值），Angle（相位角）
	//U8 char ;U16 short int; U32 int U64 
public:
	loadfile<T> get_num(T dec_num,T *DEC);
	loadfile<T> get_samplerate();
	loadfile<T> get_freq_basic();
	loadfile<T> get_data(T *data);
	bool N_num(int n); //判断dec_num是否为2的幂次倍
	int Time_dom(T *data_val, loadfile<T>dec_num);//返回值为时域上的RMS值
	int Freq_dom(T *data_val, loadfile<T> dec_num);//返回值为频域上的计算出的freq[i]=振幅
	int Freq_cacul_fundamental(univector<double> *freq,loadfile<T> freq_basic);//基频RMS
	int Freq_cacul_harmonic(univector<double> *freq,loadfile<T> freq_basic); //除DC+5个直流之外的谐波
};

template <typename T> // data type, float or double
struct dft_plan
{
	void execute(complex<T>* out,
		const complex<T>* in,
		u8* temp,
		bool inverse = false) const;
	//void execute(univector<complex<T>, N>& out,
	//	const univector<const complex<T>, N>& in,
	//	univector<u8, N2>& temp,
	//	bool inverse = false) const;
};
#endif

