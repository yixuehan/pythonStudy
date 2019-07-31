#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import openpyxl
import time
# import numpy as np
import os
import json


class Record:
    def __init__(self, line, _time, phone, empll_id,
                 empll_button_id,
                 work_path, work_path_id, work_path_name,
                 work_button_id, event_name, event_button_id):
        self.line = int(line)
        self.datatime = time.strptime(_time, '%Y/%m/%d %H:%M:%S')
        self.time = time.mktime(self.datatime)
        self.phone = phone
        self.empll_id = empll_id
        self.empll_button_id = empll_button_id
        self.work_path = work_path
        self.work_path_id = work_path_id
        self.work_path_name = work_path_name
        self.work_button_id = work_button_id
        self.event_name = event_name
        self.event_button_id = event_button_id

    def __eq__(self, that):
        return self.work_path_id == that.work_path_id

    def __str__(self):
        return '%s %s %s %s %s %s %s %s %s %s %s %s' % (
                self.line,
                self.datatime,
                self.time,
                self.phone,
                self.empll_id,
                self.empll_button_id,
                self.work_path,
                self.work_path_id,
                self.work_path_name,
                self.work_button_id,
                self.event_name,
                self.event_button_id
                )


def time_eq(t1, t2):
    return (t1 - t2) <= 10 * 60


def is_night(t):
    return t.tm_hour >= 16 or t.tm_hour < 6


indexlcyh = list(range(1, 15))
indexfcc = list(range(1, 11))
indexfccliving = list(range(1, 6))

time_duration_lcyh = 45 * 60
time_next_duration_lcyh = 60 * 60

time_duration_fcc = 35 * 60
time_next_duration_fcc = 50 * 60

time_duration_fccliving_day = 15 * 60
time_next_duration_fccliving_day = 60 * 60

time_duration_fccliving_night = 15 * 60
time_next_duration_fccliving_night = 30 * 60


f = open("result.txt", "w")


def check_time(last_group, group,
               time_duration_day, time_next_duration_day,
               time_duration_night, time_next_duration_night):
    # check time

    if not len(last_group):
        return
    assert len(group)

    _is_night = is_night(group[0].datatime)

    if not _is_night:
        time_duration = time_duration_day
        time_next_duration = time_next_duration_day
    else:
        time_duration = time_duration_night
        time_next_duration = time_next_duration_night

    if group[-1].time - group[0].time < time_duration - 60:
        f.write("行[%d ~ %d] 时间间隔不足[%ds]实际为[%fs]少了[%dm%fs][%s]\n" %
                (group[0].line, group[-1].line,
                 time_duration, group[-1].time - group[0].time,
                 int((time_duration - group[-1].time + group[0].time) / 60),
                 (time_duration - group[-1].time + group[0].time) % 60,
                 _is_night)
                )

    if group[0].time - last_group[0].time < time_next_duration - 60:
        f.write("行[%d ~ %d] 和上一组时间间隔不足[%ds]实际为[%fs]少了[%dm%fs][%s]\n" %
                (group[0].line, group[-1].line,
                 time_next_duration, group[0].time - last_group[0].time,
                 int((time_next_duration - group[0].time + last_group[0].time) / 60),
                 (time_next_duration - group[0].time + last_group[0].time) % 60,
                 _is_night)
                )

    last_group = group


def check_record(records, index_range, time_column, work_path_id_column,
                 time_duration_day, time_next_duration_day,
                 time_duration_night, time_next_duration_night):
    if not len(records):
        return
    max_repeats = len(index_range)/2
    group = []
    last_group = []
    repeat_record = []
    repeats = 0
    last_record = records[0]
    group = [last_record]
    for record in records[1:]:
        # print(str(record))
        if record not in group and not record.line - last_record.line > 4:
            group.append(record)
        else:
            repeats = repeats + 1
            if record in repeat_record:
                print("什么鬼? line[%d ~ %d]\n" %
                      (group[0].line, record.line))
                # assert False
            repeat_record.append(record)
            # ((record.work_path == '龙城一号施工现场' or record.work_path == '翡翠城施工现场') and int(record.work_path_id) == 2) or \
            if repeats > max_repeats or \
               (record.work_path == '龙城一号施工现场' and int(record.work_path_id) == 2) or \
               record.line - last_record.line > 4:
                # print(record.work_path, record.work_path_id, record.line, repeats, max_repeats)
                lefts = [i for i in index_range
                         if i not in [record.work_path_id for record in group]]
                if record.work_path == '翡翠城施工现场' and len(lefts) == 1 and lefts[0] == 10:
                    pass
                elif len(lefts) != 0:
                    f.write("行[%d ~ %d] 缺少打点[%s]\n" %
                            (group[0].line, group[-1].line, lefts))
                check_time(last_group, group, time_duration_day,
                           time_next_duration_day,
                           time_duration_night, time_next_duration_night)
                # f.write("完成一组[%d ~ %d]\n" % (group[0].line, group[-1].line))
                # if (record.work_path == '龙城一号施工现场' or record.work_path == '翡翠城施工现场') and record.work_path_id == 2:
                if record.work_path == '龙城一号施工现场' and record.work_path_id == 2:
                    repeat_index = -1
                    if len(repeat_record[:-1]) != 0:
                        repeat_ids = [record.work_path_id for record in repeat_record[:-1]]
                        f.write("碰到2，行[%d ~ %d] 有重复[%s]\n" %
                                (group[0].line,
                                 group[-1].line
                                 if group[-1].line > repeat_record[repeat_index].line
                                 else repeat_record[repeat_index].line,
                                 repeat_ids))
                    repeat_record = [repeat_record[-1]]
                last_group = group
                group = repeat_record
                repeat_record = []
                repeats = 0
        last_record = record

    if len(group):
        if len(repeat_record) != 0:
            repeat_ids = [record.work_path_id for record in repeat_record]
            f.write("行[%d ~ %d] 有重复[%s]\n" %
                    (group[0].line, group[-1].line, repeat_ids))

        check_time(last_group, group, time_duration_day,
                   time_next_duration_day,
                   time_duration_night, time_next_duration_night)
        last_group = group
        # f.write("完成一组[%d ~ %d]\n" % (group[0].line, group[-1].line))
        group = repeat_record + [record]
        repeat_record = []
        repeats = 0


def unique_record(records):
    if not len(records):
        return records
    rs = []
    rs = [records[0]]
    for record in records[1:]:
        if rs[-1].work_path_id == record.work_path_id:
            f.write("第[%d]行和第[%d]行巡检点序号重复[巡查点序号%d]\n" %
                    (rs[-1].line, record.line, record.work_path_id))
            continue
        rs.append(record)
    return rs


def save_array(filename, array):
    with open(filename, 'w') as f:
        json.dump(array, f, ensure_ascii=False)


def load_array(filename):
    with open(filename, 'r') as f:
        return json.load(f, object_pairs_hook=dict)


if __name__ == '__main__':
    excel_file = '巡检记录_20190701-20190729.xlsx'
    excel_arr = excel_file + "_array"

    lines = []
    records = []
    if not os.path.exists(excel_arr):
        wb = openpyxl.load_workbook(excel_file)
        print(wb.sheetnames)
        sheet_name = wb.sheetnames[0]
        sheet = wb.get_sheet_by_name(sheet_name)
        for i in range(2, sheet.max_row):
            # for i in range(2, 11):
            print('读取第[%d]条记录' % i)
            line = sheet[i]
            line = [i] + [value.value for value in line]
            assert len(line) == 11
            lines.append(line)
        # 保存数组
        save_array(excel_arr, lines)
    else:
        lines = load_array(excel_arr)

    for i in range(len(lines)):
        record = Record(*lines[i])
        print('处理第[%d]行记录' % record.line)
        if not record.work_path or not record.work_path_id:
            f.write('第[%d]条记录不全，跳过\n' % i)
            continue
        record.work_path_id = int(record.work_path_id)
        records.append(record)

    recordlcyh = [record for record in records
                  if record.work_path == '龙城一号施工现场']
    recordlcyh = unique_record(recordlcyh)

    recordfcc = [record for record in records
                 if record.work_path == '翡翠城施工现场']
    recordfcc = unique_record(recordfcc)

    recordfccliving = [record for record in records
                       if record.work_path == '翡翠城生活区']
    recordfccliving = unique_record(recordfccliving)

    print(len(recordlcyh), len(recordfcc), len(recordfccliving))

    check_record(recordlcyh, indexlcyh, 0, 5,
                 time_duration_lcyh, time_next_duration_lcyh,
                 time_duration_lcyh, time_next_duration_lcyh)

    check_record(recordfcc, indexfcc, 0, 5,
                 time_duration_fcc, time_next_duration_fcc,
                 time_duration_fcc, time_next_duration_fcc)

    check_record(recordfccliving, indexfccliving, 0, 5,
                 time_duration_fccliving_day,
                 time_next_duration_fccliving_day,
                 time_duration_fccliving_night,
                 time_next_duration_fccliving_night)
