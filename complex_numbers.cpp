#include "complex_numbers.h"
#include <cmath>
#include <iostream>

complex_numbers::complex_numbers(double r, double i) : real(r), imaginary(i) {}

double complex_numbers::get_real() const {
    return real;
}

double complex_numbers::get_imaginary() const {
    return imaginary;
}

double complex_numbers::abs(){
    return std::sqrt(real * real + imaginary * imaginary);
}

complex_numbers& complex_numbers::operator+=(const complex_numbers& other){
    real += other.real;
    imaginary += other.imaginary;
    return *this;
}

complex_numbers& complex_numbers::operator-=(const complex_numbers& other){
    real -= other.real;
    imaginary -= other.imaginary;
    return *this;
}

complex_numbers& complex_numbers::operator*=(const complex_numbers& other){
    double new_real = real * other.real - imaginary * other.imaginary;
    double new_imaginary = real * other.imaginary + other.real * imaginary;
    real = new_real;
    imaginary = new_imaginary;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const complex_numbers& complex){
    if(complex.imaginary >= 0){
        out << complex.real << "+" << complex.imaginary << "i";
    } else {
        out << complex.real << complex.imaginary << "i";
    }
    return out;
}

complex_numbers const operator+(const complex_numbers& l, const complex_numbers& r){
    return complex_numbers(l.get_real() + r.get_real(), l.get_imaginary() + r.get_imaginary());
}

complex_numbers const operator-(const complex_numbers& l, const complex_numbers& r){
    return complex_numbers(l.get_real() - r.get_real(), l.get_imaginary() - r.get_imaginary());
}

complex_numbers const operator*(const complex_numbers& l, const complex_numbers& r){
    return complex_numbers(
        l.get_real() * r.get_real() - l.get_imaginary() * r.get_imaginary(),
        l.get_real() * r.get_imaginary() + r.get_real() * l.get_imaginary()
    );
}


