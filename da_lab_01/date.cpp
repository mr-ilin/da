//
//  date.cpp
//  Lab1_xcode
//
//  Created by Илья Ильин on 21.09.2020.
//

#include "date.hpp"

namespace NDate {
    TDate::TDate() {
        day = 0;
        month = 0;
        year = 0;
        dateString = "0.0.0";
    }

    TDate::TDate(std::string& inputLine) {
        SetDate(inputLine);
    }
    
    TDate::~TDate() {
        day = 0;
        month = 0;
        year = 0;
        dateString = "";
    }

    int TDate::GetDay() const {
        return day;
    }
    int TDate::GetMonth() const {
        return month;
    }
    int TDate::GetYear() const {
        return year;
    }

    int TDate::GetDigit(const int& idx) {
        switch (idx) {
            case 0:
                return day + month * 100;
            case 1:
                return year;
            default:
                return -1;
        }
    }

    std::string TDate::GetDate() const {
        return dateString;
    }

    void TDate::SetDay(const int& newDay) {
        day = newDay;
    }
    void TDate::SetMonth(const int& newMonth) {
        month = newMonth;
    }
    void TDate::SetYear(const int& newYear) {
        year = newYear;
    }
     
    void TDate::SetDate(const std::string& newDate) {
        dateString = newDate;
        int idx = 0;
        int state = 0;
        day = 0;
        month = 0;
        year = 0;
        while (idx < dateString.length()) {
            if (dateString[idx] == '.') {
                ++state;
                ++idx;
            }
            if (state == 0) {
                day = day * 10 + (dateString[idx] - '0');
                ++idx;
            } else if (state == 1) {
                month = month * 10 + (dateString[idx] - '0');
                ++idx;
            } else {
                year = year * 10 + (dateString[idx] - '0');
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
