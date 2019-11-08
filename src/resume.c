#include <string.h>
#include <stdio.h>

void loadFile(char* buf, char* fname) {
    FILE* f;
    f = fopen(fname, "r");
    fgets(buf, sizeof(buf), f);
}
