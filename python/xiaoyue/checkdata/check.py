#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import openpyxl
import time


class Record:
    def __init__(self, _time, phone, empll_id,
                 empll_button_id,
                 work_path, work_path_id, work_path_name,
                 work_button_id, event_name, event_button_id):
        t = time.strptime(_time, '%Y/%m/%d %H:%M:%S')
        self.time = time.mktime(t)
        self.phone = phone
        self.empll_id = empll_id
        self.empll_button_id = empll_button_id
        self.work_path = work_path
        self.work_path_id = work_path_id
        self.work_path_name = work_path_name
        self.work_button_id = work_button_id
        self.event_name = event_name
        self.event_button_id = event_button_id


indexlcyh = list(range(1, 15))
indexfcc = list(range(1, 10))
indexfccliving = list(range(1, 5))


records = []


if __name__ == '__main__':
    wb = openpyxl.load_workbook('巡检记录_20190701-20190729.xlsx')
    print(wb.sheetnames)
    sheet_name = wb.sheetnames[0]
    sheet = wb.get_sheet_by_name(sheet_name)

    for i in range(2, sheet.max_row):
        s = sheet[i]
        s = [value.value for value in s]
        assert len(s) == 10
        record = Record(*s)
        if not record.work_path or not record.work_path_id:
            print('第[%d]条记录跳过' % i)
            continue
        print('第[%d]条记录' % i)
        records.append(record)

    recordlcyh = [record for record in records
                  if record.work_path == '龙城一号施工现场']
    recordfcc = [record for record in records
                 if record.work_path == '翡翠城施工现场']
    recordfccliving = [record for record in records
                       if record.work_path == '翡翠城生活区']

    print(len(recordlcyh), len(recordfcc), len(recordfccliving))
