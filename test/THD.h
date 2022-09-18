#pragma once
#ifndef THD_H_
#define THD_H_
#include<kfr.h>
#include"data_preprocess.h"
using namespace kfr;

template<typename T>
class THD
{
public:
	double thd_Cacu(Data_preprocess<T> thd_harm,Data_preprocess<T> snr_fund_freq);

private:
	Data_preprocess<T> thd_harm; //Ð³²¨
	Data_preprocess<T> snr_fund_freq;//»ù²¨
	double thd_fin;

};
#endif
