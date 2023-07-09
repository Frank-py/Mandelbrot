#pragma once
#include <complex>
class Math
{
public:
	//std::complex<double> checkifinmandel(std::complex<double> z, std::complex<double> c, int iterations);
	std::complex<double> checkifinmandel(
		std::complex<double> z,
		std::complex<double> c,
		int iterations,
		double limit = 4.0
	);
	
private:
	
};

