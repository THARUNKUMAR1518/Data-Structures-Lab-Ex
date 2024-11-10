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

    return 0;
}



Sample output:

Enter a username to register (or type 'exit' to quit): user1
Username registered successfully
Enter a username to register (or type 'exit' to quit): user2
Username registered successfully
Enter a username to register (or type 'exit' to quit): user1
Username already taken


Scenario 2: An e-commerce platform uses hashing to store and retrieve
product IDs for fast lookups. The system uses dynamic memory allocation 
to handle varying numbers of products, allowing quick access by product ID.


#include<stdio.h>
#include<stdlib.h>

#define TABLE_SIZE 100

typedef struct Node{
    int productID;
    struct Node* next;
}Node;

int hashFunction(int productID){
    return productID % TABLE_SIZE;
}

void insertProduct(Node** hashTable,int productID){
    int index=hashFunction(productID);
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->productID=productID;
    newNode->next=hashTable[index];
    hashTable[index]=newNode;
}

int searchProduct(Node** hashTable,int productID){
    int index=hashFunction(productID);
    Node* current=hashTable[index];
    while(current!=NULL){
        if(current->productID==productID){
            return 1;
        }
        current=current->next;
    }
    return 0;
}

int main(){
    
    Node* hashTable[TABLE_SIZE] ={NULL};
    int numProducts,productID;
    printf("Enter the number of products: ");
    scanf("%d",&numProducts);

    for(int i=0;i<numProducts;i++){
        printf("Enter product ID %d: ",i+1);
        scanf("%d",&productID);
        insertProduct(hashTable,productID);
    }

    printf("Enter the product ID to search for: ");
    scanf("%d",&productID);
    if(searchProduct(hashTable,productID)){
        printf("Product ID %d found.\n",productID);
    }else{
        printf("Product ID %d not found.\n",productID);
    }


    for(int i=0;i<TABLE_SIZE;i++){
        Node* current=hashTable[i];
        while(current!=NULL){
            Node* temp=current;
            current=current->next;
            free(temp);
        }
    }

    return 0;
}


Sample output:

Enter the number of products: 3
Enter product ID 1: 101
Enter product ID 2: 205
Enter product ID 3: 309
Enter the product ID to search for: 205
Product ID 205 found.




Scenario 3: A content management system needs to store articles by their
unique titles and ensure quick retrieval when searching for a specific 
article. A hash table is used for storing articles, with each article 
title being hashed for efficient access


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TABLE_SIZE 100

typedef struct ArticleNode{
    char* title;
    char* content;
    struct ArticleNode* next;
}ArticleNode;

int hashFunction(char* title){
    int hash=0;
    while(*title){
        hash=(hash+*title) % TABLE_SIZE;
        title++;
    }
    return hash;
}

void insertArticle(ArticleNode** hashTable,char* title,char* content){
    int index=hashFunction(title);
    ArticleNode* newNode=(ArticleNode*)malloc(sizeof(ArticleNode));
    newNode->title=strdup(title);
    newNode->content=strdup(content);
    newNode->next=hashTable[index];
    hashTable[index]=newNode;
}

ArticleNode* searchArticle(ArticleNode** hashTable,char* title){
    int index=hashFunction(title);
    ArticleNode* current=hashTable[index];
    while(current!=NULL){
        if(strcmp(current->title,title)==0){
            return current;// Found
        }
        current=current->next;
    }
    return NULL;
}

int main(){
    ArticleNode* hashTable[TABLE_SIZE] ={ NULL };
    int numArticles;
    char title[100],content[1000];

    printf("Enter the number of articles: ");
    scanf("%d",&numArticles);
    getchar();

    for(int i=0;i<numArticles;i++){
        printf("Enter title of article %d: ",i+1);
        fgets(title,sizeof(title),stdin);
        title[strcspn(title,"\n")]='\0';// Remove newline character

        printf("Enter content of article %d: ",i+1);
        fgets(content,sizeof(content),stdin);
        content[strcspn(content,"\n")]='\0';// Remove newline character

        insertArticle(hashTable,title,content);
    }

    
    printf("Enter the title to search for: ");
    fgets(title,sizeof(title),stdin);
    title[strcspn(title,"\n")]='\0';// Remove newline character

    ArticleNode* result=searchArticle(hashTable,title);
    if(result!=NULL){
        printf("Article found: %s\nContent: %s\n",result->title,result->content);
    }else{
        printf("Article '%s' not found.\n",title);
    }

    
    for(int i=0;i<TABLE_SIZE;i++){
        ArticleNode* current=hashTable[i];
        while(current!=NULL){
            ArticleNode* temp=current;
            current=current->next;
            free(temp->title);
            free(temp->content);
            free(temp);
        }
    }

    return 0;
}


Sample output:

Enter the number of articles: 2
Enter title of article 1: Tech Trends 2024
Enter content of article 1: This article discusses upcoming tech trends.
Enter title of article 2: AI and the Future
Enter content of article 2: AI will play a major role in future innovations.
Enter the title to search for: Tech Trends 2024
Article found: Tech Trends 2024
Content: This article discusses upcoming tech trends.
