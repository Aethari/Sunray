#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <libgen.h>

#ifdef __unix__
	#include <unistd.h>
#elif _WIN32
	#define WIN32_LEAN_AND_MEAN
	#define NOMINMAX
	#include <windows.h>
#endif

char log_path[1000];

char *log_get_path() {
	char *out = malloc(strlen(log_path) + 1);
	strcpy(out, log_path);
	return out;
}

void log_clear(char path[]) {
	FILE *log_file = fopen(path, "w");
	fclose(log_file);
}

void log_write(char path[], char msg[]) {
	FILE *log_file = fopen(path, "a");
	fwrite(msg, strlen(msg), 1, log_file);
	fclose(log_file);
}

void log_pwrite(char path[], char msg[]) {
	printf(msg);
	log_write(path, msg);
}

void log_init() {
	// get the absolute path to the directory of the running exe
	char exe_path[1000];

	#ifdef __unix__
		ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path)-1);
		exe_path[len] = '\0';
	#elif _WIN32
		GetModuleFileNameA(NULL, exe_path, 1000);
	#endif
	strcpy(log_path, exe_path);
	strcpy(log_path, dirname(log_path));

	strcat(log_path, "/log.txt");

	time_t currentTime;
	time(&currentTime);

	char msg[1000];
	char buff[] = "[ C ] [Core] Log file successfully created at %s";
	sprintf(msg, buff, ctime(&currentTime));

	log_pwrite(log_path, msg);
}

