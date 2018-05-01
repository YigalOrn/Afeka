from urllib.request import urlopen
import re

ctr = 0

# Along with 'g' there could be 4-6 additional letters because 1+4<=5-7<=1+6
p = re.compile(r"\bg[a-zA-Z]{4,6}\b")
p2 = re.compile("g[a-zA-Z]{4,6}\n")

with urlopen('http://www.puzzlers.org/pub/wordlists/unixdict.txt') as response, \
        open("answer.txt", 'w') as outputFile:
    for line in response:
        line = line.decode('utf-8')
        # m = p.match(line) # ans 472
        # print(repr(line))
        m = p2.fullmatch(line)
        if m:
            ctr+=1
            # outputFile.write(m.group() + '\n')
            outputFile.write(m.group())

print("Yigal len - ", ctr)


# Ronens
from urllib.request import urlopen

with urlopen('http://www.puzzlers.org/pub/wordlists/unixdict.txt') as response, open("RonensAnswer.txt", 'w') as f:
    lst = list(response)
    lst = [word.decode('utf-8') for word in lst]
    lst = [word[:-1] for word in lst if len(word) >= 6 and len(word) <= 8 and word[0] == 'g']
    print("Ronens len - ", len(lst))
    f.write('\n'.join(lst))







#check \b regex
# p = re.compile(r'\bclass\b')
# print(p.search('no class at all'))
#
# print(p.search('the declassified algorithm'))
# print(p.search('one classified is'))
# print(p.search('one classs is'))
# print(p.search('one subclass is'))
