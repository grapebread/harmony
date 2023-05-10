#include "library.h"

struct library *add_entry(struct library *head, char *path);
struct library *add_directory_recursive(struct library *head, char *base_path);
void swap(struct library *a, struct library *b);
void quicksort(struct library *arr[], int low, int high);
int partition(struct library *arr[], int low, int high);

struct library *create_library()
{
    struct library *library = calloc(1, sizeof(library));
    library->album = NULL;
    library->next = NULL;

    return library;
}

struct library *add_to_library(struct library *head, char *path)
{
    struct stat stat_path;
    stat(path, &stat_path);

    // check if path is a file or directory
    if (S_ISREG(stat_path.st_mode))
        return add_entry(head, path);
    else
        return add_directory_recursive(head, path);
}

struct album *find_album(struct library *head, char *name)
{
    while (head)
    {
        if (!strcmp(head->album->name, name))
            return head->album;

        head = head->next;
    }

    return NULL;
}

struct library *add_entry(struct library *head, char *path)
{
    // create new track
    struct track *new_track = create_metadata_tags();
    read_metadata(new_track, path);

    // if library is empty
    if (head->album == NULL)
    {
        // attach new album to head
        struct album *new_album = create_album();
        new_album = add_to_album(new_album, new_track);
        head->album = new_album;

        return head;
    }
    else // library has entries
    {
        // check if album exists in library
        struct album *found = find_album(head, new_track->album);

        // doesn't exist so append album to library
        if (found == NULL)
        {
            struct library *temp = head; // iterate dummy ptr while head same
            while (temp->next != NULL)
                temp = temp->next;

            struct album *new_album = create_album();
            struct library *new_entry = create_library();
            new_album = add_to_album(new_album, new_track);

            new_entry->album = new_album;
            temp->next = new_entry;

            return head;
        }
        else // exists so add track to album
        {
            add_to_album(found, new_track);

            return head;
        }
    }
}

struct library *add_directory_recursive(struct library *head, char *base_path)
{
    char path[1024];
    struct dirent *dp;
    struct stat stat_path;
    DIR *dir = opendir(base_path);

    // if not a director, recurse out
    if (!dir)
        return head;

    while (dp = readdir(dir))
    {
        if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, ".."))
        {
            strcpy(path, base_path);
            strcat(path, "/");
            strcat(path, dp->d_name);

            stat(path, &stat_path);
            if (S_ISREG(stat_path.st_mode))
                head = add_entry(head, path);

            head = add_directory_recursive(head, path);
        }
    }

    closedir(dir);

    return head;
}

void print_library(struct library *head)
{
    printf("Library\n---------\n");

    while (head)
    {
        print_album(head->album);
        head = head->next;
    }
}

int library_len(struct library *head)
{
    int i = 0;
    while (head)
    {
        ++i;
        head = head->next;
    }

    return i;
}

// quick sort
// 0 = asc, 1 = desc
struct library *sort(struct library *head, int order)
{
    int len = library_len(head);

    if (len < 2)
        return head;

    struct library *temp = head;
    struct library *arr[len];
    struct library *new_head;

    int i = 0;
    while (temp)
    {
        arr[i] = temp;

        ++i;
        temp = temp->next;
    }

    quicksort(arr, 0, len - 1);

    if (order)
    {
        new_head = arr[len - 1];
        temp = new_head;

        for (int i = len - 2; i >= 0; --i)
        {
            temp->next = arr[i];
            temp = temp->next;
        }
    }
    else
    {
        new_head = arr[0];
        temp = new_head;

        for (int i = 1; i < len; ++i)
        {
            temp->next = arr[i];
            temp = temp->next;
        }
    }

    temp->next = NULL;

    return new_head;
}

void quicksort(struct library *arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high);
        quicksort(arr, low, pivot - 1);
        quicksort(arr, pivot + 1, high);
    }
}

int partition(struct library *arr[], int low, int high)
{
    struct library pivot = *arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j)
    {
        if (strcasecmp(arr[j]->album->name, pivot.album->name) < 0)
        {
            ++i;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    return i + 1;
}

void swap(struct library *a, struct library *b)
{
    struct library temp = *a;
    *a = *b;
    *b = temp;
}
