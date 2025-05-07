// This Code for AVL Tree Address Book
#include<iostream>
#define ContactExist 2
#define Successfully 1
#define Failure -1
using namespace std;

struct AVLNode{
    int key;
    string name;
    string phone;
    string email;
    AVLNode* right;
    AVLNode* left;
    int height;
    AVLNode():right(nullptr),left(nullptr){}
    AVLNode(int key,string name,string phone,string email)
        :key(key),name(name),phone(phone),email(email),right(nullptr),left(nullptr){}
    // bool operator<(const AVLNode& node){return this->key < node.key;}
};
ostream& operator<<(ostream&out,const AVLNode& node){
    out<<"ID: "<<node.key<<", Name: "<<node.name<<", Phone: "<<node.phone<<", Email: "<<node.email;
    return out;
}

class AVLTree{
    AVLNode* root;
    void ListAllContactsUtility(AVLNode* root){
        if(root == nullptr)return;
        ListAllContactsUtility(root->left);
        cout<<*root<<'\n';
        ListAllContactsUtility(root->right);
    }
    void destroy(AVLNode* root){
        if(root == nullptr)return;
        destroy(root->left);
        destroy(root->right);
        delete root;
    }
public:
    AVLTree():root(nullptr){}
    void ListAllContacts(){
        ListAllContactsUtility(root);
    }
    int insertContact(int key,string name,string phone,string email){
        AVLNode* newNode = new AVLNode(key,name,phone,email);
        if(root == nullptr){
            root = newNode;
        }else{
            AVLNode* temp = nullptr;
            AVLNode* current = root;
            while(current != nullptr){
                temp = current;
                if(current->key == newNode->key){return ContactExist;}
                if(current->key < newNode->key){
                    current = current->right;
                }else{
                    current = current->left;
                }
            }
            if(temp->key < newNode->key){
                temp->right = newNode;
            }else temp->left = newNode;
        }
        return Successfully;
    }
    AVLNode* search(int key){
        AVLNode* current=root;
        while(current != nullptr){
            if(current->key == key)
                return current;
            if(current->key < key)
                current = current->right;
            else current = current->left;
        }
        return current;
    }
    void SearchContact(int key){
        AVLNode* node = search(key);
        if(node == nullptr){
            cout<<"Contact not found.\n";
        }else{
            cout<<"ID: "<<node->key<<'\n';
            cout<<"Name: "<<node->name<<'\n';
            cout<<"Phone: "<<node->phone<<'\n';
            cout<<"Email: "<<node->email<<'\n';
        }
    }
    int DeleteContact(int key){
        AVLNode *node = search(key);
        AVLNode *temp =node;
        if(node == nullptr)
            return Failure;
        if(node->right == nullptr){
            node = node->left;
            // node->left = 
        }else if(node->left == nullptr){
            node = node->right;
        }else{
            temp = node->left;
            AVLNode* prev = node;
            while(temp->right != nullptr){
                prev = temp;
                temp = temp->right;
            }
            node->key = temp->key;
            if(node == prev)
                prev->left = temp->left;
            else prev->right = temp->left;
            // node->key = 
        }
        cout<<temp<<'\n';
        delete temp;
        return Successfully;
    }
    ~AVLTree(){
        destroy(root);
    }
};








int main(){
    // maximum 134 chars in line 
    
    AVLTree tree;
    tree.insertContact(1000,"Ahmad","01065062493","ahmad2005717@gmail.com");
    tree.insertContact(150,"John Doe","011-123-7890","john.doe@example.com");
    tree.insertContact(350,"Peter Jones","011-123-7890","peter.jones@example.org");
    tree.insertContact(210,"Omar Hassan","010-876-5432","omar.hassan@example.com");
    tree.DeleteContact(1000);
    tree.ListAllContacts();


    return 0;
}