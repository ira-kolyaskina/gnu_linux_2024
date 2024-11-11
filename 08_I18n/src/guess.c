#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "po"


int main() {
    setlocale(LC_ALL, "");
    bindtextdomain("guess", LOCALE_PATH);
    textdomain("guess");

    printf(_("Guess a number from 1 to 100.\n"));

    size_t left = 1, right = 100;
    char answer[10];

    while (left < right) {
        printf(_("Is your number greater than %zu? (yes/no)\n"), (left + right) / 2);

        if (scanf("%9s", answer) != 1) {
            continue;
        }

        if (strcmp(answer, _("yes")) == 0) {
            left = (left + right) / 2 + 1;
        } else if (strcmp(answer, _("no")) == 0) {
            right = (left + right) / 2;
        }
    }
    printf(_("Your number is %zu\n"), right);
    return 0;
}