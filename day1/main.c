#include "../utils/file.c"
#include "../utils/vector.c"
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int part1() {

	FILE *fptr;
	Vector left;
	Vector right;
	char content[100];
	int distance = 0;

	v_init(&left);
	v_init(&right);

	fptr = fopen("input.txt", "r");
	while (fgets(content, 100, fptr)) {
		char *token = strtok(content, " ");
		int c = 0;
		while (token != NULL) {
			int item = atoi(token);

			if (c == 0) {
				v_push(&left, item);
			}

			if (c == 1) {
				v_push(&right, item);
			}

			token = strtok(NULL, " ");
			c++;
		}
	}

	qsort(left.data, left.size, sizeof(int), compare);
	qsort(right.data, right.size, sizeof(int), compare);

	for (size_t i = 0; i < left.size; i++) {
		distance += abs(v_get(&left, i) - v_get(&right, i));
	}

	fclose(fptr);

	return distance;
}

int part2() {

	FILE *fptr;
	Vector left;
	Vector right;
	char content[100];
	int similarity = 0;

	v_init(&left);
	v_init(&right);

	fptr = fopen("input.txt", "r");
	while (fgets(content, 100, fptr)) {
		char *token = strtok(content, " ");
		int c = 0;
		while (token != NULL) {
			int item = atoi(token);

			if (c == 0) {
				v_push(&left, item);
			}

			if (c == 1) {
				v_push(&right, item);
			}

			token = strtok(NULL, " ");
			c++;
		}
	}

	for (size_t i = 0; i < left.size; i++) {
		int res = 0;
		int left_value = v_get(&left, i);

		for (size_t x = 0; x < right.size; x++) {
			if (v_get(&right, x) == left_value) {
				res++;
			}
		}

		similarity += (left_value * res);
	}

	return similarity;
}

int main() {

	printf("Day 1 - Part 1: %i\n", part1());
	printf("Day 1 - Part 2: %i\n", part2());

	return 0;
}
