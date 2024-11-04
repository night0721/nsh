#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define COLOR_RESET "\033[0m"
#define COLOR_BLUE "\033[38;2;137;180;250m"
#define COLOR_GREEN "\033[38;2;166;227;161m"
#define COLOR_ORANGE "\033[38;2;250;179;135m"
#define COLOR_OVERLAY0 "\033[38;2;108;112;134m"
#define COLOR_TEAL "\033[38;2;148;226;213m"
#define COLOR_MAUVE "\033[38;2;203;166;247m"
#define COLOR_YELLOW "\033[38;2;249;226;175m"
#define COLOR_SKY "\033[38;2;137;220;235m"
#define COLOR_RED "\033[38;2;243;139;168m"
#define COLOR_PEACH "\033[38;2;250;179;135m"
#define COLOR_PINK "\033[38;2;245;194;231m"

const char *keywords[] = {
	"if", "else", "while", "for", "return", "switch", "case", "default",
	"break", "continue", "const", "#define", "#include", NULL
};

const char *types[] = {
	"void", "int", "char", "float", "double", "long", "short", "unsigned",
	"signed", "struct", "enum", "union", NULL
};

/* Function declarations for different token handling */
void highlight_keyword(const char *word);
void highlight_type(const char *word);
void highlight_function(const char *word);
void highlight_string(const char *line, int *i);
void highlight_char(const char *line, int *i);
void highlight_single_comment(const char *line, int *i);
void highlight_multi_comment(const char *line, int *i);

/* Check if a word is a keyword */
int is_keyword(const char *word)
{
	for (int i = 0; keywords[i] != NULL; i++) {
		if (strcmp(word, keywords[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

/* Check if a word is a type */
int is_type(const char *word)
{
	for (int i = 0; types[i] != NULL; i++) {
		if (strcmp(word, types[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

/* Function to handle and highlight keywords */
void highlight_keyword(const char *word)
{
	printf(COLOR_MAUVE "%s" COLOR_RESET, word);
}

/* Function to handle and highlight types */
void highlight_type(const char *word)
{
	printf(COLOR_YELLOW "%s" COLOR_RESET, word);
}

/* Function to handle and highlight function names */
void highlight_function(const char *word)
{
	printf(COLOR_BLUE "%s" COLOR_RESET, word);
}

void highlight_symbol(const char *word)
{
	printf(COLOR_SKY "%s" COLOR_RESET, word);
}

void highlight_number(const char *word)
{
	printf(COLOR_ORANGE "%s" COLOR_RESET, word);
}

void highlight_normal(const char *word)
{
	int is_constant = 1;
	for (int i = 0; i < strlen(word); i++) {
		if (word[i] == '_') continue;
		if (word[i] > 'a' && word[i] < 'z') {
			is_constant = 0;
		}

	}
	if (is_constant) {
		printf(COLOR_ORANGE "%s" COLOR_RESET, word);
	} else {
		printf("%s", word);
	}
}

void highlight_brackets(const char *word)
{
	printf(COLOR_RED "%s" COLOR_RESET, word);
}

/* Function to handle and highlight single-line comments */
void highlight_single_comment(const char *line, int *i)
{
	printf(COLOR_OVERLAY0 "//");
	(*i) += 2;
	while (line[*i] != '\0') {
		printf("%c", line[*i]);
		(*i)++;
	}
	printf(COLOR_RESET);
}

/* Function to handle and highlight multi-line comments */
void highlight_multi_comment(const char *line, int *i)
{
	printf(COLOR_OVERLAY0 "/*");
	(*i) += 2;
	while (!(line[*i] == '*' && line[*i + 1] == '/') && line[*i] != '\0') {
		printf("%c", line[*i]);
		(*i)++;
	}
	if (line[*i] == '*' && line[*i + 1] == '/') {
		printf("*/" COLOR_RESET);
		(*i) += 2;
	}
}

/* Function to handle and highlight character literals */
void highlight_char(const char *line, int *i)
{
	printf(COLOR_TEAL "'");
	(*i)++;
	while (line[*i] != '\'' && line[*i] != '\0') {
		/* Handle escape sequence */
		if (line[*i] == '\\' && line[*i+1] > 32 && line[*i+1] < 127) {
			printf(COLOR_PINK "%c%c" COLOR_RESET, line[*i], line[*i + 1]);
			/* Check if escape sequence is octal */
			int cur_idx = (*i) + 2;
			while (line[cur_idx] > 47 && line[cur_idx] < 58) {
				printf(COLOR_PINK "%c" COLOR_RESET, line[cur_idx]);
				cur_idx++;
			}
			if (cur_idx == *i + 2) {
				/* Not octal escape code */
				(*i) += 2;
			} else {
				(*i) += cur_idx - *i;
			}
		} else {
			printf(COLOR_TEAL "%c", line[*i]);
			(*i)++;
		}
	}
	if (line[*i] == '\'') {
		printf("'" COLOR_RESET);
	}
}

/* Function to handle and highlight string literals */
void highlight_string(const char *line, int *i)
{
	printf(COLOR_GREEN "\"");
	(*i)++;
	while (line[*i] != '"' && line[*i] != '\0') {
		/* Handle escape sequence */
		if (line[*i] == '\\' && line[*i+1] > 32 && line[*i+1] < 127) {
			printf(COLOR_PINK "%c%c" COLOR_RESET, line[*i], line[*i + 1]);
			/* Check if escape sequence is octal */
			int cur_idx = (*i) + 2;
			while (line[cur_idx] > 47 && line[cur_idx] < 58) {
				printf(COLOR_PINK "%c" COLOR_RESET, line[cur_idx]);
				cur_idx++;
			}
			if (cur_idx == *i + 2) {
				/* Not octal escape code */
				(*i) += 2;
			} else {
				(*i) += cur_idx - *i;
			}
		} else {
			printf(COLOR_GREEN "%c", line[*i]);
			(*i)++;
		}
	}
	if (line[*i] == '"') {
		printf("\"" COLOR_RESET);
	}
}

/* Function to handle and highlight include strings */
void highlight_include(const char *line, int *i)
{
	printf(COLOR_GREEN "<");
	(*i)++;
	while (line[*i] != '>' && line[*i] != '\0') {
		printf(COLOR_GREEN "%c", line[*i]);
		(*i)++;
	}
	if (line[*i] == '>') {
		printf(">" COLOR_RESET);
	}
}

/* Main function to process input */
int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "nsh <file> <file2> ...\n");
		exit(1);
	}
	for (int i = 1; i < argc; i++) {
		FILE *f = fopen(argv[i], "r");
		if (!f) {
			fprintf(stderr, "Unable to open file: %s\n", argv[i]);
			exit(1);
		}
		/* Handle file without extension */
		char *ext = strrchr(argv[i], '.');
		if (ext != NULL) {
			/* How to identify file type if there isn't extension? */
			ext++;
		}
		char buffer[1024];
		char word[256];
		int word_len = 0;

		while (fgets(buffer, sizeof(buffer), f) != NULL) {
			if (ext && strcmp(ext, "c") == 0) {
				for (int i = 0; buffer[i] != '\0'; i++) {
					if (buffer[i] == '\t') {
						printf("    ");
						continue;
					}
					if (buffer[i] == '\'') {
						highlight_char(buffer, &i);
						continue;
					}
					if (buffer[i] == '"') {
						highlight_string(buffer, &i);
						continue;
					}
					if (buffer[i] == '<') {
						if ((buffer[i-1] != '\0' && buffer[i-1] == 'e') ||
								(buffer[i-1] != '\0' && buffer[i-1] == ' ' &&
								 buffer[i-2] != '\0' && buffer[i-2] == 'e')) {
							highlight_include(buffer, &i);
							continue;
						}
					}
					if (buffer[i] == '/' && buffer[i+1] == '/') {
						highlight_single_comment(buffer, &i);
						break;
					}
					if (buffer[i] == '/' && buffer[i+1] == '*') {
						highlight_multi_comment(buffer, &i);
					}
					if (isspace(buffer[i]) || (ispunct(buffer[i]) &&
								buffer[i] != '_' && buffer[i] != '#')) {
						if (word_len > 0) {
							word[word_len] = '\0';
							if (buffer[i] == '(' && !is_keyword(word) &&
									!is_type(word)) {
								highlight_function(word);
							} else if (is_type(word)) {
								highlight_type(word);
							} else if (is_keyword(word)) {
								highlight_keyword(word);
							} else {
								highlight_normal(word);
							}
							word_len = 0;
						}
						if (buffer[i] == '[' || buffer[i] == ']' ||
								buffer[i] == '(' || buffer[i] == ')' ||
								buffer[i] == '{' || buffer[i] == '}') {
							word[word_len++] = buffer[i];
							word[word_len] = '\0';
							highlight_brackets(word);
							word_len = 0;
							continue;
						}
						if (buffer[i] == '*' || buffer[i] == '&' ||
								buffer[i] == '=' || buffer[i] == '+' ||
								buffer[i] == '|' || buffer[i] == '!' ||
								buffer[i] == '<' || buffer[i] == '>') {
							word[word_len++] = buffer[i];
							word[word_len] = '\0';
							word_len = 0;
							highlight_symbol(word);
							continue;
						}
						printf("%c", buffer[i]);
					} else if (isdigit(buffer[i]) ) {
						word[word_len++] = buffer[i];
						if (isdigit(buffer[i+1]) == 0) {
							word[word_len] = '\0';
							highlight_number(word);
							word_len = 0;
						}
					} else {
						word[word_len++] = buffer[i];
					}
				}
			} else {
				/* Remove newline from buffer, if present */
				size_t len = strlen(buffer);
				if (len > 0 && buffer[len - 1] == '\n') {
					buffer[len - 1] = '\0';
				}

				if (strncmp(buffer, "---", 3) == 0) {
					printf(COLOR_YELLOW "%s" COLOR_RESET "\n", buffer);
				} else if (strncmp(buffer, "+++", 3) == 0) {
					printf(COLOR_PEACH "%s" COLOR_RESET "\n", buffer);
				} else if (strncmp(buffer, "@@", 2) == 0) {
					printf(COLOR_OVERLAY0 "%s" COLOR_RESET "\n", buffer);
				} else if (strncmp(buffer, "index", 5) == 0) {
					printf(COLOR_TEAL "%s" COLOR_RESET "\n", buffer);
				} else if (strncmp(buffer, "diff", 4) == 0) {
					printf(COLOR_BLUE "%s" COLOR_RESET "\n", buffer);
				} else if (buffer[0] == '+') {
					printf(COLOR_GREEN "%s" COLOR_RESET "\n", buffer);
				} else if (buffer[0] == '-') {
					printf(COLOR_RED "%s" COLOR_RESET "\n", buffer);
				} else {
					printf("%s\n", buffer);
				}
			}
		}
	}
	return 0;
}
