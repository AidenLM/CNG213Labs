#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 16
#define FALSE 0
#define TRUE 1

/*A tree Node declaration*/
struct Node
{
    int val;
    struct Node* left;
    struct Node* right;
};

typedef struct Node *Tree;
/*Function signatures*/
Tree CreateTree(void);
Tree MakeEmptyTree(Tree);
Tree InsertElement(int, Tree);
void DisplayTree(Tree);
int IterativeFindMinimum(Tree t);
int IterativeFindMaximum(Tree t);
int RecursiveFindMaximum(Tree t);
int RecursiveFindMinimum(Tree t);
Tree RecursiveFindElement(Tree t,int val);
Tree IterativeFindElement(Tree t,int val);
int CountTree(Tree t);
int TreeHeight(Tree t);

int main()
{
    Tree myTree, pos, Value;
    int exit, val, height;
    char command;
    int minVal = -1;

    myTree = CreateTree();
    exit = FALSE;
    fflush(stdin);

    while (!exit)
    {
        fflush(stdin);
        printf("\nMenu:\n i)nitialize\n n)ew element \n a)Iterative Find Minimum\n b)Iterative Find Maximum\n"
               " c)Recursive Find Maximum\n d)Recursive Find Minimum\n e)xit\n f)Recursive Find Element\n g)Iterative Find Element\n h)Count Nodes\n j)Height of Tree\n Enter command: ");
        scanf("%c", &command);
        fflush(stdin);

        switch(command)
        {
            case 'i':
                myTree = MakeEmptyTree(myTree);
                break;
            case 'n':
                printf("enter value: ");
                scanf("%d", &val);
                myTree = InsertElement(val, myTree);
                DisplayTree(myTree);
                break;
            case 'a':
                minVal = IterativeFindMinimum(myTree);
                printf("Min Val: %d\n",minVal);
                break;
            case 'b':
                minVal = IterativeFindMaximum(myTree);
                printf("Max Val: %d\n",minVal);
                break;
            case 'c':
                minVal= RecursiveFindMaximum(myTree);
                printf("Max Val: %d\n",minVal);
                break;
            case 'd':
                minVal = RecursiveFindMinimum(myTree);
                printf("Min Val: %d\n",minVal);
                break;
            case 'e':
                exit = TRUE;
                break;
            case 'f':
                printf("enter value: ");
                scanf("%d", &val);
                Value = RecursiveFindElement(myTree,val);
                if(Value == NULL){
                    printf("Element not found!\n");
                }else{
                    printf("Element is found : %d\n",Value->val);
                }
                break;
            case 'g':
                printf("enter value: ");
                scanf("%d", &val);
                Value = IterativeFindElement(myTree,val);
                if(Value == NULL){
                    printf("Element not found!\n");
                }else{
                    printf("Element is found : %d\n",Value->val);
                }
                break;
            case 'h':
                minVal = CountTree(myTree);
                printf("Number of Count: %d\n",minVal);
                break;
            case 'j':
                height = TreeHeight(myTree);
                printf("Height of Tree: %d\n",height);
                break;
            default:
                printf("command not recognized\n");
                break;

        }
        fflush(stdin);


    }

    printf("\n\n");
    system("PAUSE");
    return 0;
}

/*Function that mainly creates a tree which is initially NULL*/
Tree CreateTree(void)
{
    return NULL;
}

/*Function that takes a tree and makes it an empty tree by removing all the nodes from that tree*/
Tree MakeEmptyTree(Tree t)
{
    if (t != NULL)
    {
        MakeEmptyTree(t->left);
        MakeEmptyTree(t->right);
        free(t);
    }
    return NULL;
}

/*This function takes an integer value and a tree,
  and inserts that value to the tree*/
Tree InsertElement(int val, Tree t)
{
    if(t == NULL){
        t = malloc(sizeof(struct Node));
        if(t == NULL){
            printf("Allocation is failed!\n");
            exit(1);
        }else{
            t->val = val;
            t->right = t->left = NULL;
        }
    }
    else if(val > t->val){
        t->right = InsertElement(val,t->right);
    }
    else if(val< t->val){
        t->left = InsertElement(val,t->left);
    }

    return t;
}

/*This function takes a tree and displays its content on the screen*/
void DisplayTree(Tree t)
{
    if (t !=NULL)
    {
        DisplayTree(t->left);
        printf("%d\n", t->val);
        DisplayTree(t->right);
    }
}


int IterativeFindMinimum(Tree t){


    while (t != NULL){

        if(t->left == NULL){
            return t->val;
        }

        if(t->left != NULL){
            t = t->left;
        }
    }

    return 0;
}

int IterativeFindMaximum(Tree t){


    while (t != NULL){

        if(t->right == NULL){
            return t->val;
        }

        if(t->right != NULL){
            t = t->right;
        }
    }

    return 0;
}

int RecursiveFindMaximum(Tree t){

    if(t->right == NULL){
        return t->val;
    }else{
        return RecursiveFindMaximum(t->right);
    }

}

int RecursiveFindMinimum(Tree t){

    if(t->left == NULL){
        return t->val;
    }
    else{
        return RecursiveFindMinimum(t->left);
    }
}


Tree RecursiveFindElement(Tree t,int val){

    if(t == NULL || t->val == val){
        return t;
    }else if(t->val > val){
        return RecursiveFindElement(t->left,val);
    }else if(t->val < val){
        return RecursiveFindElement(t->right,val);
    }

}

Tree IterativeFindElement(Tree t,int val){
    while (t != NULL){
        if(t->val == val){
            return t;
        }else if(t->val > val){
            t = t->left;
        }else if(t->val < val)
        {
            t = t->right;
        }
    }
    return NULL;
}

int CountTree(Tree t){

    if(t == NULL){
        return 0;
    }else{
        return (CountTree(t->right) + CountTree(t->left) + 1);
    }

}

int TreeHeight(Tree t){
    if(t == NULL){
        return -1;
    }
    int rightTree = TreeHeight(t->right);
    int leftTree = TreeHeight(t->left);

    if(rightTree > leftTree){
        return rightTree + 1;
    }else{
        return leftTree + 1;
    }

}


