#include<stdio.h>
#include<string.h>

typedef struct{
    int id;
    char name[50];
    float gpa;
} Student;

void searchStudent(Student students[],int n,int searchID){
    for(int i=0;i<n;i++){
        if(students[i].id==searchID){
            printf("Record Found:\nID: %d\nName: %s\nGPA: %.2f\n",students[i].id,students[i].name,students[i].gpa);
            return;
        }
    }
    printf("Record not found for Student ID %d\n",searchID);
}

int main(){
    int n,searchID;
    printf("Enter the number of students: ");
    scanf("%d",&n);

    Student students[n];
    for(int i=0;i<n;i++){
        printf("Enter ID,Name,and GPA for student %d:\n",i+1);
        scanf("%d %s %f",&students[i].id,students[i].name,&students[i].gpa);
    }

    printf("Enter Student ID to search: ");
    scanf("%d",&searchID);

    searchStudent(students,n,searchID);

}


Sample output:

Enter the number of students: 2
Enter ID, Name, and GPA for student 1:
101 John 3.7
Enter ID, Name, and GPA for student 2:
102 Jane 3.9
Enter Student ID to search: 102
Record Found:
ID: 102
Name: Jane
GPA: 3.90


Scenario 2: A social media platform needs to search for a user by their 
unique username in a list of thousands of users. The system should be 
designed to search through a dynamic list, optimizing performance for 
large datasets

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int searchUsername(char **usernames,int numUsers,char *target){
    for (int i=0;i< numUsers;i++){
        if (strcmp(usernames[i],target)==0){
            return i;
        }
    }
    return -1;
}

int main(){
    int numUsers;
    printf("Enter the number of users: ");
    scanf("%d",&numUsers);

    char **usernames=(char **)malloc(numUsers*sizeof(char *));
    if (usernames==NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }

 
    char buffer[50];
    getchar();
    for (int i=0;i< numUsers;i++){
        printf("Enter username %d: ",i + 1);
        fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer,"\n")]='\0';

        usernames[i]=(char *)malloc((strlen(buffer) + 1)*sizeof(char));
        if (usernames[i]==NULL){
            printf("Memory allocation failed for username.\n");
            return 1;
        }
        strcpy(usernames[i],buffer);
    }


    char target[50];
    printf("Enter the username to search for: ");
    fgets(target,sizeof(target),stdin);
    target[strcspn(target,"\n")]='\0';


    int result=searchUsername(usernames,numUsers,target);
    if (result != -1){
        printf("Username '%s' found at index %d.\n",target,result);
    } else{
        printf("Username '%s' not found.\n",target);
    }

    for (int i=0;i< numUsers;i++){
        free(usernames[i]);
    }
    free(usernames);

    return 0;
}

sample output:

Enter the number of users: 3
Enter username 1: alice123
Enter username 2: bob_the_builder
Enter username 3: charlie89
Enter the username to search for: bob_the_builder
Username 'bob_the_builder' found at index 1.



Scenario 3: A telephone directory application needs to search for 
a specific contact’s phone number by their name. The contact list is 
stored using dynamic memory allocation, and the search should be 
efficient and work for any list size.



#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char *name;
    char *phoneNumber;
} Contact;

int searchContact(Contact *contacts,int numContacts,char *target){
    for (int i=0;i< numContacts;i++){
        if (strcmp(contacts[i].name,target)==0){
            return i;// Return the index if found
        }
    }
    return -1;// Return -1 if not found
}

int main(){
    int numContacts;
    printf("Enter the number of contacts: ");
    scanf("%d",&numContacts);

    Contact *contacts=(Contact *)malloc(numContacts*sizeof(Contact));
    if (contacts==NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }


    char buffer[50];
    getchar();  
    for (int i=0;i< numContacts;i++){

        printf("Enter name of contact %d: ",i + 1);
        fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer,"\n")]='\0';// Remove newline character
        contacts[i].name=(char *)malloc((strlen(buffer) + 1)*sizeof(char));
        if (contacts[i].name==NULL){
            printf("Memory allocation failed for contact name.\n");
            return 1;
        }
        strcpy(contacts[i].name,buffer);

        printf("Enter phone number of contact %d: ",i + 1);
        fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer,"\n")]='\0';
        contacts[i].phoneNumber=(char *)malloc((strlen(buffer) + 1)*sizeof(char));
        if (contacts[i].phoneNumber==NULL){
            printf("Memory allocation failed for phone number.\n");
            return 1;
        }
        strcpy(contacts[i].phoneNumber,buffer);
    }

    char target[50];
    printf("Enter the name to search for: ");
    fgets(target,sizeof(target),stdin);
    target[strcspn(target,"\n")]='\0';// Remove newline character

    int result=searchContact(contacts,numContacts,target);
    if (result != -1){
        printf("Contact found: %s,Phone Number: %s\n",contacts[result].name,contacts[result].phoneNumber);
    } else{
        printf("Contact '%s' not found.\n",target);
    }

    for (int i=0;i< numContacts;i++){
        free(contacts[i].name);
        free(contacts[i].phoneNumber);
    }
    free(contacts);

    return 0;
}


Sample output:

Enter the number of contacts: 2
Enter name of contact 1: John Doe
Enter phone number of contact 1: 123-456-7890
Enter name of contact 2: Jane Smith
Enter phone number of contact 2: 987-654-3210
Enter the name to search for: Jane Smith
Contact found: Jane Smith, Phone Number: 987-654-3210
