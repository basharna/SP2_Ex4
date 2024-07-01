/*
ID: 212487144
Email: nbashar4@gmail.com
*/

#include "complex.hpp"

using namespace std;

double Complex::getReal() const
{
    return real;
}

double Complex::getImag() const
{
    return imag;
}

double Complex::magnitude() const
{
    return sqrt(real * real + imag * imag);
}

Complex Complex::operator+(const Complex &other) const
{
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex &other) const
{
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(const Complex &other) const
{
    return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
}

Complex Complex::operator/(const Complex &other) const
{
    double denominator = other.real * other.real + other.imag * other.imag;
    return Complex((real * other.real + imag * other.imag) / denominator, (imag * other.real - real * other.imag) / denominator);
}

bool Complex::operator==(const Complex &other) const
{
    return real == other.real && imag == other.imag;
}

bool Complex::operator!=(const Complex &other) const
{
    return !(*this == other);
}

bool Complex::operator<(const Complex &other) const
{
    return magnitude() < other.magnitude();
}

bool Complex::operator>(const Complex &other) const
{
    return magnitude() > other.magnitude();
}

bool Complex::operator<=(const Complex &other) const
{
    return magnitude() <= other.magnitude();
}

bool Complex::operator>=(const Complex &other) const
{
    return magnitude() >= other.magnitude();
}

ostream &operator<<(ostream &out, const Complex &c)
{
    out << c.real << " + " << c.imag << "i";
    return out;
}