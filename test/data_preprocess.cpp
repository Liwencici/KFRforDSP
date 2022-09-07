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
loadfile<T> Data_preprocess<T>::get_data(T *data)
{
	data_val = data;
	return data_val;
}

template<typename T>
int Data_preprocess<T>::Time_dom(T *data_val, loadfile<T> dec_num)
{
	for (int i = 0; i < dec_num; i++)
		sum = sum + data_val[i]^2;
	RMS_time = sqrt(sum / dec_num);
	return RMS_time;
}

template<typename T>
int Data_preprocess<T>::Freq_dom(T *data_val, loadfile<T> dec_num)
{
	dft_plan<u32> plan(dec_num);
	univector<u32> temp(plan.temp_size);
	plan.execute(freq, data_val, temp, false); 
	return freq;
}

template<typename T>
int Data_preprocess<T>::Freq_cacul(univector<double> * freq, loadfile<T> dec_num)
{
	int sum = freq[0].real();
	int sum1 = 0;
	for (int i = 1; i < dec_num; i++)
		sum1 = sum1 + freq[i].real() ^ 2 + freq[i].imag()^2;
	int sum_all = sum1 + sum;
	int amp_all = sqrt(sum_all / dec_num);

	int sum2 = 0;
	for (int i = 1; i < 6; i++)
		sum2 = sum2 + freq[i].real() ^ 2 + freq[i].imag() ^ 2;
	int sum_5 = sum2 + sum;
	int amp_5 = sqrt(sum_all / 6);

	snr_pre = amp_all - amp_5;
	return snr_pre;
}
