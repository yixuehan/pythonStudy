#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import ftplib
import os
import time


class MyFtp:
    def __init__(self, host, port, user, passwd, timeout):
        self.__ftp = ftplib.FTP()
        self.__host = host
        self.__port = port
        self.__user = user
        self.__passwd = passwd
        self.__timeout = timeout
        self.__ftp.connect(host=host, port=port, timeout=timeout)
        self.__ftp.login(user=user, passwd=passwd)
        self.__file = None
        self.__filename = None
        self.__filesize = None
        self.__last_print_time = 0
        self.__curr_filesize = 0
        self.__last_print_filesize = 0
        # self.__start_time = 0

    def reconnect(self):
        self.__ftp.close()
        self.__ftp.connect(host=self.__host, port=self.__port, timeout=self.__timeout)
        self.__ftp.login(user=self.__user, passwd=self.__passwd)

    def __read_cb(self, data):
        now = time.time()
        self.__file.write(data)
        self.__curr_filesize += len(data)  # os.path.getsize(self.__filename)
        if self.__filesize == self.__curr_filesize:
            self.__file.close()
            end = "\n"
        else:
            # 每秒更新一次
            if now - self.__last_print_time < 1:
                return
            end = ""

        percent = self.__curr_filesize / self.__filesize * 100
        curr_filesize_m = self.__curr_filesize / 1024 / 1024
        filesize_m = self.__filesize / 1024 / 1024
        # avg_speed = self.__curr_filesize / (now - self.__start_time)

        speed = (self.__curr_filesize - self.__last_print_filesize) / (now - self.__last_print_time)
        if speed > 0:
            left_time = (self.__filesize - self.__curr_filesize) / speed
        else:
            left_time = 99999
        speed_k = speed / 1024
        print("\rfilename[%s] process[%6.2f%%] download_size[%6.2fM], total_size[%6.2fM], speed[%8.2fKB/s], left_time[%8.2fs]"
              % (self.__filename, percent, curr_filesize_m, filesize_m, speed_k, left_time), end=end, flush=True)
        self.__last_print_time = now
        self.__last_print_filesize = self.__curr_filesize
        # 保活
        if int(now) % 10 == 0:
            self.__ftp.voidcmd('NOOP')

    def downloadOne(self, remote_file, local_file):
        # os.remove(local_file)
        self.__filename = local_file
        self.__filesize = self.__ftp.size(remote_file)
        if os.path.exists(local_file):
            self.__curr_filesize = os.path.getsize(local_file)
        else:
            self.__curr_filesize = 0
        self.__last_print_filesize = self.__curr_filesize
        dirname = os.path.dirname(local_file)
        if not os.path.exists(dirname):
            os.makedirs(dirname)

        # 接收
        done = False
        while not done:
            try:
                # self.__file = None
                with open(local_file, "ab") as self.__file:
                    self.__ftp.retrbinary("RETR %s" % remote_file, self.__read_cb, rest=self.__curr_filesize)
            except Exception as e:
                print(e)
                time.sleep(3)
                self.reconnect()
                # assert False
                continue
            # TODO 检验md5

            print("下载文件[%s]结束" % self.__filename)
            done = True

    def downloadlist(self, files):
        for k, v in files.items():
            self.downloadOne(k, v)


def make_downloadlist():
    remote_local_list = {
            # 在这加
            ("modules", "PicoSDK", "PicoSDK_2.0.443.rar"): "FtpRoot",                         # only lib
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
    start = time.time()
    ftp = MyFtp()
    # ftp.downloadOne(remote_file=remote_file, local_file=local_file)
    downloadlist = make_downloadlist()
    ftp.downloadlist(downloadlist)
    end = time.time()
    print("共花费%f秒" % (end-start))
