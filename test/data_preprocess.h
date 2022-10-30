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
	double samplerate; //采样率
	double freq_basic; //（输入）基波频率

	loadfile<T> dec_num;  //采样点个数
	loadfile<T> DEC; //十进制文件（补0）
	int N=0; //2的n次幂的倍数采样点
	//loadfile<T> data; //没补0的值//int[]
	
	int dec_num_0; //补0后的采样点个数
	
	int RMS_time; //时域上的RMS值
	double snr_pre;//频域上的除前5个谐波和DC之外的所有其他分量的RMS
	double snr_fund_freq;//基波(一次谐波)的RMS
	univector<complex<double>> freq; //freq为无符号double容器
									 
	//univector<complex<double>> data_val; //data-->data_val
	
	double thd_harm;//THD谐波
	//频域信号的Real Part（实部），Imag Part（虚部），Mag（幅值），Angle（相位角）
	//U8 char ;U16 short int; U32 int U64 
public:
	//snr_set
	void set_num0(T &dec_num,T *&DEC);//采样点补0
    void set_samplerate(double x);
	void set_freq_basic(double x);

	//snr_get
	
	//snr_caculate
	bool N_num(int n); //判断dec_num是否为2的幂次倍
	int Time_dom(T *data_val, loadfile<T>dec_num);//返回值为时域上的RMS值
	double *Freq_dom(T *data_val, loadfile<T> dec_num);//FFT:返回值为频域上的计算出的freq[i]=振幅
	double Freq_cacul_fundamental(univector<double> *freq, double samplerate, double freq_basic);//基频RMS
	double Freq_cacul_harmonic(univector<double> *freq, double samplerate, double freq_basic); //除DC+5个直流之外的谐波

	//THD
	double Freq_cacul_har(univector<double> *freq, double samplerate, double freq_basic);//谐波

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

