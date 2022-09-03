#include <kfr.h>
#include"data_preprocess.h"
#include "loadfile.h"
using namespace kfr;

template<typename T>
 loadfile<T> Data_preprocess<T>::get_num() 
{
	 return dec_num;
}

template<typename T>
loadfile<T> Data_preprocess<T>::get_samplerate()
{
	return samplerate;
}

template<typename T>
loadfile<T> Data_preprocess<T>::get_data()
{
	data_val=data
	return data_val;
}

template<typename T>
int Data_preprocess<T>::Time_dom(Data_preprocess& data)
{
	for (int i = 0; i < dec_num; i++)
		RMS_time = RMS_time + data[i];
	return RMS_time;
}

template<typename T>
int Data_preprocess<T>::Freq_dom(Data_preprocess & data)
{
	dft_plan<u32> plan(dec_num);
	univector<u32> temp(plan.temp_size);
	plan.execute(freq, in, temp, false);
	return freq;
}
