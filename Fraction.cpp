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
    numerator{0}, denominator{1}
{ }

Fraction::Fraction(int nn) :
    numerator{nn}, denominator{1}
{ }

Fraction::Fraction(int nn, int dd) :
    numerator{abs(nn)}, denominator{abs(dd)}
{
    if(dd == 0)
        throw invalid_argument("divide by zero");
    if(nn < 0)
        numerator *= -1;
    if(dd < 0)
        numerator *= -1;
    reduce();
}

Fraction::Fraction(const Fraction& other) :
    numerator{other.numerator}, denominator{other.denominator}
{ }

/*******************************************************************
 *                           operators                             *
 *******************************************************************/

Fraction& Fraction::operator+=(const Fraction& other) {
    int common = lcm(denominator, other.denominator);
    numerator *= common / denominator;
    numerator += other.numerator * (common / other.denominator);
    denominator = common;
    reduce();
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& other) {
    return operator+=(negative(other));
}

Fraction& Fraction::operator*=(const Fraction& other) {
    numerator *= other.numerator;
    denominator *= other.denominator;
    reduce();
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
    return numerator == other.numerator && denominator == other.denominator;
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


void Fraction::set_numerator(int nn) {
    numerator = nn;
    reduce();
}

void Fraction::set_denominator(int dd){
    if(dd == 0)
        throw invalid_argument("divide by zero");
    denominator = dd;
    reduce();
}


void Fraction::reduce() {
    int g = gcd(numerator, denominator);
    while(g > 1) {
        numerator /= g;
        denominator /= g;
        g = gcd(numerator, denominator);
    }
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

// TODO try to return a representation as expanded with new denominator ndd
string expanded(const Fraction& fr, int ndd) {
    ostringstream os;
    int nn = fr.get_numerator();
    int dd = fr.get_denominator();
    char sign = '\0';
    if(nn < 0) {
        sign = '-';
        nn = abs(nn);
    }
    if(dd == ndd)
        os << fr;
    else {
        int common = lcm(dd, ndd);
        nn *= common / dd;
        if(nn % (common/ndd) == 0) {
            nn /= (common/ndd);
            dd = ndd;
            os << sign << setw(2) << nn << "/" << setw(2) << dd;
        }
        else
            os << fr;
    }

    return os.str();
}

// return a representation as a mixed number
string mixed(const Fraction& fr) {
    ostringstream os;
    int nn = fr.get_numerator();
    int dd = fr.get_denominator();
    int ww = 0;
    char sign = '\0';
    if(nn < 0) {
        sign = '-';
        nn = abs(nn);
    }
    if(nn < dd)
        os << fr;
    else {
        ww = nn / dd;
        nn = nn % dd;
        os << sign << setw(2) << ww;
        if(nn > 0)
            os << ' ' << setw(2) << nn << "/" << setw(2) << dd;
    }
    return os.str();
}


// TODO implement mixed_and_expanded()


ostream& operator<<(ostream& os, const Fraction& fr) {
    int nn = fr.get_numerator();
    if(nn < 0) {
        os << '-';
        nn = abs(nn);
    }
    return os << setw(2) << nn << "/" << setw(2) << fr.get_denominator();
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
