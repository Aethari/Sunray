/*
 * Game screen/page handling
 * 2025 Aethari
 */

#ifndef PAGE_H
#define PAGE_H

/// Changes local string page_name to a given string.
///
/// Parameters:
/// - new_name: The string that page_name will be changed to
void page_set_name(char new_name[]);

/// Copies local string page_name to a dynamically
/// allocated string, then returns a pointer to it.
///
/// Returns:
/// A pointer to a dynamically allocated string representing
/// the current page's name.
char *page_get_name();

#endif
