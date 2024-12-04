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

int level_loop(char **token, int skip) {
	int last_token = -1;
	int faults = 0;

	// 0 is not set, 1 is asc, 2 is desc
	int direction = 0;

	int c = 0;
	while (*token != NULL) {
		int item = atoi(*token);
		*token = strtok(NULL, " ");

		// printf("%i", skip);
		// if (c == skip) {
		// 	continue;
		// }

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

int part2() {

	int safe_count = 0;

	FILE *fptr;
	char content[100];
	fptr = fopen("small-input.txt", "r");

	while (fgets(content, 100, fptr)) {
		char *token = strtok(content, " ");

		int tokenlen = strlen(content);
		printf("%i", tokenlen);
		int faults = level_loop(&token, -1);

		if (token == NULL) {
			continue;
		}

		if (faults > 1) {
			continue;
		}

		bool safe = false;

		if (faults == 1) {
			for (int i = 0; i < tokenlen; i++) {
				int new = level_loop(&token, i);

				if (level_loop(&token, i)) {
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
