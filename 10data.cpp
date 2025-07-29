#include<iostream>
#include<cstring>
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

// Name Input
void printName(char Name[]) {
    bool valid = false;
    while (!valid) {
        cout << "\nEnter the name (name_surname): ";
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
    while (head) {
        if (strcmp(head->name, Name) == 0) return true;
        head = head->next;
    }
    return false;
}

// Rollno Input
void printRollno(char Rollno[]) {
    bool valid = false;
    while (!valid) {
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

// Marks Input
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

// Email Input
void printEmail(char Email[]) {
    bool valid = false;
    while (!valid) {
        cout << "\nEnter email (name.surname@vit.edu): ";
        cin >> Email;
        int len = strlen(Email);
        valid = true;

        if (len < 13 || strcmp(Email + len - 8, "@vit.edu") != 0) {
            cout << "Invalid email format. Must end with @vit.edu\n";
            valid = false;
            continue;
        }

        int atCount = 0, atPos = -1;
        for (int i = 0; i < len; i++) {
            if (Email[i] == '@') {
                atCount++;
                atPos = i;
            }
        }

        if (atCount != 1 || atPos < 3 || strchr(Email, '.') == nullptr) {
            cout << "Invalid email structure.\n";
            valid = false;
        }
    }
}

bool isDuplicateEmail(Node* head, char Email[]) {
    while (head) {
        if (strcmp(head->email, Email) == 0) return true;
        head = head->next;
    }
    return false;
}

// Mobile Number Input
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

    int total;
    cout << "Enter total number of students: ";
    cin >> total;

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
