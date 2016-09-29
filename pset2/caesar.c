#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[]) 
{
    
    //---------Validate command line argument---------
    if (argc != 2 || atoi(argv[1]) <= 0)
    {
        printf("Enter a valid command line argument");
        return 1;
    }
    
    
    
    //---------Convert string argument to integer---------
    int k = atoi(argv[1]);
    int r = k % 26;



    //---------Receive string input from user---------
    string message = GetString();

    
    
    //---------Encrypt each character---------
    for (int i = 0, l = strlen(message); i < l; i ++)
    {
        char c = message[i];

        if (isalpha(c))
        {
            if (isupper(c))
            {
                if ( (c + r) > 90)
                {
                    c -= (26 - r);
                    printf("%c", c);
                }
                else 
                {
                    printf("%c", c + r);
                }
            }
            
            else if (islower(c))
            {
                if ( (c + r) > 122)
                {
                    c -= (26 - r);
                    printf("%c", c);
                }
                else 
                {
                    printf("%c", c + r);
                }
            }
        }
        
        else
        {
            printf("%c", c);
        }
    }
    printf("\n");
    return 0;
}