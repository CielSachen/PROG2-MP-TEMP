/*
 * Copyright (C) 2025  CielSachen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file utils.c
 * @brief The source file for the utility functions used throughout the project.
 */

#include "utils.h"

#include <stdio.h>

/**
 * @brief Clears the input buffer
 * ([`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin))) by reading
 * every succeeding excess character.
 * @remarks Characters will be read until an escape character (`\n`) or the end of the file (`EOF`)
 * is reached.
 */
void clear_input_buffer() {
    char excess_character;

    while ((excess_character = getchar()) != '\n' && excess_character != EOF) {
    }
}

/**
 * @brief Gets a character from the user through
 * ([`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin))).
 * @returns The inputted character.
 * @note This will flush output buffer
 * ([`stdout`](https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout))) before
 * getting the input and clear the input buffer
 * ([`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin))) after.
 */
char get_character_input() {
    char character_input;

    fflush(stdout);

    scanf(" %c", &character_input);

    clear_input_buffer();

    return character_input;
}

/**
 * @brief Gets a string with a maximum length of 20 from the user through
 * ([`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin))).
 * @returns The inputted string.
 * @note This will flush output buffer
 * ([`stdout`](https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout))) before
 * getting the input and clear the input buffer
 * ([`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin))) after.
 */
void get_string_20_input(String20 string_input) {
    fflush(stdout);

    scanf(" %20s", string_input);

    clear_input_buffer();
}

/**
 * @brief Gets a string with a maximum length of 30 from the user through
 * ([`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin))).
 * @returns The inputted string.
 * @note This will flush output buffer
 * ([`stdout`](https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout))) before
 * getting the input and clear the input buffer
 * ([`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin))) after.
 */
void get_string_30_input(String30 string_input) {
    fflush(stdout);

    scanf(" %30s", string_input);

    clear_input_buffer();
}

/**
 * @brief Prints the warning message corresponding to the situation encountered.
 * @param situation_id The ID of the situation encountered.
 */
void print_warning_message(enum WarningID situation_id) {
    switch (situation_id) {
        case MAXED_ENTRIES:
            printf(SHELL_TEXT_COLOR_YELLOW
                   "You have reached the maximum number of entries." SHELL_FORMATTING_DEFAULT "\n");

            break;
        case MAXED_TRANSLATIONS:
            printf(SHELL_TEXT_COLOR_YELLOW
                   "You have reached the maximum number of translations." SHELL_FORMATTING_DEFAULT
                   "\n");

            break;
        case NO_ENTRIES_WITH_TRANSLATION:
            printf(
                SHELL_TEXT_COLOR_YELLOW
                "There's no entry containing the translation you provided." SHELL_FORMATTING_DEFAULT
                "\n");

            printf("\n");

            printf(
                SHELL_BACKGROUND_COLOR_GREEN
                "TIP:" SHELL_FORMATTING_DEFAULT " " SHELL_TEXT_COLOR_GREEN
                "Use the \"Add Entry\" action to add an entry containing the translation." SHELL_FORMATTING_DEFAULT
                "\n");

            break;
        case NO_ENTRIES_WITH_WORD:
            printf(SHELL_TEXT_COLOR_YELLOW
                   "There's no entry containing the word you provided." SHELL_FORMATTING_DEFAULT
                   "\n");

            printf("\n");

            printf(
                SHELL_BACKGROUND_COLOR_GREEN
                "TIP:" SHELL_FORMATTING_DEFAULT " " SHELL_TEXT_COLOR_GREEN
                "Use the \"Add Entry\" action to add an entry containing the word." SHELL_FORMATTING_DEFAULT
                "\n");

            break;
    }
}

/**
 * @brief Prints the error message corresponding to the type of error encountered.
 * @param error_type The type of the error encountered.
 */
void print_error_message(enum ErrorCode error_type) {
    printf(SHELL_BACKGROUND_COLOR_RED "ERROR:" SHELL_FORMATTING_DEFAULT " " SHELL_TEXT_COLOR_RED);

    switch (error_type) {
        case INVALID_ACTION_ID:
            printf("Unknown ID, please pick from the provided options.");

            break;
        case FILE_CREATION_FAILED:
            printf("The program could not create or overwrite the file.");

            break;
        case FILE_READING_FAILED:
            printf("The program could not open and read the file.");

            break;
        case NO_ENTRIES_PRESENT:
            printf("No entries are present at the moment.");

            break;
        default:
            printf("The program encountered an unknown error.");

            break;
    }

    printf(SHELL_FORMATTING_DEFAULT "\n");
}
