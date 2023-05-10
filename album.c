#include "album.h"

struct album *create_album()
{
    struct album *album = calloc(1, sizeof(struct album));
    album->track = NULL;
    album->next = NULL;
}

struct album *add_to_album(struct album *head, struct track *track)
{
    // check if album is empty
    if (head->track == NULL) // empty
    {
        strcpy(head->name, track->album);
        head->track = track; // set new track as head of album

        return head;
    }
    else // has entries
    {
        // iterate to end of album
        struct album *temp = head;
        while (temp->next != NULL)
            temp = temp->next;

        // create album entry and append it to end
        struct album *new_entry = create_album();
        strcpy(new_entry->name, track->album);
        new_entry->track = track;
        temp->next = new_entry;

        return head;
    }
}

void print_album(struct album *head)
{
    printf("%s\n---\n", head->name);

    while (head)
    {
        printf("%s\n", head->track->title);
        head = head->next;
    }
    printf("\n");
}