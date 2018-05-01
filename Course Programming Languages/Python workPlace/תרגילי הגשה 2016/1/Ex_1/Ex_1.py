"""
import time
start = time.time()
k=0
for i in range(100000): k+=1
end = time.time()
print(end - start)
"""






#Q1

def Reverse1(lst):
    # stop con
    if (len(lst) == 1):
        return lst
    # recursion step
    param = lst[0]
    tempLst = Reverse1(lst[1:])
    tempLst.append(param)
    return tempLst


def Reverse2(myStack):
    emptyStack = []
    while len(myStack)!=0:
        emptyStack.append(myStack.pop())
    return emptyStack


def Reverse3(lst):
    return [lst[-1*(i+1)] for i in range(len(lst))]


lst1 = list(range(17))
print(lst1)
print("Reverse1 - {0}".format(Reverse1(lst1)))
print("Reverse2 - {0}".format(Reverse2(lst1)))

print("------------------------------")

lst2 = ["cat", 1, 22, [9,"window",7,"a"], 0]
l = lst2[:]
l.reverse()
print(lst2)
print("built_in reverse - {0}".format(l))
print("Reverse1 - {0}".format(Reverse1(lst2)))
print("Reverse2 - {0}".format(Reverse2(lst2[:])))
print("Reverse3 - {0}".format(Reverse3(lst2)))


print("------------------------------")






#Q2


def encrypt1(myStr):
    vowels = ["a","e","i","o","u"]
    lstMystr = list(myStr)
    tempLst = []
    for ch in lstMystr:
        if vowels.count(ch)==0 and ch!=' ':
            tempLst.append(ch)
            tempLst.append(ch)
        else:
            tempLst.append(ch)
    return tempLst


def encrypt2(myStr):
    vowels = ["a","e","i","o","u"]
    lstMystr = list(myStr)
    i = 0
    for ch in lstMystr[:] :
        if vowels.count(ch) == 0 and ch != ' ':
            lstMystr.insert(i, ch)
            i+=2
        else:
            i+=1
    return lstMystr


def encrypt3(myStr):
    lstMystr = list(myStr)
    i = 0
    for ch in lstMystr[:] :
        if ch not in ["a","e","i","o","u"] and ch != ' ':
            lstMystr.insert(i, ch)
            i+=2
        else:
            i+=1
    return lstMystr

def decrypt3(myStr):
    lstMystr = list(myStr)
    i = 0
    while i<len(lstMystr):
        if lstMystr[i] not in ["a","e","i","o","u"] and lstMystr[i] != ' ':
            del lstMystr[i]
            i+=1
        else:
            i+=1
    return lstMystr



print(" ".join(encrypt1("this is so fun")))
print(" ".join(encrypt2("this is so fun")))
print(" ".join(encrypt3("this is so fun")))


print("------------------------------")

print(" ".join(encrypt3("this is so fun")))
print(" ".join(decrypt3("tthhiss iss sso ffunn")))


print("------------------------------")


def helpEncrypt(ch):
    if ch not in ['a', 'e', 'i', 'o', 'u']:
        return ch*2
    else:
        return ch

def encrypt(phrase):
    #str is a sequence the same as list just str is a sequence of chars.
    return map(helpEncrypt, phrase)

print( "".join(encrypt("this is so fun")))


print("------------------------------")

#Q3

def char_freq(myStr):
    d = dict()
    for ch in myStr:
        if d.get(ch) != None:
            d[ch]+=1
        else:
            d[ch] = 1
    return d

def char_freq2(myStr):
    d = dict()
    for ch in myStr:
        if ch in d:
            d[ch]+=1
        else:
            d[ch] = 1
    return d


res = char_freq2("abbabcbdbabdbdbabababcbcba")
print(res)

res = char_freq2("aaaaaaaaaabaaaaabaaaaaa")#21,2
print(res)

res = char_freq2("abcdefghijkl")
print(res)

res = char_freq2("11111939")#1:5,9:2,3:1
print(res)


res = char_freq2("!@#$%^&*()_+")
print(res)

print("------------------------------")



#Q4

def create_occurances_list(lst):
    res = [lst[b] for b in range(len(lst)) for a in range(b)]
    return res


res = create_occurances_list([5,4,3,2,1])
print(res)



print("------------------------------")



#Q5

import functools
def mult_odds(l1, l2):
    return functools.reduce(lambda x, y: x*y, [l2[k] for k in l1 if l2[k]%2!=0])

l1 = [0, 2, 4]
l2 = [6, 7, 9, 13, 17, 22]
print(mult_odds (l1,l2))








