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
 * @file data_management.c
 * @brief The source file for the functions behind the Data Management menu.
 */

#include "data_management.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Checks if a translation already has an entry containing it.
 * @param[in] translation The translation to check. If the language of the translation is empty, the
 * language will be ignored.
 * @param[in] entries The entries to check against.
 * @return The amount entries containing the translation.
 */
int has_entry(Translation *translation, EntryList *entries) {
    int entry_index;
    Entry *current_entry;
    bool has_entry = false;
    int translation_index = 0;
    Translation *current_translation;
    int entry_count = 0;

    for (entry_index = 0; entry_index < entries->length; entry_index++) {
        current_entry = &entries->values[entry_index];

        while (!has_entry && translation_index < current_entry->translations_amount) {
            current_translation = &current_entry->translations[translation_index];

            if (strlen(translation->language) == 0 &&
                strcmp(current_translation->word, translation->word) == 0) {
                entry_count++;
                has_entry = true;
            } else if (strlen(translation->language) > 0 &&
                       strcmp(current_translation->language, translation->language) == 0 &&
                       strcmp(current_translation->word, translation->word) == 0) {
                entry_count++;
                has_entry = true;
            } else {
                translation_index++;
            }
        }

        has_entry = false;
        translation_index = 0;
    }

    return entry_count;
}

/**
 * @brief Gets the index of the nth entry containing the translation.
 * @param[in] translation The translation to get the index of the entry of. If the language of the
 * translation is empty, the language will be ignored.
 * @param[in] entries The entries to get from.
 * @param nth The position in the sequence of indexes to get.
 * @return The index of the translation, or `-1` if it doesn't exist.
 */
int get_entry_index(Translation *translation, EntryList *entries, int nth) {
    bool has_nth_entry = false;
    int entry_index = 0;
    Entry *current_entry;
    bool has_entry = false;
    int translation_index = 0;
    Translation *current_translation;
    int entry_count = 0;

    while (!has_nth_entry && entry_index < entries->length) {
        current_entry = &entries->values[entry_index];

        while (!has_entry && translation_index < current_entry->translations_amount) {
            current_translation = &current_entry->translations[translation_index];

            if (strlen(translation->language) == 0 &&
                strcmp(current_translation->word, translation->word) == 0) {
                entry_count++;
                has_entry = true;
            } else if (strlen(translation->language) > 0 &&
                       strcmp(current_translation->language, translation->language) == 0 &&
                       strcmp(current_translation->word, translation->word) == 0) {
                entry_count++;
                has_entry = true;
            } else {
                translation_index++;
            }
        }

        if (has_entry && entry_count == nth) {
            has_nth_entry = true;
        } else {
            has_entry = false;
            translation_index = 0;
            entry_index++;
        }
    }

    if (has_nth_entry) {
        return entry_index;
    }

    return -1;
}

/**
 * @brief Gets the index of the English translation of the entry.
 * @param[in] entry The entry to find the English translation of.
 * @returns The index of the English translation, or `-1` if it doesn't exist.
 */
int get_english_translation_index(Entry *entry) {
    int index = 0;
    bool is_containing_english = false;

    while (!is_containing_english && index < entry->translations_amount) {
        if (strcmp(entry->translations[index].language, "English") == 0) {
            is_containing_english = true;
        } else {
            index++;
        }
    }

    if (!is_containing_english) {
        return -1;
    }

    return index;
}

/**
 * @brief Sorts the entries by alphabetical order based on their English translation.
 * @param[in,out] entries The entries to sort.
 */
void sort_entries(EntryList *entries) {
    int entry_index;
    int other_entry_index;
    Entry current_entry;
    int current_entry_english_index;
    Entry other_entry;
    int other_entry_english_index;
    Entry temporary;

    for (entry_index = 0; entry_index < entries->length - 1; entry_index++) {
        for (other_entry_index = entry_index + 1; other_entry_index < entries->length;
             other_entry_index++) {
            current_entry = entries->values[entry_index];
            current_entry_english_index = get_english_translation_index(&current_entry);
            other_entry = entries->values[other_entry_index];
            other_entry_english_index = get_english_translation_index(&other_entry);

            if ((current_entry_english_index >= 0 && other_entry_english_index >= 0 &&
                 strcmp(current_entry.translations[current_entry_english_index].word,
                        other_entry.translations[other_entry_english_index].word) > 0) ||
                (current_entry_english_index == -1 && other_entry_english_index >= 0)) {
                temporary = current_entry;
                entries->values[entry_index] = other_entry;
                entries->values[other_entry_index] = temporary;
            }
        }
    }
}

/**
 * @brief Sorts the translations of the entries by alphabetical order based on their language.
 * @param[in,out] entries The entries to sort the translations of.
 */
void sort_translations(EntryList *entries) {
    int entry_index;
    Entry *entry;
    int current_translation_index;
    int other_translation_index;
    Translation current_translation;
    Translation other_translation;
    Translation temporary;

    for (entry_index = 0; entry_index < entries->length; entry_index++) {
        entry = &entries->values[entry_index];

        if (entry->translations_amount > 1) {
            for (current_translation_index = 0;
                 current_translation_index < entry->translations_amount - 1;
                 current_translation_index++) {
                for (other_translation_index = current_translation_index + 1;
                     other_translation_index < entry->translations_amount;
                     other_translation_index++) {
                    current_translation = entry->translations[current_translation_index];
                    other_translation = entry->translations[other_translation_index];

                    if (strcmp(current_translation.language, other_translation.language) > 0) {
                        temporary = current_translation;
                        entry->translations[current_translation_index] = other_translation;
                        entry->translations[other_translation_index] = temporary;
                    }
                }
            }
        }
    }
}

/**
 * @brief Prints an entry to `stdout`.
 * @param[in] entry The entry to print.
 */
void print_entry(Entry *entry) {
    int index;

    printf(
        "|--------------------------------------------------|\n"
        "| ID |       Language       |     Translation      |\n"
        "|--------------------------------------------------|\n");

    for (index = 0; index < entry->translations_amount; index++) {
        printf("| %-2d | %-20s | %-20s |\n", index + 1, entry->translations[index].language,
               entry->translations[index].word);
    }

    printf("|--------------------------------------------------|\n");
}

/**
 * @brief Adds an entry or multiple entries by asking the user to input their first translations.
 * @param[in,out] entries The entries to add to.
 */
void add_entry(EntryList *entries) {
    Entry entry;
    entry.translations_amount = 1;
    char is_new;
    bool is_adding;
    char is_adding_more;
    bool is_exiting;

    if (entries->length < MAXIMUM_ENTRY_TRANSLATIONS) {
        do {
            printf(
                "Input the language of the first translation in the entry " SHELL_TEXT_COLOR_YELLOW
                "(maximum of 20 characters)" SHELL_FORMATTING_DEFAULT ": ");

            get_string_20_input(entry.translations[0].language);

            printf("Input the first translation in the entry " SHELL_TEXT_COLOR_YELLOW
                   "(maximum of 20 characters)" SHELL_FORMATTING_DEFAULT ": ");

            get_string_20_input(entry.translations[0].word);

            if (has_entry(&entry.translations[0], entries)) {
                printf("\n");

                print_entry(&entry);

                printf("\n");

                printf("Is this a new entry? " SHELL_TEXT_COLOR_YELLOW
                       "([y]es / [ANY] no)" SHELL_FORMATTING_DEFAULT ": ");

                is_new = tolower(get_character_input());

                if (is_new == 'y') {
                    is_adding = true;
                } else {
                    is_adding = false;
                }
            } else {
                is_adding = true;
            }

            if (is_adding) {
                entries->values[entries->length++] = entry;

                printf("\n");

                printf(SHELL_TEXT_COLOR_GREEN
                       "Added the entry into the stored list!" SHELL_FORMATTING_DEFAULT "\n");
            }

            printf("\n");

            if (entries->length < MAXIMUM_ENTRY_TRANSLATIONS) {
                printf("Add another entry? " SHELL_TEXT_COLOR_YELLOW
                       "([y]es / [ANY] no)" SHELL_FORMATTING_DEFAULT ": ");

                is_adding_more = tolower(get_character_input());

                if (is_adding_more == 'y') {
                    printf("\n");

                    is_exiting = false;
                } else {
                    is_exiting = true;
                }
            } else {
                print_warning_message(MAXED_ENTRIES);

                is_exiting = true;
            }

        } while (!is_exiting);

        sort_entries(entries);
    } else {
        print_warning_message(MAXED_ENTRIES);
    }
}

/**
 * @brief Adds a translation or multiple translations to an entry or multiple entries.
 * @param[in,out] entries The entries to add translations to.
 * @remarks The user will be asked to input a translation from the entry to add to.
 */
void add_translations(EntryList *entries) {
    bool is_different_entry = true;
    Translation translation;
    int entry_count;
    int entry_index = 1;
    int temporary_entry_id = 1;
    char chosen_action_id = 1;
    bool is_valid_action_id;
    bool has_picked_entry;
    Translation new_translation;
    Entry *entry;
    char is_adding_more;
    bool is_exiting;

    do {
        if (is_different_entry) {
            printf("Input the language of a translation in the entry " SHELL_TEXT_COLOR_YELLOW
                   "(maximum of 20 characters)" SHELL_FORMATTING_DEFAULT ": ");

            get_string_20_input(translation.language);

            printf("Input a translation in the entry " SHELL_TEXT_COLOR_YELLOW
                   "(maximum of 20 characters)" SHELL_FORMATTING_DEFAULT ": ");

            get_string_20_input(translation.word);

            printf("\n");
        }

        if ((entry_count = has_entry(&translation, entries))) {
            if (entry_count > 1) {
                do {
                    entry_index = get_entry_index(&translation, entries, temporary_entry_id);

                    print_entry(&entries->values[entry_index]);

                    do {
                        printf("\n");

                        if (temporary_entry_id > 1) {
                            printf(" [P] <-- Previous\n");
                        }

                        if (temporary_entry_id < entry_count) {
                            printf(" [N] --> Next\n");
                        }

                        printf(
                            " [%d] Add to This Entry\n"
                            "\n"
                            "> ",
                            temporary_entry_id);

                        chosen_action_id = toupper(get_character_input());

                        printf("\n");

                        if (chosen_action_id == 'P' && entry_index > 0) {
                            is_valid_action_id = true;
                            temporary_entry_id--;
                            has_picked_entry = false;
                        } else if (chosen_action_id == 'N' && entry_index < entries->length - 1) {
                            is_valid_action_id = true;
                            temporary_entry_id++;
                            has_picked_entry = false;
                        } else if (chosen_action_id == temporary_entry_id + 48) {
                            is_valid_action_id = true;
                            has_picked_entry = true;
                        } else {
                            is_valid_action_id = false;

                            print_error_message(INVALID_ACTION_ID);
                        }
                    } while (!is_valid_action_id);
                } while (!has_picked_entry);
            } else {
                entry_index = get_entry_index(&translation, entries, 1);
            }

            printf("Input the language of the new translation in the entry " SHELL_TEXT_COLOR_YELLOW
                   "(maximum of 20 characters)" SHELL_FORMATTING_DEFAULT ": ");

            get_string_20_input(new_translation.language);

            printf("Input the new translation in the entry " SHELL_TEXT_COLOR_YELLOW
                   "(maximum of 20 characters)" SHELL_FORMATTING_DEFAULT ": ");

            get_string_20_input(new_translation.word);

            entry = &entries->values[entry_index];

            strcpy(entry->translations[entry->translations_amount].language,
                   new_translation.language);
            strcpy(entry->translations[entry->translations_amount].word, new_translation.word);

            entry->translations_amount++;

            sort_translations(entries);

            printf("\n");

            printf(SHELL_TEXT_COLOR_GREEN
                   "Added the translation into the entry!" SHELL_FORMATTING_DEFAULT "\n");

            printf("\n");

            if (entry->translations_amount < MAXIMUM_ENTRY_TRANSLATIONS) {
                printf("Add another translation? " SHELL_TEXT_COLOR_YELLOW
                       "([y]es / [ANY] no)" SHELL_FORMATTING_DEFAULT ": ");

                is_adding_more = tolower(get_character_input());

                if (is_adding_more == 'y') {
                    printf("Add to the same entry? " SHELL_TEXT_COLOR_YELLOW
                           "([y]es / [ANY] no)" SHELL_FORMATTING_DEFAULT ": ");

                    // Reusing the variable because, because, because . . .
                    is_adding_more = tolower(get_character_input());

                    printf("\n");

                    if (is_adding_more == 'y') {
                        is_different_entry = false;
                    } else {
                        is_different_entry = true;
                    }

                    is_exiting = false;
                } else {
                    is_exiting = true;
                }
            } else {
                print_warning_message(MAXED_TRANSLATIONS);

                is_exiting = true;
            }
        } else {
            print_warning_message(NO_ENTRIES_WITH_TRANSLATION);

            is_exiting = true;
        }
    } while (!is_exiting);
}

/**
 * @brief Deletes an entry by moving it at the end of the list and decreasing the length.
 * @param entries[in,out] The entries to delete one of.
 */
void delete_entry(EntryList *entries) {
    int entry_index = 0;
    char chosen_action_id;
    bool is_valid_action_id;
    bool is_deleting = false;
    bool is_exiting;

    if (entries->length > 0) {
        do {
            print_entry(&entries->values[entry_index]);

            do {
                printf("\n");

                if (entry_index > 0) {
                    printf(" [P] <-- Previous\n");
                }

                if (entry_index < entries->length - 1) {
                    printf(" [N] --> Next\n");
                }

                printf(
                    " [%d] Delete This Entry\n"
                    "\n" SHELL_TEXT_COLOR_RED " [X] Exit\n" SHELL_FORMATTING_DEFAULT
                    "\n"
                    "> ",
                    entry_index + 1);

                chosen_action_id = toupper(get_character_input());

                printf("\n");

                if (chosen_action_id == 'P' && entry_index > 0) {
                    is_valid_action_id = true;
                    entry_index--;
                    is_exiting = false;
                } else if (chosen_action_id == 'N' && entry_index < entries->length - 1) {
                    is_valid_action_id = true;
                    entry_index++;
                    is_exiting = false;
                } else if (chosen_action_id - 49 == entry_index) {
                    is_valid_action_id = true;
                    is_deleting = true;
                    is_exiting = true;
                } else if (chosen_action_id == 'X') {
                    is_valid_action_id = true;
                    is_exiting = true;
                } else {
                    is_valid_action_id = false;

                    print_error_message(INVALID_ACTION_ID);
                }
            } while (!is_valid_action_id);
        } while (!is_exiting);

        if (is_deleting) {
            entries->values[entry_index] = entries->values[--entries->length];

            sort_entries(entries);

            printf(SHELL_TEXT_COLOR_RED
                   "Deleted the entry from the stored list!" SHELL_FORMATTING_DEFAULT "\n");
        }
    } else {
        print_error_message(NO_ENTRIES_PRESENT);
    }
}

/**
 * @brief Deletes translations from entries by moving them at the end of the lists and decreasing
 * their lengths. Entries with zero translations will be deleted.
 * @param entries The entries to delete translations from.
 */
void delete_translations(EntryList *entries) {
    int entry_index = 0;
    char chosen_action_id;
    bool is_valid_action_id;
    bool is_deleting = false;
    bool is_exiting;
    Entry *entry;
    int translation_index;

    if (entries->length > 0) {
        do {
            print_entry(&entries->values[entry_index]);

            do {
                printf("\n");

                if (entry_index > 0) {
                    printf(" [P] <-- Previous\n");
                }

                if (entry_index < entries->length - 1) {
                    printf(" [N] --> Next\n");
                }

                printf(
                    " [%d] Delete From This Entry\n"
                    "\n" SHELL_TEXT_COLOR_RED " [X] Exit\n" SHELL_FORMATTING_DEFAULT
                    "\n"
                    "> ",
                    entry_index + 1);

                chosen_action_id = toupper(get_character_input());

                printf("\n");

                if (chosen_action_id == 'P' && entry_index > 0) {
                    is_valid_action_id = true;
                    entry_index--;
                    is_exiting = false;
                } else if (chosen_action_id == 'N' && entry_index < entries->length - 1) {
                    is_valid_action_id = true;
                    entry_index++;
                    is_exiting = false;
                } else if (chosen_action_id == entry_index + 49) {
                    is_valid_action_id = true;
                    is_deleting = true;
                    is_exiting = true;
                } else if (chosen_action_id == 'X') {
                    is_valid_action_id = true;
                    is_exiting = true;
                } else {
                    is_valid_action_id = false;

                    print_error_message(INVALID_ACTION_ID);
                }
            } while (!is_valid_action_id);
        } while (!is_exiting);

        if (is_deleting) {
            entry = &entries->values[entry_index];

            do {
                print_entry(entry);

                do {
                    printf("\n");

                    for (translation_index = 0; translation_index < entry->translations_amount;
                         translation_index++) {
                        printf(" [%d] Delete This Translation\n", translation_index + 1);
                    }

                    printf("\n" SHELL_TEXT_COLOR_RED " [X] Exit\n" SHELL_FORMATTING_DEFAULT
                           "\n"
                           "> ");

                    chosen_action_id = toupper(get_character_input());

                    printf("\n");

                    if (chosen_action_id > 48 &&
                        chosen_action_id - 49 < entry->translations_amount) {
                        is_valid_action_id = true;
                        is_deleting = true;
                        translation_index = chosen_action_id - 49;
                        is_exiting = false;
                    } else if (chosen_action_id == 'X') {
                        is_valid_action_id = true;
                        is_deleting = false;
                        is_exiting = true;
                    } else {
                        is_valid_action_id = false;

                        print_error_message(INVALID_ACTION_ID);
                    }
                } while (!is_valid_action_id);

                if (is_deleting && entry->translations_amount > 1) {
                    entry->translations[translation_index] =
                        entry->translations[--entry->translations_amount];

                    sort_translations(entries);

                    printf(SHELL_TEXT_COLOR_RED
                           "Deleted the entry from the stored list!" SHELL_FORMATTING_DEFAULT "\n");

                    printf("\n");
                } else if (is_deleting) {
                    entries->values[entry_index] = entries->values[--entries->length];

                    sort_entries(entries);

                    printf(SHELL_TEXT_COLOR_RED
                           "Deleted the translation from the entry!" SHELL_FORMATTING_DEFAULT "\n");

                    is_exiting = true;
                }
            } while (!is_exiting);
        }
    } else {
        print_error_message(NO_ENTRIES_PRESENT);
    }
}

/**
 * @brief Displays the entries by printing them entry-per-entry to `stdout.
 * @param[in] entries The entries to display.
 */
void display_entries(EntryList *entries) {
    int entry_index = 0;
    char chosen_action_id;
    bool is_valid_action_id;
    bool is_exiting;

    if (entries->length > 0) {
        do {
            print_entry(&entries->values[entry_index]);

            do {
                printf("\n");

                if (entry_index > 0) {
                    printf(" [P] <-- Previous\n");
                }

                if (entry_index < entries->length - 1) {
                    printf(" [N] --> Next\n");
                }

                if (entry_index > 0 || entry_index < entries->length - 1) {
                    printf("\n");
                }

                printf(SHELL_TEXT_COLOR_RED " [X] Exit\n" SHELL_FORMATTING_DEFAULT
                                            "\n"
                                            "> ");

                chosen_action_id = toupper(get_character_input());

                printf("\n");

                if (chosen_action_id == 'P' && entry_index > 0) {
                    is_valid_action_id = true;
                    entry_index--;
                    is_exiting = false;
                } else if (chosen_action_id == 'N' && entry_index < entries->length - 1) {
                    is_valid_action_id = true;
                    entry_index++;
                    is_exiting = false;
                } else if (chosen_action_id == 'X') {
                    is_valid_action_id = true;
                    is_exiting = true;
                } else {
                    is_valid_action_id = false;

                    print_error_message(INVALID_ACTION_ID);
                }
            } while (!is_valid_action_id);
        } while (!is_exiting);
    } else {
        print_error_message(NO_ENTRIES_PRESENT);
    }
}

/**
 * @brief Searches for the entries containing a specific word and displays them.
 * @param[in] entries The entries to search through.
 */
void search_word(EntryList *entries) {
    Translation translation;
    int entry_count;
    int entry_index = 1;
    int temporary_entry_id = 1;
    char chosen_action_id = 1;
    bool is_valid_action_id;
    bool is_exiting;

    strcpy(translation.language, "");

    if (entries->length > 0) {
        printf("Input the word to search entries for " SHELL_TEXT_COLOR_YELLOW
               "(maximum of 20 characters)" SHELL_FORMATTING_DEFAULT ": ");

        get_string_20_input(translation.word);

        printf("\n");

        if ((entry_count = has_entry(&translation, entries))) {
            do {
                entry_index = get_entry_index(&translation, entries, temporary_entry_id);

                print_entry(&entries->values[entry_index]);

                do {
                    printf("\n");

                    if (temporary_entry_id > 1) {
                        printf(" [P] <-- Previous\n");
                    }

                    if (temporary_entry_id < entry_count) {
                        printf(" [N] --> Next\n");
                    }

                    printf(SHELL_TEXT_COLOR_RED " [X] Exit\n" SHELL_FORMATTING_DEFAULT
                                                "\n"
                                                "> ");

                    chosen_action_id = toupper(get_character_input());

                    printf("\n");

                    if (chosen_action_id == 'P' && entry_index > 0) {
                        is_valid_action_id = true;
                        temporary_entry_id--;
                        is_exiting = false;
                    } else if (chosen_action_id == 'N' && entry_index < entries->length - 1) {
                        is_valid_action_id = true;
                        temporary_entry_id++;
                        is_exiting = false;
                    } else if (chosen_action_id == 'X') {
                        is_valid_action_id = true;
                        is_exiting = true;
                    } else {
                        is_valid_action_id = false;

                        print_error_message(INVALID_ACTION_ID);
                    }
                } while (!is_valid_action_id);
            } while (!is_exiting);
        } else {
            print_warning_message(NO_ENTRIES_WITH_WORD);
        }
    } else {
        print_error_message(NO_ENTRIES_PRESENT);
    }
}

/**
 * @brief Searches for the entries containing a specific translation and displays them.
 * @param[in] entries The entries to search through.
 */
void search_translation(EntryList *entries) {
    Translation translation;
    int entry_count;
    int entry_index = 1;
    int temporary_entry_id = 1;
    char chosen_action_id = 1;
    bool is_valid_action_id;
    bool is_exiting;

    if (entries->length > 0) {
        printf(
            "Input the language of the translation to search entries for " SHELL_TEXT_COLOR_YELLOW
            "(maximum of 20 characters)" SHELL_FORMATTING_DEFAULT ": ");

        get_string_20_input(translation.language);

        printf("Input the translation to search entries for " SHELL_TEXT_COLOR_YELLOW
               "(maximum of 20 characters)" SHELL_FORMATTING_DEFAULT ": ");

        get_string_20_input(translation.word);

        printf("\n");

        if ((entry_count = has_entry(&translation, entries))) {
            do {
                entry_index = get_entry_index(&translation, entries, temporary_entry_id);

                print_entry(&entries->values[entry_index]);

                do {
                    printf("\n");

                    if (temporary_entry_id > 1) {
                        printf(" [P] <-- Previous\n");
                    }

                    if (temporary_entry_id < entry_count) {
                        printf(" [N] --> Next\n");
                    }

                    printf(SHELL_TEXT_COLOR_RED " [X] Exit\n" SHELL_FORMATTING_DEFAULT
                                                "\n"
                                                "> ");

                    chosen_action_id = toupper(get_character_input());

                    printf("\n");

                    if (chosen_action_id == 'P' && entry_index > 0) {
                        is_valid_action_id = true;
                        temporary_entry_id--;
                        is_exiting = false;
                    } else if (chosen_action_id == 'N' && entry_index < entries->length - 1) {
                        is_valid_action_id = true;
                        temporary_entry_id++;
                        is_exiting = false;
                    } else if (chosen_action_id == 'X') {
                        is_valid_action_id = true;
                        is_exiting = true;
                    } else {
                        is_valid_action_id = false;

                        print_error_message(INVALID_ACTION_ID);
                    }
                } while (!is_valid_action_id);
            } while (!is_exiting);
        } else {
            print_warning_message(NO_ENTRIES_WITH_TRANSLATION);
        }
    } else {
        print_error_message(NO_ENTRIES_PRESENT);
    }
}

/**
 * @brief Exports the stored entries into a new or overwritten text file.
 * @param[in] entries The entries to export.
 * @remarks The user will be asked to input the name of the text file.
 */
void export_entries(EntryList *entries) {
    String30 file_name;
    FILE *output_file;
    int entry_index;
    int index;
    Translation *translation;

    if (entries->length > 0) {
        printf("Input your preferred name for the output file " SHELL_TEXT_COLOR_YELLOW
               "(maximum of 30 characters)" SHELL_FORMATTING_DEFAULT ": ");

        get_string_30_input(file_name);

        output_file = fopen(strcat(file_name, FILE_EXTENSION), "w");

        if (output_file != NULL) {
            for (entry_index = 0; entry_index < entries->length; entry_index++) {
                for (index = 0; index < entries->values[entry_index].translations_amount; index++) {
                    translation = &entries->values[entry_index].translations[index];

                    fprintf(output_file, "%s: %s\n", translation->language, translation->word);
                }

                fprintf(output_file, "\n");
            }

            fclose(output_file);

            printf("\n");

            printf(SHELL_TEXT_COLOR_GREEN
                   "Exported the entries into the file `%s`!" SHELL_FORMATTING_DEFAULT "\n",
                   strcat(file_name, FILE_EXTENSION));
        } else {
            print_error_message(FILE_CREATION_FAILED);
        }
    } else {
        print_error_message(NO_ENTRIES_PRESENT);
    }
}

/**
 * @brief Imports the entries stored in a text file into the stored entries list.
 * @param[in] entries The entries to import into.
 * @param is_data_management Whether this function is called from the data management menu.
 * @remarks The user will be asked to input the name of the text file.
 */
void import_entries(EntryList *entries, bool is_data_management) {
    String30 file_name;
    FILE *input_file;
    Entry entry;
    bool is_finished;
    char input_buffer[43];
    Translation translation;
    bool is_originally_empty = entries->length == 0;
    char is_new;
    bool is_adding;

    printf("%s" SHELL_TEXT_COLOR_YELLOW "(maximum of 30 characters)" SHELL_FORMATTING_DEFAULT ": ",
           is_data_management ? "Input the name of the file containing entries "
                              : "Input the name of the file containing the translation data ");

    get_string_30_input(file_name);

    input_file = fopen(strcat(file_name, FILE_EXTENSION), "r");

    if (input_file != NULL) {
        do {
            entry.translations_amount = 0;

            while (!(is_finished = fgets(input_buffer, sizeof(input_buffer), input_file) == NULL) &&
                   strcmp(input_buffer, "\n") != 0) {
                sscanf(input_buffer, "%20s %20s", translation.language, translation.word);

                if (translation.language[strlen(translation.language) - 1] == ':') {
                    translation.language[strlen(translation.language) - 1] = '\0';
                }

                entry.translations[entry.translations_amount] = translation;
                entry.translations_amount++;
            }

            if (!is_finished) {
                if (!is_originally_empty) {
                    printf("\n");

                    print_entry(&entry);

                    printf("\n");

                    printf("Add this entry? " SHELL_TEXT_COLOR_YELLOW
                           "([y]es / [ANY] no)" SHELL_FORMATTING_DEFAULT ": ");

                    // Name doesn't match well, but implementing boolean input is not a priority.
                    is_new = tolower(get_character_input());

                    if (is_new == 'y') {
                        is_adding = true;
                    } else {
                        is_adding = false;
                    }
                } else {
                    is_adding = true;
                }

                if (is_adding) {
                    entries->values[entries->length++] = entry;

                    if (!is_originally_empty) {
                        printf("\n");

                        printf(SHELL_TEXT_COLOR_GREEN
                               "Added the entry into the stored list!" SHELL_FORMATTING_DEFAULT
                               "\n");
                    }
                }
            }
        } while (!is_finished);

        if (is_originally_empty) {
            printf("\n");

            printf(SHELL_TEXT_COLOR_GREEN
                   "Added the entries into the stored list!" SHELL_FORMATTING_DEFAULT "\n");
        }

        fclose(input_file);

        sort_entries(entries);
        sort_translations(entries);
    } else {
        print_error_message(FILE_READING_FAILED);
    }
}
