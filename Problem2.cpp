#include <iostream>
#include<iomanip>
using namespace std;

#define HeightBase 0
const int dash = -1193125632,MN =-1193725633,space=-1793125634,slash=-1193125675,backslash=-1193925636;

struct AVLNode {
    int key;
    string name;
    string phone;
    string email;
    AVLNode* right;
    AVLNode* left;
    int height;
    AVLNode() : right(nullptr), left(nullptr), height(HeightBase) {}
    AVLNode(int key, string name, string phone, string email)
        : key(key), name(name), phone(phone), email(email), right(nullptr), left(nullptr), height(HeightBase) {}
};

ostream& operator<<(ostream& out, const AVLNode& node) {
    out << "ID: " << node.key << '\n'
        << "Name: " << node.name << '\n'
        << "Phone: " << node.phone << '\n'
        << "Email: " << node.email;
    return out;
}

class AVLTree {
    static int f;
    int size = 0;
    AVLNode* root;

    int height(AVLNode* node) {
        if (node == nullptr) return HeightBase - 1;
        return node->height;
    }

    int maxHeight(AVLNode* node) {
        return 1 + max(height(node->left), height(node->right));
    }

    void leftRotation(AVLNode*& node) {
        AVLNode* newNode = node->right;
        node->right = newNode->left;
        newNode->left = node;
        node = newNode;

        node->left->height = maxHeight(node->left);
        node->height = maxHeight(node);
    }

    void rightRotation(AVLNode*& node) {
        AVLNode* newNode = node->left;
        node->left = newNode->right;
        newNode->right = node;
        node = newNode;

        node->right->height = maxHeight(node->right);
        node->height = maxHeight(node);
    }

    int getBalanceFactor(AVLNode* node) {
        return height(node->right) - height(node->left);
    }

    void balanceTree(AVLNode*& current) {
        int BF = getBalanceFactor(current);
        if (BF < -1) {
            if (getBalanceFactor(current->left) < 1) {
                rightRotation(current);
            } else {
                leftRotation(current->left);
                rightRotation(current);
            }
        } else if (BF > 1) {
            if (getBalanceFactor(current->right) > -1) {
                leftRotation(current);
            } else {
                rightRotation(current->right);
                leftRotation(current);
            }
        }
    }

    void insert(AVLNode*& current, AVLNode* newNode) {
        if (current != nullptr && newNode->key == current->key) {
            f = 1;
            return;
        }

        if (current->right == nullptr && newNode->key > current->key) {
            current->right = newNode;
            current->height = maxHeight(current);
            size++;
            return;
        }
        if (current->left == nullptr && current->key > newNode->key) {
            current->left = newNode;
            current->height = maxHeight(current);
            size++;
            return;
        }

        if (current->key < newNode->key) {
            insert(current->right, newNode);
        } else {
            insert(current->left, newNode);
        }
        current->height = maxHeight(current);
        balanceTree(current);
    }

    AVLNode* search(int key) {
        AVLNode* current = root;
        while (current != nullptr) {
            if (current->key == key)
                return current;
            if (current->key < key)
                current = current->right;
            else
                current = current->left;
        }
        return current;
    }

    void deleteContactHelper(AVLNode*& node, int key) {
        if (node == nullptr) return;
        if (node->key > key)
            deleteContactHelper(node->left, key);
        else if (node->key < key)
            deleteContactHelper(node->right, key);
        else {
            AVLTree::f = true;
            deleteNode(node);
        }
        if (node == nullptr) return;

        node->height = maxHeight(node);
        balanceTree(node);
    }

    void deleteNode(AVLNode*& node) {
        AVLNode* temp = node;
        if (node->right == nullptr) {
            node = node->left;
        } else if (node->left == nullptr) {
            node = node->right;
        } else {
            temp = node->left;
            AVLNode* prev = node;
            while (temp->right != nullptr) {
                prev = temp;
                temp = temp->right;
            }
            node->key = temp->key;
            node->name = temp->name;
            node->phone = temp->phone;
            node->email = temp->email;

            if (node == prev)
                prev->left = temp->left;
            else
                prev->right = temp->left;
        }
        delete temp;
        size--;
    }

    void destroy(AVLNode* root) {
        if (root == nullptr) return;
        destroy(root->left);
        destroy(root->right);
        delete root;
        size--;
    }

    void ListAllContactsHelper(AVLNode* root) {
        if (root == nullptr) return;
        ListAllContactsHelper(root->left);
        cout << "ID: " << root->key
             << ", Name: " << root->name
             << ", Phone: " << root->phone
             << ", Email: " << root->email << '\n';

        ListAllContactsHelper(root->right);
    }


    void DisplayTreeHelper(AVLNode* node, string indent = "", bool last = true) {
        if (node) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "     ";
            } else {
                cout << "L----";
                indent += "|    ";
            }
            cout << node->key << '\n';
            DisplayTreeHelper(node->left, indent, false);
            DisplayTreeHelper(node->right, indent, true);
        }
    }
    /* Added by Ahmad Ibrahim */
    void print2DTree(int**show,int N,int M,int s){
        cout<<'\n';
        for(int i=0;i<N;++i){
            for(int j=0;j<M;++j){
                if(show[i][j]==dash)cout<<setfill('_')<<setw(s)<<"_";
                else if(show[i][j]==space)cout<<setfill(' ')<<setw(s)<<" ";
                else if(show[i][j]==slash)cout<<right<<setw(s)<<'/';
                else if(show[i][j]==backslash)cout<<left<<setw(s)<<'\\';
                else if(N-i-1)cout<<setfill('_')<<setw(s)<<show[i][j];
                else cout<<setfill(' ')<<setw(s)<<show[i][j];        
            }cout<<'\n';
        }
    }
    void setDash(int**show,int i,int j,int l){if(j>l)swap(j,l);for(int k=j+1;k<l;++k)show[i][k]=dash;}
    void navigate(int arr[],int**show,int N,int M,int k=1,int i=0,int j=15,int s=8){
        if(k>M)return;
        show[i][j]=arr[k-1];
        int d= k<<1;
        if(d<=M && arr[d-1]!=MN){
            setDash(show,i,j,j-s);
            show[i+1][j-s]=slash;
            navigate(arr,show,N,M,d,i+2,j-s,s>>1);
        }
        if(d<=M && arr[d]!=MN){
            setDash(show,i,j,j+s);
            show[i+1][j+s]=backslash;
            navigate(arr,show,N,M,d+1,i+2,j+s,s>>1);
        }
    }
    /*          The End         */
public:
    AVLTree() : root(nullptr), size(0) {}
    ~AVLTree() { destroy(root); }

    void insertContact(int key, string name, string phone, string email) {
        AVLNode* newNode = new AVLNode(key, name, phone, email);
        if (root == nullptr) {
            root = newNode;
            size++;
        } else {
            f = false;
            insert(root, newNode);
            if (f) {
                delete newNode;
                cout << "Error: Contact with ID " << key << " already exists.\n";
            }
        }
    }

   void SearchContact(int key) {
        AVLNode* node = search(key);
        if (node == nullptr) {
            cout << "Contact not found.\n";
        } else {
            cout << "Contact found:\n\n" << *node << "\n\n";
        }
    }

    void DeleteContact(int key) {
        AVLTree::f = false;
        deleteContactHelper(root, key);
        if (!f) {
            cout << "Contact not found.\n";
        } else {
            cout << "Contact deleted successfully.\n";
        }
    }

    void ListAllContacts() {
        if (size == 0) {
            cout << "Address Book is empty.\n";
        } else {
            cout << "Contacts in Address Book (sorted by ID):\n";
            ListAllContactsHelper(root);
        }
    }

    void displayTree() {
        if (root == nullptr) {
            cout << "Tree is empty.\n";
        } else {
            DisplayTreeHelper(root);
        }
    }
/* 
public static void sketch(Node node){
   printNode(node,0);
}
public static int printNode(Node node, int level){
  String line = "";
  String lineLeft = "";
  String lineRight = "";
  for (int i = 0; i++; i<level){
   line = line + "  ";
   lineLeft = lineLeft + "  ";
   lineRight = lineRight + "  ";
  }
  line = line + node.getValue();

  System.out.println(line);
  System.out.println(lineLeft);
  if(node.getLeft() != null){
   printNode(node.getLeft(), level+1); 
  }
 .... proceed here
*/
    void printNode(AVLNode *node,int level){
        string line = "";
        string lineLeft = "";
        string lineRight = "";
        for(int i=0;i<level;++i){
            line+=" ";lineLeft+=" ";lineRight+=" ";
        }
    }
    void printHelper(int*data,AVLNode *node,int i=1){
        if(node == nullptr)return;
        data[i -1] = node->key;
        printHelper(data,node->right,i*2+1);
        printHelper(data,node->left,i*2);
    }
    void printTree(){
        if(root != nullptr){
            int H = (root->height) - HeightBase +1;
            int MXnodes = (1<<H)-1;
            int showH = H+H-1;
            if(showH<0)showH=0;
            int dashes = 1<<(H-2);
            if(dashes<0)dashes=0;
            int s=0;
            cout<<"The height is: "<<H<<'\n';
            int data[MXnodes];
            for(int i=0;i<MXnodes;++i)data[i]=MN;
            // store tree in a static array to ease the navigation
            printHelper(data,root);
            int**show = new int*[showH];
            // Get max_length of the numbers
            for(int i=0;i<MXnodes;++i){
                if(data[i]!=MN && s < to_string(data[i]).size())
                    s=to_string(data[i]).size();
            }
            for(int i=0;i<showH;++i){
                show[i] = new int[MXnodes];
                for(int j=0;j<MXnodes;++j){
                    show[i][j]=space;
                }
            }
            navigate(data,show,showH,MXnodes,1,0,MXnodes>>1,dashes);
            print2DTree(show,showH,MXnodes,s);
            for(int i=0;i<showH;++i)
                delete[] show[i];
            delete[] show;
        }
    }
};
int AVLTree::f = 1;




void displayOptions() {
    cout << "---------------------------------------\n"
         << " 1. Add New Contact\n"
         << " 2. Search for Contact\n"
         << " 3. Delete Contact\n"
         << " 4. List All Contacts (Sorted by ID)\n"
         << " 5. Display Current Tree Structure\n"
         << " 6. Exit\n"
         << "---------------------------------------\n"
         << "Enter operation (1-6): ";
}

void AddNewContact(AVLTree& tree) {
    int id;
    string name, phone, email;
    cout << "Enter unique ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Phone: ";
    getline(cin, phone);
    cout << "Enter Email: ";
    getline(cin, email);
    tree.insertContact(id, name, phone, email);
    cout << "Contact added successfully.\n";
}

void SearchForContact(AVLTree& tree) {
    int id;
    cout << "Enter ID to search: ";
    cin >> id;
    tree.SearchContact(id);
}

void DeleteContact(AVLTree& tree) {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;
    tree.DeleteContact(id);
}

void ListAllContacts(AVLTree& tree) {
    tree.ListAllContacts();
}

void DisplayCurrentTreeStructure(AVLTree& tree) {
    cout << "Current AVL Tree:\n";
    tree.displayTree();
}


int main() {
    AVLTree tree;
    /*  Added by Ahmad Ibrahim*/
    // tree.insertContact(100,"","","");
    // tree.printTree();
    // tree.insertContact(200,"","","");
    // tree.printTree();
    // tree.insertContact(300,"","","");
    // tree.printTree();
    // tree.insertContact(900,"","","");
    // tree.printTree();
    // tree.insertContact(500,"","","");
    // tree.printTree();
    // tree.insertContact(800,"","","");
    // tree.printTree();
    // tree.insertContact(400,"","","");
    // tree.printTree();
    /*  */
    int choice;

    while (true) {
        displayOptions();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: AddNewContact(tree); break;
            case 2: SearchForContact(tree); break;
            case 3: DeleteContact(tree); break;
            case 4: ListAllContacts(tree); break;
            case 5: DisplayCurrentTreeStructure(tree); break;
            case 6: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
