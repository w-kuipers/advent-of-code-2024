#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isnumeric(const char *str) {
	for (int i = 0; str[i] != '\0'; i++) {
		if (!isdigit(str[i])) {
			return 0;
		}
	}
	return 1;
}

void parse_functions(char *val, int values[2]) {
	char *valclone = strdup(val);
	if (!valclone) {
		free(valclone);
		return;
	}

	char *tptr;
	char *t = strtok_r(valclone, ",", &tptr);
	int c = 0;
	while (t != NULL) {
		if (c > 1) {
			values[0] = -1;
			values[1] = -1;
			break;
		}

		if (!isnumeric(t)) {
			values[c] = -1;
		} else {
			int param = atoi(t);
			values[c] = param;
		}

		t = strtok_r(NULL, ",", &tptr);
		c++;
	}

	free(valclone);
}

int part1(char *input) {
	int answer = 0;
	char sub[] = "mul";

	while ((input = strstr(input, sub)) != NULL) {

		// If mul is directly followed with "(", it could be a function
		if (input[3] == '(') {
			// Find the index for the ")"
			char *e = strchr(input, ')');
			if (!e) {
				input++;
				continue;
			}
			int index = (int)(e - input);

			// Get the substring that is between the "(" and ")"
			int len = (index)-4;
			char *params = malloc(len + 1);
			if (!params) {
				input++;
				free(params);
				continue;
			}
			strncpy(params, input + 4, len);
			params[len] = '\0';

			int values[2];
			parse_functions(params, values);

			if (values[0] != -1 && values[1] != -1) {
				answer += values[0] * values[1];
			}

			free(params);
		}

		input++;
	}

	return answer;
}

int part2(char *input) {

	int answer = 0;
	char *tokptr;
	char *tok = strtok_r(input, "do", &tokptr);

	// 0 for do 1 for don't
	int type = 0;

	int c = 0;
	while (tok != NULL) {

		// Find the index for the ")"
		char *e = strchr(tok, ')');

		if (!e) {
			tok = strtok_r(NULL, "do", &tokptr);
			c++;
			continue;
		}

		int index = (int)(e - tok);

		// Get the substring that is between the "do" and ")"
		char *fntype = malloc(index + 1);
		if (!fntype) {
			tok = strtok_r(NULL, "do", &tokptr);
			free(fntype);
			c++;
			continue;
		}
		strncpy(fntype, tok, index);
		fntype[index] = '\0';

		if (c > 0) {
			if (strcmp(fntype, "n't(") == 0) {
				type = 1;
			}

			if (strcmp(fntype, "(") == 0) {
				type = 0;
			}
		}

		if (type == 0) {
			answer += part1(tok);
		}

		tok = strtok_r(NULL, "do", &tokptr);
		free(fntype);
		c++;
	}

	return answer;
}

int main() {

	FILE *file;
	char *buffer;
	long file_size;

	// file = fopen("small-input2.txt", "r");
	// file = fopen("small-input.txt", "r");
	file = fopen("input.txt", "r");

	if (file == NULL) {
		printf("Error reading input\n");
		return -1;
	}

	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	rewind(file);

	buffer = (char *)malloc(file_size * sizeof(char));
	fread(buffer, 1, file_size, file);
	fclose(file);

	buffer[file_size] = '\0';

	char *buffer_copy = strdup(buffer);
	if (!buffer_copy) {
		free(buffer);
		return -1;
	}

	if (buffer) {
		printf("Day 3 - Part 1: %i\n", part1(buffer));
		printf("Day 3 - Part 2: %i\n", part2(buffer_copy));
	}

	free(buffer);

	return 0;
}
