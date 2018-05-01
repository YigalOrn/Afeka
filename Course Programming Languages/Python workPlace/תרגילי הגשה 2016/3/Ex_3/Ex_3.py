"""
Name:Yigal.O
Id:303893416
"""

from urllib.request import urlopen
import re


# 1
def ParseEmails(emailsLst):
    p = re.compile("([\w]+)@([\w]+).com")
    parsedDict = {}
    for email in emailsLst:
        m = p.match(email)
        if m:
            parsedDict[m.group(1)] = m.group(2)

    return parsedDict


# 2
def PrintProfessionalContacts(emailsParsedDict):
    f = lambda x: len(x)
    maxNameLen, maxCompanyLen = len(max(emailsParsedDict.keys(), key=f)), len(max(emailsParsedDict.values(), key=f))
    print("{}   {}".format("Name".center(maxNameLen), "Company".center(maxCompanyLen)))

    if maxNameLen < len('Name'):
        maxNameLen = len('Name')
    if maxCompanyLen < len('Company'):
        maxCompanyLen = len('Company')

    print("{}   {}".format("=" * maxNameLen, "=" * maxCompanyLen))
    for key, val in sorted(emailsParsedDict.items()):
        key, val = str(key).capitalize(), str(val).capitalize()
        print("{}   {}".format(key.ljust(maxNameLen), val.ljust(maxCompanyLen)))


# 3
"""
\b - is from the regex how to in:
https://docs.python.org/3/howto/regex.html

if intrested look for : 'p = re.compile(r'\bclass\b')' , on that web page
"""
# Along with 'g' there could be 4-6 additional letters because 1+4<=5-7<=1+6
p1 = re.compile(r"\bg[a-zA-Z]{4,6}\b")
p2 = re.compile("g[a-zA-Z]{4,6}\n")

with urlopen('http://www.puzzlers.org/pub/wordlists/unixdict.txt') as response, \
        open("answer.txt", 'w') as outputFile:
    for line in response:
        line = line.decode('utf-8')
        # m = p1.match(line)# one option with p1
        m = p2.fullmatch(line)  # second option with p2
        if m:
            # outputFile.write(m.group() + '\n')# one option with p1
            outputFile.write(m.group())  # second option with p2
