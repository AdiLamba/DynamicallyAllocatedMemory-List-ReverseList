#include <stdio.h> /*included for standard input/output functions*/
#include <stdlib.h> /*included so malloc and free can be used*/
#include <string.h> /*included for string functions*/

typedef struct {
    char *title;
    char *author;
    int year;
} Book;

/*Function prototypes*/
Book *create_library(char *filename);
void display_books(Book *library);
Book *reverse_books(Book *library);
void save_to_file(char *filename, Book *library);

int main(int argc, char **argv) {

/*have the program ensure the number of arguements is 2 or 3 (1 will always be the programs executable name)*/
    if (argc < 2 || argc > 3) {
        printf("Invalid arguements\n");
        return 1;
    }

    /* create the library */
    Book *library = create_library(argv[1]);
    if (library == NULL) {
        printf("error: cannot read file\n");
        return 1;
    }

    printf("*************** Original Library ***************\n");
    /* display the library onto the screen */
    display_books(library);


    /* Create a reversed library */
    Book *reversed_library = reverse_books(library);

    printf("\n*************** Reversed Library ***************\n");
    display_books(reversed_library);

    /* Save the reversed library to a file */
    /*make it so the function only executes if there are 3 arguements, 3rd being the out file*/
    if (argc == 3){
        save_to_file(argv[2], reversed_library);
    }

    /*iterate through the lists and then free the memory*/

    int i;
    for (i = 0; i < 50; i++) {
        if (library[i].title == NULL){
            break;
        }
        free(library[i].title);
        free(library[i].author);
    }
    free(library);

    
    for (i = 0; i < 50; i++) {
        if (reversed_library[i].title == NULL) {
            break;
        }
        free(reversed_library[i].title);
        free(reversed_library[i].author);
    }
    free(reversed_library);

    /*Once the allocated memory has been released, end the program*/

    return 0;


}

Book *create_library(char *filename) {

/*File input creation and initialization*/
    FILE *in;
    in = fopen(filename, "r");
    if (in == NULL) {
        printf("could not open file\n");
        return NULL;
    }

/*allocate the memory for 50 book structs, each being the size of one Book structure*/
    Book *library = malloc(50 * sizeof(Book));

    char buffer[150];
    int i = 0;
   
/*use the 'file get string' function but get the entries in each line */
/*buffer has been set to 150, title/author is size of 50 chars*/
    while (fgets(buffer, sizeof(buffer), in) != NULL && i < 50) {
        library[i].title = malloc(50 * sizeof(char));
        library[i].author = malloc(50 * sizeof(char));
        if (library[i].title == NULL || library[i].author == NULL) {
            printf("Memory allocation failed\n");
            fclose(in);
            return NULL;
        }

        /*Was getting errors formatting before with %s but using this operator*/
        /*was able to treat the entries in the file as  comma separated values*/
        /*This will read up to 99 chars or until it encounters a comma*/
        sscanf(buffer, "%99[^,], %99[^,], %d", library[i].title, library[i].author, &library[i].year);
        i++;
    }

    fclose(in);

/*return the list of books*/
    return library;

}

/*Iterate through the list printing the entries as formatted below*/
void display_books(Book *library) {
    int i;
    for (i = 0; i < 50; i ++) {
        if (library[i].title==NULL){
            break;
        }
        printf("Book %d: %s by %s, %d\n", i, library[i].title, library[i].author, library[i].year);
    }

}

Book *reverse_books(Book *library) {

    /*Allocate memory for the reverse list*/
    Book *reversed_library = malloc(50 * sizeof(Book));
    if (reversed_library == NULL) {
        printf("Memory error\n");
        return NULL;
    }

    int num_books = 0;
    
    /*count the number of books in the list*/
    while (library[num_books].title != NULL && num_books < 50) {
        num_books++;
    }

/*Create the memory for the books that will be going in the reverse list with malloc*/
/*Use the num_books from before to work backwards num_books = 50. 50- 1 = 49 (Starts at index 49)*/
    int i;
    for (i = 0; i < num_books; i++) {
        reversed_library[i].title = malloc(strlen(library[num_books - 1 - i].title) + 1);
        reversed_library[i].author = malloc(strlen(library[num_books - 1 - i].author) + 1);
        if (reversed_library[i].title == NULL || reversed_library[i].author == NULL) {
            printf("Memory error\n");
            return NULL;
        }

        /*use the same logic to now fill the memory created above with a copy of the string in that index*/
        strcpy(reversed_library[i].title, library[num_books - 1 - i].title);
        strcpy(reversed_library[i].author, library[num_books - 1 - i].author);
        reversed_library[i].year = library[num_books - 1 - i].year;
    }

/*Return the reversed list of books*/
    return reversed_library;
}

/*Iterate through the list and add entries to the newly created file using the 'write' permission*/
void save_to_file(char *filename, Book *library) {
    FILE *out;
    out = fopen(filename, "w");
    if (out == NULL) {
        printf("could not open file\n");
        return;
    }
    int i;
    for (i = 0; i < 50; i++) {
        if (library[i].title == NULL) {
            break;
        }
        fprintf(out, "%s, %s, %d\n", library[i].title, library[i].author, library[i].year);
    }
    fclose(out);

}




/* 1245_66611 */
