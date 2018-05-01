# import pprint
#
# class A:
#     def __init__(self):
#         self.attr_4 = lambda x: x + 1
#         self.attr_1 = '1'
#         self.attr_2 = 2
#         self.attr_3 = 3
#
#
#
# a = A()
# pprint.pprint(dir(a))
# print(type(a.__getattribute__('attr_1')))
# myAttrList = [s for s in dir(a) if not s.startswith('__')]
# print(myAttrList)

# for attr_str in myAttrList:
#     attr = a.__getattribute__(attr_str)
#     print(type(attr))
#     print(attr)


# import re
#
# p = re.compile('cat')
# m = p.search('pop corn every day untill windows shuts my cat allmost every year for the next month')
# if m:
#     print(m.group())


print('cat' in 'popcat Yell')
