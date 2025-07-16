#include "utils.hpp"

#include <iostream>


void TODO() {
    std::cout << "TODO" << std::endl;
}

std::string POWERS_OF_1000[102] = {
    "K", "M", "B", "T", "Qa", "Qi", "Sx", "Sp", "Oc", "No",
    "Dc", "Ud", "Dd", "Td", "Qad", "Qid", "Sxd", "Spd", "Ocd", "Nod", 
    "Vg", "Uvg", "Dvg", "Tvg", "Qavg", "Qivg", "Sxvg", "Spvg", "Ocvg", "Novg", 
    "Tg", "Utg", "Dtg", "Ttg", "Qatg", "Qitg", "Sxtg", "Sptg", "Octg", "Notg", 
    "Qag", "Uqag", "Dqag", "Tqag", "Qaqag", "Qiqag", "Sxqag", "Spqag", "Ocqag", "Noqag", 
    "Qig", "Uqig", "Dqig", "Tqig", "Qaqig", "Qiqig", "Sxqig", "Spqig", "Ocqig", "Noqig", 
    "Sxg", "Usxg", "Dsxg", "Tsxg", "Qasxg", "Qisxg", "Sxsxg", "Spsxg", "Ocsxg", "Nosxg", 
    "Spg", "Uspg", "Dspg", "Tspg", "Qaspg", "Qispg", "Sxspg", "Spspg", "Ocspg", "Nospg", 
    "Ocg", "Uocg", "Docg", "Tocg", "Qaocg", "Qiocg", "Sxocg", "Spocg", "Ococg", "Noocg", 
    "Nog", "Unog", "Dnog", "Tnog", "Qanog", "Qinog", "Sxnog", "Spnog", "Ocnog", "Nonog",
    "Dc", "UDc"
};

double four_digits(double value) {
    if (value >= 1000 || value < 1) {
        return value;
    }
    if (value < 10) {
        return floor(value * 1000) / 1000;
    }
    if (value < 100) {
        return floor(value * 100) / 100;
    }
    return floor(value * 10) / 10;
}

std::string double_to_string(double value) {
    if (value < 1000000) {
        return std::format("{}", (int)floor(value));
    }
    int power_of_1000 = floor(log10(value) / 3);
    double before_indicator = value / pow(1000, power_of_1000);
    std::string indicator = POWERS_OF_1000[power_of_1000];
    return std::format("{} {}", four_digits(before_indicator), indicator);
}