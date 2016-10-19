#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Song {
    char *name;
    char *artist;
};

struct SongNode {
    struct Song *song;
    struct SongNode *next;
};

struct SongNode* insert_front(struct SongNode* start, struct Song* song) {
    struct SongNode *newSongNode = (struct SongNode*)malloc(16);
    newSongNode->song = song;
    newSongNode->next = start;
    return newSongNode;
}

struct SongNode* insert_ordered(struct SongNode* start, struct Song* song) {
  if(start == NULL || strcmp(song->name, start->song->name) <= 0) {
    return insert_front(start, song);
  }
  struct SongNode *last = start;
  struct SongNode *iter = start->next;
  while(iter != NULL) {
    if(strcmp(song->name, iter->song->name) <= 0) {
      struct SongNode *new = insert_front(iter, song);
      last->next = new;
    }
  }
  return start;
}

struct SongNode* free_list(struct SongNode* start) {
    if(start == NULL) {
        return NULL;
    }
    free_list(start->next);  // make sure all memory past is gone
    start->next = NULL;  // make sure we aren't pointing to freed memory
    free(start->song);
    start->song = NULL;
    free(start);  // now we can free this memory
    return NULL;
}

void print_list(struct SongNode* start) {
    if(start == NULL || start->song == NULL) {
        printf("NULL\n");
        return;
    }
    printf("%s - %s -> ", start->song->artist, start->song->name);
    print_list(start->next);
}

struct Song *newSong(char *artist, char *name) {
  struct Song *new = (struct Song*)malloc(sizeof(struct Song));
  new->name = name;
  new->artist = artist;
  return new;
}

int main() {
  struct Song *s1 = newSong("a guy", "some song");
  struct SongNode *sn1 = insert_ordered(NULL, s1);
  sn1 = insert_ordered(sn1, s1); //two copies
  print_list(sn1);
  struct Song *s2 = newSong("other guy", "another song");
  sn1 = insert_ordered(sn1, s2);
  printf("inserted 2");
  struct Song *s3 = newSong("other guy", "his other song");
  sn1 = insert_ordered(sn1, s3);
  print_list(sn1);
  sn1 = free_list(sn1);
  print_list(sn1);
}
