#include <kfr.h>
#include"data_preprocess.h"
#include "loadfile.h"
using namespace kfr;

template<typename T>
 void Data_preprocess<T>::set_num0(T &dec_num,T *&DEC) //�����㲹0 
{
	 int N = dec_num;
	 while (N_num(N) == false)
	 {
		 N = N + 1;
		 DEC[N] = 0;
	 }
	 dec_num_0 = N;
}

template<typename T>
void Data_preprocess<T>::set_samplerate(double x)
{
	samplerate = x;
}

template<typename T>
void Data_preprocess<T>::set_freq_basic(double x)
{
	freq_basic = x;
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
int Data_preprocess<T>::Time_dom(T *DEC, loadfile<T> dec_num) //����Ҫ��0
{
	for (int i = 0; i < dec_num; i++)
		sum = sum + DEC[i]^2;
	RMS_time = sqrt(sum / dec_num);
	return RMS_time;
}

template<typename T>
double *Data_preprocess<T>::Freq_dom(T *DEC, loadfile<T> dec_num) //��Ҫ��0
{
	Data_preprocess h;
	h.set_num0(int &dec_num, int *&DEC);
	int N_add = dec_num;
	std::vector<double> dec;
	dec = DEC;
	dft_plan<u32> plan(dec_num);
	univector<u32> temp(plan.temp_size);
	plan.execute(freq, dec, temp, false); 
	return freq;
}

template<typename T>
double Data_preprocess<T>::Freq_cacul_fundamental(univector<double>* freq,double samplerate, double freq_basic)
{
	Data_preprocess h;

	double fs = h.set_samplerate(samplerate);//������
	double fre_input = h.set_freq_basic(freq_basic);//��Ƶ

	double F = fs / N; //Ƶ�ʷֱ���
	int i = fre_input/ F; //��Ƶ��
	int sum = freq[i].real() ^ 2 + freq.imag() ^ 2;
	snr_fund_freq = sqrt(sum);
	return snr_fund_freq;
}

template<typename T>
double Data_preprocess<T>::Freq_cacul_harmonic(univector<double> * freq, double samplerate, double freq_basic)
{
	Data_preprocess h;
	h.set_num0(int &dec_num, int *&DEC);
	int N = dec_num;
	std::vector<double> dec;
	dec = DEC;

	double fs = h.set_samplerate(samplerate);//������
	double fre_input = h.set_freq_basic(freq_basic);//��Ƶ

	double F = fs / N;
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

template<typename T>
double Data_preprocess<T>::Freq_cacul_har(univector<double> * freq, double samplerate, double freq_basic)
{
	Data_preprocess h;
	h.set_num0(int &dec_num, int *&DEC);
	int N = dec_num;
	std::vector<double> dec;
	dec = DEC;

	double fre_input = h.set_freq_basic(freq_basic);//��Ƶ
	double F = fs / N; //Ƶ�ʷֱ���
	int bas = fre_input / F; //��Ƶ��
	double sum = 0;

	int a[1000];
	int j = 0;
	for (int i = 1; i < N / 2 - 1; i++)
		if (i%bas == 0)
			a[j] = i;//������Ƶλ��
	for (int i = 1; i <= j; i++)
		sum = freq[a[i]].real() ^ 2 + freq[a[i]].imag() ^ 2;
	thd_harm = sqrt(sum);
	return thd_harm;
}
