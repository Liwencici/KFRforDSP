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
	loadfile samplerate;
	loadfile dec_num;
	loadfile data; //loadfile �����
	int RMS_time; //ʱ���ϵ�RMSֵ
	univector<complex<double>, dec_num> freq; //freqΪ��Сdec_num���޷���double����
	univector<complex<double>, dec_num> data_val;
	//Ƶ���źŵ�Real Part��ʵ������Imag Part���鲿����Mag����ֵ����Angle����λ�ǣ�
	//U8 char ;U16 short int; U32 int U64 
public:
	loadfile get_num();
	loadfile get_samplerate();
	loadfile get_data();
	int Time_dom(Data_preprocess &data);
	int Freq_dom(Data_preprocess &data);
};

template <typename T> // data type, float or double
struct dft_plan
{
	dft_plan(size_t size);
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

