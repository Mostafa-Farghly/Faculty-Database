#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include <iostream>
#include <string>
#include <algorithm>
#include <locale>
#include <fstream>

using namespace std;


/* ========================================================================================*/

// Department, Title and Year Enums:
enum Departments {
#   define Dep(d) d,
#   include "Departments.def"
#   undef Dep
    NODEP
};

enum Titles {
#   define Tit(t) t,
#   include "Title.def"
#   undef Tit
    NOTIT
};

enum Years {
#   define Yr(y) y,
#   include "Year.def"
#   undef Yr
    NOYR
};
/* ========================================================================================*/

// Parent Class FacultyMember:
class FacultyMember{
protected:
    string name;
    Departments department;

//protected methods;
    string stringfyDep(Departments dep);
    Departments convDep(const string &stdep);

public:
// Constructors:
    FacultyMember(const string &n, const string &dep);
// Public Methods:
    void setName(const string &n) {name=n;}
    void setDep(const string &dep);
    string getName() {return name;}
    virtual void printData(ostream &os) = 0;
    virtual void scanData(istream &is) = 0;
    friend ostream & operator << (ostream& os, FacultyMember& fm);
    friend istream & operator >> (istream& is, FacultyMember& fm);

};
/* ========================================================================================*/

class StaffMember : public FacultyMember{
    Titles title;

//private methods;
    string stringfyTit(Titles tit);
    Titles convTit(const string &sttit);

public:
// Constructors:
    StaffMember();
    StaffMember(const string &n, const string &dep, const string &tit);
// public Methods:
    void setTitle(const string &tit);
    virtual void printData(ostream &os);
    virtual void scanData(istream &is);

};
/* ========================================================================================*/

class Student : public FacultyMember{
    Years year;
    int id;

// private methods:
    string stringfyYr(Years yr);
    Years convYr(const string &yr);

public:
// Constructors:
    Student();
    Student(const string &n, const string &dep, const string &yr, const int nid);
    int createID(); // Sets a suitable ID
    void setID(int code) {id = code;}
    void setYear(const string &yr);
    virtual void printData(ostream &os);
    virtual void scanData(istream &is);

};
/* ========================================================================================*/

class Node{
    FacultyMember *member;
    Node *next;

public:
    Node* getNext() {return next;}
    FacultyMember* getMem() {return member;}
    void setMem(FacultyMember *mem);
    void setNext(Node* nxt);
};

/* ========================================================================================*/

class List{
    Node *current;

public:
// Public Members:
    static int memNum;
    static Node *head;
    static Node *last;

// Constructors:
    List(FacultyMember *mem);

};

/* ========================================================================================*/

// Global Functions Prototypes:
void addNode(FacultyMember* mem);
void loadfile();
void saveFile();
void createNode();
void showMem();
void searchMem();
void removeMem();
/* ========================================================================================*/

#endif // DATABASE_H_INCLUDED
