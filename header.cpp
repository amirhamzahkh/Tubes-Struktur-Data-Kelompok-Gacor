#include "header.h"
#include <iostream>

using namespace std;

void createListLagu(ListLagu &L){
    L.first = nullptr;
    L.last = nullptr;
}
void createListPlaylist(ListPlaylist &P){
    P.first = nullptr;
}
adrLagu allocateLagu(InfoLagu &data){
    adrLagu P = new ElmLagu;
    P->info = data;
    P->next = P->prev = nullptr;
    return P;
}
adrPlaylist allocatePlaylist(string &nama){
    adrPlaylist P = new ElmPlaylist;
    P->namaPlaylist = nama;
    P->isiLagu = nullptr;
    P->next = nullptr;
    return P;
}
adrNode allocateNode(adrLagu L) {
    adrNode N = new ElmNode;
    N->pLagu = L;
    N->next = nullptr;
    return N;
}

void insertFirstLagu(ListLagu &L, adrLagu P){
    if (!L.first) {
        L.first = L.last = P;
    } else {
        P->next = L.first;
        L.first->prev = P;
        L.first = P;
    }
}
void insertLastLagu(ListLagu &L, adrLagu P){
    if (!L.first) {
        insertFirstLagu(L, P);
    } else {
        L.last->next = P;
        P->prev = L.last;
        L.last = P;
    }
}
void insertAfterLagu(ListLagu &L, adrLagu Prec, adrLagu P){
    if (!Prec) {
        insertFirstLagu(L, P);
    } else if (Prec == L.last) {
        insertLastLagu(L, P);
    } else {
        P->next = Prec->next;
        P->prev = Prec;
        Prec->next->prev = P;
        Prec->next = P;
    }
}
void removeNodeFromAll(ListPlaylist &PL, adrLagu target){
    adrPlaylist PP = PL.first;
    while(PP){
        adrNode N = PP->isiLagu;
        adrNode prev = nullptr;
        while(N){
            if(N->pLagu == target){
                N->pLagu = nullptr;
                if(prev == nullptr){
                    PP->isiLagu = N->next;
                    N = PP->isiLagu;
                } else {
                    prev->next = N->next;
                    N = prev->next;
                }
            }
            else {
                prev = N;
                N = N->next;
            }
        }
        PP = PP->next;
    }
}

void deleteFirstLagu(ListLagu &L, ListPlaylist &PL, adrLagu &P){
    if (!L.first) {
        P = nullptr;
    } else {
        P = L.first;
        removeNodeFromAll(PL, P);
        if (L.first == L.last) {
            L.first = L.last = nullptr;
        } else {
            L.first = P->next;
            L.first->prev = nullptr;
        }
        P = nullptr;
    }
}
void deleteLastLagu(ListLagu &L, ListPlaylist &PL, adrLagu &P){
    if (!L.last) {
        P = nullptr;
    } else {
        P = L.last;
        removeNodeFromAll(PL, P);
        if (L.first == L.last) {
            L.first = L.last = nullptr;
        } else {
            L.last = P->prev;
            L.last->next = nullptr;
        }
        P = nullptr;
    }
}
void deleteAfterLagu(ListLagu &L, ListPlaylist &PL, adrLagu Prec, adrLagu &P){
    if (!Prec || !Prec->next) {
        P = nullptr;
    } else {
        P = Prec->next;
        removeNodeFromAll(PL, P);
        Prec->next = P->next;
        if (P->next) P->next->prev = Prec;
        if (P == L.last) L.last = Prec;
        P = nullptr;
    }
}

void deleteLaguByID(ListLagu &L, ListPlaylist &PL, int id_lagu){
    adrLagu P = L.first;
    bool found = false;
    while(P){
        if(P->info.id_lagu == id_lagu){
            found = true;
            removeNodeFromAll(PL, P);
            if(P == L.first && P == L.last){
                L.first = L.last = nullptr;
            } else if(P == L.first){
                L.first = P->next;
                if(L.first) L.first->prev = nullptr;
            } else if(P == L.last){
                L.last = P->prev;
                if(L.last) L.last->next = nullptr;
            } else {
                if(P->prev) P->prev->next = P->next;
                if(P->next) P->next->prev = P->prev;
            }
            cout << "Lagu dengan ID " << id_lagu << " dihapus.\n";
        }
        P = P->next;
    }
    if(!found){
        cout << "ID lagu tidak ditemukan.\n";
    }
}

void showAllLagu(ListLagu &L){
    if (!L.first) {
        cout << "\nLibrary kosong.\n";
    } else {
        cout << "\n==== Daftar Lagu di Library ====\n";
        adrLagu P = L.first;
        while(P){
            cout << "ID: " << P->info.id_lagu
                 << " | Judul: " << P->info.judul
                 << " | Artis: " << P->info.penyanyi
                 << " | Genre: " << P->info.genre
                 << " | Tahun: " << P->info.tahun
                 << " | Durasi(s): " << P->info.durasi
                 << "\n";
            P = P->next;
        }
    }
}

adrLagu findLaguByTitle(ListLagu &L, string &judul){
    adrLagu P = L.first;
    while(P){
        if (P->info.judul == judul) return P;
        P = P->next;
    }
    return nullptr;
}
adrLagu findLaguByID(ListLagu &L, int id_lagu){
    adrLagu P = L.first;
    while(P){
        if (P->info.id_lagu == id_lagu) return P;
        P = P->next;
    }
    return nullptr;
}
void updateLagu(adrLagu P, InfoLagu &newData){
    if (P) {
        P->info = newData;
    }
}
void addPlaylist(ListPlaylist &PL, string &nama){
    adrPlaylist walker = PL.first;

    while(walker != nullptr){
        if(walker->namaPlaylist == nama){
            cout << "Nama playlist sudah ada.\n";
            return;
        }
        walker = walker->next;
    }
    adrPlaylist P = allocatePlaylist(nama);
    P->next = PL.first;
    PL.first = P;
    cout << "Playlist \"" << nama << "\" dibuat.\n";
}
void deletePlaylist(ListPlaylist &PL, string &nama){
    adrPlaylist P = PL.first;
    adrPlaylist prev = nullptr;
    while(P){
        if(P->namaPlaylist == nama){
            adrPlaylist nextNode = P->next;
            if(prev == nullptr){
                PL.first = nextNode;
            } else {
                prev->next = nextNode;
            }

            P->isiLagu = nullptr;
            cout << "Playlist \"" << nama << "\" dihapus.\n";
            return;
        }
        prev = P;
        P = P->next;
    }
    cout << "Playlist tidak ditemukan.\n";
}
void showAllPlaylists(ListPlaylist &PL){
    if (!PL.first){
        cout << "Belum ada playlist.\n";
    } else {
        cout << "\n==== List Playlist ====\n";
        adrPlaylist P = PL.first;
        while(P){
            cout << "- " << P->namaPlaylist << "\n";
            P = P->next;
        }
    }
}
adrPlaylist findPlaylist(ListPlaylist &PL, string &nama){
    adrPlaylist P = PL.first;
    while(P){
        if (P->namaPlaylist == nama) return P;
        P = P->next;
    }
    return nullptr;
}

void addSongToPlaylist(adrPlaylist P, adrLagu L){
    if(P == nullptr){
        cout << "Playlist tidak ditemukan.\n";
        return;
    }
    if(L == nullptr){
        cout << "Lagu tidak ditemukan di library.\n";
        return;
    }
    adrNode N = P->isiLagu;
    while(N != nullptr){
        if(N->pLagu == L){
            cout << "Lagu sudah ada di playlist.\n";
            return;
        }
        N = N->next;
    }
    adrNode New = allocateNode(L);
    New->next = P->isiLagu;
    P->isiLagu = New;
    cout << "Lagu \"" << L->info.judul
         << "\" ditambahkan ke playlist \""
         << P->namaPlaylist << "\".\n";
}
void removeSongFromPlaylist(adrPlaylist P, adrLagu L){
    if(P == nullptr){
        cout << "Playlist tidak ditemukan.\n";
    }
    else {
        adrNode N = P->isiLagu;
        adrNode prev = nullptr;
        bool removed = false;
        while(N != nullptr){
            if(N->pLagu == L){
                if(prev == nullptr){
                    P->isiLagu = N->next;
                    N = P->isiLagu;
                }
                else {
                    prev->next = N->next;
                    N = prev->next;
                }
                removed = true;
            }
            else {
                prev = N;
                N = N->next;
            }
        }

        if(removed == true){
            cout << "Lagu berhasil dihapus dari playlist.\n";
        }
        else {
            cout << "Lagu tidak ada di playlist.\n";
        }
    }
}
void showSongsInPlaylist(adrPlaylist P){
    if(!P){
        cout << "Playlist tidak ditemukan.\n";
    } else if(!P->isiLagu){
        cout << "Playlist kosong.\n";
    } else {
        cout << "\n==== Isi Playlist: " << P->namaPlaylist << " ====\n";
        adrNode N = P->isiLagu;
        int idx = 1;
        while(N){
            cout << idx++ << ". " << N->pLagu->info.judul << " - " << N->pLagu->info.penyanyi << "\n";
            N = N->next;
        }
    }
}
void playSong(adrLagu P){
    if(P){
        cout << "\n========== Sedang Memutar ==========\n";
        cout << "Judul   : " << P->info.judul << "\n";
        cout << "Penyanyi: " << P->info.penyanyi << "\n";
        cout << "Album   : " << P->info.album << "\n";
        cout << "Genre   : " << P->info.genre << "\n";
        cout << "Tahun   : " << P->info.tahun << "\n";
        cout << "Durasi  : " << P->info.durasi << " detik\n";
        cout << "===================================\n";
    } else {
        cout << "Lagu tidak ditemukan.\n";
    }
}

void playNext(adrPlaylist PL, adrLagu song){
    if(PL != nullptr){
        adrNode pos = PL->isiLagu;
        while(pos != nullptr){
            if(pos->pLagu == song){
                if(pos->next != nullptr){
                    playSong(pos->next->pLagu);
                } else {
                    cout << "Tidak ada lagu berikutnya di playlist.\n";
                }
                return;
            }
            pos = pos->next;
        }
        cout << "Lagu tidak ditemukan di playlist.\n";
        return;
    }
    if(song == nullptr){
        cout << "Tidak ada lagu yang dijadikan acuan.\n";
        return;
    }
    if(song->next != nullptr){
        playSong(song->next);
        return;
    }
    cout << "Sudah di lagu terakhir Library.\n";
}
void playPrev(adrPlaylist PL, adrLagu song){
    if(PL != nullptr){
        adrNode pos = PL->isiLagu;
        adrNode prev = nullptr;
        while(pos != nullptr){
            if(pos->pLagu == song){
                if(prev != nullptr){
                    playSong(prev->pLagu);
                } else {
                    cout << "Tidak ada lagu sebelumnya di playlist.\n";
                }
                return;
            }
            prev = pos;
            pos = pos->next;
        }
        cout << "Lagu tidak ditemukan di playlist.\n";
        return;
    }
    if(song == nullptr){
        cout << "Tidak ada lagu yang dijadikan acuan.\n";
        return;
    }

    if(song->prev != nullptr){
        playSong(song->prev);
        return;
    }
    cout << "Sudah berada di awal Library.\n";
}
adrLagu findSimilarSong(ListLagu &L, adrLagu nowSong){
    if(!nowSong)
return nullptr;
    adrLagu P = L.first;
    while(P){
        if(P != nowSong && P->info.penyanyi == nowSong->info.penyanyi)
            return P;
        P = P->next;
    }
    P = L.first;
    while(P){
        if(P != nowSong && P->info.genre == nowSong->info.genre)
            return P;
        P = P->next;
    }
    return nowSong;
}

void menuAdmin(ListLagu &L, ListPlaylist &PL){
    bool running = true;
    while(running){
        cout << "\n===== MENU ADMIN =====\n";
        cout << "1. Tambah Lagu\n2. Tampilkan Semua Lagu\n3. Edit Lagu (by judul)\n4. Hapus Lagu (by ID)\n0. Kembali\n>> ";

        int pilih;
        cin >> pilih;
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input tidak valid.\n";
        }
        else if(pilih == 0){
            running = false;
        }
        else if(pilih == 1){
            InfoLagu X;
            cout << "ID: "; cin >> X.id_lagu;
            cout << "Judul: "; cin >> X.judul;
            cout << "Artis: "; cin >> X.penyanyi;
            cout << "Album: "; cin >> X.album;
            cout << "Genre: "; cin >> X.genre;
            cout << "Tahun: "; cin >> X.tahun;
            cout << "Durasi (detik): "; cin >> X.durasi;

            insertLastLagu(L, allocateLagu(X));
            cout << "Lagu ditambahkan.\n";
        }
        else if(pilih == 2){
            showAllLagu(L);
        }
        else if(pilih == 3){
            string judul;
            cout << "Masukkan judul lagu yang ingin diupdate: ";
            cin >> judul;
            adrLagu P = findLaguByTitle(L, judul);
            if(!P){
                cout << "Lagu tidak ditemukan.\n";
            }
            else{
                InfoLagu X;
                cout << "ID baru: "; cin >> X.id_lagu;
                cout << "Judul baru: "; cin >> X.judul;
                cout << "Artis baru: "; cin >> X.penyanyi;
                cout << "Album baru: "; cin >> X.album;
                cout << "Genre baru: "; cin >> X.genre;
                cout << "Tahun baru: "; cin >> X.tahun;
                cout << "Durasi baru: "; cin >> X.durasi;
                updateLagu(P, X);
                cout << "Lagu diperbarui.\n";
            }
        }
        else if(pilih == 4){
            int id;
            cout << "Masukkan ID yang akan dihapus: ";
            cin >> id;
            deleteLaguByID(L, PL, id);
        }
        else{
            cout << "Pilihan tidak valid.\n";
        }
    }
}
void menuUser(ListLagu &L, ListPlaylist &PL){
    bool running = true;
    while(running){
        cout << "\n===== MENU USER =====\n";
        cout << "1. Tampilkan semua lagu\n"
             << "2. Buat playlist\n"
             << "3. Tampilkan playlist\n"
             << "4. Tambah lagu ke playlist\n"
             << "5. Hapus lagu dari playlist\n"
             << "6. Lihat isi playlist\n"
             << "7. Putar lagu\n"
             << "0. Kembali\n>> ";

        int pilih;
        cin >> pilih;

        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input tidak valid.\n";
        }
        else if(pilih == 0){
            running = false;
        }
        else if(pilih == 1){
            showAllLagu(L);
        }
        else if(pilih == 2){
            string nama;
            cout << "Nama playlist: ";
            cin >> nama;
            addPlaylist(PL, nama);
        }
        else if(pilih == 3){
            showAllPlaylists(PL);
        }
        else if(pilih == 4){
            string nama, judul;
            cout << "Nama playlist: ";
            cin >> nama;
            cout << "Judul lagu: ";
            cin >> judul;

            adrPlaylist P = findPlaylist(PL, nama);
            adrLagu LAGU = findLaguByTitle(L, judul);
            addSongToPlaylist(P, LAGU);
        }
        else if(pilih == 5){
            string nama, judul;
            cout << "Nama playlist: ";
            cin >> nama;
            cout << "Judul lagu: ";
            cin >> judul;

            adrPlaylist P = findPlaylist(PL, nama);
            adrLagu LAGU = findLaguByTitle(L, judul);
            removeSongFromPlaylist(P, LAGU);
        }
        else if(pilih == 6){
            string nama;
            cout << "Nama playlist: ";
            cin >> nama;

            adrPlaylist P = findPlaylist(PL, nama);
            showSongsInPlaylist(P);
        }
        else if(pilih == 7){
            string judul;
            cout << "Judul lagu: ";
            cin >> judul;

            adrLagu LAGU = findLaguByTitle(L, judul);
            if(!LAGU){
                cout << "Lagu tidak ditemukan.\n";
            }
            else{
                adrPlaylist activePL = nullptr;
                playSong(LAGU);

                bool playLoop = true;
                adrLagu current = LAGU;

                while(playLoop){
                    cout << "\nOpsi pemutaran:\n";
                    cout << "1. Stop\n"
                         << "2. Next\n"
                         << "3. Prev\n"
                         << "4. Set active playlist\n"
                         << "5. Kembali ke menu\n>> ";

                    int op;
                    cin >> op;

                    if(cin.fail()){
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Input tidak valid.\n";
                    }
                    else if(op == 1){
                        cout << "\n---------------------------------\n";
                        cout << " Pemutaran dihentikan: "
                             << current->info.judul << "\n";
                        cout << "---------------------------------\n";
                        playLoop = false;
                    }
                    else if(op == 2){
                        playNext(activePL, current);
                        if(activePL){
                            adrNode pos = activePL->isiLagu;
                            while(pos && pos->pLagu != current)
                                pos = pos->next;
                            if(pos && pos->next)
                                current = pos->next->pLagu;
                        }
                        else if(current->next){
                            current = current->next;
                        }
                    }
                    else if(op == 3){
                        playPrev(activePL, current);
                        if(activePL){
                            adrNode pos = activePL->isiLagu;
                            adrNode prev = nullptr;
                            while(pos && pos->pLagu != current){
                                prev = pos;
                                pos = pos->next;
                            }
                            if(prev)
                                current = prev->pLagu;
                        }
                        else if(current->prev){
                            current = current->prev;
                        }
                    }
                    else if(op == 4){
                        string pname;
                        cout << "Nama playlist aktif: ";
                        cin >> pname;

                        adrPlaylist P = findPlaylist(PL, pname);
                        if(!P){
                            cout << "Playlist tidak ditemukan.\n";
                        }
                        else{
                            activePL = P;
                            cout << "Playlist aktif: "
                                 << P->namaPlaylist << "\n";
                        }
                    }
                    else if(op == 5){
                        cout << "Kembali ke menu.\n";
                        playLoop = false;
                    }
                    else{
                        cout << "Pilihan tidak valid.\n";
                    }
                }
            }
        }
        else{
            cout << "Pilihan tidak valid.\n";
        }
    }
}
