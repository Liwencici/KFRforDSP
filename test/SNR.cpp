#include"SNR.h"
#include <vector>
#include <kfr.h>
#include <vector>
#include"data_preprocess.h"

using namespace kfr;
template <typename T>
 Data_preprocess<T> SNR<T>::Snr(Data_preprocess<T> snr_pre, Data_preprocess<T> snr_fund_freq)
{
	 snr = snr_fund_freq / snr_pre;
	 return snr;
}