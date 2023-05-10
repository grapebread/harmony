#include "metadata.h"

struct track *create_metadata_tags()
{
    struct track *metadata = calloc(1, sizeof(struct track));

    return metadata;
}

int clean_track_num(char *str)
{
    int len = strlen(str);
    int n = 0;

    for (int i = 0; i < len; ++i)
    {
        if (!isdigit(str[i]))
        {
            n = i;
            break;
        }
    }

    char temp[n + 1];
    strncpy(temp, str, n + 1);
    temp[n + 1] = '\0';

    return atoi(temp);
}

int read_metadata(struct track *metadata, char *filename)
{
    int ret;
    AVFormatContext *fmt_ctx = NULL;
    const AVDictionaryEntry *tag = NULL;

    char *res = realpath(filename, metadata->path);
    if (res == NULL)
        return -1;

    if (ret = avformat_open_input(&fmt_ctx, filename, NULL, NULL))
        return ret;

    if ((ret = avformat_find_stream_info(fmt_ctx, NULL)) < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "Cannot find stream information\n");
        return ret;
    }

    metadata->duration = fmt_ctx->duration / 1000000;

    while (tag = av_dict_iterate(fmt_ctx->metadata, tag))
    {
        if (!strcmp(tag->key, "title"))
        {
            strcpy(metadata->title, tag->value);
        }
        else if (!strcmp(tag->key, "artist"))
        {
            strcpy(metadata->artist, tag->value);
        }
        else if (!strcmp(tag->key, "album"))
        {
            strcpy(metadata->album, tag->value);
        }
        else if (!strcmp(tag->key, "ORGANIZATION") || !strcmp(tag->key, "CIRCLE"))
        {
            strcpy(metadata->circle, tag->value);
        }
        else if (!strcmp(tag->key, "genre"))
        {
            strcpy(metadata->genre, tag->value);
        }
        else if (!strcmp(tag->key, "comment"))
        {
            strcpy(metadata->comment, tag->value);
        }
        else if (!strcmp(tag->key, "date"))
        {
            metadata->date = atoi(tag->value);
        }
        else if (!strcmp(tag->key, "track"))
        {
            metadata->track = clean_track_num(tag->value);
        }
    }

    return 0;
}

void print_track(struct track *metadata)
{
    printf("Title: %s\n", metadata->title);
    printf("Artist: %s\n", metadata->artist);
    printf("Album: %s\n", metadata->album);
    printf("Circle: %s\n", metadata->circle);
    printf("Genre: %s\n", metadata->genre);
    printf("Comment: %s\n", metadata->comment);
    printf("Path: %s\n", metadata->path);
    printf("Date: %d\n", metadata->date);
    printf("Track: %d\n", metadata->track);
    printf("Duration: %d\n", metadata->duration);
}