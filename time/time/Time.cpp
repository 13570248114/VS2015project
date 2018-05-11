using namespace std;

#include <iostream>
#include <iomanip>
#include "Time.h"

Time::Time()
{ hour = min = sec = 0;
}

Time::Time(int h, int m, int s)
{ setTime(h, m, s);
}

void Time::setTime(int h, int m, int s)
{ hour = (h>=0 && h<24) ? h : 0;
  min = (m>=0 && m<60) ? m : 0;
  sec = (s>=0 && s<60) ? s : 0;
}

Time& Time::operator+=(unsigned int n)
{ sec += n;
  if (sec >= 60)
  { min += sec/60;
    sec %= 60;
    if (min >=60)
    { hour = (hour + min/60) % 24;
      min %= 60;
    }
  }
  return *this;
}

Time Time::operator+(unsigned int n) const
{ Time tCopy(*this);
  tCopy += n;
  return tCopy;
}

Time& Time::operator++()        // prefix version
{ *this += 1;
  return *this;
}

Time Time::operator++(int n)    // postfix version
{ Time tCopy(*this);
  *this += 1;
  return tCopy;
}

ostream& operator<<(ostream &o, const Time &t)
{ o << setfill('0') << setw(2) <<  t.hour << ':' << setw(2) << t.min << ':' << setw(2) << t.sec;
  return o;
}

bool  Time::operator==(const Time& rsh) const
{
	return hour == rsh.hour&&min == rsh.min&&sec == rsh.sec;
}

bool Time::operator<=(const Time& rsh) const
{
	if (hour < rsh.hour)
		return true;
	else if (hour == rsh.hour)
	{
		if (min < rsh.min)
			return true;
		else if (min == rsh.min)
		{
			if (sec <= rsh.sec)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

bool Time::operator>=(const Time& rsh) const
{
	return *this == rsh || !(*this <= rsh);
}


Time Time::operator-(unsigned int n) const
{
	Time tCopy(*this);
	tCopy -= n;
	return tCopy;
}

Time& Time::operator-=(unsigned int n)
{
	sec -= n;
	if (sec < 0)                    //�����С��0��ӷ��Ӵ���λ
	{
		min -=  -sec /60+(sec%60!=0);                   
		sec = 60* (sec % 60 != 0) + sec%60;
		if (min < 0)
		{
			hour -= -min / 60 + (min % 60 != 0);    // �������С��0���Сʱ����λ
			min = 60* (min % 60 != 0) + min%60;
			if (hour < 0)
				hour = 24 *(hour % 24 != 0) + hour%24;
		}
	}
	return *this;
}

Time& Time::operator--() {
	*this -= 1;
	return *this;
}

bool operator<(const Time& lsh, const Time& rsh)
{
	return lsh != rsh&&lsh <= rsh;
}

bool operator>(const Time& lsh, const Time& rsh)
{
	return  lsh != rsh&&lsh >= rsh;
}
bool operator!=(const Time& lsh, const Time& rsh)
{
	return !(lsh == rsh);
}

Time operator--(Time& lsh, int)  // postfix version
{
	Time tCopy(lsh);
	--lsh;
	return tCopy;
}

unsigned int operator-(const Time& lsh, const Time& rsh)  // difference in seconds
{
	if (lsh == rsh)
		return 0;

	int nhour, nmin, nsec;                //�����������������������ʱ���Сʱ����Ӳ�����
	nsec = lsh.sec - rsh.sec;
	nmin = lsh.min - rsh.min;
	nhour = lsh < rsh ? lsh.hour + 24 - rsh.hour : lsh.hour - rsh.hour;          //�������ʱ��ȿ�ʼʱ���磬�������ʱ�����24Сʱ

	if (nsec < 0)                            //������Ϊ������ͨ����С���Ӳ���ʹ��������
	{
		nmin -= -nsec / 60 + (nsec % 60 != 0);
		nsec = 60 * (nsec % 60 != 0) + nsec % 60;
	}
	if (nmin < 0)                             //������Ӳ�Ϊ������ͨ����ССʱ����ʹ��������
	{
		nhour -= -nmin / 60 + (nmin % 60 != 0);
		nmin = 60 * (nmin % 60 != 0) + nmin % 60;
	}
	return nhour * 3600 + nmin * 60 + nsec;
}

