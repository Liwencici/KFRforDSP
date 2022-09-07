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
class Data_preprocess :
{
private:
	loadfile samplerate; //������
	loadfile dec_num;  //���������
	loadfile<T> data; 
	int RMS_time; //ʱ���ϵ�RMSֵ
	int snr_pre;//Ƶ���ϵĳ�ǰ5��г����DC֮�����������������RMS
	univector<complex<double>, dec_num> freq; //freqΪ��Сdec_num���޷���double����
	univector<complex<double>, dec_num> data_val; //data-->data_val
	
	//Ƶ���źŵ�Real Part��ʵ������Imag Part���鲿����Mag����ֵ����Angle����λ�ǣ�
	//U8 char ;U16 short int; U32 int U64 
public:
	loadfile get_num();
	loadfile get_samplerate();
	loadfile get_data(T *data);
	int Time_dom(T *data_val, loadfile<T> dec_num);//����ֵΪʱ���ϵ�RMSֵ
	int Freq_dom(T *data_val, loadfile<T> dec_num);//����ֵΪƵ���ϵļ������freq[i]=���
	int Freq_cacul(univector<double> *freq, loadfile<T> dec_num);
	template<typename T>
};

template <typename T> // data type, float or double
struct dft_plan
{
	void execute(complex<T>* out,
		const complex<T>* in,
		u8* temp,
		bool inverse = false) const;
	void execute(univector<complex<T>, N>& out,
		const univector<const complex<T>, N>& in,
		univector<u8, N2>& temp,
		bool inverse = false) const;
};
#endif

