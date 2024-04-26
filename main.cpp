#include <iostream>
#include "Ressources/folder.cpp"
#include "Ressources/account.cpp"

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
Account Root("Root", 3);

    
File First("First", &User, &Result);

void ChangeDirectory ( string input ) {
    stringstream ss(input);
    string token;
    vector<string> tokens;

    while (getline(ss, token, '/')) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

    bool found = true;

    Folder* temp = root.Folders;

    string dir = "";

    for (const string& part : tokens) {

        found = false;

        while ( temp != NULL ) {
            if ( temp->Name == part ) {
                found = true;
                break;
            }
            temp = temp->Next;
        }


        if ( !found ) {
            cout << "\033[31m" << "Folder not found !" << "\033[0m" << endl;
            break;
        }

        temp = temp->Folders;

        dir = dir + "/" + part;

    }

    if ( found ) {
        current_directory = dir;
    }
}

void CreateDir ( string input, string name ) {
    stringstream ss(input);
    string token;
    vector<string> tokens;

    while (getline(ss, token, '/')) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

    bool found = true;

    Folder* temp = &root;

    for (const string& part : tokens) {
        
        temp = temp->Folders;

        found = false;

        while ( temp != NULL ) {
            if ( temp->Name == part ) {
                found = true;
                break;
            }
            temp = temp->Next;
        }


        if ( !found ) {
            cout << "\033[31m" << "Folder not found !" << "\033[0m" << endl;
            break;
        }

    }

    if ( found ) {
        Folder* newFolder = new Folder( name, temp, &Result );
    }
}

void CreateF ( string input, string name ) {
    stringstream ss(input);
    string token;
    vector<string> tokens;

    while (getline(ss, token, '/')) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

    bool found = true;

    Folder* temp = &root;

    for (const string& part : tokens) {
        
        temp = temp->Folders;

        found = false;

        while ( temp != NULL ) {
            if ( temp->Name == part ) {
                found = true;
                break;
            }
            temp = temp->Next;
        }


        if ( !found ) {
            cout << "\033[31m" << "Folder not found !" << "\033[0m" << endl;
            break;
        }

    }

    if ( found ) {
        File* newFile = new File( name, temp, &Result );
    }
}

Account* SearchAccount(string name){
    bool found=false;
    Account* temp = &Root;
    while(temp->name != name){
        temp = temp->Next;
    }
    return temp;
}


void Command ( string input ) {
    stringstream ss(input);

    vector<string> tokens;

    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }

    if (tokens.size() >= 2) { 

        string command = tokens[0];
        string argument = tokens[1];

        if ( command == "ls" ) {
            DisplayFolder(argument, root);
        } else if ( command == "cd" ) {
            ChangeDirectory(argument);
        } else if ( command == "mkdir" ) {
            CreateDir(current_directory,argument);
        }  else if ( command == "touch" ) {
            CreateF(current_directory,argument);
        } else if ( command == "SetAccessLvl") {
            int access = token[2];
            cout << "Enter access lvl";
            if (access != 1 || access != 2 || access != 3){
                cout << "Access lvl not recognized";
            }
            SearchAccount(argument)->AccessibiliyLvl = access ;
        }else if( command == "NewUser" ) {
            Account temp = Root;
            temp.Next = new Account(argument);
            cout << "New User created with success.\n";
            cout << "AccessibilityLvl set to lowest settings.\n";
        } else if ( command == "echo" ) {
            for ( int i = 1; i<tokens.size(); i++ ) {
                cout << tokens[i] << " ";
            } 
            cout << endl;
        } else {
            cout << "\033[31m" << "Uknown Command !" << "\033[0m" << endl;
        }
    } else if ( tokens.size() == 1 ) {
        
        string command = tokens[0];

        if ( command == "pwd" ) {
            cout << current_directory << endl;
        } else if ( command == "cls" ) {
            system("cls");
        } else if( command == "exit"){
            exit(0);
        }else if ( command == "ls" ) {
            DisplayFolder(current_directory, root);
        } else {
            cout << "\033[31m" << "Uknown Command !" << "\033[0m" << endl;
        }
    } else {
    }

}

int main ( ) {
    string in;
    system("cls");
    cout << "\x1b[92m" << "Enter your username: "<< "\x1b[0m";
    cin >> user;
    fflush(stdin);
    system("cls");
    while ( true ) {
        cout << "\x1b[92m" << user << "\x1b[0m:\x1b[94m" << current_directory << "\x1b[0m$ ";
        getline(cin, in);
        Command(in);
    }
}