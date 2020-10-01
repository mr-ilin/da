//
//  date.hpp
//  Lab1_xcode
//
//  Created by Илья Ильин on 21.09.2020.
//

#ifndef date_hpp
#define date_hpp

#include <iostream>

namespace NDate {
    class TDate {
    public:
        TDate();
        TDate(std::string& dateString);
        ~TDate();
        
        int GetDigit(const int& idx);
        int GetDay() const;
        int GetMonth() const;
        int GetYear() const;
        std::string GetDate() const;
        
        void SetDay(const int& day);
        void SetMonth(const int& month);
        void SetYear(const int& year);
        void SetDate(const std::string& inputLine);
    private:
        int day_;
        int month_;
        int year_;
        std::string dateString_;
    };
} // namespace NDate
    
std::ostream& operator<<(std::ostream& output, const NDate::TDate& date);
std::istream& operator>>(std::istream& input, NDate::TDate& date);

#endif /* date_hpp */
