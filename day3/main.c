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

	char valclone[100];
	strcpy(valclone, val);

	char *t = strtok(valclone, ",");
	int c = 0;
	while (t != NULL) {
		if (c == 2) {
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

		t = strtok(NULL, ",");

		c++;
	}
}

int part1(char *input) {
	int answer = 0;
	char sub[] = "mul";

	while ((input = strstr(input, sub)) != NULL) {

		// If mul is directly followed with "(", it could be a function
		if (input[3] == '(') {
			// Find the index for the ")"
			char *e;
			int index;
			e = strchr(input, ')');
			index = (int)(e - input);

			// Get the substring that is between the "(" and ")"
			int len = (index)-4;
			char *params = malloc(len + 1);
			strncpy(params, input + 4, len);
			params[len] = '\0';

			int values[2];
			parse_functions(params, values);

			if (values[0] != -1 && values[1] != -1) {
				answer += values[0] * values[1];
			}
		}

		input++;
	}

	return answer;
}

int part2(char *input) {
	int answer = 0;
	char *tok = strtok(input, "do");

	// 0 for do 1 for don't
	int type = 0;

	int c = 0;
	while (tok != NULL) {

		// Find the index for the ")"
		char *e;
		int index;
		e = strchr(tok, ')');
		index = (int)(e - tok);

		// Get the substring that is between the "do" and ")"
		int len = index;
		char *params = malloc(len + 1);
		strncpy(params, tok, len);
		params[len] = '\0';

		if (strcmp(params, "n't(") == 0) {
			type = 1;
		}

		if (strcmp(params, "(") == 0) {
			type = 0;
		}

		printf("type: %i\n\n\n", type);

		if (type == 0) {
			int values[2];
			parse_functions(params, values);

			// printf("%i - %i\n", values[0], values[1]);

			// if (values[0] != -1 && values[1] != -1) {
			// 	answer += values[0] * values[1];
			// }
		}

		tok = strtok(NULL, "do");
		c++;
	}

	// char sub[] = "mul";
	//
	// while ((input = strstr(input, sub)) != NULL) {
	//
	// 	// If mul is directly followed with "(", it could be a function
	// 	if (input[3] == '(') {
	// 		// Find the index for the ")"
	// 		char *e;
	// 		int index;
	// 		e = strchr(input, ')');
	// 		index = (int)(e - input);
	//
	// 		// Get the substring that is between the "(" and ")"
	// 		int len = (index)-4;
	// 		char *params = malloc(len + 1);
	// 		strncpy(params, input + 4, len);
	// 		params[len] = '\0';
	//
	// 		// Get the 2 parameter values
	// 		char *tok = strtok(params, ",");
	// 		int values[2];
	// 		int c = 0;
	// 		while (tok != NULL) {
	// 			if (c == 2) {
	// 				values[0] = -1;
	// 				values[1] = -1;
	// 				break;
	// 			}
	//
	// 			if (!isnumeric(tok)) {
	// 				values[c] = -1;
	// 			} else {
	// 				int param = atoi(tok);
	// 				values[c] = param;
	// 			}
	//
	// 			tok = strtok(NULL, ",");
	//
	// 			c++;
	// 		}
	//
	// 		if (values[0] != -1 && values[1] != -1) {
	// 			answer += values[0] * values[1];
	// 		}
	// 	}
	//
	// 	input++;
	// }

	return answer;
}

int main() {

	FILE *file;
	char *buffer;
	long file_size;

	file = fopen("small-input2.txt", "r");
	// file = fopen("small-input.txt", "r");
	// file = fopen("input.txt", "r");

	if (file == NULL) {
		printf("Error reading input\n");
	}

	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	rewind(file);

	buffer = (char *)malloc(file_size * sizeof(char));
	fread(buffer, 1, file_size, file);
	fclose(file);

	buffer[file_size] = '\0';

	if (buffer) {
		printf("Day 2 - Part 1: %i\n", part1(buffer));
		printf("Day 2 - Part 2: %i\n", part2(buffer));
	}

	free(buffer);

	return 0;
}
