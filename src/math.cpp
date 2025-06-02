#include "Math.hpp"
#include "iostream"
#include <algorithm>
#include <complex>
#include <vector>
int Math::checkifinmandel(std::complex<double> c, int iterations,
                          double limit) {

  // std::vector<std::complex<double>> previousInnerZ = {z};
  std::complex<double> z = std::complex<double>(0, 0);
  double z_abs = 0;
  for (int j = 0; j < iterations; j++) {
    if (z_abs > limit) {
      return j;
    }
    z = z * z + c;
    z_abs = std::norm(z);
    // if (std::find(previousInnerZ.begin(), previousInnerZ.end(), z) !=
    //     previousInnerZ.end()) {
    //   return 0;
    // }
    // previousInnerZ.push_back(z);
  }

  if (z_abs < 2) {
    return 0;
  }
  return iterations;
}
// check for repeating patterns cuz if not thats inneficient

std::complex<double> Math::funcNewton1(std::complex<double> z) {
  return (std::pow(z, 3) - std::complex<double>(1, 0)) /
         (std::complex<double>(3, 0) * std::pow(z, 2));
}

std::complex<double> Math::funcNewton2(std::complex<double> z) {
  return (std::pow(z, 8) + std::pow(z, 4) * std::complex<double>(15, 0) -
          std::complex<double>(16, 0)) /
         (std::complex<double>(8, 0) * std::pow(z, 7) +
          std::complex<double>(60, 0) * std::pow(z, 3));
}
int Math::generalNewtonFractalRecursive(std::complex<double> z, int numFunc,
                                        int iterations) {
  int rootNum = 1;
  for (int i = 0; i < iterations; i++) {
    rootNum = 1;
    for (std::complex<double> root : roots[numFunc]) {
      if (std::norm(z - root) < toleranceNewton) {
        return rootNum;
      }
      rootNum += 1;
    }
    z = z - (this->*funcList[numFunc])(z);
  }
  return 0;
}
