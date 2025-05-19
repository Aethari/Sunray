/*
 * Game screen/page handling
 * See page.h for documentation
 * 2025 Aethari
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

char page_name[1000];

void page_set_name(char new_name[]) {
	char *log_path = log_get_path();

	char msg[1000];
	char buff[] = "[ C ] [Page] Changing page to \"%s\"\n";
	sprintf(msg, buff, new_name);

	log_pwrite(log_path, msg);
	free(log_path);

	strcpy(page_name, new_name);
}

char *page_get_name() {
	char *out = malloc(strlen(page_name) + 1);
	strcpy(out, page_name);
	return out;
}
