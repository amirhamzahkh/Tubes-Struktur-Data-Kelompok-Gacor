#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>

using namespace std;

struct InfoLagu {
    int id_lagu;
    string judul;
    string penyanyi;
    string album;
    string genre;
    int tahun;
    int durasi;
};

typedef struct ElmLagu* adrLagu;
typedef struct ElmPlaylist* adrPlaylist;
typedef struct ElmNode* adrNode;

struct ElmLagu {
    InfoLagu info;
    adrLagu next;
    adrLagu prev;
};

struct ElmNode {
    adrLagu pLagu;
    adrNode next;
};

struct ElmPlaylist {
    string namaPlaylist;
    adrNode isiLagu;
    adrPlaylist next;
};

struct ListLagu {
    adrLagu first;
    adrLagu last;
};

struct ListPlaylist {
    adrPlaylist first;
};


void createListLagu(ListLagu &L);
void createListPlaylist(ListPlaylist &P);

adrLagu allocateLagu(InfoLagu &data);
adrPlaylist allocatePlaylist(string &nama);
adrNode allocateNode(adrLagu L);

void insertFirstLagu(ListLagu &L, adrLagu P);
void insertLastLagu(ListLagu &L, adrLagu P);
void insertAfterLagu(ListLagu &L, adrLagu Prec, adrLagu P);

void removeNodeFromAll(ListPlaylist &PL, adrLagu target);
void deleteFirstLagu(ListLagu &L, ListPlaylist &PL, adrLagu &P);
void deleteLastLagu(ListLagu &L, ListPlaylist &PL, adrLagu &P);
void deleteAfterLagu(ListLagu &L, ListPlaylist &PL, adrLagu Prec, adrLagu &P);
void deleteLaguByID(ListLagu &L, ListPlaylist &PL, int id_lagu);

void showAllLagu(ListLagu &L);
adrLagu findLaguByTitle(ListLagu &L, string &judul);
adrLagu findLaguByID(ListLagu &L, int id_lagu);
void updateLagu(adrLagu P, InfoLagu &newData);

void addPlaylist(ListPlaylist &PL, string &nama);
void deletePlaylist(ListPlaylist &PL, string &nama);
void showAllPlaylists(ListPlaylist &PL);
adrPlaylist findPlaylist(ListPlaylist &PL, string &nama);

void addSongToPlaylist(adrPlaylist P, adrLagu L);
void removeSongFromPlaylist(adrPlaylist P, adrLagu L);
void showSongsInPlaylist(adrPlaylist P);

void playSong(adrLagu P);
void playNext(adrPlaylist PL, adrLagu song);
void playPrev(adrPlaylist PL, adrLagu song);

adrLagu findSimilarSong(ListLagu &L, adrLagu nowSong);

void menuAdmin(ListLagu &L, ListPlaylist &PL);
void menuUser(ListLagu &L, ListPlaylist &PL);

#endif // HEADER_H_INCLUDED
