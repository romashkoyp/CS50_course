#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("After the command's name you have to type the name of a raw file\n");
        return 1;
    }

    // Open memory card
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }

    // Create dynamic memory to read into
    uint8_t *buffer = malloc(sizeof(uint8_t) * BLOCK_SIZE);

    // Create filecounter for JPG
    int filecount = 0;

    // Create pointer for outfile
    FILE *outfile = NULL;

    // Create filename ***.jpg\0
    char new_file[8];

    // Repeat until end of card:
    // Read 512 bytes into a buffer
    while (fread(buffer, 1, BLOCK_SIZE, infile) == BLOCK_SIZE)
    {
        // Check the first 4 bytes
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Case for 000.jpg
            if (filecount == 0)
            {
                // Create new file
                sprintf(new_file, "%03i.jpg", filecount);
                outfile = fopen(new_file, "w");
                fwrite(buffer, 1, BLOCK_SIZE, outfile);
                filecount++;
            }

            // Case for JPG++
            else if (filecount > 0)
            {
                // Close 000.jpg
                fclose(outfile);

                // Create new file
                sprintf(new_file, "%03i.jpg", filecount);
                outfile = fopen(new_file, "w");
                fwrite(buffer, 1, BLOCK_SIZE, outfile);
                filecount++;
            }
        }

        // Continue writing to current JPEG file
        else if (filecount > 0)
        {
            fwrite(buffer, 1, BLOCK_SIZE, outfile);
        }
    }

    // Close any remaining files
    fclose(outfile);
    fclose(infile);

    // Free allocated memory
    free(buffer);

    // Exit program with success status
    return 0;
}