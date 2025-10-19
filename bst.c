#include<stdio.h>
#include<stdlib.h>
struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* create(int val){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->data=val;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int val) {
    if (root == NULL)
        return create(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);
    return root;
}


void inorder(struct Node* root){
    if(!root)return;
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

void preorder(struct Node* root){
    if(!root)return;
    printf("%d ",root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct Node* root){
    if(!root)return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ",root->data);
}

struct Node* succ(struct Node* root){
    while(root->left !=NULL)root=root->left;
    return root;
}

struct Node* delete(struct Node* root, int val){
    if(!root)return NULL;
    if(val<root->data)root->left= delete(root->left,val);
    else if(val>root->data)root->right= delete(root->right,val);
    else{
        if(root->left==NULL && root->right==NULL){free(root);return NULL;}
        if(root->left==NULL && root->right !=NULL){
            struct Node* temp=root;
            root=root->right;
            free(temp);
            return root;
        }
        if(root->right==NULL && root->left !=NULL){
            struct Node* temp=root;
            root=root->left;
            free(root);
            return temp;
        }
        else{
            struct Node* next=succ(root->right);
            root->data=next->data;
            root->right=delete(root->right,next->data);
        }
    }
    return root;
}

int main(){
    int ch,op;
    int val;
    printf("Enter root node value: ");
    scanf("%d",&val);
    struct Node* root=(struct Node*)malloc(sizeof(struct Node));
    root->data=val;
    root->left=NULL;
    root->right=NULL;

    do{
    printf("\nBST MENU\n1-Insert node\n2-Inorder traversal\n3-PreorderTraversal\n4-Postorder Traversal\n5-Delete node\nAny higher key-exit\n");
    scanf("%d",&op);
    switch(op){
        case 1:printf("Enter value: ");\
               scanf("%d",&val);
               insert(root,val);
               break;
        case 2:inorder(root);
               break;
        case 3:preorder(root);
               break;
        case 4:postorder(root);
               break;
        case 5:printf("Enter value to delete: ");
               scanf("%d",&val);
               delete(root,val);
               break;  
        default: break;                                 
    }
    }while(op<6);
    return 0;
}