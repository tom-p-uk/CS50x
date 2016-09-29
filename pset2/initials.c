#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    //---------Get string---------
    string name = GetString();
    


    //---------Convert to upper case---------
    for (int i = 0, l = strlen(name); i < l; i++)
    {
        if (((name[i] >= 'a') && (name[i] <= 'z')))
        {
            name[i] = toupper(name[i]);
        }
    }
    


    //---------Print initials---------
    for (int i = 0, l = strlen(name); i < l; i ++)
    {
        if (i == 0)
        {
            printf("%c", name[i]);
        }
        else if (name[i] == ' ')
        {
            printf("%c", name[i+1]);
        }
    }
    printf("\n");
}