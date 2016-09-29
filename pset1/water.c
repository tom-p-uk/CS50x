#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int bottlesPerMin = 12;
    printf("minutes: ");
    int time = GetInt();
    printf("\nbottles: %i", (time * bottlesPerMin) );
}