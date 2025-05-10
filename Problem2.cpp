// This Code for AVL Tree Address Book
#include<iostream>
#define ContactExist 2
#define ContactNotExist -2
#define Successfully 1
#define Failure 0
#define HeightBase 0
using   namespace std;

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
        :key(key),name(name),phone(phone),email(email),right(nullptr),left(nullptr),height(HeightBase){}
    // bool operator<(const AVLNode& node){return this->key < node.key;}
};

ostream& operator<<(ostream&out,const AVLNode& node){
    out<<node.key<<':'<<node.height;
    // out<<"ID: "<<node.key<<", Name: "<<node.name<<", Phone: "<<node.phone<<", Email: "<<node.email;
    return out;
}


class AVLTree{
// public:
    static int f;
    int size = 0;
    AVLNode* root;
    void ListAllContactsHelper(AVLNode* root){
        if(root == nullptr)return;
        ListAllContactsHelper(root->left);
        cout<<*root<<'\n';
        ListAllContactsHelper(root->right);
    }
    void preOrder(AVLNode*node){
        if(node == nullptr)return;
        cout<< *node <<'\n';
        preOrder(node->left);
        preOrder(node->right);
    }
    void inOrder(AVLNode*node){
        if(node == nullptr)return;
        inOrder(node->left);
        cout<< *node <<'\n';
        inOrder(node->right);
    }
    void postOrder(AVLNode*node){
        if(node == nullptr)return;
        postOrder(node->left);
        postOrder(node->right);
        cout<< *node <<'\n';
    }
    void destroy(AVLNode* root){
        if(root == nullptr)return;
        destroy(root->left);
        destroy(root->right);
        delete root;
        size--;
    }
    int height(AVLNode* node){
        if(node == nullptr) return HeightBase-1;
        return node->height;
    }
    int maxHeight(AVLNode* node){
        return 1 + max(height(node->left),height(node->right));
    }
    /*     |||   
            2
             \|
              3
               \
                4
    */
    void leftRotation(AVLNode* &node){
        AVLNode* newNode = node->right;
        node->right = newNode->left;
        newNode->left = node;
        node = newNode;
        
        node->left->height = maxHeight(node->left);
        node->height = maxHeight(node);
    }
    /*   |||
          5
        |/ \
        4
       / \
      3
    */
    void rightRotation(AVLNode* &node){
        AVLNode* newNode = node->left;
        node->left = newNode->right;
        newNode->right = node;
        node = newNode;
        
        node->right->height = maxHeight(node->right);
        node->height = maxHeight(node);
    }
    int getBalanceFactor(AVLNode *node){return height(node->right) - height(node->left);}
    void balanceTree(AVLNode* &current){
        int BF = getBalanceFactor(current);
        if(BF < -1){
            if(getBalanceFactor(current->left) < 1){
                // cout<<" -- ";
                /*--    5
                       /
                      3
                     /
                    1
                */
                rightRotation(current);
            }else{
                /* -+   5
                       /
                      3
                       \
                        4
                */
            //    cout<<" -+ ";
               leftRotation(current->left);
               rightRotation(current);
            }
        }else if(BF > 1){
            if(getBalanceFactor(current->right)>-1){
                /* ++
                     3
                      \
                       5
                        \
                         7
                */
            //    cout<<" ++ ";
               leftRotation(current);
           }else{
                /*+-
                    3
                     \
                      5
                     /
                    4
                */
                // cout<<" +- ";
                rightRotation(current->right);
                leftRotation(current);
           }
        }
    }
    
    void insert(AVLNode* &current,AVLNode* newNode){
        if(current!=nullptr && newNode->key == current->key){f=1;return;}
        
        if(current->right==nullptr && newNode->key > current->key){
            current->right = newNode;
            current->height = maxHeight(current);
            size++;
            return;
        }
        if(current->left==nullptr && current->key > newNode->key){
            current->left = newNode;
            current->height = maxHeight(current);
            size++;
            return;
        }
        if(current->key < newNode->key){
            insert(current->right,newNode);
        }else{
            insert(current->left,newNode);
        }
        current->height = maxHeight(current);
        balanceTree(current);   
        // current->height = maxHeight(current);
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
        void deleteContactHelper(AVLNode* &node,int key){
        if(node==nullptr)return;
        if(node->key > key) deleteContactHelper(node->left,key);
        else if(node->key < key) deleteContactHelper(node->right,key);
        else{
            AVLTree::f = true;
            deleteNode(node);
        }
        if(node == nullptr)return;

        node->height = maxHeight(node);
        balanceTree(node);
    }
    AVLTree(const AVLTree&)=delete;
    AVLTree(const AVLTree&&)=delete;
    void deleteNode(AVLNode* &node){
        AVLNode* temp =node;
        if(node->right == nullptr){
            node = node->left;
        }else if(node->left == nullptr){
            node = node->right;
        }else{
            temp = node->left;
            AVLNode* prev = node;
            while(temp->right != nullptr){
                prev = temp;
                temp = temp->right;
            }
            /*  5
               / \
       temp-> 3   7
             / \
            1   4
               */
            node->key = temp->key;
            if(node == prev)
                prev->left = temp->left;
            else prev->right = temp->left;
        }
        delete temp;
        size--;
    }

public:
    AVLTree():root(nullptr),size(0){}

    void ListAllContacts(){
        ListAllContactsHelper(root);
    }
    void insertContact(int key,string name,string phone,string email){
        AVLNode* newNode = new AVLNode(key,name,phone,email);
        if(root == nullptr){
            root = newNode;
            size++;
        }else{
            f = false;
            insert(root,newNode);
            if(f){
                delete newNode;
                cout<<"this ID: "<<key<<" already exist.\n";
            }
        }
    }
    void SearchContact(int key){
        AVLNode* node = search(key);
        if(node == nullptr){
            cout<<"Contact not found.\n";
        }else{
            cout<<"ID: "   <<node->key  <<'\n';
            cout<<"Name: " <<node->name <<'\n';
            cout<<"Phone: "<<node->phone<<'\n';
            cout<<"Email: "<<node->email<<'\n';
        }
    }
    
    void DeleteContact(int key){
        AVLTree::f = false;
        
        deleteContactHelper(root,key);
        
    }
    ~AVLTree(){
        destroy(root);
    }
};
int AVLTree::f = 1;



// Add New Contact                      Done
// Search for Contact                   Done
// Delete Contact (Optional)            Done
// List All Contacts (Sorted by ID)     Done
// Display Current Tree Structure

void displayOptions(){
    cout<<"---------------------------------------\n"
        <<" 1. Add New Contact ?\n"
        <<" 2. Search for Contact ?\n"
        <<" 3. Delete Contact ?\n"
        <<" 4. List All Contacts (Sorted by ID) ?\n"
        <<" 5. Display Current Tree Structure ?\n"
        <<" 6. Exit ?\n"
        <<"---------------------------------------\n"
        <<"Enter operation (1-6): ";
}
void AddNewContact(AVLTree &tree){
    int id;
    string name,phone,email;
    cout<<"Enter unique ID: ";
    cin>>id;
    cout<<"Enter Name: ";
    getline(cin,name);
    cout<<"Enter phone: ";
    getline(cin,phone);
    cout<<"Enter Email: ";
    getline(cin,email);
    tree.insertContact(id,name,phone,email);
}
void SearchForContact(AVLTree &tree){
    int id;
    cout<<"Enter ID to search: ";
    cin>>id;
    tree.SearchContact(id);
}
void DeleteContact(AVLTree &tree){
    int id;
    cout<<"Enter ID to delete: ";
    cin>>id;
    tree.DeleteContact(id);
}
void ListAllContacts(AVLTree &tree){
    tree.ListAllContacts();
}
void DisplayCurrentTreeStructure(AVLTree &tree){
    // Code
}

int main(){
    // maximum 134 chars in line 

    AVLTree tree;    
    tree.insertContact(1000,"Ahmad","01065062493","ahmad2005717@gmail.com");
    tree.insertContact(210,"Peter Jones","011-123-7890","peter.jones@example.org");
    tree.insertContact(150,"John Doe","011-123-7890","john.doe@example.com");
    tree.insertContact(310,"Omar Hassan","010-876-5432","omar.hassan@example.com");
    // tree.DeleteContact(1000);
    tree.insertContact(10,"Peter Jones","011-123-7890","peter.jones@example.org");
    tree.insertContact(9,"Peter Jones","011-123-7890","peter.jones@example.org");
    tree.insertContact(8,"Peter Jones","011-123-7890","peter.jones@example.org");
    tree.insertContact(7,"Peter Jones","011-123-7890","peter.jones@example.org");
    tree.insertContact(6,"Peter Jones","011-123-7890","peter.jones@example.org");
    tree.insertContact(5,"Omar Hassan","010-876-5432","omar.hassan@example.com");
    tree.insertContact(4,"Peter Jones","011-123-7890","peter.jones@example.org");
    tree.insertContact(3,"Omar Hassan","010-876-5432","omar.hassan@example.com");
    tree.insertContact(2,"Peter Jones","011-123-7890","peter.jones@example.org");
    tree.insertContact(1,"Peter Jones","011-123-7890","peter.jones@example.org");
    tree.insertContact(0,"Peter Jones","011-123-7890","peter.jones@example.org");
     // cout<<tree.size;
    // tree.DeleteContact(7);
    // tree.DeleteContact(310);
    // tree.DeleteContact(8);
    // tree.DeleteContact(3);
    // tree.DeleteContact(1);
    // tree.DeleteContact(0);
    // tree.DeleteContact(2);

    tree.ListAllContacts();
    return 0;
}