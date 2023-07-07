#include <stdio.h>
#include <stdlib.h>
#include "myheader.h"

VSpace newVSpace(int max) {
    VSpace vs;
    
    vs.max = max%2 == 0? max: max + 1;
    vs.count = 0;
    vs.data = malloc(sizeof(Data) * vs.max);
    vs.avail = vs.max/2;
    
    int i;
    for(i = 0; i < vs.avail; ++i) {
        vs.data[i].elem = EMPTY;
        vs.data[i].link = -1;
    }
    
    for(; i < vs.max-1; ++i) {
        vs.data[i].elem = EMPTY;
        vs.data[i].link = i + 1;    
    }
    vs.data[i].elem = EMPTY;
    vs.data[i].link = -1;
    
    return vs;
}

int allocSpace(VSpace *vs) {
    if (vs->avail == -1) {
        printf("No available space.\n");
        return -1;
    }

    int loc = vs->avail;
    vs->avail = vs->data[loc].link;
    vs->count++;
    vs->data[loc].link = -1;

    return loc;
}

void freeSpace(VSpace *vs, int loc) {
    if (loc >= 0 && loc < vs->max && vs->data[loc].link == -1) {
        vs->data[loc].link = vs->avail;
        vs->avail = loc;
        vs->count--;
    } else {
        printf("Invalid location to free space.\n");
    }
}

bool addElement(VSpace *vs) {
    if (vs->count >= vs->max) {
        printf("No space available to add element.\n");
        return false;
    }

    int val;
    printf("Enter the element to add: ");
    scanf("%d", &val);

    int loc = allocSpace(vs);
    vs->data[loc].elem = val;

    int hashedLoc = hash(val, vs->max);
    if (vs->data[hashedLoc].elem == EMPTY) {
        vs->data[hashedLoc].link = loc;
    } else {
        int currLoc = vs->data[hashedLoc].link;
        while (vs->data[currLoc].link != -1) {
            currLoc = vs->data[currLoc].link;
        }
        vs->data[currLoc].link = loc;
    }

    return true;
}

bool removeElement(VSpace *vs) {
    if (vs->count == 0) {
        printf("No elements to remove.\n");
        return false;
    }

    int val;
    printf("Enter the element to remove: ");
    scanf("%d", &val);

    int hashedLoc = hash(val, vs->max);
    int currLoc = vs->data[hashedLoc].link;
    int prevLoc = hashedLoc;
    while (currLoc != -1) {
        if (vs->data[currLoc].elem == val) {
            break;
        }
        prevLoc = currLoc;
        currLoc = vs->data[currLoc].link;
    }

    if (currLoc == -1) {
        printf("Element not found.\n");
        return false;
    }

    if (prevLoc == hashedLoc) {
        vs->data[hashedLoc].link = vs->data[currLoc].link;
    } else {
        vs->data[prevLoc].link = vs->data[currLoc].link;
    }

    freeSpace(vs, currLoc);

    return true;
}

void visualize(VSpace vs) {
    int i, half = vs.max/2;
    printf("%5s | %5s | %5s %10s %5s | %5s | %5s \n", "INDEX", "DATA", "LINK", "","INDEX", "DATA", "LINK");
    printf("----------------------          ----------------------\n");    
    for(i = 0; i < half; ++i) {
        printf("%5d | %5d | %5d %10s %5d | %5d | %5d \n", 
                i, vs.data[i].elem, vs.data[i].link, "",
                i + half, vs.data[i+half].elem, vs.data[i+half].link);
    }
}

int hash(int val, int size) {
    // Implementation of the hash function
    return val % size;
}
