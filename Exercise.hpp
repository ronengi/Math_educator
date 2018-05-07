/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Exercise.hpp
 * Author: Ronen Gilead-Raz <ronengi@gmail.com>
 *
 * Created on May 7, 2018, 7:43 PM
 */

#ifndef EXERCISE_HPP
#define EXERCISE_HPP


#include <iostream>
#include "Fraction.hpp"
using namespace std;


class Exercise {
public:
    Exercise();

private:
    Fraction fr1, fr2, ans;
    char action;
    bool answered, correct;
};


ostream& operator<<(ostream& os, const Exercise& ex);


#endif /* EXERCISE_HPP */
