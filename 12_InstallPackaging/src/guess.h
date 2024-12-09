#pragma once

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

/** @file guess.c
* Implementation
*
* Guesses the number.
*/

/// Wrapper for gettext function
#define _(STRING) gettext(STRING)
/// Path to locale file
#define LOCALE_PATH "po"


static const char* romans_numbers[100] = {
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
const char* to_roman(int num);


/** Translate Roman number @p num to the Arabic number.
 * @param num Roman number
 * @return Arabic number
 */
int to_arabic(const char *num);

/** Start guessing
 * @param argc number of command line arguments.
 * @param argv pointer to array of program arguments.
 * @return 0 is without errors,  other code is error.
 */
int start(int argc, char **argv);