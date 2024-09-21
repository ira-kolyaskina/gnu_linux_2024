#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>

#define DX 3


void create_text(WINDOW *win, char ** text, size_t start, size_t end, int start_symbol, int symbols_count) {
    for(size_t i = start; i < end; ++i) {
        if (start_symbol > strlen(text[i])) {
            wprintw(win, " %3ld:\n", i + 1);
        } else {
            wprintw(win, " %3ld: %.*s\n", i + 1, symbols_count, &text[i][start_symbol]);
        }
    }
}


void create(const char* filename, char ** text, size_t text_size) {
    WINDOW *win;
    int c = 0;

    initscr();
    noecho();
    cbreak();
    printw("%s\n", filename);
    refresh();


    win = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
    keypad(win, TRUE);
    scrollok (win, TRUE);
    box(win, 0, 0); 
    wmove(win, 1, 0); 


    size_t start = 0;
    size_t end = LINES-2*DX-2;
    int start_symbol = 0;
    int symbols_count = COLS-2*DX-7;
    do {
        //chek bottom
        if (c == 258) { // down
            if (end < text_size) {
                start++;
                end++;
            }
        } else if (c == 259) { // up
            if (start > 0) {
                start--;
                end--;
            }
        } 
        else if (c == 260) { // left
            if (start_symbol > 0) {
                start_symbol--;
            }
        } else if (c == 261) { // right
                start_symbol++;
        }
        
        //drow text
        werase(win);
        wmove(win, 1, 0); 
        create_text(win, text, start, end, start_symbol, symbols_count);
        box(win, 0, 0); 
        wrefresh(win);

    } while ((c = wgetch(win)) != 27);

    endwin();
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "No arguments!\n");
        return 1;
    }
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "File can't open!\n");
        return 1;
    }

    char **text = NULL;
    size_t num_lines = 0;
    size_t read_size;
    size_t buffer_size = 1;
    text = (char**) realloc(text, (num_lines + 1) * sizeof(char *));
    text[num_lines] = NULL;
    while ((read_size = getline(&text[num_lines], &buffer_size, file)) != -1) {
        if (read_size > 0 && text[num_lines][read_size - 1] == '\n') {
            text[num_lines][read_size - 1] = '\0';
        }
        ++num_lines;
        text = (char**) realloc(text, (num_lines + 1) * sizeof(char *));
        text[num_lines] = NULL;
    }
    free(text[num_lines]);
    text[num_lines] = NULL;
    fclose(file);

    create(argv[1], text, num_lines);

    for (int index_line = 0; index_line < num_lines; ++index_line) {
        free(text[index_line]);
    }
    free(text);

    return 0;
} 