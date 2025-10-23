#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    int i;
    printf("-----------------------------------------------------------------------------\n");
    printf("%-10s %-20s %-20s %s\n", "Sl.no", "Name", "phn_no", "Email_id");
    printf("-----------------------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-10d %-20s %-20s %s\n",i + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf("-----------------------------------------------------------------------------\n");
}
    
    


void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}




void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    printf("Enter the name : ");
    scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);
    char phone[20];
    char email[30];
    int ret;
    do
    {
        
        printf("Enter mobile number : ");
        scanf("%s",phone);
        ret = validate_phone(phone,addressBook);
        if(ret==0)
        {
            printf("Invalid number!");
        }
    }while (ret == 0);
    if(ret == 1)
    {
        strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
        //addressBook->contactCount++;
    }
    int res;
    do
    {
        printf("Enter the email ID: ");
        scanf("%s",email);
        res = validate_email(email,addressBook);
        if(res == 0)
            printf("Invalid Email ID!");
    } while (res == 0);
    if(res == 1)
    {
        strcpy(addressBook->contacts[addressBook->contactCount].email,email);
        addressBook->contactCount++;
        printf("\nContact created successfully.");
    }
    
    
}
int validate_phone(char*phone , AddressBook*addressBook)
{
    if(strlen(phone) != 10)
        return 0;
    int i = 0;
    while(phone[i])
    {
        if(phone[i] < '0' || phone[i] > '9')
        {
                return 0;
        }
        i++;
    }
    //checking dupicates
    for(i = 0;i< addressBook->contactCount; i++)
    {
        int cmp = strcmp(phone,addressBook->contacts[i].phone);
        if (cmp == 0)
            return 0;
    }
    return 1;
    
}
int validate_email(char*email , AddressBook*addressBook)
{
    char *ptr1 =strchr(email,'@');
    if(ptr1 == NULL)
        return 0;
    char *dot_ptr = strstr(email,".com");
    if(dot_ptr == NULL)
        return 0;
    if((strcmp(dot_ptr,".com") != 0))
        return 0;

    int i = 0;
    while(email[i])
    {
        if(email[i] >= 'A' && email[i] <= 'Z')
        {
                return 0;
        }
        i++;
    }
    char *ptr =strchr(email,'@');
    if (!isalnum(email[0]) || !isalnum(*(ptr + 1)))
        return 0;
    for(i = 0;i< addressBook->contactCount; i++)
    {
        int cmp = strcmp(email,addressBook->contacts[i].email);
        if (cmp == 0)
            return 0;
    }
    return 1;
}
    
void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    char str[5];
    int choice;
    char search_term[50];
    do
    {
        printf("\nSearching Menu\n1.Search by name\n2.Search by phone number\n3.Search by Email ID\n4.Exit ");
        scanf("%s",str);
        choice = atoi(str);

        switch(choice)
        {
            case 1: search_name(search_term , addressBook);
                    break;
            case 2: search_phone(search_term , addressBook);
                    break;
            case 3: search_email(search_term , addressBook);
                    break;
            case 4:break;
            default:printf("Invalid choice. Please try again.\n");
        }
    } while (choice > 0 && choice <= 3);
    
}
int search_name(char *search_term,AddressBook *addressBook)
{
    //char name[30];
    printf("Enter the name: ");
    scanf(" %[^\n]",search_term);
    int i,flag= 0,j = 1;
    for( i = 0;i< addressBook->contactCount; i++)
    {
        //int cmp = strcmp(name,addressBook->contacts[i].name);
        if (!(strcmp(search_term,addressBook->contacts[i].name)))
        {
            printf("%-10d %-20s %-20s %s\n",i + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            flag = 1;
            j++;
        }

    }
    if(flag ==1)
        return i;
    if (!flag)
        printf("Contact not found");
    
}
int search_phone(char *search_term,AddressBook *addressBook)
{
    printf("Enter the phone number: ");
    scanf("%s",search_term);
    int i, flag= 0;
    for( i = 0;i< addressBook->contactCount; i++)
    {
        
        if (!(strcmp(search_term,addressBook->contacts[i].phone)))
        {
            printf("1  %s %s %s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            flag = 1;
            break;
        }

    }
    if(flag == 1)
        return i;
    if (!flag)
    {
        printf("Contact not found");
        return 0;
    }
    
}
int search_email(char *search_term,AddressBook *addressBook)
{
    //char mail[30];
    printf("Enter the name: ");
    scanf("%s",search_term);
    int i, flag= 0;

    for( i = 0;i< addressBook->contactCount; i++)
    {
    
        if (!(strcmp(search_term,addressBook->contacts[i].email)))
        {
            printf("1  %s %s %s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            flag = 1;
            break;
        }

    }
    if(flag == 1)
        return i;
    if (!flag)
    {
        printf("Contact not found");
        return 0;
    }
    
}

void editContact(AddressBook *addressBook)
{
    char str[5];
	int choice;
    char search_term[50];
    int index_arr[addressBook->contactCount];
    do
    {
        printf("\nSearching Menu\n1.Search by name\n2.Search by phone number\n3.Search by Email ID\n4.Exit\n");
        scanf("%s",str);
        choice = atoi(str);

        switch(choice)
        {
            case 1: int index1 = search_by_name(search_term , addressBook,index_arr);
                    edit_contact(index1,addressBook,index_arr);
                    break;
            case 2: int index2 = search_phone(search_term , addressBook);
                    edit_contact(index2,addressBook,index_arr);
                    break;
            case 3: int index3 = search_email(search_term , addressBook);
                    edit_contact(index3,addressBook,index_arr);
                    break;
            case 4 : break;
            default:printf("Invalid choice. Please try again.\n");
        }
    } while (choice > 0 && choice <4);
    
}
int edit_contact(int index,AddressBook *addressBook,int *index_arr)
{
    char str[5];
    int opt;
    if(index == 0)
    {
        return 0;
    }
    do
    {
        printf("\nChoose the field you want to edit :\n");//printing menu
        printf("1.Name\n2.Phone number\n3.Email\n4.Exit\n ");
        scanf("%s",str);
        opt = atoi(str);

        switch(opt)
        {
            case 1:
                    char Name[20];
                    printf("Enter  new name: ");
                    scanf(" %[^\n]",Name);
                    strcpy(addressBook->contacts[index].name,Name); 
                    printf("\nName updated successfully.");               
                    
                    break;
            case 2: char Phone[20];
                    int ret;
                    do
                    {
        
                        printf("Enter the new mobile number : ");
                        scanf("%s",Phone);
                        ret = validate_phone(Phone,addressBook);
                        if(ret==0)
                        {
                            printf("Invalid number!");
                        }
                    }while (ret == 0);
                    if(ret == 1)
                    {
                        strcpy(addressBook->contacts[index].phone,Phone);
                        printf("\nPhone number updated successfully");
                    }
                    break;
            case 3 : char Mail[50];
                    int res;
                    do
                    {
                        printf("Enter the new email ID: ");
                        scanf("%s",Mail);
                        res = validate_email(Mail,addressBook);
                        if(res == 0)
                        printf("Invalid Email ID!");
                    }while (res == 0);
                    if(res == 1)
                    {
                        strcpy(addressBook->contacts[index].email,Mail);
                        printf("\nEmail ID updated successfully.");
                    }
                    break;
            case 4 : break;
            default : printf("Invalid choice! try again");
        }
    
    }while(opt > 0 && opt < 4);
}
int search_by_name(char *search_term ,AddressBook *addressBook,int *index_arr)
{
    printf("Enter the name: ");
    scanf(" %[^\n]",search_term);
    int i,flag= 0,j=0,contact;
    for( i = 0;i< addressBook->contactCount; i++)
    {

        if (!(strcmp(search_term,addressBook->contacts[i].name)))
        {
            flag = 1;
            printf("\n%d  %s %s %s",j+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            index_arr[j] = i;
            j++;

        }

    }
    if (!flag)
    {
      printf("Contact not found");
      return 0;
    }
    if(j>=2)
    {
        printf("\nchoose the contact  : ");
        scanf("%d",&contact);
        return index_arr[contact-1];
    }
    else
        return index_arr[0];

}




void deleteContact(AddressBook *addressBook)
{
    char str[5];
	int choice;
    char search_term[50];
    int index_arr[addressBook->contactCount];
    do
    {
        printf("\nSearching Menu\n1.Search by name\n2.Search by phone number\n3.Search by Email ID\n4.Exit\n");
        scanf("%s",str);
        choice = atoi(str);

        switch(choice)
        {
            case 1: int index1 = search_by_name(search_term , addressBook,index_arr);
                    delete(index1,addressBook,index_arr);
                    break;
            case 2: int index2 = search_phone(search_term , addressBook);
                    delete(index2,addressBook,index_arr);
                    break;
            case 3: int index3 = search_email(search_term , addressBook);
                    delete(index3,addressBook,index_arr);
                    break;
            case 4 : break;
            default:printf("Invalid choice. Please try again.\n");
        }
    } while (choice > 0 && choice <4);
   
}
int delete(int index1,AddressBook *addressBook,int*index_arr)
{
    int option;
    if(index1 == 0)
    {
        return 0;
    }
    printf("\nDo you want to delete the contact?\n");
    printf("1.Yes\n2.No\n");
    scanf("%d",&option);
    switch(option)
    {
        case 1: for(int i = index1;i<addressBook->contactCount;i++)
                {
                    strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
                    strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
                    strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email);
                }
                addressBook->contactCount--;
                printf("Contact deleted successfully.");
                break;
        case 2: break;

        default: printf("Invalid choice.");
    }
}