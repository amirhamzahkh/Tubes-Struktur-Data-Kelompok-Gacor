#include "header.h"
#include <iostream>
using namespace std;

int main(){
    ListLagu library;
    ListPlaylist playlistList;

    createListLagu(library);
    createListPlaylist(playlistList);

    cout << "=== Aplikasi Pemutar Musik (Console) ===\n";

    int role = -1;

    while(role != 0){
        cout << "\nPilih role:\n";
        cout << "1. Admin\n";
        cout << "2. User\n";
        cout << "0. Keluar\n";
        cout << ">> ";
        cin >> role;

        if(role == 1){
            menuAdmin(library, playlistList);
        }
        else if(role == 2){
            menuUser(library, playlistList);
        }
        else if(role == 0){
            cout << "Keluar. Sampai jumpa!\n";
        }
        else{
            cout << "Pilihan tidak valid.\n";
        }
    }

    return 0;
}
