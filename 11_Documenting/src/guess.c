/** @mainpage
*   # Programm for guessing number from 1 to 100.
*/
/** @page Programm for guessing number.
*   You should come up with a number from 1 to 100
*   This program will ask you if your number more or less then aome number.
*   You must answer yes or no.
*
*   Argument --help will show the helping message.
*   Argument -r will enable Roman number representation.
*
*/
#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

/** @file guess.c
* Implementation
*
* Guesses the number.
*/

/// Wrapper for gettext function
#define _(STRING) gettext(STRING)
/// Path to locale file
#define LOCALE_PATH "po"

const char* romans_numbers[100] = {
    "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX",
    "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL",
    "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX",
    "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX",
    "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"
};



/** Translate Arabic number @p num to the Roman number.
 * @param num Arabic number
 * @return Roman number
 */
const char* to_roman(int num) {
    return romans_numbers[num - 1];
}


/** Translate Roman number @p num to the Arabic number.
 * @param num Roman number
 * @return Arabic number
 */
int to_arabic(const char *num) {
    for (int i = 0; i < 100; ++i) {
        if (!strcmp(romans_numbers[i], num))
            return i + 1;
    }

    return -1;
}


int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    bindtextdomain("guess", LOCALE_PATH);
    textdomain("guess");

    int is_roman = 0;
    if (argc > 1) {
        if (!strcmp(argv[1], "--help")) {
            printf(_("Usage: ./guess [OPTIONS]\n"));
            printf(_("    OPTIONS:\n"));
            printf(_("        --help  print help message\n"));
            printf(_("        -r      use Roman numbers\n"));
            return 0;
        } else if (!strcmp(argv[1], "-r")) {
            is_roman = 1;
        } 
    }

    printf(_("Guess a number from 1 to 100.\n"));

    size_t left = 1, right = 100;
    char answer[16];

    while (left < right) {
        if (is_roman) {
            printf(_("Is your number greater than %s? (yes/no)\n"), to_roman((left + right) / 2));
        } else {
            printf(_("Is your number greater than %zu? (yes/no)\n"), (left + right) / 2);
        }

        if (scanf("%9s", answer) != 1) {
            continue;
        }

        if (strcmp(answer, _("yes")) == 0) {
            left = (left + right) / 2 + 1;
        } else if (strcmp(answer, _("no")) == 0) {
            right = (left + right) / 2;
        }
    }
    if (is_roman) {
        printf(_("Your number is %s\n"), to_roman(right));
    } else {
        printf(_("Your number is %zu\n"), right);
    }
    return 0;
}