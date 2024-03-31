#include <iostream>
using namespace std;

class Date{
private:
    int year, month, day, hour, minute, second;
    bool isOurEra;

public:
    Date () : year(1960), month(1), day(1), hour(0), minute(0), second(0), isOurEra(true){}

    Date (int year, int month, int day, int hour, int minute, int second, bool isOurEra) {
        this->second = second % 60;
        minute += second / 60;
        this->minute = minute % 60;
        hour += minute / 60;
        this->hour = hour % 24;
        day += hour / 24;
        // 0 год беру за нашу эру
        if (year == 0) {
            this->isOurEra = true;
            this->year = 0;
        } else {
            this->isOurEra = isOurEra;
        }
        // отрицательный год - до н.э.
        if (year < 0) {
            this->isOurEra = !this->isOurEra;
            this->year = (-year);
        } else {
            this->year = year;
            this->isOurEra = isOurEra;
        }

        if ((month > 12) or (month < 1)) {
            this->year += ((month-1) / 12);
            if (month > 0){
                this->month = month - 12*(month/12);
                month = this->month;
            }
            if (month < 0) {
                month = !month;
                month = month - 12*(month/12);
                this->month = 12 - month;
            }
            if (month == 0) {
                this->month = 12;
            }
            if (year < 0) {
                this->isOurEra = !this->isOurEra;
                this->year = !this->year;
            }
        } else {
            this->month = month;
        }


        if ((day > 31) or (day < 1)){
            bool stipulation = false;
            while (!stipulation){
                switch (this->month){
                    //Январь
                    case 1:{
                        if (day > 31) {
                            this->month = 2;
                            day = day - 31;
                        } else if(day < 1){
                            this->month = 12;
                            this->year--;
                            day= 31 + day;
                        } else {
                            this->day = day;
                            stipulation = true;
                        }
                        break;
                    }
                    //Февраль
                    case 2: {
                        if ((this->year%4 == 0) or ((this->year%4 == 0) and (this->year%100 == 0) and (this->year%400 == 0))) { // високосный год
                            if(day > 29){
                                this->month = 3;
                                day = day - 29;
                            } else if (day < 1){
                                this->month=1;
                                day = 31 + day;
                            } else {
                                this->day = day;
                                stipulation = true;
                            }
                        } else {
                            // Невисокосный год
                            if(day > 28){
                                this->month = 3;
                                day = day - 28;
                            } else if (day < 1){
                                this->month=1;
                                day = 31 + day;
                            } else {
                                this->day = day;
                                stipulation = true;
                            }
                        }
                        break;
                    }
                    //Март
                    case 3:{
                        if (day > 31){
                            this->month = 4;
                            day = day - 31;
                        } else if (day < 1){
                            this->month = 2;
                            if ((this->year%4 == 0) or ((this->year%4 == 0) and (this->year%100 == 0) and (this->year%400 == 0))) {// високосный год
                                day = 29 + day;
                            } else { //невисокосный год
                                day = 28 + day;
                            }
                        } else {
                            this->day = day;
                            stipulation = true;
                        }
                        break;
                    }
                    //Апрель, июнь, сентябрь, ноябрь
                    case 4: case 6: case 9: case 11:{
                        if (day > 30){
                            this->month++;
                            day = day - 30;
                        } else if (day < 1){
                            this->month--;
                            day = 31 + day;
                        } else {
                            this->day = day;
                            stipulation = true;
                        }
                        break;
                    }
                    //Май, июль, октябрь
                    case 5: case 7: case 10: {
                        if (day > 31){
                            this->month++;
                            day = day - 31;
                        } else if (day < 1){
                            this->month--;
                            day = 30 + day;
                        } else {
                            this->day = day;
                            stipulation = true;
                        }
                        break;
                    }
                    //Август
                    case 8:{
                        if (day > 31) {
                            this->month=9;
                            day = day - 31;
                        } else if (day < 1){
                            this->month = 7;
                            day = 31 + day;
                        } else {
                            this->day = day;
                            stipulation = true;
                        }
                        break;
                    }
                    //Декабрь
                    case 12:{
                        if (day > 31){
                            this->year++;
                            this->month=1;
                            day = day - 31;
                        } else if (day < 1) {
                            this->month--;
                            day = 30 + day;
                        } else {
                            this->day = day;
                            stipulation = true;
                        }
                        break;
                    }
                }
            }

            if (year == 0) {
                this->isOurEra = true;
            }
            if (year < 0) {
                this->isOurEra = !this->isOurEra;
                this->year = -(this->year);
            }
        } else {
            this->day = day;
        }

    }

    Date add(int year, int month, int day, int hour, int minute, int second){
        return Date(this->year + year, this->month + month, this->day + day, this->hour + hour, this->minute + minute, this->second + second, this->isOurEra);
    }

    Date subtract(int year, int month, int day, int hour, int minute, int second){
        return Date(this->year - year, this->month - month, this->day - day, this->hour - hour, this->minute - minute, this->second - second, this->isOurEra);
    }

    friend ostream& operator<<(ostream& os, const Date& ec) { // перегрузка <<
        os << ec.isOurEra <<" " << ec.year << " " << ec.month << " " << ec.day << " " << ec.hour << " " << ec.minute << " " << ec.second << endl;
        return os;
    }

    Date operator=(const Date &other) {
        this->year = other.year;
        this->month = other.month;
        this->day = other.day;
        this->hour = other.hour;
        this->minute = other.minute;
        this->second = other.second;
        this->isOurEra = other.isOurEra;
    }
    bool operator==(const Date &two) const {
        bool answer = false;
        if (this->isOurEra == two.isOurEra){
            if (this->year == two.year){
                if (this->month == two.month){
                    if (this->day == two.day){
                        if (this->hour == two.hour){
                            if(this->minute == two.minute){
                                if (this->second == two.second){
                                    answer = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        return answer;
    }

    Date operator+(const Date &other){
        if (other.isOurEra == this->isOurEra) {
            return Date(this->year + other.year, this->month + other.month, this->day + other.day, this->hour + other.hour, this->minute + other.minute, this->second + other.second, this->isOurEra);
        } else {
            return Date(other.year-this->year, other.month-this->month, other.day-this->day, other.hour-this->hour, other.minute-this->minute, other.second-this->second, other.isOurEra);
        }
    }

    Date operator+=(const Date &other){
        if (other.isOurEra == this->isOurEra) {
            *this = Date(this->year + other.year, this->month + other.month, this->day + other.day, this->hour + other.hour, this->minute + other.minute, this->second + other.second, this->isOurEra);
        } else {
            *this = Date(other.year-this->year, other.month-this->month, other.day-this->day, other.hour-this->hour, other.minute-this->minute, other.second-this->second, other.isOurEra);
        }
    }

    Date operator-(const Date &other) {
        if (this->isOurEra != other.isOurEra) {
            return Date(this->year + other.year, this->month + other.month, this->day + other.day, this->hour + other.hour, this->minute + other.minute, this->second + other.second, this->isOurEra);
        } else {
            return Date(this->year - other.year, this->month - other.month, this->day - other.day,this->hour - other.hour, this->minute - other.minute, this->second - other.second, this->isOurEra);
        }
    }

    Date operator-=(const Date &other) {
        if (this->isOurEra != other.isOurEra) {
            *this = Date(this->year + other.year, this->month + other.month, this->day + other.day, this->hour + other.hour, this->minute + other.minute, this->second + other.second, this->isOurEra);
        } else {
            *this = Date(this->year - other.year, this->month - other.month, this->day - other.day,this->hour - other.hour, this->minute - other.minute, this->second - other.second, this->isOurEra);
        }
    }

    bool operator<(const Date &two) const {
        bool answer = false;
        if (this->isOurEra < two.isOurEra) {
            answer = true;
        } else if (this->isOurEra == two.isOurEra) {
            if (this->year < two.year) {
                answer = true;
            } else if (this->year == two.year) {
                if (this->month < two.month) {
                    answer = true;
                } else if (this->month == two.month) {
                    if (this->day < two.day) {
                        answer = true;
                    } else if (this->day == two.day) {
                        if (this->hour < two.hour) {
                            answer = true;
                        } else if (this->hour == two.hour) {
                            if (this->minute < two.minute) {
                                answer = true;
                            } else if (this->minute == two.minute) {
                                if (this->second < two.second) {
                                    answer = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (((this->isOurEra == two.isOurEra) and (this->isOurEra == false)) and (answer == true)) {
            answer = false;
        }
        return answer;
    }

    bool operator>(const Date &two) const {
        bool answer = false;
        if (this->isOurEra > two.isOurEra) {
            answer = true;
        } else if (this->isOurEra == two.isOurEra) {
            if (this->year > two.year) {
                answer = true;
            } else if (this->year == two.year) {
                if (this->month > two.month) {
                    answer = true;
                } else if (this->month == two.month) {
                    if (this->day > two.day) {
                        answer = true;
                    } else if (this->day == two.day) {
                        if (this->hour > two.hour) {
                            answer = true;
                        } else if (this->hour == two.hour) {
                            if (this->minute > two.minute) {
                                answer = true;
                            } else if (this->minute == two.minute) {
                                if (this->second > two.second) {
                                    answer = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (((this->isOurEra == two.isOurEra) and (this->isOurEra == false)) and (answer == true)) {
            answer = false;
        }
        return answer;
    }
};

int main() {
    return 0;
}