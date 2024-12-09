#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool level_loop(char *content, int skip) {
	int last_token = -1;
	int faults = 0;
	bool is_safe = true;

	char *token = strtok(content, " ");

	if (token == NULL) {
		return false;
	}

	// 0 is not set, 1 is asc, 2 is desc
	int direction = 0;

	int c = 0;

	while (token != NULL) {
		int item = atoi(token);
		token = strtok(NULL, " ");

		if (c == skip) {
			skip = -1;
			continue;
		}

		// First one should always pass
		if (c == 0) {
			last_token = item;
			c++;
			continue;
		}

		// When the current level equals the last, report is unsafe
		if (item == last_token) {
			return false;
		}

		// With the second iteration determine direction
		if (c == 1) {
			if (item > last_token) {
				direction = 1;
			} else {
				direction = 2;
			}
		}

		// Difference can must be at least 1 and max 4
		int diff = abs(item - last_token);
		if (diff < 1 || diff > 3) {
			return false;
		}

		if (direction == 1 && item < last_token) {
			return false;
		}

		if (direction == 2 && item > last_token) {
			return false;
		}

		last_token = item;
		c++;
	}

	return true;
}

int get_len(char *content) {

	char *token = strtok(content, " ");
	int c = 0;
	while (token != NULL) {
		c++;
		token = strtok(NULL, " ");
	}
	return c;
}

int part2() {

	int safe_count = 0;

	FILE *fptr;
	char content[100];
	fptr = fopen("input.txt", "r");

	while (fgets(content, 100, fptr)) {
		char lenclone[100];
		char clone[100];

		strcpy(lenclone, content);
		strcpy(clone, content);

		int len = get_len(lenclone);
		bool initially_safe = level_loop(content, -1);

		if (initially_safe) {
			safe_count += 1;
			continue;
		}

		bool safe = initially_safe;

		if (!initially_safe) {
			for (int i = 0; i < len; i++) {
				char inner[100];
				strcpy(inner, clone);

				if (level_loop(inner, i)) {
					safe = true;
					break;
				}
			}
		}

		if (safe == true) {
			safe_count += 1;
		}
	}

	return safe_count;
}

int part1() {
	int safe_count = 0;

	FILE *fptr;
	char content[100];
	fptr = fopen("input.txt", "r");

	while (fgets(content, 100, fptr)) {
		if (level_loop(content, -1)) {
			safe_count += 1;
		}
	}

	return safe_count;
}

int main() {

	printf("Day 2 - Part 1: %i\n", part1());
	printf("Day 2 - Part 2: %i\n", part2());

	return 0;
}
