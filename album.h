#include "metadata.h"

struct album
{
    char name[256];
    struct track *track;
    struct album *next;
};

struct album *create_album();
struct album *add_to_album(struct album *head, struct track *track);
void print_album(struct album *head);