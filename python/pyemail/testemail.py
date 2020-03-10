#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from email.mime.text import MIMEText
import smtplib

msg = MIMEText('hello, send by python...', 'plain', 'utf-8')
from_addr = "505703394@qq.com"
smtp_server = "smtp.qq.com"

from_addr = "15000207570@163.com"
smtp_server = "smtp.163.com"

password = input('Password:')

to_addr = "15000207570@163.com"
# to_addr = "505703394@qq.com"


server = smtplib.SMTP_SSL(smtp_server, 587)
server.set_debuglevel(1)
server.login(from_addr, password)
server.sendmail(from_addr, [to_addr], msg.as_string())
server.quit()
