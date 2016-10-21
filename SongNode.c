#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SongNode.h"
//used for random

int length(SongNode* kyle){
  int x = 1;
  while (kyle->next != NULL){
    x++;
    kyle = kyle->next;
  }
  return x;
}
SongNode *remove_node(SongNode* start, SongNode* removed){
  if (start == removed){
    SongNode *new = start->next;
    start->next = NULL;
    free_list(start);
    return new;
  }

  SongNode *orig = start;
  while (start->next != removed){
    start = start->next;
  }

  SongNode *newnext = start->next->next;
  start->next->next = NULL;
  free_list(start->next);
  start->next = start->next->next;
  return orig;
}

SongNode* random_Song(SongNode* start){
  int x = rand() % length(start);
  SongNode *curr = start;
  while (x != 0){
    x--;
    curr = curr->next;
  }
  return curr;
}

SongNode* from_song(Song* song) {
    SongNode *newSN = (SongNode*) malloc(sizeof(SongNode));
    newSN->song = song;
    newSN->next = NULL;
    return newSN;
}

SongNode* insert_front(SongNode* start, SongNode* new) {
    new->next = start;
    return new;
}

// usage: go to node before removal
// node->next = remove_front(node->next);
SongNode *remove_front(SongNode* start) {
    SongNode *newStart = start->next;
    start->next = NULL;
    free_list(start);
    return newStart;
}

SongNode* insert_ordered(SongNode* start, SongNode* new) {
    if(start == NULL || strcmp(new->song->name, start->song->name) <= 0) {
        return insert_front(start, new);
    }
    SongNode *last = start;
    SongNode *iter = start->next;
    while(iter != NULL) {
        if(strcmp(new->song->name, iter->song->name) <= 0) {
            SongNode *ins = insert_front(iter, new);
            last->next = ins;
            break;
        }
        last = iter;
        iter = iter->next;

    }
    if(iter == NULL) {
        SongNode *ins = insert_front(iter, new);
        last->next = ins;
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
        return;
    }
    printf("\"%s\" by %s\n", start->song->name, start->song->artist);
    print_list(start->next);
}

Song *new_song(char *artist, char *name) {
    Song *new = (Song*)malloc(sizeof(Song));
    strcpy(new->name, name);
    strcpy(new->artist, artist);
    return new;
}

SongNode *by_name(SongNode *start, char *name) {
    while(start != NULL) {
        if(strcmp(start->song->name, name) == 0) break;
        start = start->next;
    }
    return start;
}

SongNode *by_artist(SongNode *start, char *artist) {
    while(start != NULL) {
        if(strcmp(start->song->artist, artist) == 0) break;
        start = start->next;
    }
    return start;
}

/*
int main() {
    setbuf(stdout, NULL);  // for debug
    Song *s1 = new_song("a guy", "some song");
    SongNode *sn1 = insert_ordered(NULL, from_song(s1));
    sn1 = insert_ordered(sn1, from_song(s1)); //two copies
    print_list(sn1);
    Song *s2 = new_song("other guy", "another song");
    sn1 = insert_ordered(sn1, from_song(s2));
    print_list(sn1);
    Song *s3 = new_song("other guy", "his other song");
    sn1 = insert_ordered(sn1, from_song(s3));
    Song *s4 = new_song("me", "zyzzva is the last word in the alphabet sometimes");
    sn1 = insert_ordered(sn1, from_song(s4));
    print_list(sn1);
    print_list(by_artist(sn1, "a guy"));
    SongNode *other = by_name(sn1, "his other song");
    print_list(other);
    other->next = remove_front(other->next);
    print_list(sn1);
    sn1 = free_list(sn1);
    print_list(sn1);
}
*/
