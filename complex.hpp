/*
class to represent complex numbers
*/
#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <cmath>

class Complex
{
private:
    double real;
    double imag;

public:
    Complex(double real = 0, double imag = 0) : real(real), imag(imag) {}

    double getReal() const;

    double getImag() const;

    double magnitude() const;

    Complex operator+(const Complex &other) const;

    Complex operator-(const Complex &other) const;

    Complex operator*(const Complex &other) const;

    Complex operator/(const Complex &other) const;

    bool operator==(const Complex& other) const;

    bool operator!=(const Complex& other) const;

    bool operator<(const Complex& other) const;

    bool operator>(const Complex& other) const;

    bool operator<=(const Complex& other) const;

    bool operator>=(const Complex& other) const;

    friend std::ostream &operator<<(std::ostream &out, const Complex &c);
};

#endif // COMPLEX_HPP