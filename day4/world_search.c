// AI answer... pretty clean
// #include <stdio.h>
// #include <string.h>
// 
// #define MAX_ROWS 145
// #define MAX_COLS 145
// #define WORD "XMAS"
// 
// int dx[] = {0, 0, -1, 1, -1, 1, -1, 1}; // Directions: horizontal, vertical, diagonal
// int dy[] = {1, -1, 0, 0, -1, -1, 1, 1}; // (right, left, up, down, diagonals)
// 
// int is_within_bounds(int x, int y, int rows, int cols) {
//     return x >= 0 && x < rows && y >= 0 && y < cols;
// }
// 
// int search_from_position(char grid[MAX_ROWS][MAX_COLS], int x, int y, int rows, int cols) {
//     int count = 0;
//     int len = strlen(WORD);
// 
//     for (int dir = 0; dir < 8; dir++) { // Check all 8 directions
//         int i, nx = x, ny = y;
// 
//         for (i = 0; i < len; i++) {
//             if (!is_within_bounds(nx, ny, rows, cols) || grid[nx][ny] != WORD[i]) {
//                 break;
//             }
//             nx += dx[dir];
//             ny += dy[dir];
//         }
// 
//         if (i == len) { // Word found
//             count++;
//         }
//     }
// 
//     return count;
// }
// 
// int count_occurrences(char grid[MAX_ROWS][MAX_COLS], int rows, int cols) {
//     int total_count = 0;
// 
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++) {
//             if (grid[i][j] == WORD[0]) {
//                 total_count += search_from_position(grid, i, j, rows, cols);
//             }
//         }
//     }
// 
//     return total_count;
// }
// 
// int main(int argc, char *argv[]) {
//     if (argc < 2) {
//         printf("Usage: %s <filename>\n", argv[0]);
//         return 1;
//     }
// 
//     FILE *file = fopen(argv[1], "r");
//     if (!file) {
//         perror("Error opening file");
//         return 1;
//     }
// 
//     char grid[MAX_ROWS][MAX_COLS];
//     int rows = 0, cols = 0;
// 
//     // Read the grid from the file
//     while (fgets(grid[rows], MAX_COLS, file)) {
//         // Remove the newline character
//         char *newline = strchr(grid[rows], '\n');
//         if (newline) {
//             *newline = '\0';
//         }
//         rows++;
//     }
//     fclose(file);
// 
//     cols = strlen(grid[0]); // Assume all rows have the same number of columns
// 
//     int total_occurrences = count_occurrences(grid, rows, cols);
//     printf("Total occurrences of '%s': %d\n", WORD, total_occurrences);
// 
//     return 0;
// }


#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ROWS 145
#define MAX_COLS 145

// Check if a pattern matches "MAS" or reversed "SAM"
bool is_mas_or_reverse(char a, char b, char c) {
    return (a == 'M' && b == 'A' && c == 'S') || (a == 'S' && b == 'A' && c == 'M');
}

// Count X-MAS patterns in the grid
int count_xmas_patterns(char grid[MAX_ROWS][MAX_COLS], int rows, int cols) {
    int count = 0;

    // Iterate over every possible center point of an X
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            // Check diagonals forming the "X"
            if (is_mas_or_reverse(grid[i - 1][j - 1], grid[i][j], grid[i + 1][j + 1]) &&
                is_mas_or_reverse(grid[i + 1][j - 1], grid[i][j], grid[i - 1][j + 1])) {
                count++;
            }
        }
    }

    return count;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char grid[MAX_ROWS][MAX_COLS];
    int rows = 0, cols = 0;

    // Read the grid from the file
    while (fgets(grid[rows], MAX_COLS, file)) {
        char *newline = strchr(grid[rows], '\n');
        if (newline) *newline = '\0'; // Remove newline character
        rows++;
    }
    fclose(file);

    cols = strlen(grid[0]); // Assume all rows have the same number of columns

    int total_patterns = count_xmas_patterns(grid, rows, cols);
    printf("Total X-MAS patterns: %d\n", total_patterns);

    return 0;
}

