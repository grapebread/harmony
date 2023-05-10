#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

#include <libavformat/avformat.h>
#include <libavutil/dict.h>

struct track
{
    char title[256];
    char artist[256];
    char album[256];
    char circle[256];
    char genre[256];
    char comment[4096];
    char path[1024];
    int date;
    int track;
    int duration;
};

struct track *create_metadata_tags();
int read_metadata(struct track *metadata, char *filename);
void print_track(struct track *metadata);