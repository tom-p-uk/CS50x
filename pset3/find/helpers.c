/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"


bool search(int value, int values[], int n)
{
    // Binary searching algorithm
    if (n < 1)
    {
        return false;
    }
    
    int start, end, mid;
    
    start = 0;
    end = n-1;
    
    while (start <= end)
    {   
        mid = (start + end) / 2;
        if (value < values[mid])
        {
            end = mid - 1;
        }
        else if (value > values[mid])
        {
            start = mid + 1;
        }
        else
        {
            return true;
        }
        
    }
    if (start > end)
    {
        return false;
    }
    return true;
}
    
    

// Sort n values of an array

void sort(int values[], int n)
{



    // Bubble sort
    
    for (int i = 0, temp; i < n-1; i++)
    {
        for(int j = i+1; j < n; j ++)
        {
            if (values[i] > values[j])
            {
                temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
    }
    
    return;
}
    