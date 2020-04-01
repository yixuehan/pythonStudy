#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from ftplib import FTP
import time
# import tarfile
import os
import sys
import ftplib
import threading
'''
块注释
初次运行该脚本，会将ftp上所有相关的库都下载都本地qtpro/ftpRoot中，并且全部解压拷贝到相应的目录
如果再次执行，会先检测本地ftpRoot中是否存在与ftp上相同的库包，如果存在则不会下载，也不会解压，只会下载本地不存在的库；
如果本地已经存在的库，想随着新下载的库，一起解压拷贝，需要传递一个参数“1”，例如： ./getLibFromFtp.py 1

注意：1.压缩包的后缀名，必须是三个字母的；例如xxx.7z这个中压缩包就会失败.
      2.下载的过程中尽量不要打断。因为会导致正在下载的库文件下载不完整。
'''
#  单行注释
#  易变的库
mutableLibArray = {
    #  目录名:库名
    'MapEngine': 'HtMapEngine_167',                                # only lib
    'MapCutline': 'HtMapCutline_167',                              # only lib
    'MapCommon': 'HtMapCommon_167',                                # only lib
    'MapAlphashape': 'HtMapAlphashape_167',                         # only lib
    'PicoSDK': 'PicoSDK_433',                                        # only lib
    'WaveformEngine': 'WaveformEngine_203'                          # only lib
}
#  稳定的库
stableLibArray = {
    # 目录名:库名
    'Config': 'Config',                                              # only lib
    'dbghelp': 'dbghelp',                                            # only lib
    'emReg': 'emReg',                                                # only lib
    'gtest': 'gtest',                                                # only lib
    'gtest_main': 'gtest_main',                                      # only lib
    'heartbeat': 'heartbeat',                                        # only lib
    'HtGeoMath': 'HtGeoMath',                                        # only lib
    'HtImage': 'HtImage',                                            # only lib
    'libPng': 'libPng',                                              # only lib
    'libprotobuf': 'libprotobuf',                                    # only lib
    'libprotobuf-lite': 'libprotobuf-lite',                          # only lib
    'libprotoc': 'ibprotoc',                                         # only lib
    'Log': 'Log',                                                    # only lib
    'zlib': 'zlib',                                                  # only lib
    'CGAL_Core-vc120': 'CGAL_Core-vc120-mt-4.11.3',                  # only lib
    'surface_mesh': 'surface_mesh',                                  # only lib
    'OpenSceneGraph': 'OpenSceneGraph',                              # both lib and dll
    'ANN': "ANN",                                                    # both lib and dll
    'CGAL-vc120': 'CGAL-vc120-mt-4.11.3',                            # both lib and dll
    'geogram': 'geogram',                                            # both lib and dll
    'libboost_system-vc120': 'libboost_system-vc120-mt-1_58',        # both lib and dll
    'libboost_thread-vc120': 'libboost_thread-vc120-mt-1_58',        # both lib and dll
    'libgmp': 'libgmp-10',                                           # both lib and dll
    'libmpfr': 'libmpfr-4',                                          # both lib and dll
    'boost_chrono-vc120': 'boost_chrono-vc120-mt-1_58',              # only dll
    'osgPlugins': 'osgPlugins',                                      # only dll
    'msvcp140': 'msvcp140',                                          # only dll
    'ucrtbase': 'ucrtbase',                                          # only dll
    'vcruntime140': 'vcruntime140'                                   # only dll
}


# 连接ftp
def ftpconnect(host, port, username, password):
    ftp = FTP()
    #  打开调试级别2，显示详细信息
    #  ftp.set_debuglevel(2)
    ftp.connect(host, port)
    ftp.login(username, password)
    return ftp


# 从ftp下载文件
def downloadfile(ftp, remotepath, localpath, existFileSize=0):
    #  设置的缓冲区大小
    bufsize = 10240
    # bufsize = ftp.size(remotepath)
    with open(localpath, 'wb+') as fp:
        try:
            ftp.retrbinary('RETR ' + remotepath, fp.write, bufsize, existFileSize)
            fp.flush()
        except ftplib.error_perm:
            return False
        return True


# 获取系列文件中最新的文件
def getLatestFileName(ftp, final_names):
    latest_time = None
    latest_name = None
    for name in final_names:
        time = ftp.sendcmd("MDTM " + name)
        if (latest_time is None) or (time > latest_time):
            latest_name = name
            latest_time = time
    return latest_name


# 开启线程上报文件下载进度
def printDownloadPercent(remoteFileSize, localFile):
    while True:
        existSize = None
        if not os.path.exists(localFile):
            existSize = 0
        else:
            existSize = os.path.getsize(localFile)
        ret = existSize / remoteFileSize
        num = ret * 100
        # print("\r" + '已下载大小:%d' % existSize + " " + '文件总大小:%d' % remoteFileSize + " " + '下载进度:%.2f%%'%num, end = "")
        time.sleep(1)
        print("\rlocalFile:%s已下载大小:%d 文件总大小:%d  下载进度:%.2f%%'" % (localFile, existSize, remoteFileSize, num), end="")
        # print ('下载进度:%.2f%%'%num)
        if existSize == remoteFileSize:
            break
    print("")


if __name__ == "__main__":
    print("脚本名：", sys.argv[0])
    params = None
    if len(sys.argv) > 1:
        params = sys.argv[1]
    for i in range(1, len(sys.argv)):
        print("参数", i, sys.argv[i])

    downloadedLibArray = []
    existLibArray = []
    ftpRoot = "ftpRoot"
    # includePath = "..\modules\include"
    includePath = os.path.join("..", 'modules', 'include')
    # releaseLibPath = r"..\modules\libs\win32\release"
    releaseLibPath = os.path.join("..", "modules", "libs", "win32", "release")
    # debugLibPath = r"..\modules\libs\win32\debug"
    debugLibPath = os.path.join("..", "modules", "libs", "win32", "debug")
    # debugRunPath = r"..\bin"
    debugRunPath = os.path.join("..", "bin")
    # buildRunPath = r"..\output\bin"
    buildRunPath = os.path.join("..", "output", "bin")
    if not os.path.exists(ftpRoot):
        os.makedirs(ftpRoot)
    if not os.path.exists(debugRunPath):
        os.makedirs(debugRunPath)
    if not os.path.exists(buildRunPath):
        os.makedirs(buildRunPath)

    # host,port, username, password
    ftp = ftpconnect("47.101.177.9", 21, "htuser", "4xbZgNxBGI")
    ftp.set_debuglevel(0)  # 参数为0，关闭调试模式
    ftp.cwd("modules")
    for key in mutableLibArray:
        ftp.cwd(key)
        # ftp.retrlines('LIST')
        names = ftp.nlst()
        libName = mutableLibArray.get(key)
        final_names = [line for line in names if libName in line]
        if len(final_names) > 0:
            local_file = os.path.join(ftpRoot, final_names[0])
            if not os.path.exists(local_file):
                print("正在下载:", local_file)
                t = threading.Thread(target=printDownloadPercent, args=(ftp.size(final_names[0]), local_file))
                t.start()
                # if downloadfile(ftp, final_names[0], rf'.\ftpRoot\{final_names[0]}'):
                if downloadfile(ftp, final_names[0], local_file):
                    t.join()
                    # time.sleep(0.1)
                    print("下载成功:", final_names[0])
                    downloadedLibArray.append(final_names[0])
                else:
                    print("下载失败:", final_names[0])
                print("-----------------")
            else:
                existSize = os.path.getsize(local_file)
                # print("exist file size:", existSize)
                # print("ftp file size:", ftp.size(final_names[0]))
                if existSize < ftp.size(final_names[0]):
                    print("文件有损坏:", final_names[0])
                #   print("正在续传:", final_names[0])
                #   t = threading.Thread(target = printDownloadPercent, args = (ftp.size(final_names[0]), ftpRoot+final_names[0]))
                #   t.start()
                #   if downloadfile(ftp, final_names[0], rf'.\ftpRoot\{final_names[0]}', existSize) == True:
                #       time.sleep(0.1)
                #       print("续传成功:", final_names[0])
                #       downloadedLibArray.append(final_names[0])
                #   else:
                #      print("续传失败:", final_names[0])
                #   print("-----------------")
                else:
                    print("已经存在:", final_names[0])
                    print("-----------------")
                    existLibArray.append(final_names[0])
        ftp.cwd("..")

    for key in stableLibArray:
        ftp.cwd(key)
        # ftp.retrlines('LIST')
        names = ftp.nlst()
        final_names = [line for line in names if key in line]
        desName = getLatestFileName(ftp, final_names)
        local_file = os.path.join(ftpRoot, desName)
        if not os.path.exists(local_file):
            print("正在下载:", desName)
            t = threading.Thread(target=printDownloadPercent, args=(ftp.size(desName), local_file))
            t.start()
            # if downloadfile(ftp, desName, rf'.\ftpRoot\{desName}') == True:
            if downloadfile(ftp, desName, local_file):
                t.join()
                # time.sleep(0.1)
                print("下载成功:", desName)
                downloadedLibArray.append(desName)
            else:
                print("下载失败:", desName)
            print("-----------------")
        else:
            existSize = os.path.getsize(local_file)
            # print("exist file size:", existSize)
            # print("ftp file size:", ftp.size(desName))
            if existSize < ftp.size(desName):
                print("文件有损坏:", final_names[0])
                # print("正在续传:", desName)
                # t = threading.Thread(target = printDownloadPercent, args = (ftp.size(desName), ftpRoot+desName))
                # t.start()
                # if downloadfile(ftp, desName, rf'.\ftpRoot\{desName}', existSize) == True:
                #     time.sleep(0.1)
                #     print("续传成功:", desName)
                #     downloadedLibArray.append(desName)
                # else:
                #     print("续传失败:", desName)
                # print("-----------------")
            else:
                print("已经存在:", desName)
                print("-----------------")
                existLibArray.append(desName)
        ftp.cwd("..")
    print("")
    print("download success!!!")
    ftp.close()  # 关闭ftp

    # 解压下下来的包
    for file in downloadedLibArray:
        # 必须使用这种格式,使用+进行字符连接时，因为语言中转义字符的存在会出现路径识别时的错误。
        # rar_command = '"C:\\"Program Files (x86)"\WinRAR\WinRAR.exe" -o+ x %s %s\\'%(ftpRoot+file, ftpRoot)
        rar_command = '"C:\\"Program Files"\\WinRAR\\WinRAR.exe" -o+ x %s %s\\' % (ftpRoot+file, ftpRoot)
        print(rar_command)
        # os.system(rar_command)

    # 若带了一个参数1，则解压已经存在的lib，并且添加到后续拷贝的列表中
    print("params: ", params)
    if params == '1':
        for f in existLibArray:
            # rar_command = '"C:\\"Program Files (x86)"\WinRAR\WinRAR.exe" -o+ x %s %s\\'%(ftpRoot+file, ftpRoot)
            rar_command = '"C:\\"Program Files"\\WinRAR\\WinRAR.exe" -o+ x %s %s\\' % (ftpRoot+f, ftpRoot)
            print(rar_command)
            # os.system(rar_command)
            downloadedLibArray.append(f)

    sys.exit(1)
    # 拷贝解压后的库
    libIncludePath = None
    libReleasePath = None
    libDebugPath = None
    dllReleasePath = None
    dllDebugPath = None
    if len(downloadedLibArray) != 0:
        print("正在拷贝解压后的库...")
    for file in downloadedLibArray:
        if os.path.exists(ftpRoot+file[:-4]+r"\include"):
            libIncludePath = ftpRoot+file[:-4]+r"\include\*"
        if os.path.exists(ftpRoot+file[:-4]+r"\lib"):
            libReleasePath = ftpRoot+file[:-4]+r"\lib\release\*"
            libDebugPath = ftpRoot+file[:-4]+r"\lib\debug\*"
        if os.path.exists(ftpRoot+file[:-4]+r"\dll"):
            dllReleasePath = ftpRoot+file[:-4]+r"\dll\release\*"
            dllDebugPath = ftpRoot+file[:-4]+r"\dll\debug\*"
        if not libIncludePath:
            copy_command = 'xcopy /e /h /r /y %s %s\\' % (libIncludePath, includePath)
            os.system(copy_command)
        if not libReleasePath:
            copy_command = 'copy /y %s %s\\' % (libReleasePath, releaseLibPath)
            os.system(copy_command)
        if not libDebugPath:
            copy_command = 'copy /y %s %s\\' % (libDebugPath, debugLibPath)
            os.system(copy_command)
        if not dllReleasePath:
            copy_command = 'copy /y %s %s\\' % (dllReleasePath, buildRunPath)
            os.system(copy_command)
            copy_command = 'copy /y %s %s\\' % (dllReleasePath, debugRunPath)
            os.system(copy_command)
        if not dllDebugPath:
            copy_command = 'copy /y %s %s\\' % (dllDebugPath, debugRunPath)
            os.system(copy_command)
