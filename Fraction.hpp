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
#include <sstream>
using namespace std;


class Fraction {
public:
    Fraction();                             // default constructor
    Fraction(int nn);
    Fraction(int nn, int dd);
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

    void set_numerator(int nn);
    void set_denominator(int dd);

    void reduce();

private:
    int numerator;      // the sign of the whole fraction is here
    int denominator;    // always positive
};


Fraction reciprocal(const Fraction& fr);
Fraction negative(const Fraction& fr);

string mixed(const Fraction& fr);
string expanded(const Fraction& fr, int new_denominator);

ostream& operator<<(ostream& os, const Fraction& fr);
istream& operator>>(istream& is, Fraction& fr);


#endif /* FRACTION_HPP */

