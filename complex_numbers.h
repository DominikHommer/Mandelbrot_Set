#ifndef COMPLEX_NUMBERS_H
#define COMPLEX_NUMBERS_H

#include <iostream>

// Class to represent and manipulate complex numbers
class complex_numbers {
private:
    double real;     
    double imaginary;

public:
    // Constructor initializing a complex number with real and imaginary parts
    complex_numbers(double r, double i = 0);
    
    // Getters for the real and imaginary parts
    double get_real() const;
    double get_imaginary() const;

    // Method to compute the magnitude (absolute value) of the complex number
    double abs();

    // Operator overloads for +=, -=, and *= to perform arithmetic on complex numbers
    complex_numbers& operator+=(const complex_numbers& other);
    complex_numbers& operator-=(const complex_numbers& other);
    complex_numbers& operator*=(const complex_numbers& other);

    // Friend function to enable output stream overloading
    friend std::ostream& operator<<(std::ostream& out, const complex_numbers& complex);
};

// Non-member operator overloads for +, -, and * to perform arithmetic on complex numbers
complex_numbers const operator+(const complex_numbers& l, const complex_numbers& r);
complex_numbers const operator-(const complex_numbers& l, const complex_numbers& r);
complex_numbers const operator*(const complex_numbers& l, const complex_numbers& r);

#endif // COMPLEX_NUMBERS_H

