#include "readFile.h"
#include "error_allocator.h"


int CrackFile(Text* buf, err_allocator* err_alloc)
{
    assert(buf);
    assert(err_alloc);

    buf->position = 66;                 // i hope this position 75h = 117d
    if (buf->str[buf->position] == 117)
    {
        buf->position++;
        buf->str[buf->position] = 0;    //
    }
    else 
    {
        ERROR_INSERT("doesnt match with 75");
        return 1;
    }

    return 0;
}


int main(const int argc, const char* argv[])
{
    if (argc != 3)
    {
        printf("Введите in-/out- файлы\n");
        return 1;
    }

    const char*  input_file = argv[1];
    const char* output_file = argv[2];
    
    struct err_allocator err_alloc = {};
    struct Text buf = {};

    error_allocator_Ctor(&err_alloc);

    

    if (CreateBuffer(&buf, input_file, &err_alloc) == 1)
    {
        dump_error(&err_alloc);

        error_allocator_Dtor(&err_alloc);
        DeleteBuffer(&buf);
        return 1;
    }


    CrackFile(&buf, &err_alloc);

    if (WriteFile(&buf, output_file, &err_alloc) == 1)
    {
        dump_error(&err_alloc);

        error_allocator_Dtor(&err_alloc);
        DeleteBuffer(&buf);
        return 1;
    }

    
    error_allocator_Dtor(&err_alloc);
    
    DeleteBuffer(&buf);

    return 0;
}
