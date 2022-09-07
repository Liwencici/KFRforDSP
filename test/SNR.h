#pragma once
#ifndef SNR_H_
#define SNR_H_
#include<kfr.h>
#include"data_preprocess.h"
using namespace kfr;
template<typename T>
class SNR
{
public:
	Data_preprocess Snr(Data_preprocess<int>  snr_pre, Data_preprocess<int> RMS_time);

private:
	Data_preprocess<T> snr_pre; //int
	Data_preprocess<T> RMS_time; //int
	double snr;
};
#endif


