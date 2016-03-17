#include <stdlib.h>
#include <mcheck.h>
 
int main(void) { 
 
        mtrace(); /* Starts the recording of memory allocations and releases */
 
        int* a = NULL;
 
        a = malloc(sizeof(int)); /* allocate memory and assign it to the pointer */
        if (a == NULL) {
                return 1; /* error */
        }
 
        free(a); /* we free the memory we allocated so we don't have leaks */
        muntrace();
 
        return 0; /* exit */
 
}

