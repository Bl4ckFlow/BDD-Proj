#include <iostream>
#include <windows.h>
#include <sstream>
#include <vector>

using namespace std;

class Folder;

class File {
    public:
        string Name;
		string Content = "";
        File* Next = NULL;

        File ( string Name, Folder* Parent, bool* Result);
};

class Folder {
    public:
        string Name;
        Folder* Folders = NULL;
        File* Files = NULL;
        Folder* Next = NULL;

        Folder ( string Name ) {
            this->Name = Name;
        }

        Folder ( string Name, Folder* Parent, bool* Result) {
            
            *Result = true;
            this->Name = Name;
            Folder* temp = Parent->Folders;
            if ( ( temp != NULL) && ( temp->Name == Name ) ) {
                cout << "\033[31m" << "Folder already exists with same name !" << "\033[0m" << endl;
                return;
            }
            if ( temp == NULL ) {
                Parent->Folders = this;
            } else {
                while ( temp->Next != NULL ) {
                    if ( ( temp->Name == Name ) || ( temp->Next->Name == Name ) ) {
                        *Result = false;
                        cout << "\033[31m" << "Folder already exists with same name !" << "\033[0m" << endl;
                        break;
                    }
                    temp = temp->Next;
                }
                if ( *Result ) {
                    temp->Next = this;
                }
            }
        };    
};

File::File ( string Name, Folder* Parent, bool* Result) {
            
            *Result = true;

            this->Name = Name;
            File* temp = Parent->Files;

            if ( ( temp != NULL) && ( temp->Name == Name ) ) {
                cout << "\033[31m" << "File already exists with same name !" << "\033[0m" << endl;
                return;
            }
            if ( temp == NULL ) {
                Parent->Files = this;
            } else {
                while ( temp->Next != NULL ) {
                    if ( ( temp->Name == Name ) || ( temp->Next->Name == Name ) ) {
                        *Result = false;
                        cout << "\033[31m" << "File already exists with same name !" << "\033[0m" << endl;
                        break;
                    }
                    temp = temp->Next;
                }
                if ( *Result ) {
                    temp->Next = this;
                }
            }
        };

void DisplayFolder ( string input, Folder root ) {

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
    File* tempfiles = NULL;

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

        tempfiles = temp->Files;
        temp = temp->Folders;

    }

    if ( found ) {
        while ( temp != NULL ) {
            cout << temp->Name << "/" << endl;
            temp = temp->Next;
        }
        while ( tempfiles != NULL ) {
            cout << tempfiles->Name << endl;
            tempfiles = tempfiles->Next;
        }

    }
    

}

