#include <stdio.h>
#include <stdlib.h>
#include "myheader.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	VSpace vs = newVSpace(10); // Initialize virtual space with a maximum size of 10

    addElement(&vs); // Add elements to the virtual space
    addElement(&vs);
    addElement(&vs);
    addElement(&vs);
	addElement(&vs);
    

    visualize(vs); // Display the contents of the virtual space

    removeElement(&vs); // Remove an element from the virtual space

    visualize(vs); // Display the updated contents of the virtual space

    // Test other functions or functionalities

    return 0;
}
