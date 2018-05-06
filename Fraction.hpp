/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Fraction.hpp
 * Author: Ronen Gilead-Raz <ronengi@gmail.com>
 *
 * Created on May 6, 2018, 1:15 PM
 */

#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <numeric>
using namespace std;


class Fraction {
public:
    Fraction();                             // default constructor
    Fraction(int nn);
    Fraction(int nn, int dd);
    Fraction(int nn, int dd, int ww);
    Fraction(const Fraction& other);        // copy constructor

    Fraction& operator+=(const Fraction& other);
    Fraction& operator-=(const Fraction& other);
    Fraction& operator*=(const Fraction& other);
    Fraction& operator/=(const Fraction& other);

    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;

    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;

    bool operator>(const Fraction& other) const;
    bool operator<(const Fraction& other) const;

    int get_numerator() const;
    int get_denominator() const;
    int get_whole() const;

    void set_numerator(int nn);
    void set_denominator(int dd);
    void set_whole(int ww);

    void reduce();
    void mixed();
    void unmixed();

private:
    int numerator;
    int denominator;
    int whole;
};


Fraction reciprocal(const Fraction& fr);
Fraction negative(const Fraction& fr);


ostream& operator<<(ostream& os, const Fraction& fr);
istream& operator>>(istream& is, Fraction& fr);


#endif /* FRACTION_HPP */

