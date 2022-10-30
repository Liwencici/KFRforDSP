#pragma once
#ifndef DATA_PREPROCESS_H_
#define DATA_PREPROCESS_H_
#include <kfr.h>
#include "loadfile.h"
#include "dft.hpp"

using namespace kfr;

//dec_numΪ�����ʵ�ʲ����㣬���ݲ���Ƶ�ʼ���ó�ʱ������
//����ʱ���ϵ�RMSֵ
//����Ƶ����ÿ��Ƶ�ʶ�Ӧ�ķ�ֵ�Ͳ�����������ṹ�壩,�����ǰ���г����DC֮�������Ƶ�ʷ�����RMS����

template <typename T >
class Data_preprocess 
{
private:
	double samplerate; //������
	double freq_basic; //�����룩����Ƶ��

	loadfile<T> dec_num;  //���������
	loadfile<T> DEC; //ʮ�����ļ�����0��
	int N=0; //2��n���ݵı���������
	//loadfile<T> data; //û��0��ֵ//int[]
	
	int dec_num_0; //��0��Ĳ��������
	
	int RMS_time; //ʱ���ϵ�RMSֵ
	double snr_pre;//Ƶ���ϵĳ�ǰ5��г����DC֮�����������������RMS
	double snr_fund_freq;//����(һ��г��)��RMS
	univector<complex<double>> freq; //freqΪ�޷���double����
									 
	//univector<complex<double>> data_val; //data-->data_val
	
	double thd_harm;//THDг��
	//Ƶ���źŵ�Real Part��ʵ������Imag Part���鲿����Mag����ֵ����Angle����λ�ǣ�
	//U8 char ;U16 short int; U32 int U64 
public:
	//snr_set
	void set_num0(T &dec_num,T *&DEC);//�����㲹0
    void set_samplerate(double x);
	void set_freq_basic(double x);

	//snr_get
	
	//snr_caculate
	bool N_num(int n); //�ж�dec_num�Ƿ�Ϊ2���ݴα�
	int Time_dom(T *data_val, loadfile<T>dec_num);//����ֵΪʱ���ϵ�RMSֵ
	double *Freq_dom(T *data_val, loadfile<T> dec_num);//FFT:����ֵΪƵ���ϵļ������freq[i]=���
	double Freq_cacul_fundamental(univector<double> *freq, double samplerate, double freq_basic);//��ƵRMS
	double Freq_cacul_harmonic(univector<double> *freq, double samplerate, double freq_basic); //��DC+5��ֱ��֮���г��

	//THD
	double Freq_cacul_har(univector<double> *freq, double samplerate, double freq_basic);//г��

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

