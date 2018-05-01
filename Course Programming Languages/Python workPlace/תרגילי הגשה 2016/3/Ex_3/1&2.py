import re


def ParseEmails(emailsLst):
    p = re.compile("([\w]+)@([\w]+).com")
    parsedDict = {}
    for email in emailsLst:
        m = p.match(email)
        if m:
            parsedDict[m.group(1)] = m.group(2)

    return parsedDict


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


emails = ["sergey@google.com", "tim@apple.com", "david@cavaliers.com"]
# emails = ["s@go.com"]
# emails = ["sergey@google.com", "tim@apple.com", "david@cavaliers.com",
#           "_@google.com", "@yahoo.com", "vitalka12@rambler.com",
#           "sergey@google.co.il", "someone@mail.afeka.ac.il", "str",
#           " ", "", "@", "ert45_12_pop@gmail.com", "ert45_12_pop@", "rtD2V13@MIT.com", "bob_1.3@MIT.com"]
mapping = ParseEmails(emails)
PrintProfessionalContacts(mapping)
