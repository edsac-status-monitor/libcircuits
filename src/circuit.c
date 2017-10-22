#include "circuit.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 512

int circuit_parse_file(FILE *infile, circuit_t *circuit)
{
    char *eol_token, *eol_last_token;
    char *string_iterator;
    char EOL[2] = "\n";

    char buffer[MAX_LINE_SIZE];
    char line_buf[MAX_LINE_SIZE];
    char item_type[16];

    size_t number_read;
    size_t line_len;

    // Used for wire types
    int startX, startY;
    int endX, endY;

    // Loop to read file line by line
    while (1)
    {
        memset(&buffer, '\0', MAX_LINE_SIZE);
        memset(&line_buf, '\0', MAX_LINE_SIZE);

        // Read a buffer-full
        eol_last_token = eol_token;
        number_read = fread(buffer, sizeof(char), MAX_LINE_SIZE - 1, infile);

        if (number_read == 0)
            goto break_loop;


        // Check for lines
        //  by filling up the buffer, and checking for the end of line
        //  character sequence
        //
        // Set eol_token search to the start of the buffer
        eol_last_token = NULL;
        eol_token = strtok(buffer, EOL);

        while (eol_token != NULL)
        {

            // On first iteration, eol_last_token is set to buffer
            //  and is updated to the last " " if required 
            eol_last_token = eol_token;
            eol_token = strtok(NULL, EOL);
            
            memset(&line_buf, '\0', MAX_LINE_SIZE);

            // No eol_token was found in the the buffer
            //  only ocurs when last token is set to start, and
            //  the next token is end
            //   i.e. the line is longer than the buffer
            if (eol_token == NULL && eol_last_token == buffer)
            {

                fprintf(stderr, "Error - one or more lines"
                        "of .asc file are longer than the"
                        "permitted buffer size (%d characters)\n",
                        MAX_LINE_SIZE - 1);
                return CIRCUIT_ERR;
            }

            // If a newline character was found in the buffer 
            if (eol_token != NULL)
            {
                // Calculate the length of the line
                line_len = eol_token - eol_last_token;

                // Copy the line from the read buffer, into the line buffer
                //  (makes string functions easier as we can set it to be null
                //   terminated where required)
                memcpy(line_buf, eol_token, line_len);


                // Capitalise the string
                //  should be capitalised in file, but just in case
                for (string_iterator = line_buf;
                    string_iterator < line_buf + line_len;
                    string_iterator++)
                {
                   *string_iterator = toupper((unsigned char)*string_iterator);
                }


                // Get the string name of the type
                //  e.g. WIRE, SHEET etc.
                sscanf(line_buf, "%s", item_type);

                // Switch depending on item_type
                if (memcmp(item_type, CIRCUIT_TYPE_WIRE, sizeof(CIRCUIT_TYPE_WIRE)-1) == 0)
                {
                    // A WIRE type

                    // Extract line data
                    sscanf(line_buf, "%s %d %d %d %d", item_type, &startX, &startY, &endX, &endY);

                    // Allocate a new item on the heap for the wire
                    wire_t *wire = (wire_t*)malloc(sizeof(wire_t));
                    wire->start_x = startX;
                    wire->start_y = startY;
                    wire->end_x = endX;
                    wire->end_y = endY;

                    // Add the vector
                    vector_add(&circuit->wires, wire);
                }

                // Reset eol_token to allow next line to be searched for
                //  i.e. set eol_token back to where it was in the buffer
                eol_token = strtok(eol_token, EOL);
            }
        }

        // Advance to check the next 'block'
        //  will return non-zero when end of file is reached
        if (fgetc(infile) == EOF)
            goto break_loop;

        // Move to the next location
        //  so we fetch new data when the buffer is refilled
        if (fseek(infile, (eol_last_token - buffer) - MAX_LINE_SIZE, SEEK_CUR) != 0)
            goto break_loop;

    }

break_loop:
    return CIRCUIT_OK;
}

void circuit_init(circuit_t *circuit)
{
    // Need to initialise all the vectors members of
    //  circuit_t
    vector_init(&circuit->wires);
}

void circuit_free(circuit_t *circuit)
{
    // Free heap memory
    //  to prevent memory leaks
    // 
    // Need to include all members of circuit_t
    int i;

    // Free wires
    for (i=circuit->wires.length-1; i<=0; i++)
    {
        free(vector_get(&circuit->wires, i));
    }

    // And free the vector itself
    vector_free(&circuit->wires);
}


