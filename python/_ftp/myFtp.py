#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import ftplib
import os
import time


class MyFtp:
    def __init__(self, host, port, user, passwd, timeout):
        self.__ftp = ftplib.FTP()
        self.__ftp.connect(host=host, port=port, timeout=timeout)
        self.__ftp.login(user=user, passwd=passwd)
        self.__file = None
        self.__filename = None
        self.__filesize = None
        self.__last_print_time = 0
        self.__curr_filesize = 0
        self.__last_print_filesize = 0

    def __read_cb(self, data):
        self.__file.write(data)
        now = time.time()
        self.__curr_filesize = os.path.getsize(self.__filename)
        end = ""
        if self.__filesize == self.__curr_filesize:
            self.__file.close()
            end = "\n"
        else:
            # 每秒更新一次
            if now - self.__last_print_time < 1:
                return

        percent = self.__curr_filesize / self.__filesize * 100
        curr_filesize_m = self.__curr_filesize / 1024 / 1024
        filesize_m = self.__filesize / 1024 / 1024

        speed = (self.__curr_filesize - self.__last_print_filesize) / (now - self.__last_print_time) / 1024
        print("\r当前下载的文件进度为[%5.2f%%], 当前文件大小为[%8.2fM], 文件总大小[%8.2fM], 速度为[%8.2fKB/s]"
              % (percent, curr_filesize_m, filesize_m, speed), end=end, flush=True)
        self.__last_print_time = now
        self.__last_print_filesize = self.__curr_filesize
        # 保活
        self.__ftp.voidcmd('NOOP')

    def downloadOne(self, remote_file, local_file):
        try:
            self.__filename = local_file
            self.__filesize = self.__ftp.size(remote_file)
            dirname = os.path.dirname(local_file)
            if not os.path.exists(dirname):
                os.makedirs(dirname)
            with open(local_file, "wb") as self.__file:
                self.__ftp.retrbinary("RETR %s" % remote_file, self.__read_cb)
        except Exception as e:
            print(e)
        print("结束")

    def downloadlist(self, files):
        for k, v in files.items():
            self.downloadOne(k, v)


# 把你的狗屎路径在这拼接
def make_downloadlist():
    # 这里给你举个例子，假如保持和ftp的目录结构一致，指定一个本地目录
    remote_local_list = {
            # 在这加
            ("modules", "boost", "boost_1.58.0.zip"): "local_prefix_dir",
            }
    result = {}
    for remote_paths, local_path in remote_local_list.items():
        r = remote_paths[0]
        for p in remote_paths[1:]:
            r = os.path.join(r, p)
        local = os.path.join(local_path, r)

        result[r] = local
    return result


if __name__ == '__main__':
    ftp = MyFtp(host="47.101.177.9", port=21, user="htuser",
                passwd="4xbZgNxBGI", timeout=5)
    remote_file = os.path.join("modules", "boost", "boost_1.58.0.zip")
    local_file = os.path.join("ftpRoot", "modules", "boost", "boost_1.58.0.zip")
    # ftp.downloadOne(remote_file=remote_file, local_file=local_file)
    downloadlist = make_downloadlist()
    ftp.downloadlist(downloadlist)
