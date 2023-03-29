/******************************************************************************
FILENAME:     lab3_bst.c
COURSE:       MREN 178
LAB:          3
STUDENTS:    [Hannah Vibien 20332596, Coleman Farvolden 20335398]
DATE: 2023-03-12

ATTRIBUTIONS: [https://www.geeksforgeeks.org/deletion-binary-tree/]
******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/* MREN 178 - Code is missing from the implmentation of this binary search tree.
 * Fill in the missing code.
 */
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include "lab3_bst.h"


Node *initNode (Key k, void *v)
// Allocate memory for new node and initialize fields.
// Returns pointer to node created.
{
    Node *n = (Node*) malloc(sizeof(Node));
// initialize node if memory obtained
    if (n != NULL){
        n->key = k;
        n->value = v;
        n->leftChild = NULL;
        n->rightChild = NULL;
    }
    return n;
}//initNode()


Tree *initTree(Key k, void *v)
// Set up new tree. Allocates memory for Tree structure, then
// calls initNode() to allocate first node.
{
    Tree* t = (Tree*) malloc(sizeof(Tree));
    if (t != NULL)
        t->root = initNode(k,v);
    return t;
}//initTree()


void printTreeExplanation (void)
// Prints hint to reader what to expect on screen
{
    static int done = 0;
    if (!done) {
        printf ("First time explanation of tree display:\n");
        printf ("Every node is displayed as a comma-separated pair within brackets:");
        printf (" (kk,vv)\n");
        printf ("where kk is the key and vv is the value\n");
        printf ("A tree starts with a curly bracket { and ends with a curly bracket }.\n");
        printf ("An empty tree will be {}\n");
        printf ("A tree with no children will be { (kk,vv),{},{} }\n");
        printf ("If either subtree is populated, it will be shown using the same ");
        printf ("technique as described above\n");
        printf ("(Hint: Start at root - and then match up all the remaining\n");
        printf ("brackets, then interpret what those bracket pairs are telling\n");
        printf ("you.)\n============\n\n");
        done = 1;
    }
}//printTreeExplanation()


void printTree (Node* root)
// Print whole tree. We cannot make it look pretty graphically, so we add some
// characters to make it a little easier to understand.  We also don't really
// know what the value field is - it is declared to be a void pointer - so we
// treat it as though it points to an integer.
{
// assume printTree magically knows the types in the tree node
    printTreeExplanation();
// start of this tree
    printf("{");
// values in the root node (assuming value is pointing to an integer)
    printf("(%ld,%d),", root->key, *(int*)root->value);

// Now show left subtree or {} if there is no left subtree
    if (root->leftChild != NULL) printTree(root->leftChild);
    else printf("{}");
// Marker between left and right subtrees
    printf(",");
// Now show right subtree or {} if there is no right subtree
    if (root->rightChild != NULL) printTree(root->rightChild);
    else printf("{}");
// Close display of this tree with closing curly bracket
    printf("}");
}//printTree()


Node *find (Key k, Node *root)
// Function locates node with key value equal to parameter k. Parameter
// root holds pointer to root node of tree. Function returns immediately
// if either root pointer is null, or the node that root points to has
// key value sought.  If neither of those conditions is true, then the
// function calls itself with a pointer to either the left or right
// subtree.
{
// termination conditions - either true, search is ended
    if ((root == NULL) || (root->key == k)) return root;
// search continues.  Since this is a search tree, we know that
// every key in the right subtree is bigger than the key in the tree's
// root, and every key in the left subtree is smaller than the key in
// the tree's root.  That allows us to choose the appropriate subtree
// to search.
    if (k > root->key)
// Key value sought is larger than current node key, so search right
// subtree
        return find(k,root->rightChild);
    else
// Key value sought is smaller than current node key (the equal case
// was handled as a termination condition in the first line), so
// search left subtree
        return find(k,root->leftChild);
}//find()



int insert(Key k, void *v, Node *root)
// Function inserts a new node into the tree, with key k and value pointed to
// by v. Parameter root points to root node of tree.  Note that this code
// rejects an attempt to insert a duplicate key.
{
    int result = BST_FAIL;
// this if statement can only be true with first root (root of whole tree)
    if (root == NULL) {
        Node *n = initNode(k,v);
        root = n;
        return BST_SUCCESS;
    }

// already exists in tree ==> can't insert
    if (root->key == k)
        result = BST_FAIL;
    else if (k < root->key) {
// key value less than key value in root node - try to insert into left
// subtree, if it exists.
        if (root->leftChild != NULL)
// there is a left subtree - insert it
            result = insert(k, v, root->leftChild);
        else {
// new Node becomes the left subtree
            Node *n = initNode(k,v);
            root->leftChild = n;
            result = BST_SUCCESS;
        }
    } else if (k > root->key) { // test actually redundant
// key is greater than this nodes key value, so value goes into right
// subtree, if it exists
        if (root->rightChild != NULL)
// there is a right subtree - insert new node
            result = insert(k,v,root->rightChild);
        else {
// no right subtree - new node becomes right subtree
            Node*n = initNode(k,v);
            root->rightChild = n;
            result = BST_SUCCESS;
        }
    }
    return result;
}//insert()


int intmax(int a, int b)
// YOU WILL USE THIS FUNCTION WHEN YOU IMPLEMENT HEIGHT() !!
// Useful function - returns the greater value of two integers.
// Called intmax, not max, because max already exists.
// It is a chance to see a conditional expression in C - a value that is the
// first one (after the ?) if the condition is true, or the second one (after
// the :) if the condition is false.
{
    return (a>=b) ? a : b;
}//intmax()


int _height(Node *root)
// Height definition:
// Height of an empty tree is -1.  Height of a leaf node is 0. Height of other
// nodes is 1 more than larger height of node's two subtrees.
{
    int leftHeight, rightHeight;

    if(root==NULL)return -1;//if tree is emoty then return -1;

    if(root->leftChild==NULL && root->rightChild==NULL) return 0;//if tree only has one node, height is 0

    else{
        leftHeight = _height(root->leftChild);//recursively iterating down the tree
        rightHeight = _height(root->rightChild);//recursively iterating down the tree

        if(max(leftHeight, rightHeight)==leftHeight)return(leftHeight +1); //add to height sum with the longest path which is the left side of the node
        else return (rightHeight+1); //add to height sum with the longest path which is the right side of the node

        // your code goes here  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    }//height()
}


Node *_findParentHelper (Key k, Node* root){
// Help find parent of node with key == k. Parameter root is node with
// at least one child (see findParent()).
//ALL YOU ARE FDOING IS FINDING THE PARENTS KEY

    while(root!=NULL && root->key !=k){//while root dosen't equal NULL or the key isn't found run the loop

        Node *temp=root;//set temp to root

        if(k > root->key){
            root=root->rightChild;//if the value of the key is bigger then the value of the right set the root to be roots right node
        }
        else root=root->leftChild;//if the value of the key is smaller then the value of the right set the root to be roots left node

        if(k == root->key) return temp;//if the valye fo the new root is equal to the key, return temp as that is the nodes parent
        else _findParentHelper(k, root);//if not call the function with the new root, and go through again  b



    }
}

// your code goes here  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//findparenthelper()


Node *findParent(Key k, Node *root){

    // Deal with special special cases which could only happen for root
    // of whole tree
    if (root == NULL)  return root;
    // real root doesn't have parent so we make it parent of itself
    if (root->key == k)    return root;
    // root has no children
    if ((root->leftChild == NULL) && (root->rightChild == NULL))
        return NULL;

    // Deal with cases where root has at least one child
    return _findParentHelper(k, root);
}//findParent()


void _delete (Node *p, Node *n)
// Delete node pointed to by n.
// Parameters:
// n  - points to node to be deleted
// p  - points to parent of node to be deleted.
{
    // your code goes here  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//Case 1 if parent is null
    if (p  == NULL){
        return;
    }




    //Case 2 for right side of p and is leaf node

    if(p->rightChild==n) {//if n is on the right side of p
        if(n->rightChild==NULL && n->leftChild==NULL) {//if both n left and right children are equal to NULL
            free(n);    //delete node
            p->rightChild = NULL;//set parents right child to NULL
            return;
        }
    }

//case 3 for left side of p and is leaf node
    if(p->leftChild==n) {//if n is on the right side of p
        if(n->rightChild==NULL && n->leftChild==NULL) {//if both n left and right children are equal to NULL
            free(n);    //delete node
            p->leftChild = NULL;//set parents right child to NULL
            return;
        }
    }


    if(n->rightChild==NULL || n->leftChild==NULL){//if either the left or the right child of n is NULL

        //Case 4 n only has right children and is on left side of p
        if(p->leftChild==n) {//if n is on the right side of p
            if(n->rightChild!=NULL){//if n's right child isn't NULL
                p->leftChild=n->rightChild;//set p right child to be n right child
                free(n);//delete n
                return;
            }
        }

//Case 5 n only has left children and is on left side of p
        if(p->leftChild==n) {//if n is on the right side of p
            if(n->leftChild!=NULL){//if n's right node isn't NULL
                p->leftChild=n->leftChild;//set p rights child to be n left child
                free(n);//delete n
                return;
            }
        }

//Case 6 n only has right children and is on right side of p
        if(p->rightChild==n) {//if n is on the right side of p
            if(n->rightChild!=NULL){//if n's right child isn't NULL
                p->rightChild=n->rightChild;//set p right child to be n right child
                free(n);//delete n
                return;
            }
        }

//Case 7 n only had left children and is on the right side of p

        if(p->rightChild==n) {//if n is on the right side of p
            if(n->leftChild!=NULL){//if n's right child isn't NULL
                p->rightChild=n->leftChild;//set p right child to be n right child
                free(n);//delete n
                return;
            }
        }
    }

//Case 8 deleting node with both subtrees on left side of parent

    if(p->leftChild == n){ //if the leftchild of parent is the value node be deleted

        struct Node* trail = n; //Create a pointer to the parent as a follower pointer
        struct Node* searhTrail = n->leftChild; //Create a temporary traversal pointer to the left child of the node to be deleted

        struct Node* replace; //Create replacement pointer

        while(searhTrail->rightChild != NULL){ //Find the maximum node on the left side of the node to be deleted

            trail = searhTrail; //Iterate follower at each repitition to move and find maximum node's parent
            searhTrail = searhTrail->rightChild; //Iterate transverser at each repitition to move and find maximum node

        }

        p->leftChild = NULL; //Sets the parents leftchild to be null
        replace = searhTrail; //replacement pointer is the max node on left side


        replace->rightChild = n->rightChild; //sets the replacement children to be the same as the deleted node children

        if(n->leftChild != replace) { //Check that your not replacing the nodes leftchild with itself

            replace->leftChild = n->leftChild; //sets the replacement children to be the same as the deleted node children
        }

        p->leftChild = replace; //The parent of the deleted nodes leftchild is the replacement node

        free(n); //Free the deleted node
        return;

    }



//Case 9 deleting node with both subtrees on right side of parent

    if(p->rightChild == n){ //if the righthild of parent is the value nodo be deleted

        struct Node* searhTrail = n->leftChild; //Create a temporary traversal pointer to the left child of the node to be deleted


        struct Node* trail = n; //Create a pointer to the parent as a follower pointer

        struct Node* replace; //Create replacement pointer


        while(searhTrail->rightChild != NULL){ //Find the maximum node on the left side of the node to be deleted


            trail = searhTrail; //Iterate follower at each repitition to move and find maximum node's parent

            searhTrail = searhTrail->rightChild; //Iterate transverser at each repitition to move and find maximum node

        }

        p->rightChild = NULL; //Sets the parents Rightchild to be null

        replace = searhTrail; //replacement pointer is the max node on left side



        replace->rightChild = n->rightChild; //sets the replacement children to be the same as the deleted node children

        if(n->leftChild!= replace) { //Check that your not replacing the nodes rightchild with itself

            replace->leftChild = n->leftChild; //sets the replacement children to be the same as the deleted node children
        }


        p->rightChild = replace; //The parent of the deleted nodes rightchild is the replacement node


        free(n); //Free the deleted node
        return;
    }

}//_delete(