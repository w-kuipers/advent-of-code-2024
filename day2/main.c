#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part1() {
	int safe_count = 0;

	FILE *fptr;
	char content[100];
	fptr = fopen("input.txt", "r");

	while (fgets(content, 100, fptr)) {
		char *token = strtok(content, " ");
		int last_token = -1;
		bool is_safe = true;

		// 0 is not set, 1 is asc, 2 is desc
		int direction = 0;

		int c = 0;
		while (token != NULL) {
			int item = atoi(token);
			token = strtok(NULL, " ");

			// First one should always pass
			if (c == 0) {
				last_token = item;
				c++;
				continue;
			}

			// When the current level equals the last, report is unsafe
			if (item == last_token) {
				is_safe = false;
				break;
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
				is_safe = false;
				break;
			}

			if (direction == 1 && item < last_token) {
				is_safe = false;
				break;
			}

			if (direction == 2 && item > last_token) {
				is_safe = false;
				break;
			}

			last_token = item;
			c++;
		}

		if (is_safe) {
			safe_count += 1;
		}
	}

	return safe_count;
}

int level_loop(char *content, int skip) {
	int last_token = -1;
	int faults = 0;

	char *token = strtok(content, " ");

	// 0 is not set, 1 is asc, 2 is desc
	int direction = 0;

	int c = 0;
	while (token != NULL) {
		int item = atoi(token);
		token = strtok(NULL, " ");

		if (c == skip) {
			last_token = item;
			c++;
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
			faults += 1;
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
			faults += 1;
		}

		if (direction == 1 && item < last_token) {
			faults += 1;
		}

		if (direction == 2 && item > last_token) {
			faults += 1;
		}

		last_token = item;
		c++;
	}

	return faults;
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
	fptr = fopen("small-input.txt", "r");

	while (fgets(content, 100, fptr)) {
		char lenclone[100];
		strcpy(lenclone, content);
		char clone[100];
		strcpy(clone, content);

		int len = get_len(lenclone);
		int faults = level_loop(content, -1);

		// if (token == NULL) {
		// 	continue;
		// }

		if (faults > 1) {
			continue;
		}

		bool safe = false;

		if (faults == 1) {
			for (int i = 0; i < len; i++) {
				char inner[100];
				strcpy(inner, clone);

				int new = level_loop(inner, i);

				if (new == 0) {
					safe = true;
				}
			}
		}

		if (faults == 0 || safe == true) {
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
