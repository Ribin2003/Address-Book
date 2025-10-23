#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;


void createContact(AddressBook *addressBook);
int validate_phone(char*phone,AddressBook *addressBook);
int validate_email(char*email , AddressBook*addressBook);
void searchContact(AddressBook *addressBook);
int search_name(char *search_term , AddressBook *addressBook);
int search_phone(char *search_term,AddressBook *addressBook);
int search_email(char *search_term, AddressBook *addressBook);
void editContact(AddressBook *addressBook);
int edit_contact(int index,AddressBook *addressBook,int *index_arr);
int search_by_name(char *search_term ,AddressBook *addressBook,int *index_arr);
void deleteContact(AddressBook *addressBook);
int delete(int index1,AddressBook *addressBook,int*index_arr);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void saveAndExit(AddressBook *addressBook);


#endif
