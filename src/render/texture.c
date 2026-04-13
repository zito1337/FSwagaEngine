#include "texture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* read_file(const char* path)
{
    FILE* f = fopen(path, "rb"); //"rb" = read binary mode
    if (!f) return NULL;
    
    //scrolls to the end of the file
    if (fseek(f, 0, SEEK_END) != 0){
        fclose(f); return NULL;
    }

    //tells the end of the file (end of the file == file's length in bytes)
    long size = ftell(f);
    if (size < 0) {
        fclose(f); return NULL;
    }

    //rewind file to the start of it, if application does not rewind it, then it would read file as a 0-byte trash because it would be readen from the end
    rewind(f);
    
    //allocating memory for size of a file PLUS "\0" symbol at the end
    char* buf = (char*)malloc((size_t)size + 1); // +1 is for "\n" so theres no buffer overflow
    if (!buf) {
        fclose(f); return NULL;
    }

    // reading the file in buf
    size_t read = fread(buf, 1, (size_t)size, f); //fread returns how many bytes were really readen

    //file is now readen. close it
    fclose(f);
    buf[read] = '\0';
    
    return buf;
}

void bind_texture(Texture *txt)
{
}

void use_texture(Texture *txt)
{
}
