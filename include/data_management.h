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
 * @file data_management.h
 * @brief The header file for the macros, structs, and functions behind the Data Management
 * menu.
 */

#ifndef CCPROG2_DATA_MANAGEMENT_H_
#define CCPROG2_DATA_MANAGEMENT_H_

#include "stdbool.h"
#include "utils.h"

/** @brief The maximum number of entries. */
#define MAXIMUM_ENTRIES_LENGTH 150
/** @brief The maximum number of translations an entry can have. */
#define MAXIMUM_ENTRY_TRANSLATIONS 10

/** @brief A word translation. */
typedef struct Translation {
    /** @brief The language of the translation. */
    String20 language;
    /** @brief The translated word. */
    String20 word;
} Translation;
/** @brief A translation entry. */
typedef struct Entry {
    /** @brief The word translations. */
    Translation translations[MAXIMUM_ENTRY_TRANSLATIONS];
    /** @brief The actual length of `translations`. */
    int translations_amount;
} Entry;
/** @brief An array of entries with an integer member tracking the actual length. */
typedef struct EntryList {
    /** @brief The entries. */
    Entry values[MAXIMUM_ENTRIES_LENGTH];
    /** @brief The actual length of `values`. */
    int length;
} EntryList;

/**
 * @brief Adds an entry or multiple entries by asking the user to input their first translations.
 * @param[in,out] entries The entries to add to.
 */
void add_entry(EntryList *entries);

/**
 * @brief Adds a translation or multiple translations to an entry or multiple entries.
 * @param[in,out] entries The entries to add translations to.
 * @remarks The user will be asked to input a translation from the entry to add to.
 */
void add_translations(EntryList *entries);

/**
 * @brief Deletes an entry by moving it at the end of the list and decreasing the length.
 * @param[in,out] entries The entries to delete one of.
 */
void delete_entry(EntryList *entries);

/**
 * @brief Deletes translations from entries by moving them at the end of the lists and decreasing
 * their lengths. Entries with zero translations will be deleted.
 * @param entries The entries to delete translations from.
 */
void delete_translations(EntryList *entries);

/**
 * @brief Displays the entries by printing them entry-per-entry to `stdout`.
 * @param[in] entries The entries to display.
 */
void display_entries(EntryList *entries);

/**
 * @brief Searches for the entries containing a specific word and displays them.
 * @param[in] entries The entries to search through.
 */
void search_word(EntryList *entries);

/**
 * @brief Searches for the entries containing a specific translation and displays them.
 * @param[in] entries The entries to search through.
 */
void search_translation(EntryList *entries);

/**
 * @brief Exports the stored entries into a new or overwritten text file.
 * @param[in] entries The entries to export.
 * @remarks The user will be asked to input the name of the text file.
 */
void export_entries(EntryList *entries);

/**
 * @brief Imports the entries stored in a text file into the stored entries list.
 * @param[in] entries The entries to import into.
 * @param is_data_management Whether this function is called from the data management menu.
 * @remarks The user will be asked to input the name of the text file.
 */
void import_entries(EntryList *entries, bool is_data_management);

#endif  // CCPROG2_DATA_MANAGEMENT_H_
