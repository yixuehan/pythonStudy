# -*- coding: utf-8 -*-

import csv
import json5 as json
import os


title_convert = {
    "aac001": "户编号",
    "aac025": "户主个人编号",
    "aac029": "户主姓名",
    "aac031": "户主证件号码",
    "aar010": "脱贫状态",
    "aac023": "脱贫年度",
    "aac017": "家庭人口数",
    "aar041": "首次识别时间",
    "aac006": "贫困户属性",
}

# aar010
pool_state_convert = {
    0: "未脱贫",
    1: "已脱贫(享受政策)",
    3: "返贫",
    4: "已脱贫(不再享受政策)"
}

# aac006
pool_attr_convert = {
    "01": "一般贫困户",
    "02": "低保脱贫户",
    "03": "特困供养脱贫户",
    "04": "低保贫困户",
    "05": "一般脱贫户",
    "06": "特困供养贫困户",
    "07": "低保特困供养贫困户",
    "08": "低保特困供养户",
}


def get_data_files(p):
    file_list = os.listdir(p)
    # print(files)
    file_list = [filename for filename in file_list if filename.find(".json") != -1]
    # print(files)
    return file_list


def get_data(file):
    with open(file, "r", encoding="utf-8") as f:
        value_map = json.load(f, encoding="utf-8")
        # print(value_map)
        return value_map["body"]["poorFamilyList"]["data"]
    print("文件数据异常[%s]" % file)
    assert False


def get_all_data(files):
    values = []
    for file in files:
        values += (get_data(file))
    # print(values)
    return values


def convert_map_array(value_map_list):
    value_obj_list = []

    for value_map in value_map_list:
        # print("开始解析:", value_map)
        obj = {}
        for key in list(title_convert.keys()):
            obj[title_convert[key]] = str(value_map[key])
        # print(obj)
        obj["脱贫状态"] = pool_state_convert[int(obj["脱贫状态"])]
        obj["贫困户属性"] = pool_attr_convert[obj["贫困户属性"]]
        obj["首次识别时间"] = "%s年12月" % (int(obj["首次识别时间"])-1)
        # print("解析完成:", obj)
        value_obj_list.append(obj)
    # print(value_obj_list)
    return value_obj_list


if __name__ == '__main__':
    files = get_data_files(os.getcwd())
    value_map_list = get_all_data(files)
    value_obj_list = convert_map_array(value_map_list)
    # print(list(title_convert.values()))
    with open("result.csv", "w", encoding="utf-8", newline='') as f:
        f_csv = csv.DictWriter(f, list(title_convert.values()))
        f_csv.writeheader()
        # print(value_obj_list)
        f_csv.writerows(value_obj_list)

