#include "date.h"
#include <ctime>
#include <sstream>

Date::Date() : _year{0}, _day{0} {
}

Date::Date(int day, Date::Month month, int year) : _year{year}, _month{month}, _day{day} {
}

Date Date::currentDate() {
  time_t time = std::time(NULL);
  tm *now = localtime(&time);
  return Date(now->tm_mday, static_cast<Date::Month>(now->tm_mon), now->tm_year + 1900);
}

std::string Date::format() const {
  std::stringstream date;
  date << _day << '/' << _month << '/' << _year;
  return date.str();
}

bool Date::valid() const {
  if (_day != 0 && _year != 0) {
    tm thisTm = *this;
    time_t thisTime{mktime(&thisTm)};
    if (time_t(-1) != thisTime && thisTm.tm_mday == _day && thisTm.tm_mon == _month &&
        thisTm.tm_year == _year - 1900) {
      return true;
    }
  }
  return false;
}

int Date::differenceInDays(const Date &other) const {
  if (!this->valid() || !other.valid()) {
    return -1;
  }
  tm thisTime = *this;
  tm otherTime = other;
  // Convert from a struct tm to a time_t to allow calculation.
  time_t tTime = mktime(&thisTime);
  time_t oTime = mktime(&otherTime);
  double diffInSeconds = difftime(tTime, oTime);
  // Convert from seconds to days.
  return std::abs(static_cast<int>(diffInSeconds / 86400));
}

bool Date::operator==(const Date &other) const {
  return valid() && other.valid() && _day == other._day && _month == other._month &&
         _year == other._year;
}

bool Date::operator!=(const Date &other) const {
  return !(*this == other);
}

Date::operator tm() const {
  tm time{};
  time.tm_hour = 0;
  time.tm_min = 0;
  time.tm_sec = 0;
  time.tm_mday = _day;
  time.tm_mon = _month;
  time.tm_year = _year - 1900;
  return time;
}
