#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dprintf(...) fprintf(stderr, __VA_ARGS__)
#define fortil(cap) for(int i = 0; i < cap; i++)

void printPattern(char *inputPattern, int patternSize);
void applyCellRotation(char *inputPattern, int patternSize, int rotation);
void applyMatrixRotation(char *inputPattern, int patternSize, int rotation);
char *stitch(char *a, char *b, int size);

int main(int argc, char **argv) {
	if (argc < 2) {
    dprintf("Not enough arguments\n");
    return -1;
  }
	char filename[256];
	char buf[256];
	FILE *inputFile;
	bool foundRotation = false;
	bool foundPatternSize = false;
	bool encounteredError = false;
	int rotation, patternSize;
	char *inputPattern = NULL;
	char *rotatedPattern = NULL;
	char *stitchedPattern = NULL;
	int tempIndex = 0;


  dprintf("Arguments:\n");
  fortil(argc) {
    dprintf("%d: [%s]\n", i, argv[i]);
  }
	strcpy(filename, argv[1]);
	dprintf("%s\n", filename);

	inputFile = fopen(filename, "r");

	// read the parameters and data from the input file
	// 1. Get rotation
	// 2. Get size of pattern
	// 3. Read and store pattern
	while (fgets(buf, sizeof(buf), inputFile)) {
		buf[strlen(buf)-1]=0;
		if (!foundRotation) {
			rotation = (int) strtol(buf, NULL, 10);
			dprintf("Found rotation: %d\n", rotation);
			if (rotation != 90 && rotation != 180 && rotation != -90 && rotation != 0) {
				encounteredError = true;
				break;
			}
			foundRotation = true;
			continue;
		}

		if (!foundPatternSize) {
			patternSize = (int) strtol(buf, NULL, 10);
			dprintf("Found pattern size: %d\n", patternSize);
			if (patternSize < 1) {
				encounteredError = true;
				break;
			}
			// Allocate enough space for the pattern
			inputPattern = (char*) malloc(sizeof(char)*patternSize*patternSize);
			foundPatternSize = true;
			continue;
		}

		strncpy(&inputPattern[tempIndex*patternSize], buf, 4);
		tempIndex++;
		inputPattern[tempIndex*patternSize]=0;
	}

	printf("Input Pattern:\n");
	printf("Going to apply a %ddeg rotation.\n", rotation);

	printPattern(inputPattern, patternSize);

	// make a copy of input pattern to rotate
	rotatedPattern = (char *)malloc(sizeof(char)*patternSize*patternSize);
	strcpy(rotatedPattern, inputPattern);
	applyCellRotation(rotatedPattern, patternSize, rotation);
	applyMatrixRotation(rotatedPattern, patternSize, rotation);
	printf("Output Pattern:\n");
	stitchedPattern = stitch(inputPattern, rotatedPattern, patternSize);
	printPattern(stitchedPattern, patternSize*2);


	// cleanup

	fclose(inputFile);

	if (encounteredError) {
		dprintf("Warning. Encountered error...somewhere.\n");
	}

	if (foundPatternSize) {
		free(inputPattern);
	}
  free(rotatedPattern);

	free(stitchedPattern);

	return 0;
}

void printPattern(char *inputPattern, int patternSize) {
	int len = patternSize * patternSize;
	for (int i = 0; i < len; i+=patternSize) {
		printf("[%.*s]\n", patternSize, &inputPattern[i]);
	}
}
void applyCellRotation(char *inputPattern, int patternSize, int rotation) {
  if (rotation == 90) {
    fortil(patternSize*patternSize) {
      switch(inputPattern[i]) {
        case '-':
          inputPattern[i] = '|';
          break;
        default:
          break;
      }
    }
  }
}
void applyMatrixRotation(char *inputPattern, int patternSize, int rotation) {
	char *temp = NULL;
	temp = (char *)malloc(sizeof(char)*patternSize*patternSize);
	strcpy(temp, inputPattern);
	int row, col;
	int sourceIndex, destIndex;
	// rotation can be 90, 180, -90, or 0
	// we do nothing for 0
	if (inputPattern == NULL || patternSize < 1 || rotation == 0) return;

	if (rotation == 90) {
		for (row = patternSize-1; row >= 0; row--) {
			col = patternSize - row -1;
			for (int i = 0; i < patternSize; i++) {
				sourceIndex = patternSize*row + i;
				destIndex = col + patternSize*i;
				dprintf("Placing %d into %d\n", sourceIndex, destIndex);
				
				// i is our offset
				inputPattern[destIndex] = temp[sourceIndex];
			}
		}
	}
	
	free(temp);
}

char *stitch(char *a, char *b, int size) {
	char *out = NULL;
	int cur = 0;

	out = (char *)malloc(sizeof(char) * size*size*2);

	for (int i = 0; i < size*size; i+=size) {
    
		strncpy(&out[cur], &a[i], size);
		cur+=size;
		strncpy(&out[cur], &b[i], size);
		cur+=size;
		out[cur]=0;
	}
	for (int i = 0; i < size*size; i+=size) {
		strncpy(&out[cur], &b[i], size);
		cur+=size;
		strncpy(&out[cur], &a[i], size);
		cur+=size;
		out[cur]=0;
	}
  dprintf("At the end of stitch for size %d, cur is %d\n", size, cur);

	return out;
}
