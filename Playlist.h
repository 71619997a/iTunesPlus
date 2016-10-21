#ifndef PLAYLIST_H
#define PLAYLIST_H
typedef enum characteristic {NAME, ARTIST} characteristic;
void initializeTable();
char artist_index(char);
void addSong(Song*);
Song **find_songs(char, characteristic);
void print_songs(Song **);
void print_by_letter(char);
void print_all();
SongNode *shuffle(SongNode *);
void remove_song(Song *);
void remove_all();
int main();
#endif
