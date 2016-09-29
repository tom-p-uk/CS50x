#include <stdio.h>
#include <cs50.h>

int main(void) 
{
    int n;
    char hash = '#';
    char space = ' ';
    
    do 
    {
        printf("Height: ");
        n = GetInt();
    }
    while (n < 0 || n > 23);
    
    for (int i = 2; i < n+2; i++)
    {
        for (int j = n+1; j > 0; j--) 
        {
            if (j > i) 
            {
                printf("%c", space);
            } 
            else 
            {
                printf("%c", hash);
            }
        }
        printf("\n");
    }
}