"""
ID:303893416
Full Name : Yigal.O
"""

from contact import *  # in this project we know exactly which modules contact have


class PhoneBook:
    def __init__(self):
        self.contactsList = []  # create a new contact list for this PhoneBook instance

    def Start(self):
        while True:
            choice = input("What would you like to do?\n\
             1 - Add a new contact\n\
             2 - Show all contacts\n\
             3 - Edit a contact\n\
             4 - Find a contact\n\
             5 - Delete a contact\n\
             6 - Exit\n\
             -->")
            if choice == '1':
                self.Command1()
            elif choice == '2':
                self.Command2()
            elif choice == '3':
                self.Command3()
            elif choice == '4':
                self.Command4()
            elif choice == '5':
                self.Command5()
            elif choice == '6':
                break
            else:
                print("#\nMyError: no such choice#\nTry again pls...\n#")
            print("---------------------------------------")

    def Command1(self):
        while True:
            choice = input("Should this contact be Simple (S), Friend (F), Professional (P) or Both (B)?")
            if choice in ['S', 'F', 'P', 'B']:
                if choice == 'S':
                    self.contactsList.append(Contacts())
                elif choice == 'F':
                    self.contactsList.append(FriendContact())
                elif choice == 'P':
                    self.contactsList.append(ProfessionalContact())
                elif choice == 'B':
                    self.contactsList.append(ProfessionalFriendContact())
                self.contactsList.sort()
                break
            else:
                print("#\nMyError: no such choice#\nTry again pls...\n#")

    def Command2(self):
        for i, contact in enumerate(self.contactsList, start=1):
            print("contact number %d:" % i, contact)
        else:
            print("#Done#")

    def Command3(self):
        while len(self.contactsList) > 0:
            try:
                i = int(input("Enter a valid number of the contact you wish to edit:"))
                contact = self.contactsList[i - 1]
                self.contactsList.remove(contact)
            except (IndexError, ValueError):
                print("#\nMyError: no such index#\nTry again pls...\n#")
            else:
                break
        else:
            print("#contactList is empty#")
            return

        while True:
            choice = input("Should this contact be Simple (S), Friend (F), Professional (P) or Both (B)?")
            if choice in ['S', 'F', 'P', 'B']:
                print("For the following fields\nclick enter if there's no change,\n"
                      "a new value if you want to replace the field,\n"
                      "or x if you want to delete the field (the name field cannot be deleted).")

                if choice == 'S':
                    self.contactsList.append(Contacts(contact))
                elif choice == 'F':
                    self.contactsList.append(FriendContact(contact))
                elif choice == 'P':
                    self.contactsList.append(ProfessionalContact(contact))
                elif choice == 'B':
                    self.contactsList.append(ProfessionalFriendContact(contact))

                del contact
                self.contactsList.sort()
                break
            else:
                print("#\nMyError: no such choice#\nTry again pls...\n#")

    def Command4(self):
        if len(self.contactsList) > 0:
            inputStr = input("Type contact details (name, phone, email): ")
            for i, contact in enumerate(self.contactsList, start=1):
                if contact.Match(inputStr):
                    print("contact number %d:" % i, contact)
            print("#Done#")
        else:
            print("#contactList is empty#")

    def Command5(self):
        while len(self.contactsList) > 0:
            try:
                i = int(input("Enter a valid number of the contact you wish to edit:"))
                lst = self.contactsList
                lst.remove(lst[i - 1])  # throws an exception if there is no such item i.e. no such index
            except (IndexError, ValueError):
                print("#\nMyError: no such index#\nTry again pls...\n#")
            else:
                break
        else:
            print("#contactList is empty#")


# main program
phoneBook1 = PhoneBook()
phoneBook1.Start()
