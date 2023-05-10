#include "library.h"

int main(int argc, char *argv[])
{
    struct library *library = create_library();
    library = add_to_library(library, "music");
    library = sort(library, 0);
    print_library(library);
}
