#!/usr/bin/python
# -*- coding:UTF-8 -*-

counter = 100 #赋值整形变量
miles = 1000.0
name = "John and 约翰"

print counter
print miles
print name

a,b,c = 1,"abc", 100.0
print a
print b*2
print c

lList = ['abc', 'hehehe', 123, 'xyz', "hhh"]
print lList
print lList * 2

tuple = ( 'runoob', 786 , 2.23, 'john', 70.2 )
tinytuple = (123, 'john')
 
print tuple               # 输出完整元组
print tuple[0]            # 输出元组的第一个元素
print tuple[1:3]          # 输出第二个至第三个的元素 
print tuple[2:]           # 输出从第三个开始至列表末尾的所有元素
print tinytuple * 2       # 输出元组两次
print tuple + tinytuple   # 打印组合的元组

#!/usr/bin/python
# -*- coding: UTF-8 -*-
 
dict = {}
dict['one'] = "This is one"
dict[2] = "This is two"
 
tinydict = {'name': 'john','code':6734, 'dept': 'sales'}
 
 
print dict['one']          # 输出键为'one' 的值
print dict[2]              # 输出键为 2 的值
dict[2] = "new 2"
dict[2] = 100
print dict[2]
print tinydict             # 输出完整的字典
print tinydict.keys()      # 输出所有键
print tinydict.values()    # 输出所有值

print 1.20**100
