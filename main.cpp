#include <iostream>
using namespace std;
struct BSTNode{
    int value;
    BSTNode *LChild;
    BSTNode *RChild;
};
void insertNode(BSTNode **root,int val);
void insertR(BSTNode **root,int val);
void searchNode(BSTNode **root,int val);
void searchR(BSTNode **root,int val);
struct BSTNode* deleteNodeR(BSTNode **root,int val);
void InOrder(BSTNode *root);
void PreOrder(BSTNode *root);
void PostOrder(BSTNode *root);
void findMax(BSTNode **root);
int maxHeight(BSTNode **root);
struct BSTNode* FindMin(BSTNode* root);

struct BSTNode *root = NULL;
void insertNode(BSTNode **root,int val){
    BSTNode *ptr = new BSTNode;
    ptr->LChild = NULL;
    ptr->RChild = NULL;
    ptr->value = val;

    if(*root == NULL){
        *root = ptr;
    }else{
        BSTNode *curr = *root;
        while(curr->LChild != NULL && curr->RChild != NULL){
            if(val < curr->value){
                curr = curr->LChild;
            }else if(val > curr->value){
                curr = curr->RChild;
            }
        }
        if (val < curr->value){
            curr->LChild = ptr;
        }else{
            curr->RChild = ptr;
        }
    }
}

void insertR(BSTNode **root,int val){
    BSTNode *ptr = new BSTNode;
    ptr->LChild = NULL;
    ptr->RChild = NULL;
    ptr->value = val;

    if(*root == NULL){
        *root = ptr;
    }else if(val < (*root)->value){
        insertR(&((*root)->LChild),val);
    }else if(val > (*root)->value){
        insertR(&((*root)->RChild),val);
    }
}

void searchNode(BSTNode **root,int val){
    if(*root == NULL){
        cout << "Tree is Empty" << endl;
    }else{
        if((*root)->value == val){
            cout << "Value: " << val << " Found." << endl;
        }else{
            BSTNode *curr = *root;
            while(curr->LChild != NULL && curr->RChild != NULL || curr!=NULL){
                if(curr->value == val){
                   cout << "Value: " << val << " Found." << endl;
                   break;
                }else if(val < curr->value){
                    curr = curr->LChild;
//                    cout << "Left Child: " << curr->value << endl;
                }else if(val > curr->value){
                    curr = curr->RChild;
//                    cout << "Right Child: " << curr->value << endl;
                }
            }
        }
    }
}

void searchR(BSTNode **root,int val){
    if((*root)->value == val){
        cout << "Value: " << val << " Found." << endl;
        return;
    }else if(val < (*root)->value){
        searchR(&((*root)->LChild),val);
    }else if(val > (*root)->value){
        searchR(&((*root)->RChild),val);
    }
    return;
}

struct BSTNode* FindMin(BSTNode* root)
{
	while(root->LChild != NULL) root = root->LChild;
	return root;
}
struct BSTNode* deleteNodeR(BSTNode **root,int val){
    if (*root == NULL) return *root;
    else if(val < (*root)->value){
         (*root)->LChild = deleteNodeR(&((*root)->LChild), val);
    }
    else if(val > (*root)->value){
        (*root)->RChild = deleteNodeR(&((*root)->RChild), val);
    }
    else{  // Value is Found
        //Case 1: No Child
        if((*root)->LChild == NULL && (*root)->RChild == NULL){
            delete *root;
            *root = NULL;
        }
        // Case 2: One Child
        else if((*root)->LChild == NULL){
            struct BSTNode *temp = *root;
            *root = (*root)->RChild;
            delete temp;
        }else if((*root)->RChild == NULL){
            struct BSTNode *temp = *root;
            *root = (*root)->LChild;
            delete temp;

        // Case 3: Having Both Children
        }else{
            struct BSTNode *temp = FindMin((*root)->RChild);
            (*root)->value = temp->value;
            (*root)->RChild = deleteNodeR(&((*root)->RChild),temp->value);
        }
    }
    return *root;
}

int maxHeight(BSTNode **root){
    if(*root == NULL){
        return 0;
    }
    int left = maxHeight(&((*root)->LChild));
    int right = maxHeight(&((*root)->RChild));

    if(left > right){
       return 1 + left;
    }else{
        return  1 + right;
    }
}

void findMax(BSTNode **root){
    BSTNode *curr = *root;
    while(curr->RChild!=NULL){
        curr = curr->RChild;
    }
    cout << "Greatest Value: " << curr->value << endl;
}


void InOrder(BSTNode *root){
    if(root == NULL){
        return;
    }else{
        InOrder(root->LChild);
        cout << root->value << "  ";
        InOrder(root->RChild);
    }
}

void PreOrder(BSTNode *root){
    if(root == NULL){
        return;
    }else{
        cout << root->value << "  ";
        PreOrder(root->LChild);
        PreOrder(root->RChild);
    }
}

void PostOrder(BSTNode *root){
    if(root == NULL){
        return;
    }else{
        PostOrder(root->LChild);
        PostOrder(root->RChild);
        cout << root->value << "  ";
    }
}

int main()
{
//    insertNode(&root,5);
//    insertNode(&root,3);
//    insertNode(&root,8);
    int arr[] = {100,50,40,60,45,150,130,170,120,135,180,110,137,175,136};
    for(int i = 0; i < 15; i++){
        insertR(&root,arr[i]);
    }
    // Print BST
    cout << "InOrder Traversal: " << endl;
    InOrder(root);
    cout << endl;
    cout << "PostOrder Traversal: " << endl;
    PostOrder(root);
    cout << endl;
    cout << "PreOrder Traversal: " << endl;
    PreOrder(root);
    cout << endl;

    cout << endl;
    findMax(&root);
    int Height = maxHeight(&root);
    cout << "Max Height = " << Height << endl;
//    deleteR(&root,25);

    cout << endl;
    searchNode(&root,40);
    searchNode(&root,130);
    searchNode(&root,175);
    searchNode(&root,110);
//    searchNode(&root,25);
//    searchNode(&root,8);
//    searchNode(&root,12);

//    searchR(&root,20);
    cout << endl;
    cout << "Deleting 45...." << endl;
    root = deleteNodeR(&root,45);
    cout << "Deleting 170...." << endl;
    root = deleteNodeR(&root,170);
    cout << "Deleting 130...." << endl;
    root = deleteNodeR(&root,130);
    cout << endl;
    // Print BST
    cout << "InOrder Traversal: " << endl;
    InOrder(root);
    cout << endl;
    cout << "PostOrder Traversal: " << endl;
    PostOrder(root);
    cout << endl;
    cout << "PreOrder Traversal: " << endl;
    PreOrder(root);
    cout << endl;

    return 0;
}
