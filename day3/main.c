#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int part1(char *input) {
	int answer = 0;

	return answer;
}

int main() {

	char *buffer = 0;
	long length;
	FILE *f = fopen("small-input.txt", "rb");

	if (f) {
		fseek(f, 0, SEEK_END);
		length = ftell(f);
		fseek(f, 0, SEEK_SET);
		buffer = malloc(length);
		if (buffer) {
			fread(buffer, 1, length, f);
		}
		fclose(f);
	}

	if (buffer) {
		printf("Day 2 - Part 1: %i\n", part1(buffer));
		// printf("Day 2 - Part 2: %i\n", part2(buffer));
	}

	return 0;
}
