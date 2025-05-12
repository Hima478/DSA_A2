#include <iostream>
using namespace std;

#define HeightBase 0

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
}