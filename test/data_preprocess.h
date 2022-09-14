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
	loadfile<T> samplerate; //������
	loadfile<T> dec_num;  //���������
	loadfile<T> DEC; //ʮ�����ļ�����0��
	int N=0; //2��n���ݵı���������
	loadfile<T> data; //û��0��ֵ
	loadfile<T> freq_basic; //����Ƶ��
	int RMS_time; //ʱ���ϵ�RMSֵ
	float snr_pre;//Ƶ���ϵĳ�ǰ5��г����DC֮�����������������RMS
	float snr_fund_freq;//����(һ��г��)��RMS
	univector<complex<double>> freq; //freqΪ��Сdec_num���޷���double����
	univector<complex<double>> data_val; //data-->data_val
	
	//Ƶ���źŵ�Real Part��ʵ������Imag Part���鲿����Mag����ֵ����Angle����λ�ǣ�
	//U8 char ;U16 short int; U32 int U64 
public:
	loadfile<T> get_num(T dec_num,T *DEC);
	loadfile<T> get_samplerate();
	loadfile<T> get_freq_basic();
	loadfile<T> get_data(T *data);
	bool N_num(int n); //�ж�dec_num�Ƿ�Ϊ2���ݴα�
	int Time_dom(T *data_val, loadfile<T>dec_num);//����ֵΪʱ���ϵ�RMSֵ
	int Freq_dom(T *data_val, loadfile<T> dec_num);//����ֵΪƵ���ϵļ������freq[i]=���
	int Freq_cacul_fundamental(univector<double> *freq,loadfile<T> freq_basic);//��ƵRMS
	int Freq_cacul_harmonic(univector<double> *freq,loadfile<T> freq_basic); //��DC+5��ֱ��֮���г��
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

