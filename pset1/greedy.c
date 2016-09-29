#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;
    float conversion;
    int cents;
    int numCoins = 0;

    do
    {   
        printf("O hai! How much change is owed?\n");
        dollars = GetFloat();
    }
    while (dollars < 0);
        
    conversion = dollars * 100;
    cents = round(conversion);

    while (cents > 0) {

        if (cents - 25 >= 0) 
        {
        	cents -= 25;
        	numCoins ++;
        }
        
        else if (cents - 10 >= 0) 
        {
        	cents -= 10;
        	numCoins ++;
        }
        
        else if (cents - 5 >= 0) 
        {
        	cents -= 5;
        	numCoins ++;
        }
        
        else if (cents - 1 >= 0)
        {
        	cents -= 1;
        	numCoins ++;
        }
    }
    
    printf("%i\n", numCoins);
}