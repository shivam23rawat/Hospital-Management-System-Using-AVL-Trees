#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include "funcname.h"

// A utility function to get the height of the tree
int height(patient *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
}

// A utility function to get maximum of two integers
int maxint(int a, int b) 
{ 
    return (a > b)? a : b; 
}


// A utility function to right rotate 
patient *rightRotate(patient *y) 
{ 
    patient *x = y->left; 
    patient *T2 = x->right; 
  
    // Perform rotation 
    x->right = y; 
    y->left = T2; 
  
    // Update heights 
    y->height = maxint(height(y->left), height(y->right))+1; 
    x->height = maxint(height(x->left), height(x->right))+1; 
  
    // Return new root 
    return x; 
}
// A utility function to left rotate subtree rooted with x 
patient *leftRotate(patient *x) 
{ 
    patient *y = x->right; 
    patient *T2 = y->left; 
  
    // Perform rotation 
    y->left = x; 
    x->right = T2; 
  
    //  Update heights 
    x->height = maxint(height(x->left), height(x->right))+1; 
    y->height = maxint(height(y->left), height(y->right))+1; 
  
    // Return new root 
    return y; 
} 

// Get Balance factor of node N 
int getBalance(patient *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
}

/* Helper function that allocates a new node with the given key and 
    NULL left and right pointers. */
patient* newNode(int patientID) 
{ 
    patient* node = (patient*)malloc(sizeof(patient)); 
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;  // new node is initially added at leaf 
    node->patientID=patientID;
    printf("\n\t\t\t ADD PATIENT  ");
    printf("\n\n\nEnter today's date(dd/mm/yyyy):");
    scanf("%s",node->admit_date);
    getchar();
    printf("\nEnter the Name:\t");
    gets(node->name);
    printf("\nEnter the date of birth(dd/mm/yyyy):\t");
    scanf("%s",node->dob);
    printf("\nEnter the age:\t");
    scanf("%d",&node->age);
    printf("\nEnter Gender(M/F):\t");
    getchar();
    node->gender = getchar();
    printf("\nEnter the phone number:\t");
    scanf("%s",&node->phone);
    getchar();
    printf("\nEnter Disease/Injury:\t");
    gets(node->disease);
    printf("\nEnter Treatment:\t");
    gets(node->treatment);

    FILE *ptr;
    ptr=fopen("record.txt","a+");
    fprintf(ptr,"%d %s %s %s %d %c %s %s %s\n",node->patientID,node->admit_date,node->name,node->dob,node->age,node->gender,node->phone,node->disease,node->treatment);
    fclose(ptr);


    return(node); 
}

// Recursive function to insert a key in the subtree rooted 
// with node and returns the new root of the subtree.
patient* insert(patient* node,int key) 
{ 
    /* 1.  Perform the normal BST insertion */
    if (node == NULL) 
        return(newNode(key)); 
  
    if (key < node->patientID) 
        node->left  = insert(node->left, key); 
    else if (key > node->patientID) 
        node->right = insert(node->right, key); 
    else // Equal keys are not allowed in BST 
        return node; 
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + maxint(height(node->left), 
                           height(node->right)); 
  
    /* 3. Get the balance factor of this ancestor 
          node to check whether this node became 
          unbalanced */
    int balance = getBalance(node); 
  
    // If this node becomes unbalanced, then 
    // there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && key < node->left->patientID) 
        return rightRotate(node); 
  
    // Right Right Case 
    if (balance < -1 && key > node->right->patientID) 
        return leftRotate(node); 
  
    // Left Right Case 
    if (balance > 1 && key > node->left->patientID) 
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
  
    // Right Left Case 
    if (balance < -1 && key < node->right->patientID) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
  
    /* return the (unchanged) node pointer */
    return node; 
} 
//Function to Display all the nodes in AVL Tree
void displayAll(patient *root) 
{ 
    if(root != NULL) 
    { 
        printf("\nPatient ID:\t");
        printf("%d",root->patientID);
        printf("\nPatient Name:\t");
        printf("%s",root->name);
        printf("\nPatient Admit Date:\t");
        printf("%s",root->admit_date);
        printf("\n");
        displayAll(root->left); 
        displayAll(root->right); 
    }
}

// C function to search a given key in a given BST 

patient* search(patient* root,int key) 
{ 
    // Base Cases: root is null or key is present at root 
    if (root == NULL || root->patientID == key) 
       return root; 
     
    // Key is greater than root's key 
    if (root->patientID < key) 
       return search(root->right, key); 
  
    // Key is smaller than root's key 
    return search(root->left, key); 
}

patient* del(patient *tTree, int delItem) /* delete( main body) */
{
    if(!(tTree))
        return tTree;
    if(delItem < tTree->patientID)
        tTree->left = del(tTree->left, delItem);
    else 
        if(delItem > tTree->patientID)
            tTree->right = del(tTree->right, delItem); 
        else 
        {
            patient *oTree = tTree;
            if((tTree->left) && (tTree->right))
            {
                patient *parent = tTree->right;
                tTree = parent->left;
                if (tTree)
                {
                    while(tTree->left)
                    {
                        parent = tTree;
                        tTree = tTree->left;
                    }
                    parent->left = tTree->right;
                    tTree->right = oTree->right;
                }
                else
                    tTree = parent;
                tTree->left = oTree->left;
            }
            else
                if(tTree->left)
                    tTree = tTree->left;
                else
                    tTree = tTree->right;
            free(oTree);
        }
    return tTree;
}

void displayNode(patient* root)
{
    if(root==NULL)
        printf("\nNot Found\n");
    else
    {
    printf("\nPatient ID:\t");
    printf("%d",root->patientID);
    printf("\nPatient Name:\t");
    printf("%s",root->name);
    printf("\nPatient gender:\t");
    printf("%c",root->gender);
    printf("\nPatient Admit Date:\t");
    printf("%s",root->admit_date);
    printf("\nPatient DOB:\t");
    printf("%s",root->dob);
    printf("\nPatient Age:\t");
    printf("%d",root->age);
    printf("\nPatient phone:\t");
    printf("%s",root->phone);
    printf("\nPatient Disease/Injury:\t");
    printf("%s",root->disease);
    printf("\nPatient Treatment:\t");
    printf("%s\n",root->treatment);
    }
}

/* Given a non-empty binary search tree,  
return the node with minimum key value  
found in that tree. Note that the entire  
tree does not need to be searched. */

patient* minValueNode(patient* node)  
{  
    patient* current = node;  
  
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)  
        current = current->left;  
  
    return current;  
}

//Function to clear display after each operation
void clr()
{
	printf("\nPress Enter to continue\n");
	getchar();
	getchar();
	system("cls");
}

void deletefile(int key)
{
    char name[60];
    int age;
    int patientID;
    char gender;
    char disease[60];
    char treatment[60];
    char phone[11];
    char dob[11];
    char admit_date[11];
    FILE *old,*newrec;
    old=fopen("record.txt","r");
    newrec=fopen("new.txt","w");
    while(fscanf(old,"%d %s %s %s %d %c %s %s %s\n",&patientID,admit_date,name,dob,&age,&gender,phone,disease,treatment)!=EOF)
    {
        if(patientID!=key)
            fprintf(newrec,"%d %s %s %s %d %c %s %s %s\n",patientID,admit_date,name,dob,age,gender,phone,disease,treatment);
    }
    fclose(old);
    fclose(newrec);
    remove("record.txt");
    rename("new.txt","record.txt");

}

patient* insertFromFile(patient* node,char name[60],int age,int patientID,char gender,char disease[60],char treatment[60],char phone[11],char dob[11],char admit_date[11]) 
{ 
    
    /* 1.  Perform the normal BST insertion */
    if (node == NULL) 
        return(newNodeFromFile(name,age,patientID,gender,disease,treatment,phone,dob,admit_date)); 
  
    if (patientID < node->patientID) 
        node->left  = insertFromFile(node->left,name,age,patientID,gender,disease,treatment,phone,dob,admit_date); 
    else if (patientID > node->patientID) 
        node->right = insertFromFile(node->right,name,age,patientID,gender,disease,treatment,phone,dob,admit_date); 
    else // Equal keys are not allowed in BST 
        return node; 
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + maxint(height(node->left), 
                           height(node->right)); 
  
    /* 3. Get the balance factor of this ancestor 
          node to check whether this node became 
          unbalanced */
    int balance = getBalance(node); 
  
    // If this node becomes unbalanced, then 
    // there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && patientID < node->left->patientID) 
        return rightRotate(node); 
  
    // Right Right Case 
    if (balance < -1 && patientID > node->right->patientID) 
        return leftRotate(node); 
  
    // Left Right Case 
    if (balance > 1 && patientID > node->left->patientID) 
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
  
    // Right Left Case 
    if (balance < -1 && patientID < node->right->patientID) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
  
    /* return the (unchanged) node pointer */
    return node; 
} 


patient* newNodeFromFile(char name[60],int age,int patientID,char gender,char disease[60],char treatment[60],char phone[11],char dob[11],char admit_date[11]) 
{   
    patient* node = (patient*)malloc(sizeof(patient)); 
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;  // new node is initially added at leaf 
    node->age=age;
    strcpy(node->disease,disease);
    strcpy(node->admit_date,admit_date);
    strcpy(node->name,name);
    strcpy(node->dob,dob);
    strcpy(node->treatment,treatment);
    strcpy(node->phone,phone);
    node->gender=gender;
    node->patientID=patientID;
    return(node); 
}

patient* load(patient *node)
{
    char name[60];
    int age;
    int patientID;
    char gender;
    char disease[60];
    char treatment[60];
    char phone[11];
    char dob[11];
    char admit_date[11];
    FILE *ptr;
    ptr=fopen("record.txt","r");
    while(fscanf(ptr,"%d %s %s %s %d %c %s %s %s\n",&patientID,admit_date,name,dob,&age,&gender,phone,disease,treatment)!=EOF)
    {
        
        node=insertFromFile(node,name,age,patientID,gender,disease,treatment,phone,dob,admit_date);
    }
    fclose(ptr);
    return node;
}

// Function to print binary tree in 2D 
// It does reverse inorder traversal 
void print2DUtil(patient *root,int space) 
{ 
    // Base case 
    if (root == NULL) 
        return; 
  
    // Increase distance between levels 
    space += COUNT; 
  
    // Process right child first 
    print2DUtil(root->right, space); 
  
    // Print current node after space 
    // count 
    printf("\n"); 
    for (int i = COUNT; i < space; i++) 
        printf(" "); 
    printf("%d\n", root->patientID); 
  
    // Process left child 
    print2DUtil(root->left, space); 
} 
