// #include<iostream>
// #include<fstream>
// using namespace std;
//
// struct Patient{
//     string name;
//     int severity;
//     int time;
//     Patient(string name,int severity,int time):name(name),severity(severity),time(time){}
// };
// // ostream& operator<<(ostream &out,Patient &patient){
//
// // }
// class EmergencyRoom{
//     int size;
//     int capacity;
//     Patient** que;
//     void resize(){
//         int newCapacity = capacity <<1;
//         Patient** newQue = new Patient*[newCapacity];
//         for(int i=0;i<size;++i){
//             newQue[i] = que[i];
//         }
//         delete[]que;
//         que = newQue;
//         capacity = newCapacity;
//     }
// public:
//     EmergencyRoom(string fileName):capacity(1),size(0){
//         que = new Patient*[capacity];
//         ifstream file(fileName);
//         // cout<<file.good()<<' ';
//         string name;
//         int severity,time;
//         // cout<<"Done";
//         file>>name>>name>>name;
//         // cout<<name<<' '<<name<<' '<<name<<'\n';
//         while(file>>name>>severity>>time){
//             // cout<<name<<' '<<severity<<' '<<time<<'\n';
//             insertPatient(name,severity,time);
//         }
//     }
//     EmergencyRoom():capacity(1),size(0){
//         que = new Patient*[capacity];
//     }
//     void print_heap(){
//         cout<<'[';
//         for(int i=0;i<size;++i){
//             cout<<'\''<<que[i]->name<<'\'';
//             if(size-1-i)cout<<", ";
//         }
//         cout<<']';
//     }
//     void insertPatient(string name,int severity,int time){
//         if(size>=capacity)resize();
//         que[size++] = new Patient(name,severity,time);
//         int i = size;
//         while(i>1){
//             if(que[i-1]->severity < que[(i>>1)-1]->severity)break;
//             if(que[i-1]->severity == que[(i>>1)-1]->severity && que[i-1]->time > que[(i>>1)-1]->time)break;
//             swap(que[i-1],que[(i>>1)-1]);
//             i>>=1;
//         }
//         cout<<"Inserting: "<<name<<'\n';
//         cout<<"Heap: ";
//         print_heap();
//         cout<<'\n';
//     }
//     Patient extract_max(){
//         if(size<1){
//             throw std::out_of_range("Three are no patients waiting.");
//         }
//         // Code
//     }
//     Patient peek(){
//         if(size<1){
//             throw std::out_of_range("Three are no patients waiting.");
//         }
//         return *que[0];
//     }
//
//     ~EmergencyRoom(){
//         for(int i=0;i<size;++i){
//             delete que[i];
//         }
//         delete[] que;
//     }
// };
//
// int main(){
//     string fileName = "P4_TestCases.txt";
//     EmergencyRoom system(fileName);
//
//
//     return 0;
// }