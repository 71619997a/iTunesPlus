#import <stdlib.h>
#import <stdio.h>
#import "SongNode.h"
#import "Playlist.h"


SongNode *table[26];

void initializeTable() {
    int i = 0;
    for(i = 0; i < 26; i++) {
        table[i] = NULL;
    }
}

char artist_index(char letter) {
    char toIndex = letter - (letter > 'Z' ? 'a' : 'A');  // assume letter's a letter
    return toIndex;
}
void addSong(Song* song) {
    char index = artist_index(song->artist[0]);
    table[index] = insert_ordered(table[index], from_song(song));
}

Song **find_songs(char *charac, characteristic findBy) {
    // findBy can be ARTIST or NAME
    Song **results = NULL;  // array of song pointers
    int size = 0;
    if(findBy == ARTIST) {
        char index = artist_index(charac[0]);
        SongNode *list = table[index];
        while(list != NULL) {
            if(strcmp(list->song->artist, charac) == 0) {
                int alloc = ++size * sizeof(Song *);
                results = (Song **)realloc(results, alloc);
                results[size - 1] = list->song;
            }
            list = list->next;
        }
    }
    else if(findBy == NAME){
        int i = 0;
        for(i = 0; i < 26; i++) {
            SongNode *sn = by_name(table[i], charac);
            if(sn != NULL) {
                results = malloc(sizeof(Song *));
                results[0] = sn->song;
                size = 1;
                break;  // assume only one song w/ matching name
            }

        }
    }
    results = realloc(results, (size + 1) * sizeof(Song *));
    *(results + size) = NULL;
    return results;
}

void print_songs(Song **songs) {  // songs is a pointer to an array of pointers
    // *songs is a pointer to a song
    // **songs is a song
    // so *songs->name should get a song's name
    if(songs == NULL) return;
    while(*songs != NULL) {
        printf("\"%s\" by %s\n", (*songs)->name, (*songs)->artist);
        songs++;
    }
}

SongNode* reomve_song(char name[]){
    return remove_node(index[], find_songs(name, NAME));
}

SongNode* shuffle(SongNode *start){
  SongNode *header = remove_node(start, random_Song(start));
  SongNode *curr = header;
  while(length(start) != 0){
    SongNode holder = random_Song(start);
    if (holder == start){
      start = start->next;
      curr->next = holder;
      curr = curr->next;
    }
    else{
      curr->next = remove_node(holder);
      curr = curr->next;
    }
  }
  return header;

}
void print_by_letter(char letter) {
    char index = artist_index(letter);
    print_list(table[index]);
}

void print_all() {
    char i = 0;
    for(i = 0; i < 26; i++) {
        printf("\n%c:\n", i + 65);
        print_by_letter(i + 97);
    }
}

void remove_song(Song* rem) {
    char index = artist_index(rem->artist[0]);
    SongNode *iter = table[index];
    SongNode *bad = by_name(iter, rem->name);
    if(bad != NULL && bad->song == rem) {
        table[index] = remove_node(iter, bad);
    }
}

void remove_all(){
    char i;
    for(i=0;i<26;i++){
        table[index] = free_list(table[index]);
    }
}

int main() {
    sranddev();
    initializeTable();
    setbuf(stdout, NULL);
    addSong(new_song("bob boy", "the greatest"));
    addSong(new_song("billy the person", "zebra man"));
    addSong(new_song("silly sam", "doofus"));
    addSong(new_song("bob boy", "the bestest"));
    addSong(new_song("the people", "things"));
    print_all();
    printf("\nSongs by bob boy:\n");
    print_songs(find_songs("bob boy", ARTIST));
    printf("\nSongs starting with b:\n");
    print_by_letter('b');
    printf("\nSongs starting with s:\n");
    print_by_letter('s');
    printf("\nPrint the song \"zebra man\":\n");
    print_songs(find_songs("zebra man", NAME));
    printf("\nSongs by not a boy:\n");  // hes not a real boy
    print_songs(find_songs("not a boy", ARTIST));
    printf("\nPrint the song \"this song is not a song\":");
    print_songs(find_songs("this song is not a song", NAME));
    printf("shuffling");
    shuffle(table[0]);
    print_all;

}
