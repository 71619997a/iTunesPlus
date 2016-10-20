#ifndef SONGNODE_H
#define SONGNODE_H
typedef struct Song {
    char name[256];
    char artist[256];
} Song;
typedef struct SongNode {
    Song *song;
    struct SongNode *next;
} SongNode;
//int main();
Song *new_song(char *artist,char *name);
void print_list(SongNode *start);
SongNode *free_list(SongNode *start);
SongNode *insert_ordered(SongNode *start,SongNode *song);
SongNode *insert_front(SongNode *start,SongNode *song);
SongNode *from_song(Song *song);
SongNode *by_name(SongNode *start, char* name);
SongNode *by_artist(SongNode *start, char* artist);
#endif
