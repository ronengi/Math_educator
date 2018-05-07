/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Ronen Gilead-Raz <ronengi@gmail.com>
 *
 * Created on May 6, 2018, 1:11 PM
 */

#include <iostream>
#include <random>
#include <chrono>
#include "Fraction.hpp"
using namespace std;

int rand(int min, int max) {
    auto start = std::chrono::system_clock::now().time_since_epoch().count();
    // cout << start << "\n\n";
    static default_random_engine ran{start};
    return uniform_int_distribution<>{min, max}(ran);
}

char rand_action() {
    int i = rand(1, 3);
    switch(i) {
    case 1:
        return '+';
    case 2:
        return '*';
    case 3:
        return '-';
    default:
        return '/';
    }
    return '+';
}


Fraction binary_action(const Fraction& ff1, const Fraction& ff2, char action) {
    switch(action) {
    case '+':
        return ff1 + ff2;
    case '-':
        return ff1 - ff2;
    case '*':
        return ff1 * ff2;
    case '/':
        return ff1 / ff2;
    default:
        return ff1 + ff2;
    }
    return ff1 + ff2;
}


/*
 *
 */
int main(int argc, char** argv) {
    vector<Fraction> f1;
    vector<Fraction> f2;
    vector<char> action;
    vector<Fraction> answers;
    vector<bool> grades;

    for(int i = 0; i < 2; ++i) {
        Fraction ff1{rand(1, 10), rand(1, 10)};
        Fraction ff2{rand(1, 10), rand(1, 10)};
        if(ff1 < ff2) {
            f1.push_back(ff2);
            f2.push_back(ff1);
        }
        else {
            f1.push_back(ff1);
            f2.push_back(ff2);
        }
        action.push_back(rand_action());
    }

    Fraction ans1, ans2;
    for(int i = 0; i < f1.size(); ++i) {
        cout << "(" << setw(2) << i+1 << ") ";
        cout << f1[i] << "    " << action[i] << "    " << f2[i] << "    =   ? ";
        cin >> ans1;
        answers.push_back(ans1);
        ans2 = binary_action(f1[i], f2[i], action[i]);
        if(ans1 != ans2) {
            grades.push_back(false);
            cout << "\tSorry, the answer is: " << ans2 << ", \t\tNot: " << ans1;

        }
        else
            grades.push_back(true);
        cout << '\n';
    }

    double grade = 0.0;
    for(int i = 0; i < grades.size(); ++i)
        grade += grades[i] ? 1.0 : 0.0;

    grade /= grades.size();
    grade *= 100;
    cout << "\n\n" << "Your grade is: " << grade << "\n\n";


    return 0;
}
