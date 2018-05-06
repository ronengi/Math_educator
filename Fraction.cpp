/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "Fraction.hpp"

// TODO deal with negative parts correctly

/*******************************************************************
 *                         constructors                            *
 *******************************************************************/

Fraction::Fraction() :
    numerator{0}, denominator{1}, whole{0}
{ }

Fraction::Fraction(int nn) :
    numerator{nn}, denominator{1}, whole{0}
{ }

Fraction::Fraction(int nn, int dd) :
    numerator{nn}, denominator{dd}, whole{0}
{
        if(dd == 0)
            throw invalid_argument("divide by zero");
}

Fraction::Fraction(int nn, int dd, int ww) :
    numerator{nn}, denominator{dd}, whole{ww}
{
        if(dd == 0)
            throw invalid_argument("divide by zero");
}

Fraction::Fraction(const Fraction& other) :
    numerator{other.numerator}, denominator{other.denominator}, whole{other.whole}
{ }

/*******************************************************************
 *                           operators                             *
 *******************************************************************/

Fraction& Fraction::operator+=(const Fraction& other) {
    int common = lcm(denominator, other.denominator);
    numerator *= common / denominator;
    numerator += other.numerator * (common / other.denominator);
    denominator = common;
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& other) {
    return operator+=(negative(other));
}

Fraction& Fraction::operator*=(const Fraction& other) {
    numerator *= other.numerator;
    denominator *= other.denominator;
    return *this;
}

Fraction& Fraction::operator/=(const Fraction& other) {
    return operator*=(reciprocal(other));
}

Fraction Fraction::operator+(const Fraction& other) const {
    Fraction ff1{*this};
    ff1 += other;
    return ff1;
}

Fraction Fraction::operator-(const Fraction& other) const {
    return (*this) + negative(other);
}

Fraction Fraction::operator*(const Fraction& other) const {
    Fraction ff1{*this};
    ff1 *= other;
    return ff1;
}

Fraction Fraction::operator/(const Fraction& other) const {
    return (*this) * reciprocal(other);
}

bool Fraction::operator==(const Fraction& other) const {
    return((numerator * other.denominator) == (other.numerator * denominator));
}

bool Fraction::operator!=(const Fraction& other) const {
    return !(operator==(other));
}

bool Fraction::operator>(const Fraction& other) const {
    return((numerator * other.denominator) > (other.numerator * denominator));
}

bool Fraction::operator<(const Fraction& other) const {
    return((numerator * other.denominator) < (other.numerator * denominator));
}


/*******************************************************************
 *                            methods                              *
 *******************************************************************/

int Fraction::get_numerator() const {
    return numerator;
}

int Fraction::get_denominator() const {
    return denominator;
}

int Fraction::get_whole() const {
    return whole;
}

void Fraction::set_numerator(int nn) {
    numerator = nn;
}

void Fraction::set_denominator(int dd){
    if(dd == 0)
        throw invalid_argument("divide by zero");
    denominator = dd;
}

void Fraction::set_whole(int ww){
    whole = ww;
}


void Fraction::reduce() {
    int g = gcd(numerator, denominator);
    while(g > 1) {
        numerator /= g;
        denominator /= g;
        g = gcd(numerator, denominator);
    }
}

void Fraction::mixed() {
    if(numerator < denominator) {
        whole = 0;
        return;
    }
    if(numerator == denominator) {
        whole = 1;
        numerator = 0;
        return;
    }
    if(numerator > denominator) {
        whole = numerator / denominator;
        numerator = numerator % denominator;
        return;
    }

}

void Fraction::unmixed() {
    if(whole == 0)
        return;
    numerator += whole * denominator;
    whole = 0;
}


/*******************************************************************
 *                            helpers                              *
 *******************************************************************/

Fraction reciprocal(const Fraction& fr) {
   return Fraction{fr.get_denominator() ,fr.get_numerator()};
}

Fraction negative(const Fraction& fr) {
   return Fraction{-fr.get_numerator() ,fr.get_denominator()};
}


/*******************************************************************
 *                             i/o                                 *
 *******************************************************************/

ostream& operator<<(ostream& os, const Fraction& fr) {
    if(fr.get_whole() != 0)
        os << setw(2) << fr.get_whole() << " ";
    return os << setw(2) << fr.get_numerator() << "/" << setw(2) << fr.get_denominator();
 }

istream& operator>>(istream& is, Fraction& fr) {
    int nn, dd;
    char op;
    is >> nn >> op >> dd;
    if(!is || op != '/' || dd == 0) {
        is.clear(ios_base::failbit);
        throw invalid_argument("invalid fraction");
    }

    fr.set_numerator(nn);
    fr.set_denominator(dd);

    return is;
}
