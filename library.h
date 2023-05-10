#include "album.h"

#include <sys/stat.h>
#include <dirent.h>

struct library
{
    struct album *album;
    struct library *next;
};

struct library *create_library();
struct library *add_to_library(struct library *head, char *path);
struct album *find_album(struct library *head, char *name);
void print_library(struct library *head);
struct library *sort(struct library *head, int order);
int library_len(struct library *head);