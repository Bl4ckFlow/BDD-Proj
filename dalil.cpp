#include <iostream>
#include "Ressources/folder.cpp"

using namespace std;

// ############### GLOBAL VARIABLES // ###############

bool Result;
Folder root("root");
string current_directory="/User";
string user = "default";

// ############### GLOBAL VARIABLES // ###############

Folder User("User", &root, &Result);
Folder Desktop("Desktop", &User, &Result);
Folder Downloads("Downloads", &User, &Result);
Folder Documents("Documents", &User, &Result);
    
File First("First", "txt", &User, &Result);


int main () {
    cout << "mchit";
}