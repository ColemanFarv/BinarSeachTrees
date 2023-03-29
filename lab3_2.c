/******************************************************************************
FILENAME:     lab03_2.c
COURSE:       MREN 178
LAB:          3
STUDENTS:    [Hannah Vibien 20332596, Coleman Farvolden 20335398]
DATE:     2023-03-12

ATTRIBUTIONS: [https://www.enjoyalgorithms.com/blog/validate-binary-search-tree,https://onq.queensu.ca/d2l/le/content/685400/viewContent/4046059/View]
******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include	<stdio.h>
#include	<stdlib.h>
#include    <string.h>

int count=0;//counter for number of nodes in the tree (global variable)

//structure to store the ID, and password in a node.
typedef struct node{
    int ID;
    char password[13];
    struct node *left, *right;
}Node;

//function that generates a new node
Node * createNode(int ID, char password[]){
    Node * new=malloc(sizeof(Node));//get the size of the new node
    //initialize all variables inside the new node
    new->ID=ID;
    strcpy(new->password,password);
    new->right=NULL;
    new->left=NULL;
    return new;//return the new node
}
//function that inserts the node
void insertNode(int ID, Node * root, char password[]){
    //if the ID already exists, update the nodes password
    if(ID==root->ID){
        strcpy(root->password,password);
        count --;//decrease node count by one, since new node was not actually added
        return;
    }
    else if(ID >root->ID){//if the ID is bigger than the roots ID go to the roots right
        if (root->right!=NULL){//if the roots right pointer does not point to NULL, call the function again,
            // with the roots right node
            insertNode(ID,root->right, password);
        }else{//call the create new node function, and set the new node to be the roots right pointer
            Node * n=createNode(ID, password);
            root->right=n;
            return;//stop calling the function
        }
    }else if(ID<root->ID){//if the ID is smaller than the roots ID go to the roots left
        if(root->left!=NULL) {//if the roots left pointer does not point to NULL, call the function again,
            // using the roots left node
            insertNode(ID, root->left, password);
        }else {//call the create new node function, and set the new node to be the roots left node
            Node *n = createNode(ID, password);
            root->left = n;
            return;//stop calling the function
        }
    }
}

//function to find the smallest node
Node * findMinNode(Node * root){
    //return the roots left pointer value until it is equal to NULL, then return the root
    if (root->left == NULL) return root ;
    findMinNode(root->left);
}

//function to find the largest node
Node * findMaxNode(Node * root){
    //return the roots right pointer value until it is equal to NULL, then return the root
    if (root->right== NULL) return root ;
    findMaxNode(root->right);
}

//the function delete an item
Node * delete(struct node *root, int ID){
    if(root==NULL) {//if the root does not exist
        printf("The ID %d does not exist\n", ID);
        count ++;//add one to the count as no node was actually deleted.
        return NULL;
    }
    //searching for the item to be deleted, until the ID is found (ID==root->ID)
    if (ID>root->ID)//if the deleted ID is bigger than the roots ID go right
        root->right = delete(root->right, ID);//call the function again, with the roots right node
    else if(ID<root->ID)//if the deleted ID is smaller than the roots ID go left
        root->left = delete(root->left, ID);//call the function again with the roots left node
    else//if the node is found that matches the ID that is to be deleted
    {
        //case #1: No Children
        if(root->left==NULL && root->right==NULL)//when both the left and right pointer of the root are NULL, just free the root
        {
            free(root);
            return NULL;
        }
            //case #2: if there is a one child
        else if(root->left==NULL || root->right==NULL)//if either the roots left or right pointer is equal to NULL
        { struct node *temp;//create temporary pointer
            if(root->left==NULL) {//if the roots left pointer is NULL
                temp = root->right;//set the temp to the roots right pointer since that is the one to be deleted
            }else if(root->right==NULL) {//if the roots right pointer is NULL,
                temp = root->left;// then set temp to be roots left pointer
            }
            free(root);//delete the root by freeing it
            return temp;//returns root to deleted nodes parent
        }

            //Case #3: 2 children
            //Make the lowest value of the right child and make that the new parent node and delete the node
        else{
            struct node *temp = findMinNode(root->right);//find the smallest ID on the right side of the node you are replacing
            root->ID = temp->ID;
            strcpy(root->password, temp->password);
            root->right = delete(root->right, temp->ID);
        }
    }
    return root;
}
//function that find the corresponding  password when given an ID
void lookUp(Node * root, int ID){
    if(ID==root->ID) printf("Id: %d, Password: %s\n", ID, root->password);//print the ID and the corresponding password

        else if(ID<root->ID){//if searched ID is smaller than the roots ID
            if(root->left!=NULL){//if the roots left pointer does not equal NULL
                lookUp(root->left, ID);//call the function again but with the roots left node
            }
            else{
                printf("Employee ID %d is not valid.\n", ID);//if the roots left pointer is NULL, the ID does not exist
            }
    }
    else if(ID>root->ID){//if searched ID is larger than the roots ID
        if(root->right!=NULL){//if the roots right pointer does not equal NULL
            lookUp(root->right, ID);//call the function again but with the roots right node
        }
        else{
            printf("Employee ID %d is not valid.\n", ID);//if the roots left pointer is NULL, the ID does not exist
        }
    }
}
//Function that checks wheather a tree is a binary tree. Is given the root of the tree.
int verifyBST(Node* root) {

    int leftMax; //creates integer that keeps track of maximum value node on left side
    int rightMin; //creates integer that keeps track of minimum value node on right side

    if (root == NULL) return 1; //if the root is null 1 is returned for the purposes of recursion

    if (root->left != NULL) { //checks if left node is null
        leftMax = (findMaxNode(root->left))->ID;   //finds the leftmax on left side
    }
    else {
        leftMax = root->ID-1; //if leftside is empty the leftmax variable is set to less then the root node
    }

    if (root->right != NULL) { //checks if right node is null
        rightMin = (findMinNode(root->right))->ID;    //finds the minimum on the right side
    }
    else {
        rightMin = root->ID+1; //if rightside is empty the rightMin variable is set to more then the root node
    }

    int Leftside = verifyBST(root->left);  //verifies recursifly the left side of the tree

    printf("%d\n", root->ID); //prints all nodes of the tree in order recursivly

    int Rightside = verifyBST(root->right); //verifies recursivly the right side of the tree

    if(leftMax > root->ID || rightMin < root->ID){ //Checks if the tree does not satisfy conditions of a binary search tree
        return 0;
    }

    if(Leftside == 1 && Rightside == 1){ //checks if the tree satisfies conditions of binary search tree
        return 1;
    }

    else{ //something is wrong and it is not a binary search tree
        return 0;
    }

}
int main() {
    //automatic order of sequence: create BST, look up the data pieces, delete nodes, verify BST and print in order
    //**NOTE** with large files since the print in order happens last, and there are so many numbers, you cannot see what the lookUp function prints.
    //All file paths need to be changed for each user, as their path will be unique to their computer
    FILE *fp = NULL;
    Node *root;
    int ID;
    char password[13];
    fp = fopen("C:\\Users\\hanna\\OneDrive - Queen's University\\Data Struc\\Lab3\\lab03_2\\IDENTS.TXT", "r");//open IDENTS file
    if (fp == NULL)printf("File cannot open\n");

    while (fscanf(fp, "%d %s", &ID, password) != EOF) {//scans until the end of the file is reached
        if (count == 0) {//if the count is 0 (no nodes) create the first node
            root = createNode(ID, password);
        }
        count ++;//add one to the total number of nodes
        if(count !=1) insertNode(ID, root, password);//if it is not the first node being added insert the node
    }

    fclose(fp);//close the IDENTS file

    printf("BST NODES:%d\n",count);//print the number of nodes

    FILE *fDelete = NULL;
    fDelete = fopen("C:\\Users\\hanna\\OneDrive - Queen's University\\Data Struc\\Lab3\\lab03_2\\DELETES.TXT", "r");//open the deletes file
    if (fDelete == NULL)printf("Lookup file cannot open\n");//if the file cannot be found
     while (fscanf(fDelete, "%d", &ID) != EOF) {//scan in the nodes to be deleted and call the delete function until the end of the file
       delete(root, ID);
        count --;//subtract 1 each time from the number of nodes in the tree
    }
     fclose(fDelete);
    printf("NODES AFTER DELETION: %d\n",count);//print the number of nodes after deletion

    //loop up ID's
    FILE *fLookUp = NULL;
    fLookUp = fopen("C:\\Users\\hanna\\OneDrive - Queen's University\\Data Struc\\Lab3\\lab03_2\\LOOKUPS.TXT", "r");//open the file of ID's to look up
    if (fLookUp == NULL)printf("Lookup file cannot open\n");//if the file cannot be found
    while (fscanf(fLookUp, "%d", &ID) != EOF) {//scan in the ID and call the lookUp function until the end of the file
        lookUp(root, ID);
    }
    fclose(fLookUp);
    if(verifyBST(root) == 0) {//check if it is a BST. If the function returns 0, it is not, if it returns anything else it is.
        printf("Not a BST\n");
    }else{
        printf("Is a BST\n");

    }
}
