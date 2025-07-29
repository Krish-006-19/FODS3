#include<iostream>
#include<cstring>
#include <ctype.h>  
using namespace std;

class Node {
public:
    char email[100];
    char number[11];
    char rollno[10];
    char name[100];
    float marks;
    Node* next;

    Node(char Name[], char Rollno[], float Marks, char Email[], char Number[]) {
        strcpy(name, Name);
        strcpy(rollno, Rollno);
        marks = Marks;
        strcpy(email, Email);
        strcpy(number, Number);
        next = nullptr;
    }

    ~Node() {
        delete next;
    }
};

void printName(char Name[]) {
    bool valid = false;
    while (!valid) {
        cout << "\nEnter the name: ";
        cin >> Name;
        valid = true;
        for (int i = 0; i < strlen(Name); i++) {
            if (!((Name[i] >= 'A' && Name[i] <= 'Z') || (Name[i] >= 'a' && Name[i] <= 'z')) && Name[i] != '_'){
                cout << "Invalid name. Use letters and underscore only.\n";
                valid = false;
                break;
            }
        }
    }
}

bool isDuplicateName(Node* head, char Name[]) {
    for(int i = 0;i<strlen(Name);i++)
        Name[i] = tolower(Name[i]);
    while (head) {
        if (strcmp(head->name, Name) == 0) return true;
        head = head->next;
    }
    return false;
}

void printRollno(char Rollno[]) {
    bool valid = false;
    while (!valid){
        cout << "\nEnter roll number: ";
        cin >> Rollno;
        valid = true;
        for (int i = 0; i < strlen(Rollno); i++) {
            if(!(Rollno[i] >= '0' && Rollno[i] <= '9')){
                cout << "Roll number should be numeric.\n";
                valid = false;
                break;
            }
        }
    }
}

bool isDuplicateRollno(Node* head, char Rollno[]) {
    while (head) {
        if (strcmp(head->rollno, Rollno) == 0) return true;
        head = head->next;
    }
    return false;
}

void printMarks(float* Marks) {
    bool valid = false;
    while (!valid) {
        cout << "\nEnter marks (0-100): ";
        cin >> *Marks; 
        if (*Marks >= 0 && *Marks <= 100)
            valid = true;
        else
            cout << "Marks must be between 0 and 100.\n";
    }
}

void printEmail(char Email[]) {
    bool valid = false;
 while (!valid) {
        cout << "\nEnter email: ";
        cin >> Email;
        int len = strlen(Email);
        valid = true;
        for(int i = 0; i < len; i++){
            if(Email[i]=='('||Email[i]==')'||Email[i]=='#'||Email[i]=='['||Email[i]==']'||Email[i]=='\''||Email[i]==';'||Email[i]==':'||Email[i]==','||Email[i]=='<'||Email[i]=='>'||Email[i]=='"'){
                cout << " Invalid email: contains illegal characters.\n";
                valid = false;
                break;
            }
        }
        if (len < 9 || strcmp(Email + len - 8, "@vit.edu") != 0) {
            cout << " Invalid email format: Must end with @vit.edu\n";
            valid = false;
            continue;
        }

        if (Email[0] == '.') {
            cout << " Email can't start or end with a dot.\n";
            valid = false;
            continue;
        }

        for (int i = 0; i < len - 1; i++) {
            if (Email[i] == '.' && Email[i + 1] == '.') {
                cout << " Invalid email: consecutive dots found.\n";
                valid = false;
                break;
            }
        }
        if (!valid) continue;

        int atCount = 0, atPos = -1;
        for (int i = 0; i < len; i++) {
            if (Email[i] == '@') {
                atCount++;
                atPos = i;
            }
            if(Email[atPos-1] == '.'){
                cout << " Invalid email: dot found just before @.\n";
                valid = false;
                break;
            }
        }
        if (atCount != 1) {
            cout << " Email must contain exactly one '@' symbol.\n";
            valid = false;
            continue;
        }

        bool dotAfterAt = false;
        for (int i = atPos + 1; i < len; i++) {
            if (Email[i] == '.') {
                dotAfterAt = true;
                break;
            }
        }
        if (!dotAfterAt) {
            cout << " Email must contain at least one '.' after '@'.\n";
            valid = false;
            continue;
        }
    }
}

bool isDuplicateEmail(Node* head, char Email[]) {
    for(int i = 0;i<strlen(Email);i++)
        Email[i] = tolower(Email[i]);
    while (head) {
        if (strcmp(head->email, Email) == 0) return true;
        head = head->next;
    }
    return false;
}

void printNumber(char Number[]) {
    bool valid = false;
    while (!valid) {
        cout << "\nEnter 10-digit mobile number: ";
        cin >> Number;

        valid = strlen(Number) == 10;
        for (int i = 0; i < 10 && valid; i++) {
            if(!(Number[i] >= '0' && Number[i] <= '9')){
                valid = false;
                break;
            }
        }

        if (!valid)
            cout << "Invalid number. Only 10 digits allowed.\n";
    }
}

bool isDuplicateNumber(Node* head, char Number[]) {
    while (head) {
        if (strcmp(head->number, Number) == 0) return true;
        head = head->next;
    }
    return false;
}

int main() {
    char Name[100], Rollno[10], Email[100], Number[11];
    float Marks;

    int total = 10;

    cout << "\nStudent 1:\n";
    printName(Name);
    printRollno(Rollno);
    printMarks(&Marks);
    printEmail(Email);
    printNumber(Number);

    Node* head = new Node(Name, Rollno, Marks, Email, Number);
    Node* tail = head;

    for (int i = 1; i < total; i++) {
        cout << "\nStudent " << i + 1 << ":\n";

        while (true) {
            printName(Name);
            if (!isDuplicateName(head, Name)) break;
            cout << "Name already exists. Try a different one.\n";
        }

        while (true) {
            printRollno(Rollno);
            if (!isDuplicateRollno(head, Rollno)) break;
            cout << "Roll number already exists.\n";
        }

        printMarks(&Marks);

        while (true) {
            printEmail(Email);
            if (!isDuplicateEmail(head, Email)) break;
            cout << "Email already exists.\n";
        }

        while (true) {
            printNumber(Number);
            if (!isDuplicateNumber(head, Number)) break;
            cout << "Mobile number already exists.\n";
        }

        Node* newNode = new Node(Name, Rollno, Marks, Email, Number);
        tail->next = newNode;
        tail = newNode;
    }

    cout << "\nFinal Student Records:\n[\n";
    Node* temp = head;
    while (temp) {
        cout << "\t{\n";
        cout << "\t\tName: " << temp->name << "\n";
        cout << "\t\tRollno: " << temp->rollno << "\n";
        cout << "\t\tMarks: " << temp->marks << "\n";
        cout << "\t\tEmail: " << temp->email << "\n";
        cout << "\t\tNumber: " << temp->number << "\n";
        cout << "\t},\n";
        temp = temp->next;
    }
    cout << "]\n";

    temp = head;
    while (temp) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }

    return 0;
}
