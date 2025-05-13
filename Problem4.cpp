#include <iostream>
#include <cstdio>
using namespace std;

struct Patient {
    string name;
    int severity;
    int time;

    Patient(string n = "", int s = 0, int t = 0) {
        name = n;
        severity = s;
        time = t;
    }
};

bool higherPriority(Patient* a, Patient* b) {
    if (a->severity != b->severity)
        return a->severity > b->severity;
    return a->time < b->time;
}

class EmergencyRoom {
    Patient** heap;
    int size;
    int capacity;
    int insertStep;

    void resize() {
        int newCap = capacity * 2;
        Patient** newHeap = new Patient*[newCap];
        for (int i = 0; i < size; ++i)
            newHeap[i] = heap[i];
        delete[] heap;
        heap = newHeap;
        capacity = newCap;
    }

    void heapifyDown(int index) {
        while (index < size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size && higherPriority(heap[left], heap[largest]))
                largest = left;
            if (right < size && higherPriority(heap[right], heap[largest]))
                largest = right;

            if (largest != index) {
                swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    EmergencyRoom() {
        size = 0;
        capacity = 10;
        heap = new Patient*[capacity];
        insertStep = 1;
    }

    ~EmergencyRoom() {
        for (int i = 0; i < size; ++i)
            delete heap[i];
        delete[] heap;
    }

    void insertPatient(string name, int severity, int time) {
        if (size == capacity)
            resize();
        heap[size] = new Patient(name, severity, time);
        int i = size;
        ++size;

        while (i > 0) {
            int parent = (i - 1) / 2;
            if (!higherPriority(heap[i], heap[parent]))
                break;
            swap(heap[i], heap[parent]);
            i = parent;
        }

        printf("%-8d%-12s", insertStep++, name.c_str());
        printHeap();
    }

    Patient* extractMax() {
        if (size == 0)
            return nullptr;

        Patient* maxPatient = heap[0];
        heap[0] = heap[size - 1];
        --size;
        heapifyDown(0);

        return maxPatient;
    }

    void printHeap() {
        printf("[");
        for (int i = 0; i < size; ++i) {
            printf("'%s'", heap[i]->name.c_str());
            if (i < size - 1)
                printf(", ");
        }
        printf("]\n");
    }

    void loadFromFile(const char* filename, int& arrivalCounter) {
        FILE* file = fopen(filename, "r");
        if (!file) {
            cout << "Error: Cannot open file: " << filename << endl;
            return;
        }

        char name[100];
        int severity, time;
        while (fscanf(file, "%s %d %d", name, &severity, &time) == 3) {
            insertPatient(string(name), severity, time);
            if (time >= arrivalCounter)
                arrivalCounter = time + 1;
        }

        fclose(file);
    }
};

int main() {
    EmergencyRoom system;
    int choice;
    int arrivalCounter = 0;

    cout << "Emergency Room Priority Queue\n";
    cout << "1. Load patients from file (P4_TestCases.txt)\n";
    cout << "2. Enter patients manually\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "\nHeap After Insertions:\n\n";
        printf("%-8s%-12s%s\n", "Step", "Inserted", "Heap (Top to Bottom)");
        system.loadFromFile("P4_TestCases.txt", arrivalCounter);
    } else if (choice == 2) {
        int count;
        cout << "How many patients do you want to enter? ";
        cin >> count;

        string* names = new string[count];
        int* severities = new int[count];

        for (int i = 0; i < count; ++i) {
            cout << "Enter name for patient " << (i + 1) << ": ";
            cin >> names[i];
            cout << "Enter severity for " << names[i] << ": ";
            cin >> severities[i];
        }

        cout << "\nHeap After Insertions:\n\n";
        printf("%-8s%-12s%s\n", "Step", "Inserted", "Heap (Top to Bottom)");
        for (int i = 0; i < count; ++i) {
            system.insertPatient(names[i], severities[i], arrivalCounter++);
        }

        delete[] names;
        delete[] severities;
    } else {
        cout << "Invalid choice.\n";
        return 1;
    }

    cout << "\n\nTreatment Order:\n\n";
    printf("%-8s%-20s\n", "Order", "Treated Patient");

    int order = 1;
    while (true) {
        Patient* p = system.extractMax();
        if (!p) break;
        printf("%-8d%-20s\n", order++, p->name.c_str());
        delete p;
    }

    return 0;
}