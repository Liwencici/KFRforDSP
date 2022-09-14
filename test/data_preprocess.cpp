#include <kfr.h>
#include"data_preprocess.h"
#include "loadfile.h"
using namespace kfr;

template<typename T>
 loadfile<T> Data_preprocess<T>::get_num(T dec_num,T *DEC) 
{
	 N = dec_num;
	 while (N_num(N) == false)
	 {
		 N = N + 1;
		 DEC[N] = 0;
	 }
	 return N;
}

template<typename T>
loadfile<T> Data_preprocess<T>::get_samplerate()
{
	return samplerate;
}

template<typename T>
loadfile<T> Data_preprocess<T>::get_freq_basic()
{
	return freq_basic;
}

template<typename T>
loadfile<T> Data_preprocess<T>::get_data(T *data)
{
	data_val = data;
	return data_val;
}

template<typename T>
bool Data_preprocess<T>::N_num(int n)
{
	int temp = 1;
	while (temp <= num)
	{
		if (temp == num)
			return true;
		temp = temp * 2;
	}
	return false;
}

template<typename T>
int Data_preprocess<T>::Time_dom(T *data_val, loadfile<T>  dec_num) //����Ҫ��0
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
int Data_preprocess<T>::Freq_cacul_fundamental(univector<double>* freq,  loadfile<T> freq_basic)
{
	Data_preprocess h;
	N = h.get_num();
	fs = h.get_samplerate();//������
	F = fs / N; //Ƶ�ʷֱ���
	int i = fs / F; //��Ƶ��
	int sum = freq[i].real() ^ 2 + freq.imag() ^ 2;
	snr_fund_freq = sqrt(sum);
	return snr_fund_freq;
}

template<typename T>
int Data_preprocess<T>::Freq_cacul_harmonic(univector<double> * freq,  loadfile<T> freq_basic)
{
	Data_preprocess h;
	fs = h.get_samplerate();
	N = h.get_num();
	F = fs / N;
	int i1 = fs / N; //��Ƶ�㣨һ��г����
	int i2 = i1 * 2;//����г����
	int i3 = i1 * 3;//����г����
	int i4 = i1 * 4;//�Ĵ�г����
	int i5 = i1 * 5;//���г����
	int DC = freq[0].real()^2;//ֱ������
	int sum_5 = freq[i1].real() ^ 2 + freq[i1].imag() ^ 2 + freq[i2].real() ^ 2 + freq[i2].imag() ^ 2 + freq[i3].real() ^ 2 + freq[i4].imag() ^ 2 + freq[i5].real() ^ 2 + freq[i5].imag() ^ 2;
	int RMS_5 = sqrt(sum_5 + DC / 2);

	int sum = 0;
	for (int i = 1; i <= N/2-1; i++)
		sum = sum + freq[i].real() ^ 2 + freq[i].imag() ^ 2;
	int RMS_all = sqrt(sum + DC / 2);

	snr_pre = RMS_all - RMS_5;
	return snr_pre;


}

