#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
  FILE * fp = fopen("contacts.csv","w");
  fprintf(fp,"%d\n",addressBook->contactCount);
  for(int i = 0;i < addressBook->contactCount;i++)
  {
    fprintf(fp,"%s,",addressBook->contacts[i].name);
    fprintf(fp,"%s,",addressBook->contacts[i].phone);
    fprintf(fp,"%s\n",addressBook->contacts[i].email);
  }
  fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE * fptr = fopen("contacts.csv","r");
    if(fptr == NULL)
    { 
        printf("Error opening the file.\n");
        return;
    }
    char ch;
    fscanf(fptr,"%c\n",&ch);
    int count = ch -'0';
    addressBook->contactCount = count;
    for(int i = 0;i < addressBook->contactCount;i++)
    {
        fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
  }
