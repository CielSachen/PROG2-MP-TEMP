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
 * @file utils.h
 * @brief The header file for the utility macros, types, functions, and enums used throughout the
 * project.
 */

#ifndef CCPROG2_UTILS_H_
#define CCPROG2_UTILS_H_

/** @brief The accepted import and export file extension. */
#define FILE_EXTENSION ".txt"

/** @brief The ANSI code to reset the shell text formatting. */
#define SHELL_FORMATTING_DEFAULT "\033[0m"

/** @brief The ANSI code for a red shell text color. */
#define SHELL_TEXT_COLOR_RED "\033[0;31m"
/** @brief The ANSI code for a green shell text color. */
#define SHELL_TEXT_COLOR_GREEN "\033[0;32m"
/** @brief The ANSI code for a yellow shell text color. */
#define SHELL_TEXT_COLOR_YELLOW "\033[0;33m"
/** @brief The ANSI code for a blue shell text color. */
#define SHELL_TEXT_COLOR_BLUE "\033[0;34m"

/** @brief The ANSI code for a red shell background color. */
#define SHELL_BACKGROUND_COLOR_RED "\033[41m"
/** @brief The ANSI code for a green shell background color. */
#define SHELL_BACKGROUND_COLOR_GREEN "\033[42m"
/** @brief The ANSI code for a yellow shell background color. */
#define SHELL_BACKGROUND_COLOR_YELLOW "\033[43m"
/** @brief The ANSI code for a blue shell background color. */
#define SHELL_BACKGROUND_COLOR_BLUE "\033[44m"

/** @brief The maximum length of a file's name. */
#define MAXIMUM_FILENAME_LENGTH 31

/** @brief A string with a maximum length of 20 characters. */
typedef char String20[21];
/** @brief A string with a maximum length of 30 characters. */
typedef char String30[31];
/** @brief A string with a maximum length of 150 characters. */
typedef char String150[151];

/**
 * @brief Clears the input buffer
 * ([`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin))) by reading
 * every succeeding excess character.
 * @remarks Characters will be read until an escape character (`\n`) or the end of the file (`EOF`)
 * is reached.
 */
void clear_input_buffer();

/**
 * @brief Gets a character from the user through
 * ([`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin))).
 * @returns The inputted character.
 * @note This will flush output buffer
 * ([`stdout`](https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout))) before
 * getting the input and clear the input buffer
 * ([`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin))) after.
 */
char get_character_input();

/**
 * @brief Gets a string with a maximum length of 20 from the user through
 * ([`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin))).
 * @returns The inputted string.
 * @note This will flush output buffer
 * ([`stdout`](https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout))) before
 * getting the input and clear the input buffer
 * ([`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin))) after.
 */
void get_string_20_input(String20 string_input);

/**
 * @brief Gets a string with a maximum length of 30 from the user through
 * ([`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin))).
 * @returns The inputted string.
 * @note This will flush output buffer
 * ([`stdout`](https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout))) before
 * getting the input and clear the input buffer
 * ([`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin))) after.
 */
void get_string_30_input(String30 string_input);

/** @brief The warning situation IDs. */
enum WarningID {
    /** @brief The number of entries has reached the maximum. */
    MAXED_ENTRIES,
    /** @brief The number of translations in an entry has reached the maximum. */
    MAXED_TRANSLATIONS,
    /** @brief No entries contain a specific translation. */
    NO_ENTRIES_WITH_TRANSLATION,
    /** @brief No entries contain a specific word. */
    NO_ENTRIES_WITH_WORD,
};

/**
 * @brief Prints the warning message corresponding to the situation encountered.
 * @param situation_id The ID of the situation encountered.
 */
void print_warning_message(enum WarningID situation_id);

/** @brief The error status codes. */
enum ErrorCode {
    /** @brief The user gave an unknown ID input. */
    INVALID_ACTION_ID,
    /** @brief The file cannot be created or overwritten. */
    FILE_CREATION_FAILED,
    /** @brief The file cannot be opened and read. */
    FILE_READING_FAILED,
    /** @brief The entry list is empty. */
    NO_ENTRIES_PRESENT,
};

/**
 * @brief Prints the error message corresponding to the type of error encountered.
 * @param error_type The type of the error encountered.
 */
void print_error_message(enum ErrorCode error_type);

#endif  // CCPROG2_UTILS_H_
