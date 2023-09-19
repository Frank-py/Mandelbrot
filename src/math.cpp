#include "Math.hpp"
#include "iostream"
std::complex<double> Math::checkifinmandel(std::complex<double> z, std::complex<double> c, int iterations, int allit, double limit) {
    double z_abs = std::norm(z);
    if (iterations == 0 || z_abs > limit) {
        return std::complex<double>(z_abs > limit ? 0.0 : 1.0, allit-iterations);
    }
    if (real(z) == 0.0 && imag(z) == 0.0) {
        return std::complex<double>(1.0, allit-iterations);
    }
    return checkifinmandel(z*z + c, c, iterations - 1, allit, limit);
}
// check for repeating patterns cuz if not thats inneficient
