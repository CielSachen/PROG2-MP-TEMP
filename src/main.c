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
 * @file main.c
 * @brief The source file for the Simple Translator CLI application.
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "data_management.h"
#include "utils.h"

int main(void) {
    EntryList entries;
    entries.length = 0;
    bool is_exiting_program = false;
    char chosen_menu_id;
    char chosen_action_id;
    bool is_exiting_menu;

    printf("\n");

    printf(
        "Simple Translator  Copyright (C) 2025  Louis Raphael V. Panaligan\n"
        "This program comes with ABSOLUTELY NO WARRANTY.\n"
        "This is free software, and you are welcome to redistribute it under certain conditions.\n");

    printf("\n");

    while (!is_exiting_program) {
        printf(" __ _                 _        " SHELL_TEXT_COLOR_BLUE
               "_____                     _       _             " SHELL_FORMATTING_DEFAULT
               "\n"
               "/ _(_)_ __ ___  _ __ | | ___  " SHELL_TEXT_COLOR_BLUE
               "/__   \\_ __ __ _ _ __  ___| | __ _| |_ ___  _ __ " SHELL_FORMATTING_DEFAULT
               "\n"
               "\\ \\| | '_ ` _ \\| '_ \\| |/ _ \\   " SHELL_TEXT_COLOR_BLUE
               "/ /\\/ '__/ _` | '_ \\/ __| |/ _` | __/ _ \\| '__|" SHELL_FORMATTING_DEFAULT
               "\n"
               "_\\ \\ | | | | | | |_) | |  __/  " SHELL_TEXT_COLOR_BLUE
               "/ /  | | | (_| | | | \\__ \\ | (_| | || (_) | |   " SHELL_FORMATTING_DEFAULT
               "\n"
               "\\__/_|_| |_| |_| .__/|_|\\___|  " SHELL_TEXT_COLOR_BLUE
               "\\/   |_|  \\__,_|_| |_|___/_|\\__,_|\\__\\___/|_|   " SHELL_FORMATTING_DEFAULT
               "\n"
               "               |_|                                                             \n");

        printf("\n");

        printf(
            " [M] Manage Data\n"
            " [T] Translate\n"
            "\n" SHELL_TEXT_COLOR_RED " [X] Exit\n" SHELL_FORMATTING_DEFAULT
            "\n"
            "> ");

        chosen_menu_id = toupper(get_character_input());

        printf("\n");

        switch (chosen_menu_id) {
            case 'M':
                is_exiting_menu = false;

                while (!is_exiting_menu) {
                    printf(
                        "What would you like to do?\n"
                        " [1] Add Entry\n"
                        " [2] Add Translations\n"
                        " [3] Delete Entry\n"
                        " [4] Delete Translations\n"
                        " [5] Display All Entries\n"
                        " [6] Search Word\n"
                        " [7] Search Translations\n"
                        " [8] Export\n"
                        " [9] Import\n"
                        "\n" SHELL_TEXT_COLOR_RED " [X] Exit\n" SHELL_FORMATTING_DEFAULT
                        "\n"
                        "> ");

                    chosen_action_id = toupper(get_character_input());

                    printf("\n");

                    switch (chosen_action_id) {
                        case '1':
                            add_entry(&entries);

                            break;
                        case '2':
                            add_translations(&entries);

                            break;
                        case '3':
                            delete_entry(&entries);

                            break;
                        case '4':
                            delete_translations(&entries);

                            break;
                        case '5':
                            display_entries(&entries);

                            break;
                        case '6':
                            search_word(&entries);

                            break;
                        case '7':
                            search_translation(&entries);

                            break;
                        case '8':
                            export_entries(&entries);

                            break;
                        case '9':
                            import_entries(&entries, true);

                            break;
                        case 'X':
                            entries.length = 0;
                            is_exiting_menu = true;

                            break;
                        default:
                            print_error_message(INVALID_ACTION_ID);

                            break;
                    }

                    if (chosen_action_id != 'X') {
                        printf("\n");
                    }
                }

                break;
            case 'T':
                is_exiting_menu = false;

                import_entries(&entries, false);

                while (!is_exiting_menu) {
                }

                break;
            case 'X':
                is_exiting_program = true;

                break;
            default:
                print_error_message(INVALID_ACTION_ID);

                break;
        }
    }
}
