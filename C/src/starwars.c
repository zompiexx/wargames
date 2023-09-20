#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // for usleep

#define MAX_FRAME_SIZE 10000  // Arbitrary limit; adjust based on expected max size

void clearScreenAndSetCursor() {
    printf("\033[2J");       // Clear the screen
    printf("\033[1;1H");     // Move the cursor to the top-left corner
}

void displayFrame(const char frame[], int size) {
    clearScreenAndSetCursor();

    int lineCount = 0;
    int currentLineWidth = 0;

    // Calculate lineCount
    for (int i = 0; i < size; i++) {
        if (frame[i] == '\n') {
            lineCount++;
            currentLineWidth = 0;
        } else {
            currentLineWidth++;
        }
    }

    int topMargin = (24 - lineCount) / 2;
    for (int i = 0; i < topMargin; i++) {
        putchar('\n');
    }

    currentLineWidth = 0;
    for (int i = 0; i < size; i++) {
        if (frame[i] == '\n') {
            int leftMargin = 40 - (currentLineWidth / 2);  // Centering the frame line and then adding 5 for the shift
            for (int j = 0; j < leftMargin; j++) {
                putchar(' ');
            }
            currentLineWidth = 0;
        } else {
            currentLineWidth++;
        }
        putchar(frame[i]);
    }

    fflush(stdout);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp;
    char ch;
    char frame[MAX_FRAME_SIZE];
    int frameSize = 0;
    int frameDelay = 0;

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    while (1) {
        ch = fgetc(fp);
        
        if (ch == EOF) {
            // Display any remaining frame content and exit loop
            if (frameSize > 0) {
                displayFrame(frame, frameSize);
            }
            fclose(fp);
            return 0;  // Exit the program
        }

        // Check for frame marker at the beginning of a line
        if ((frameSize == 0 || frame[frameSize - 1] == '\n') && (ch >= '0' && ch <= '9')) {
            char buffer[4] = {0};  // For frame marker
            int bufferIndex = 0;

            // Gather the frame marker digits
            while (ch >= '0' && ch <= '9' && bufferIndex < 3) {
                buffer[bufferIndex++] = ch;
                ch = fgetc(fp);
            }
            buffer[bufferIndex] = '\0';
            
            frameDelay = atoi(buffer);  // Convert to integer delay

            // If there's frame content to display
            if (frameSize > 0) {
                displayFrame(frame, frameSize);
                usleep(frameDelay * 150000);  // Variable delay between frames
                //usleep(500000);  // Fixed delay between frames
                frameSize = 0;  // Reset for the next frame
            }

            // Push the non-digit char back to process it in the next iteration
            ungetc(ch, fp);
        } else {
            if (frameSize < MAX_FRAME_SIZE - 1) {
                frame[frameSize++] = ch;
            }
            // If nearing the max frame size, consider handling it gracefully.
        }
    }
}
