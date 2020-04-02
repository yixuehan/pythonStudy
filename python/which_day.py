#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# 是否闰年
def is_leap_year(year):
    return ((year % 4 == 0) and (year % 100 != 0)) or year % 400 != 0


# 日历 calendar
def get_calendar(year):
    if is_leap_year(year):
        return [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    return [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]


# 获取一年的第几天
def get_which_day(year, month, day):
    calendar = get_calendar(year)
    days = 0
    if month > len(calendar) or day > calendar[month]:
        raise ValueError
    for i in range(0, month-1):
        days += calendar[i]
    return days + day


if __name__ == '__main__':
    success = False
    while not success:
        try:
            ymd = input("请输入年月日(2010-3-1):")
            ymds = ymd.split('-')
            if len(ymds) != 3:
                raise ValueError
            year, month, day = ymds
            year, month, day = int(year), int(month), int(day)
            days = get_which_day(int(year), int(month), int(day))
        except ValueError:
            print("不合法的日期,  请重新输入")
            continue
        success = True
    print("现在是一年中的第%d天" % days)
