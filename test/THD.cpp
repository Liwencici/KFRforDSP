#include"THD.h"
#include <vector>
#include <kfr.h>
#include <vector>
#include"data_preprocess.h"

using namespace kfr;
template<typename T>
double THD<T>::thd_Cacu(Data_preprocess<T> thd_harm, Data_preprocess<T> snr_fund_freq)
{
	thd_fin = thd_harm / snr_fund_freq;
	return thd_fin;
}