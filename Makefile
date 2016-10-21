all: run
    
run: compile
    ./a.out

compile:
    gcc SongNode.c Playlist.c

clean:
    rm a.out
