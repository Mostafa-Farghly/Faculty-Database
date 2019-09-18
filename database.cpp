#include "database.h"

/* ========================================================================================*/
// Department, Title and Year Arrays:
const string departments[] = {"STRUCTURE", "IRRIGATION AND HYDRAULICS", "PUBLIC WORKS", "ARCHITECTURE",
                              "URBAN DESIGN AND PLANNING", "POWER AND ELECTRICAL MACHINES",
                              "ELECTRONICS AND ELECTRICAL COMMUNICATION", "COMPUTER AND SYSTEMS",
                              "MECHATRONICS", "MECHANICAL POWER", "AUTOMOTIVE", "DESIGN AND PRODUCTION",
                              "???"};

const string titles[] = {"DEMONSTRATOR", "TEACHING ASSISTANT", "TEACHER", "ASSISTANT PROFESSOR",
                         "PROFESSOR", "???"};

const string years[] = {"FRESHMEN","SOPHOMORE","JUNIOR","SENIOR I","SENIOR II", "???"};
/* ========================================================================================*/

// Global Functions:
// Enums ostream operator overloading:
ostream & operator << (ostream& os, Departments dep) {return os << departments[dep];}
ostream & operator << (ostream& os, Titles tit) {return os << titles[tit];}
ostream & operator << (ostream& os, Years yr) {return os << years[yr];}

// class FacultyMember ostream operator  overloading:
ostream & operator << (ostream &os, FacultyMember &fm) {
    fm.printData(os);
    return os;
}

// class FacultyMember istream operator  overloading:
istream & operator >> (istream &is, FacultyMember &fm) {
    fm.scanData(is);
    return is;
}

// String Capitalization Function:
void capit(string &str) {
    locale loc;
    for (unsigned int i=0; i<str.length(); ++i)
        str[i] = toupper(str[i],loc);
}
/* ========================================================================================*/

// class FacultyMember (string name, Departments department)
// Constructors:
FacultyMember :: FacultyMember(const string &n, const string &dep) : name(n) {
    department = convDep(dep);
}

// private methods:
string FacultyMember :: stringfyDep(Departments dep){return departments[dep];}

Departments FacultyMember :: convDep(const string &stdep){
    return Departments( find(departments, departments+NODEP+1, stdep) - departments );
}
// public methods:
void FacultyMember :: setDep(const string &dep) {department = convDep(dep);}
/* ========================================================================================*/

// class StaffMember (Title title) :: public FacultyMember
// Constructors:
StaffMember :: StaffMember(const string &n, const string &dep, const string &tit)
    : FacultyMember(n,dep) {title = convTit(tit);}

StaffMember :: StaffMember() : FacultyMember("NoName", "???"){title = NOTIT;}

//private methods;
string StaffMember :: stringfyTit(Titles tit) {return titles[tit];}

Titles StaffMember :: convTit(const string &sttit){
    return Titles( find(titles, titles+NOTIT+1, sttit) - titles );
}

// public methods:
void StaffMember :: setTitle(const string &tit) {title = convTit(tit);}

void StaffMember :: printData(ostream &os) {
    os << "STAFF" << "," << name << "," << department << "," << title << endl;
}

void StaffMember :: scanData(istream &is){
    string dep, tit;

    getline(is, name , ',');

    getline(is, dep, ',');
    capit(dep);
    if(find(departments, departments+NODEP, dep) != (departments+NODEP))
        department = convDep(dep);
    else{
        cout << "Department not Supported!" << endl;
        department = NODEP;
    }

    getline(is, tit);
    capit(tit);
    if(find(titles, titles+NOTIT, tit) != (titles+NOTIT))
        title = convTit(tit);
    else{
        cout << "Title not Supported!" << endl;
        title = NOTIT;
    }
}
/* ========================================================================================*/

// class Student(Year year, int id) : public FacultyMember
// Constructors:
Student :: Student(const string &n, const string &dep, const string &yr, const int nid)
    : FacultyMember(n, dep), id(nid) {year = convYr(yr);}

Student :: Student() : FacultyMember("NoName", "???"){
    year = NOYR;
}

//private methods:
string Student :: stringfyYr(Years yr) {return titles[yr];}

Years Student :: convYr(const string &yr) {
    return Years( find(years, years+NOYR+1, yr) - years );
}

int Student :: createID() {
    int code = List::memNum;

    if(year==FRESHMEN)
        code += 180000;

    else if(year==SOPHOMORE)
        code += 170000;

    else if(year==JUNIOR)
        code += 160000;

    else if(year==SENIOR_I)
        code += 150000;

    else if(year==SENIOR_II)
        code += 140000;

    else
        code = -1;

    return code;
}

// public methods:
void Student :: setYear(const string &yr) {year = convYr(yr);}

void Student :: printData(ostream &os) {
    os << "STUDENT" << "," << name << "," << department << "," << year  << "," << id << endl;
}

void Student :: scanData(istream &is){
    string dep, yr;

    getline(is, name , ',');

    getline(is, dep, ',');
    capit(dep);
    if(find(departments, departments+NODEP, dep) != (departments+NODEP))
        department = convDep(dep);
    else {
        cout << "Department not Supported!" << endl;
        department = NODEP;
    }

    getline(is, yr, ',');
    capit(yr);
    if(find(years, years+NOYR, yr) != (years+NOYR))
        year = convYr(yr);
    else{
        cout << "Year not Supported!" << endl;
        year = NOYR;
    }
}
/* ========================================================================================*/

// Class Node (FacultyMember *member, Node *next)
// public methods:
void Node :: setMem(FacultyMember *mem){
    member = mem;
    next = NULL;
}

void Node :: setNext(Node* nxt) {next = nxt;}
/* ========================================================================================*/

// Class List (static int memNum, static Node *head, static Node *last, Node *current)
// Static Members Initialization:
int List :: memNum = 0;
Node* List :: head = NULL;
Node* List :: last = NULL;

// Constructors:
List :: List(FacultyMember *mem){
    memNum++;
    current = new Node;
    current->setMem(mem);
    if(last != NULL){
        last->setNext(current);
    }
    last = current;
    if(head == NULL)
        head = current;
}

/* ========================================================================================*/
/* ========================================================================================*/
/* ========================================================================================*/

// Global Functions:
void addNode(FacultyMember *mem){
    List member(mem);
}

void loadfile() {
    ifstream idata("FacultyMembers.csv");
    if(idata.is_open()) {
        string role;
        while (getline(idata, role, ',')) {

            if(role == "STAFF"){
                StaffMember *mem = new StaffMember;
                idata >> *mem;
                addNode(mem);
            }
            else if(role == "STUDENT"){
                int code;
                Student *mem = new Student;
                idata >> *mem >> code;
                mem->setID(code);
                addNode(mem);
            }
            else {
                cout << "Error Loading!\tWrong File Format!\n";
                break;
            }
        }
        cout << "Loading Complete!" << endl << endl;

    }
    else {
        cout << "Can't Open File" << endl << endl;
    }
}

void saveFile(){
    ofstream odata("FacultyMembers.csv");
    for(Node* nod=List::head; nod!=NULL; nod=nod->getNext()){
        odata << *(nod->getMem());
    }
}

void createNode(){
    int stdOrstf;
    for(;;){
        cout << "To Add Staff Member Enter 1\nTo Add Student Enter 2\n" << endl;
        cin >>stdOrstf;
        if(stdOrstf==1){
            StaffMember *mem = new StaffMember;
            cout << "Enter Name, Department and title separated by ," << endl;
            cin >> *mem;
            addNode(mem);
            break;
        }
        else if(stdOrstf==2){
            Student *mem = new Student;
            cout << "Enter Name, Department and Year separated by ," << endl;
            cin >> *mem;
            mem->createID();
            addNode(mem);
            break;
        }
        cout << "Invalid input!\n";
    }
}

void showMem(){
    for(Node* nod=List::head; nod!=NULL; nod=nod->getNext()){
        cout << *(nod->getMem());
    }
}

void searchMem(){
    string nme;
    cout << "Enter name or part of name: ";
    cin >> nme;
    for(Node* nod=List::head; nod!=NULL; nod=nod->getNext()){
        if(((nod->getMem()->getName()).compare(nme)) >= 0)
             cout << *(nod->getMem());
    }
}

void removeMem(){
    string nme;
    cout << "Enter name you want to remove: ";
    cin >> nme;
    for(Node* nod=List::head; nod!=NULL; nod=nod->getNext()){
        if((nod->getNext()->getMem()->getName()).compare(nme) == 0){
            Node *temp = nod->getNext()->getNext();
            delete nod->getNext();
            nod->setNext(temp);
            List::memNum--;
        }
    }
}
