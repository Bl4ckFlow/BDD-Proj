#include <iostream>

using namespace std;

class File {};

class Folder {
    private:
        string Name;
    public:
        Folder* Folders;
        File* Files;
        Folder* Next;

        string getName () { 
            return this->Name;
         };

        Folder( string Name, Folder* Parent, bool* Return ) {
            
            Folder* temp = Parent->Folders;
            *Return = true;

            if ( Name == "" ) {
                *Return = false;
            }
            
            if ( temp == NULL ) {
                Parent->Folders = this;
            }

            while ( temp->Next != NULL && *Return ) {
                if ( temp->Name == Name ) {
                    *Return = false;
                    break;
                }
                temp = temp->Next;
            }

            if ( *Return == true ) {
                temp->Next = this;
            }

        };    

};