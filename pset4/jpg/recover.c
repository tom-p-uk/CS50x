/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdint.h>
 
 typedef uint8_t  BYTE;

int main(void)
{
    // create buffer with array for all 512 bytes
    BYTE buffer[512];    
    
    // create counter for JPEG filenames
    int counter = 0;
    
    // create char array to hold filename string
    char filename[8];
    
    // open memory card file
    FILE* inptr = fopen("card.raw", "r");
    
    if (inptr == NULL)
    {
        printf("Could not open memory card.\n");
        return 1;
    }
    
    // declare file pointer for outfile
    FILE* outptr = NULL;
    
    // load blocks of 512 bytes into buffer until end of memory card
    while (fread(buffer, 512, 1, inptr) == 1)
    {
        // check for JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1) )
        {
            // check if file is already open
            if (outptr != NULL)
            {
                // close any open files
                fclose(outptr);
            }
            
            // create a new JPEG file
            sprintf(filename, "%03d.jpg", counter);
            counter ++;
            
            // open the file
            outptr = fopen(filename, "a");
                
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", filename);
                return 2;
            }
        }
        
        // if no file is open
        if (outptr != NULL)
        {
            //write to the file
            fwrite(buffer, 512, 1, outptr);
        }
    }

    // close outfile
    fclose(outptr);

    // close infile
    fclose(inptr);
    
    return 0;
}
