#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[]) 
{
    
    //---------Validate command line argument---------
    if (argc != 2)
    {
        printf("Invalid number of command line arguments entered\n");
        return 1;
    } 

    for (int i = 0, l = strlen(argv[1]); i < l; i++)
    {
        char ch = argv[1][i];
        if (isalpha(ch) == 0)
        {
            printf("String contained a non-alphabetical character\n");
            return 1;
        }
    }
    
    
    
    //---------Save codeword to variable & convert to array of ints---------
    string codeword = argv[1];
    int codewordLength = strlen(codeword);
    int r[codewordLength];
    
    for (int i = 0; i < codewordLength; i++)
    {
        if (codeword[i] >= 'A' && codeword[i] <= 'Z')
        {
            r[i] = (codeword[i] - 65);
        }
        else if (codeword[i] >= 'a' && codeword[i] <= 'z')
        {
            r[i] = (codeword[i] - 97);
        }
    }

    
    
    //---------Receive string input from user---------
    string message = GetString();
    


    //---------Encrypt each character---------
    int j = -1;
    for (int i = 0, l = strlen(message); i < l; i ++)
    {
        char c = message[i];
  
        
        if (isalpha(c))
        {
            j++;
            if (isupper(c))
            {
                if ( (c + r[j % codewordLength]) > 90)
                {
                    c -= (26 - r[j % codewordLength]);
                    printf("%c", c);
                }
                else 
                {
                    printf("%c", c + r[j % codewordLength]);
                }
            }
            
            else if (islower(c))
            {
                if ( (c + r[j % codewordLength]) > 122)
                {
                    c -= (26 - r[j % codewordLength]);
                    printf("%c", c);
                }
                else 
                {
                    printf("%c", c + r[j % codewordLength]);
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