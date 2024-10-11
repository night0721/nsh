#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define COLOR_RESET     "\033[0m"
#define COLOR_TEAL		"\033[38;2;148;226;213m"
#define COLOR_GREEN     "\033[38;2;166;227;161m"
#define COLOR_RED       "\033[38;2;243;139;168m"
#define COLOR_BLUE      "\033[38;2;137;180;250m"
#define COLOR_PEACH		"\033[38;2;250;179;135m"
#define COLOR_YELLOW    "\033[38;2;249;226;175m"
#define COLOR_OVERLAY0  "\033[38;2;108;112;134m"

#define MAX_LINE_LENGTH 1024

int main()
{
   char buffer[MAX_LINE_LENGTH];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
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
    return 0;
}

