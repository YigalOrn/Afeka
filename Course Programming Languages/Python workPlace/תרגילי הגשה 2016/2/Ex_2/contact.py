"""
ID:303893416
Full Name : Yigal.O
"""

import re  # to check correct email pattern

# you can see that i some how get regex at leats for this part
# example shows: itzik@Cohen-Dev.co.il i.e. we have the '-' between '@' and '.'
# so one of the following should be appropriate
# global_p = re.compile('[a-zA-Z0-9]+@[a-zA-Z]+\.[a-zA-Z]+')
global_p = re.compile('.*@.*\..*')


class Contacts:
    def __init__(self, olderContact=None):
        self.CopyAttributes(olderContact)
        self.ReadValues()

    def CopyAttributes(self, olderContact=None):
        if olderContact:
            if isinstance(olderContact, Contacts):
                self.name = olderContact.name
                if hasattr(olderContact, "cellphone"):
                    self.cellphone = olderContact.cellphone

    def ReadValues(self):
        inputVal = None
        while True:
            if hasattr(self, "name"):
                oldAttr = self.name
                inputVal = input("Name({0}):".format(oldAttr))
                if inputVal == '':
                    self.name = oldAttr
                    break
                else:
                    self.name = inputVal
                    break
            else:
                inputVal = input("Name:")
                if inputVal == '':
                    print("#\nMyError: Name cant be empty#\nTry again pls...\n#")
                else:
                    self.name = inputVal
                    break
        while True:
            if hasattr(self, "cellphone"):
                oldAttr = self.cellphone
                inputVal = input("Cell Phone({0}):".format(oldAttr))
                if inputVal == '':
                    self.cellphone = oldAttr
                    break
                elif inputVal == 'x':
                    del self.cellphone
                    break
                elif not inputVal.isdigit():
                    print("#\nMyError: Cell Phone should contain digits only#\nTry again pls...\n#")
                else:
                    self.cellphone = inputVal
                    break
            else:
                inputVal = input("Cell Phone:")
                if inputVal == '':
                    break
                elif not inputVal.isdigit():
                    print("#\nMyError: Cell Phone should contain digits only#\nTry again pls...\n#")
                else:
                    self.cellphone = inputVal
                    break

    def GetMyAttrStrs(self):
        # assumption all inputs(i.e. instance variables) are strings!, in other cases if will come we should add conditions.
        # for the following list compr' is not clear..
        myAttrList = []
        for s in dir(self):
            if not s.startswith('__'):
                attr = self.__getattribute__(s)
                if isinstance(attr, str):
                    myAttrList.append(s)
        return myAttrList

    def Match(self, dataStr):
        local_p = re.compile(dataStr)
        my_Attr_str_list = self.GetMyAttrStrs()
        for attr_str in my_Attr_str_list:
            m = local_p.search(self.__getattribute__(attr_str))
            if m:
                return True
        return False

    def __lt__(self, other):
        if self.name < other.name:
            return True
        else:
            return False

    def __str__(self):
        myStr = "Name: " + self.name
        if hasattr(self, "cellphone"):
            myStr += ", Cell Phone: " + self.cellphone
        return myStr


class FriendContact(Contacts):
    def __init__(self, olderContact=None):
        self.CopyAttributes(olderContact)
        self.ReadValues()

    def CopyAttributes(self, olderContact=None):
        super().CopyAttributes(olderContact)
        if olderContact:
            if isinstance(olderContact, FriendContact):
                if hasattr(olderContact, "homePhone"):
                    self.homePhone = olderContact.homePhone
                if hasattr(olderContact, "personalEmail"):
                    self.personalEmail = olderContact.personalEmail

    def ReadValues(self):
        super().ReadValues()  # the MRO call from here as i understood from Ronen
        inputVal = None
        while True:
            if hasattr(self, "homePhone"):
                oldAttr = self.homePhone
                inputVal = input("Home Phone({0}):".format(oldAttr))
                if inputVal == '':
                    self.homePhone = oldAttr
                    break
                elif inputVal == 'x':
                    del self.homePhone
                    break
                elif not inputVal.isdigit():
                    print("#\nMyError: Home Phone should contain digits only#\nTry again pls...\n#")
                else:
                    self.homePhone = inputVal
                    break
            else:
                inputVal = input("Home Phone:")
                if inputVal == '':
                    break
                elif not inputVal.isdigit():
                    print("#\nMyError: Home Phone should contain digits only#\nTry again pls...\n#")
                else:
                    self.homePhone = inputVal
                    break
        while True:
            if hasattr(self, "personalEmail"):
                oldAttr = self.personalEmail
                inputVal = input("Personal Email({0}):".format(oldAttr))
                if inputVal == '':
                    self.personalEmail = oldAttr
                    break
                elif inputVal == 'x':
                    del self.personalEmail
                    break
                elif global_p.match(inputVal) == None:
                    print("#\nMyError: Personal Email format is incorrect#\nTry again pls...\n#")
                else:
                    self.personalEmail = inputVal
                    break
            else:
                inputVal = input("Personal Email:")
                if inputVal == '':
                    break
                elif global_p.match(inputVal) == None:
                    print("#\nMyError: Personal Email format is incorrect#\nTry again pls...\n#")
                else:
                    self.personalEmail = inputVal
                    break

    def GetMyStr(self):
        myStr = ""
        if hasattr(self, "homePhone"):
            myStr += "Home Phone: " + self.homePhone
            if hasattr(self, "personalEmail"):
                myStr += ", Personal Email: " + self.personalEmail
        elif hasattr(self, "personalEmail"):
            myStr += "Personal Email: " + self.personalEmail
        return myStr

    def __str__(self):
        return Contacts.__str__(self) + ", " + self.GetMyStr()


class ProfessionalContact(Contacts):
    def __init__(self, olderContact=None):
        self.CopyAttributes(olderContact)
        self.ReadValues()

    def CopyAttributes(self, olderContact=None):
        super().CopyAttributes(olderContact)
        if olderContact:
            if isinstance(olderContact, ProfessionalContact):
                if hasattr(olderContact, "workPhone"):
                    self.workPhone = olderContact.workPhone
                if hasattr(olderContact, "workEmail"):
                    self.workEmail = olderContact.workEmail

    def ReadValues(self):
        super().ReadValues()  # the MRO call from here as i understood from Ronen
        inputVal = None
        while True:
            if hasattr(self, "workPhone"):
                oldAttr = self.workPhone
                inputVal = input("Work Phone({0}):".format(oldAttr))
                if inputVal == '':
                    self.workPhone = oldAttr
                    break
                elif inputVal == 'x':
                    del self.workPhone
                    break
                elif not inputVal.isdigit():
                    print("#\nMyError: Work Phone should contain digits only#\nTry again pls...\n#")
                else:
                    self.workPhone = inputVal
                    break
            else:
                inputVal = input("Work Phone:")
                if inputVal == '':
                    break
                elif not inputVal.isdigit():
                    print("#\nMyError: Work Phone should contain digits only#\nTry again pls...\n#")
                else:
                    self.workPhone = inputVal
                    break
        while True:
            if hasattr(self, "workEmail"):
                oldAttr = self.workEmail
                inputVal = input("Work Email({0}):".format(oldAttr))
                if inputVal == '':
                    self.workEmail = oldAttr
                    break
                elif inputVal == 'x':
                    del self.workEmail
                    break
                elif global_p.match(inputVal) == None:
                    print("#\nMyError: Work Email format is incorrect#\nTry again pls...\n#")
                else:
                    self.workEmail = inputVal
                    break
            else:
                inputVal = input("Work Email:")
                if inputVal == '':
                    break
                elif global_p.match(inputVal) == None:
                    print("#\nMyError: Work Email format is incorrect#\nTry again pls...\n#")
                else:
                    self.workEmail = inputVal
                    break

    def GetMyStr(self):
        myStr = ""
        if hasattr(self, "workPhone"):
            myStr += "Work Phone: " + self.workPhone
            if hasattr(self, "workEmail"):
                myStr += ", Work Email: " + self.workEmail
        elif hasattr(self, "workEmail"):
            myStr += "Work Email: " + self.workEmail
        return myStr

    def __str__(self):
        return Contacts.__str__(self) + ", " + self.GetMyStr()


class ProfessionalFriendContact(FriendContact, ProfessionalContact):
    def __init__(self, olderContact=None):
        # i could construct this class as the others classes of type contacts only to show the use of the ReadValues(..)
        # method, but it seems a little bit to much. so here we have the super proxy using the MRO and in the
        # other classes we have the use of ReadValues(..) as requested!
        # pls notice that we dont even need a c'tor here!! , and it is here only for clarity at least for me..
        super().__init__(olderContact)

    def __str__(self):
        return FriendContact.__str__(self) + ", " + ProfessionalContact.GetMyStr(self)
