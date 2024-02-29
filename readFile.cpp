#include "readFile.h"

int CreateBuffer(Text* buf, const char* input_file, err_allocator* err_alloc)
{
    buf->position = 0;

    buf->size_buffer = GetSizeFile(input_file, err_alloc);
    
    if (buf->size_buffer == 0)
    {
        ERROR_INSERT("error getting size of file");
        return 1;
    }
    
    buf->str = (char*) calloc(buf->size_buffer, sizeof(char));
    if (buf->str== NULL)
    {
        ERROR_INSERT("dynamic allocation is fault");
        return 1;
    }

    if (ReadFile(buf, input_file, err_alloc) == 1)
    {
        ERROR_INSERT("error reading file");
        return 1;       
    }
    
    //buf->str[buf->size_buffer] = '\0';

    return 0;
}

void DeleteBuffer(Text* buf)
{
    buf->size_buffer = INT_MAX;
    buf->position    = INT_MAX;

    free(buf->str);
}

int ReadFile(Text* buf, const char* input_file, err_allocator* err_alloc)
{
    FILE* fname = fopen(input_file, "r");
    if (!fname)
    {
        ERROR_INSERT("file failed to open");
        return 1;
    }

    if (fread(buf->str, sizeof(char), buf->size_buffer, fname) == 0)
    {
        ERROR_INSERT("no characters were counted");
        return 1;
    }

    return 0;
}

size_t GetSizeFile(const char* input_file, err_allocator* err_alloc)
{
    struct stat buff;

    if (stat(input_file, &buff) == 1)
    {
        ERROR_INSERT("unsuccessful reading");
        return 0;
    }
    
    return (size_t) (buff.st_size);
}

int WriteFile(Text* buf, const char* output_file, err_allocator* err_alloc)
{
    FILE* fname = fopen(output_file, "w");
    if (!fname)
    {
        ERROR_INSERT("file failed to open");
        return 1;
    }

    if (fwrite(buf->str, sizeof(char), buf->size_buffer, fname) != buf->size_buffer)
    {
        ERROR_INSERT("write-to-file error");
        return 1;
    }

    return 0;
}