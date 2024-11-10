//SCENARIO-1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Book{
    char isbn[20];  
    char title[100];
    char author[100];
    float price;
}Book;

typedef struct Node{
    Book book;
    struct Node *left;
    struct Node *right;
}Node;

Node* createNode(Book book){
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->book=book;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

Node* insert(Node* root,Book book){
    if(root==NULL){
        return createNode(book);
    }
    if(strcmp(book.isbn,root->book.isbn)<0){
        root->left=insert(root->left,book);
    }else if(strcmp(book.isbn,root->book.isbn)>0){
        root->right=insert(root->right,book);
    }
    return root;
}

Book* search(Node* root,const char* isbn){
    if(root==NULL){
        return NULL;
    }
    if(strcmp(isbn,root->book.isbn)==0){
        return &root->book;
    }else if(strcmp(isbn,root->book.isbn)< 0){
        return search(root->left,isbn);
    }else{
        return search(root->right,isbn);
    }
}

void displaySorted(Node* root){
    if(root != NULL){
        displaySorted(root->left);
        printf("ISBN: %s,Title: %s,Author: %s,Price: %.2f\n",
               root->book.isbn,root->book.title,root->book.author,root->book.price);
        displaySorted(root->right);
    }
}

int main(){
    Node* root=NULL;
    int choice;
    
    do{
        printf("\nMenu:\n");
        printf("1. Insert a new book\n");
        printf("2. Search for a book by ISBN\n");
        printf("3. Display all books\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        getchar(); 
        switch(choice){
            case 1:{
                Book newBook;
                printf("Enter ISBN: ");
                fgets(newBook.isbn,sizeof(newBook.isbn),stdin);
                newBook.isbn[strcspn(newBook.isbn,"\n")]=0; 
                
                printf("Enter Title: ");
                fgets(newBook.title,sizeof(newBook.title),stdin);
                newBook.title[strcspn(newBook.title,"\n")]=0; 

                printf("Enter Author: ");
                fgets(newBook.author,sizeof(newBook.author),stdin);
                newBook.author[strcspn(newBook.author,"\n")]=0; 
                printf("Enter Price: ");
                scanf("%f",&newBook.price);
                getchar(); 
                
                root=insert(root,newBook);
                printf("Book inserted successfully!\n");
                break;
            }
            case 2:{
                char isbn[20];
                printf("Enter ISBN to search: ");
                fgets(isbn,sizeof(isbn),stdin);
                isbn[strcspn(isbn,"\n")]=0; 

                Book* foundBook=search(root,isbn);
                if(foundBook != NULL){
                    printf("Found: ISBN: %s,Title: %s,Author: %s,Price: %.2f\n",
                           foundBook->isbn,foundBook->title,foundBook->author,foundBook->price);
                }else{
                    printf("Book with ISBN %s not found.\n",isbn);
                }
                break;
            }
            case 3:
                printf("Books in sorted order:\n");
                displaySorted(root);
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }while(choice != 4);
 return 0;
}


//SCWNARIO-2

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int studentID;
    char name[50];
    int age;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int studentID, const char* name, int age) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->studentID = studentID;
    snprintf(newNode->name, sizeof(newNode->name), "%s", name);
    newNode->age = age;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* addStudent(Node* root, int studentID, const char* name, int age) {
    if (root == NULL) {
        return createNode(studentID, name, age);
    }
    if (studentID < root->studentID) {
        root->left = addStudent(root->left, studentID, name, age);
    } else if (studentID > root->studentID) {
        root->right = addStudent(root->right, studentID, name, age);
    }
    return root;
}

Node* findStudent(Node* root, int studentID) {
    if (root == NULL || root->studentID == studentID) {
        return root;
    }
    if (studentID < root->studentID) {
        return findStudent(root->left, studentID);
    }
    return findStudent(root->right, studentID);
}

void inOrderTraversal(Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("Student ID: %d, Name: %s, Age: %d\n", root->studentID, root->name, root->age);
        inOrderTraversal(root->right);
    }
}

int main() {
    Node* root = NULL;

    root = addStudent(root, 102, "Alice", 20);
    root = addStudent(root, 101, "Bob", 21);
    root = addStudent(root, 103, "Charlie", 19);

    int searchID = 102;
    Node* student = findStudent(root, searchID);
    if (student != NULL) {
        printf("Found Student - ID: %d, Name: %s, Age: %d\n", student->studentID, student->name, student->age);
    } else {
        printf("Student with ID %d not found.\n", searchID);
    }

    printf("\nAll Student IDs in Ascending Order:\n");
    inOrderTraversal(root);

    return 0;
}
```
