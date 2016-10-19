#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char name[256];
    char artist[256];
} Song;

typedef struct SongNode {
    Song *song;
    struct SongNode *next;
} SongNode;

SongNode* insert_front(SongNode* start, Song* song) {
    SongNode *newSongNode = (SongNode*)malloc(sizeof(SongNode));
    newSongNode->song = song;
    newSongNode->next = start;
    return newSongNode;
}

SongNode* insert_ordered(SongNode* start, Song* song) {
    if(start == NULL || strcmp(song->name, start->song->name) <= 0) {
        return insert_front(start, song);
    }
    SongNode *last = start;
    SongNode *iter = start->next;
    while(iter != NULL) {
        if(strcmp(song->name, iter->song->name) <= 0) {
            SongNode *new = insert_front(iter, song);
            last->next = new;
            break;
        }
        iter = start->next;
    }
    return start;
}

SongNode* free_list(SongNode* start) {
    if(start == NULL) {
        return NULL;
    }
    start->next = free_list(start->next); // free and point
    free(start->song); // same as last
    start->song = NULL;
    free(start); // now we can free this memory
    return NULL; // don't use the pointer to freed mem
}

void print_list(SongNode* start) {
    if(start == NULL || start->song == NULL) {
        printf("NULL\n");
        return;
    }
    printf("\"%s\" by %s -> ", start->song->name, start->song->artist);
    print_list(start->next);
}

Song *new_song(char *artist, char *name) {
    Song *new = (Song*)malloc(sizeof(Song));
    strcpy(new->name, name);
    strcpy(new->artist, artist);
    return new;
}

int main() {
    setbuf(stdout, NULL);  // for debug
    Song *s1 = new_song("a guy", "some song");
    SongNode *sn1 = insert_ordered(NULL, s1);
    sn1 = insert_ordered(sn1, s1); //two copies
    print_list(sn1);
    Song *s2 = new_song("other guy", "another song");
    sn1 = insert_ordered(sn1, s2);
    print_list(sn1);
    Song *s3 = new_song("other guy", "His other song");
    sn1 = insert_ordered(sn1, s3);
    print_list(sn1);
    sn1 = free_list(sn1);
    print_list(sn1);
}
