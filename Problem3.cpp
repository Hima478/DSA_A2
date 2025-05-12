#include <iostream>
#include <fstream>
using namespace std;
int minFlips(int arr[], int n, int k) {
    int flips = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            if (i + k > n) {
                return -1;
            }
            for (int j = i; j < i + k; j++) {
                arr[j] = 1 - arr[j];
            }
            flips++;
            cout<<"flip "<<flips<<" at index"<<i<<" ==> [";
            for (int p = 0; p < n; p++) {
                cout << arr[p];
                if (p != n - 1) cout << ", ";
            }

            cout<<"]"<<endl;
        }
    }

    return flips;
}
void readInput(){
    int n,k;
    int arr[100];
    cout<<"enter the size of the array";
    cin>>n;
    cout << "Enter the array elements (0 or 1): ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << "Enter the segment size k: ";
    cin >> k;
    int result = minFlips(arr, n, k);
    cout << "Minimum number of flips required: " << result << endl;
}
void readFile(){
    ifstream file("P3_TestCases.txt");
    int testCase = 1;
    while (!file.eof()) {
        cout << "test case" << testCase << endl;
        int n, k;
        int arr[100];
        file >> n;
        cout<<"Main Array: [";
        for (int i = 0; i < n; i++) {
            file >> arr[i];
            cout<<arr[i];
            if (i != n - 1) cout << ", ";
        }
        cout<<" ]"<<endl;
        file >> k;
        cout<<"n value: "<<n<<endl;
        cout<<"k value: "<<k<<endl;
        int result = minFlips(arr, n, k);
        cout << "Minimum number of flips required: " << result << endl;
        testCase++;
    }
    file.close();
}
int main() {
    int choice;
    cout<<"1-enter the input manually"<<endl;
    cout<<"2-read from file"<<endl;
    cout<<"enter your choice: ";
    cin>>choice;
    while(choice!=1 && choice!=2){
        cout<<"please enter a valid choice ";
        cin>>choice;
    }
    if(choice==1) readInput();
    if(choice==2) readFile();
    return 0;
}
