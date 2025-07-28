#include<iostream>
#include<cstring>
using namespace std;

class Data {
public:
    char email[100];
    char number[10];
    char rollno[2];
    char name[100];
    float marks;

    Data() {}
    Data(char Name[], char Rollno[], float Marks, char Email[], char Number[]) {
        strcpy(name,Name);
        strcpy(rollno,Rollno);
        marks = Marks;
        strcpy(number,Number);
        strcpy(name,Name);
    }
};

class Node {
public:
    Data data;
    Node* next;

    Node(Data obj){  
        data = obj; 
        next = nullptr;
     }

    ~Node() {
        delete next;
    }
};

void print(char Name[], char Rollno[], float* Marks, char Email[], char Number[]){
        bool validName = false;
        while (!validName) {
            cout << "\nEnter the name of the student as (name_surname): ";
            cin >> Name;

            validName = true;
            int len = strlen(Name);
            for (int j = 0; j < len; j++) {
                if (!((Name[j] >= 'A' && Name[j] <= 'Z') || (Name[j] >= 'a' && Name[j] <= 'z') || Name[j] == '_')) {
                    cout << "Invalid character in name. Only letters and underscore allowed.\n";
                    validName = false;
                    break;
                }
            }
        }
        bool validRollno = false;
        while (!validRollno) {
            cout << "\nEnter the rollno: ";
            cin >> Rollno;
            validRollno = true;

            for(int j = 0; j < strlen(Rollno); j++) {
                if(!(Rollno[j] >= '0' && Rollno[j] <= '9')) {
                    cout << "Invalid roll number. Only digits allowed.\n";
                    validRollno = false;
                    break;
                }
            }
        }
        bool validMarks = false;
        while (!validMarks) {
            cout << "\nEnter the marks of the student: ";
            cin >> *Marks;
            if(*Marks > 100 || *Marks < 0) {
                cout << "Invalid marks. Please enter marks between 0 and 100.\n";
            } else {
                validMarks = true;
            }
        }

        bool validEmail = false;
        while (!validEmail) {
            cout << "\nEnter the college email (name.surname@vit.edu): ";
            cin >> Email;
            validEmail = true;
            int len = strlen(Email);
            if (len < 13) {
                cout << "Invalid email. Too short.\n";
                continue;
            }

            const char* suffix = "@vit.edu";
            bool endsWithVit = strcmp(Email + len - 8, suffix) == 0;

            if (!endsWithVit) {
                cout << "Invalid email. Must end with @vit.edu\n";
                continue;
            }

            int atCount = 0;
            int atIndex = -1;
            for (int j = 0; j < len; j++) {
                if (Email[j] == '@') {
                    atCount++;
                    atIndex = j;
                }
            }

            if (atCount != 1 || atIndex < 3) {
                cout << "Invalid email. Must contain one '@' and valid name before it.\n";
                validEmail = false;
                continue;
            }

            bool hasDot = false;
            for (int j = 0; j < atIndex; j++) {
                if (Email[j] == '.') {
                    hasDot = true;
                    break;
                }
            }

            if (!hasDot) {
                cout << "Invalid email. Must be in format name.surname@vit.edu\n";
                validEmail = false;
                continue;
            }
        }
        bool validNumber = false;
        while (!validNumber) {
            cout << "\nEnter the mobile number of the student: ";
            cin >> Number;

            if(strlen(Number) != 10) {
                cout << "Invalid mobile number length. Please enter a 10-digit number.\n";
                continue;
            }

            validNumber = true;
            for(int j = 0; j < 10; j++) {
                if(!(Number[j] >= '0' && Number[j] <= '9')) {
                    cout << "Invalid mobile number. Digits only.\n";
                    validNumber = false;
                    break;
                }
            }
        }
}

int main(){
    char Name[100]; 
    char Rollno[2]; 
    float Marks; 
    char Email[50]; 
    char Number[10];
    print(Name,Rollno,&Marks,Email,Number);
    
    Data obj(Name, Rollno, Marks, Email, Number);
    Node* head = new Node(obj);
    Node* tail = head;

    for(int i = 0; i < 2; i++){
        print(Name,Rollno,&Marks,Email,Number);

        Data obj(Name, Rollno, Marks, Email, Number);
        Node* newNode = new Node(obj);
        tail->next = newNode;
        tail = newNode;
    }
    Node* temp = head;
    cout<<"[\n";
    while(temp){
        cout<<"\t{\n";
        cout<<"\t\t"<<"Name: "<<temp->data.name<<endl;
        cout<<"\t\t"<<"Rollno: "<<temp->data.rollno<<endl;
        cout<<"\t\t"<<"Marks: "<<temp->data.marks<<endl;
        cout<<"\t\t"<<"Email: "<<temp->data.email<<endl;
        cout<<"\t\t"<<"Number: "<<temp->data.number<<endl;
        cout<<"\t},\n";
        temp = temp->next;
    }
    cout<<"\n]";
    return 0;
}