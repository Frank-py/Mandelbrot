#pragma once
#include <cmath>
#include <complex>
#include <vector>
class Math {
public:
  // std::complex<double> checkifinmandel(std::complex<double> z,
  // std::complex<double> c, int iterations);
  std::complex<double> funcNewton1(std::complex<double> z);
  std::complex<double> funcNewton2(std::complex<double> z);
  int generalNewtonFractalRecursive(std::complex<double> z, int numFucn,
                                    int iterations);
  int checkifinmandel(std::complex<double> c, int iterations, double limit);

  std::vector<std::vector<std::complex<double>>> roots = {
      {std::complex<double>(1, 0), std::complex<double>(-0.5, std::sqrt(3) / 2),
       std::complex<double>(-0.5, -std::sqrt(3) / 2)},
      {std::complex<double>(1, 0), std::complex<double>(-1, 0),
       std::complex<double>(0, 1), std::complex<double>(0, -1),
       std::complex<double>(-std::sqrt(2), -std::sqrt(2)),
       std::complex<double>(+std::sqrt(2), +std::sqrt(2)),
       std::complex<double>(+std::sqrt(2), -std::sqrt(2)),
       std::complex<double>(-std::sqrt(2), +std::sqrt(2))}};

private:
  float toleranceNewton = 0.0001;
  std::complex<double> (Math::*funcList[2])(std::complex<double> z) = {
      &Math::funcNewton1, &Math::funcNewton2};
};
