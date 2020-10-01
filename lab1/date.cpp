//
//  date.cpp
//  Lab1_xcode
//
//  Created by Илья Ильин on 21.09.2020.
//

#include "date.hpp"

namespace NDate {
    TDate::TDate() {
        day_ = 0;
        month_ = 0;
        year_ = 0;
        dateString_ = "0.0.0";
    }

    TDate::TDate(std::string& inputLine) {
        SetDate(inputLine);
    }
    
    TDate::~TDate() {
        day_ = 0;
        month_ = 0;
        year_ = 0;
        dateString_ = "";
    }

    int TDate::GetDay() const {
        return day_;
    }
    int TDate::GetMonth() const {
        return month_;
    }
    int TDate::GetYear() const {
        return year_;
    }

    int TDate::GetDigit(const int& idx) {
        switch (idx) {
            case 0:
                return day_ + month_ * 100;
            case 1:
                return year_;
            default:
                return -1;
        }
    }

    std::string TDate::GetDate() const {
        return dateString_;
    }

    void TDate::SetDay(const int& day) {
        day_ = day;
    }
    void TDate::SetMonth(const int& month) {
        month_ = month;
    }
    void TDate::SetYear(const int& year) {
        year_ = year;
    }
     
    void TDate::SetDate(const std::string& dateString) {
        dateString_ = dateString;
        int idx = 0;
        int state = 0;
        day_ = 0;
        month_ = 0;
        year_ = 0;
        while (idx < dateString_.length()) {
            if (dateString_[idx] == '.') {
                ++state;
                ++idx;
            }
            if (state == 0) {
                day_ = day_ * 10 + (dateString_[idx] - '0');
                ++idx;
            } else if (state == 1) {
                month_ = month_ * 10 + (dateString_[idx] - '0');
                ++idx;
            } else {
                year_ = year_ * 10 + (dateString_[idx] - '0');
                ++idx;
            }
        }
    }
} // namespace NDate

std::ostream& operator<<(std::ostream& output, const NDate::TDate& date) {
    output << date.GetDate();
    return output;
}
std::istream& operator>>(std::istream& input, NDate::TDate& date) {
    std::string stringInput;
    input >> stringInput;
    date.SetDate(stringInput);
    return input;
}
