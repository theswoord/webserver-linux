#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // std::string hh = "   akala tilmido tofa7ata hh  ";
    // split(hh," t",res);
    char* hh = calloc(150,1);
    hh = strtok("   akala tilmido tofa7ata hh  "," t");
    printf("|%s|\n",hh);

    
}