#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Stack {
private:
    char** Urls;
    int Size;
    int topIndex;

    void resize(int NewSize) {

        char** newUrls = new char*[NewSize];
        for (int i = 0; i <= topIndex; i++) {
            newUrls[i] = Urls[i];
        }
        delete[] Urls;
        Urls = newUrls;
        Size = NewSize;
    }

public:
    Stack() {
        Size = 5;
        Urls = new char*[Size];
        topIndex = -1;
    }

    ~Stack() {
        clear();
        delete[] Urls;
    }

    void push(const char* url) {
        if (topIndex == Size - 1) {
            resize(Size * 2);
        }

        topIndex++;
        Urls[topIndex] = new char[strlen(url) + 1];
        strcpy(Urls[topIndex], url);
    }

    char* pop() {
        if (isEmpty()) {
            return nullptr;
        }

        char* PoppedUrl = Urls[topIndex];
        topIndex--;

        return PoppedUrl;
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    const char* peekTop() const {
        if (isEmpty()) {
            return nullptr;
        }
        return Urls[topIndex];
    }

    int getSize() const {
        return topIndex + 1;
    }

    void clear() {
        for (int i = 0; i <= topIndex; i++) {
            delete[] Urls[i];
        }
        topIndex = -1;
    }
    void display() const {
        if (isEmpty()) {
            cout << "Empty";
        } else {
            cout << "[";
            for (int i = 0; i <= topIndex; i++) {
                if (i > 0) {
                    cout << ", ";
                }
                cout << "\"" << Urls[i] << "\"";
            }
            cout << "]";
        }
    }
};

class BrowserHistoryTracker {
private:
    Stack BackStack;
    Stack ForwardStack;
    char* currentUrl;
    int testCases = 1;


public:
    BrowserHistoryTracker() {
        currentUrl = nullptr;
    }

    ~BrowserHistoryTracker() {
        if (currentUrl) {
            delete[] currentUrl;
        }
    }

    void VisitUrl(const char* url) {

        while (!ForwardStack.isEmpty()) {
            char* forwardUrl = ForwardStack.pop();
            delete[] forwardUrl;
        }

        char* newUrl = new char[strlen(url) + 1];
        strcpy(newUrl, url);

        BackStack.push(newUrl);

        if (currentUrl) {
            currentUrl = nullptr;
        }
        currentUrl = newUrl;

        cout << "Visiting: " << currentUrl <<" --> " ;
    }

    const char* goBack() {

        if (BackStack.isEmpty() || BackStack.getSize() <= 1) {
            cout << "Can't go back - no history!" << endl;
            return currentUrl;
        }

        char* topUrl = BackStack.pop();
        ForwardStack.push(topUrl);

        if (currentUrl) {
            currentUrl = nullptr;
        }
        currentUrl = const_cast<char*>(BackStack.peekTop());

        cout << "Going back to: " << currentUrl <<" --> ";

        return currentUrl;
    }

    const char* goForward() {
        if (ForwardStack.isEmpty()) {
            cout << "Can't go forward - at newest page!" << endl;
            return currentUrl;
        }
        char* nextUrl = ForwardStack.pop();

        BackStack.push(nextUrl);

        if (currentUrl) {
            currentUrl = nullptr;
        }
        currentUrl = nextUrl;

        cout << "Going forward to: " << currentUrl <<" --> ";

        return currentUrl;
    }

    void printState() {
        cout << "Test Case: " << testCases++<< endl;
        cout << "Back Stack: ";
        BackStack.display();
        cout << endl;

        cout << "Forward Stack: ";
        ForwardStack.display();
        cout << endl;

        cout << "Current URL: " << (currentUrl ? currentUrl : "None") << endl;

        cout << "------------------------" << endl;
    }
};

void processFile(const char* filename) {
    ifstream file(filename);

    BrowserHistoryTracker browser;
    char command[10];
    char url[256];

    while (file >> command) {
        if (strcmp(command, "visit") == 0) {
            file >> url;
            browser.VisitUrl(url);
            browser.printState();
        }
        else if (strcmp(command, "goBack") == 0) {
            browser.goBack();
            browser.printState();
        }
        else if (strcmp(command, "goForward") == 0) {
            browser.goForward();
            browser.printState();
        }
        else {
            cout << "Unknown command: " << command << endl;
        }
    }

    file.close();
}

int main() {
    processFile("P1_TestCases.txt");
    return 0;
}
