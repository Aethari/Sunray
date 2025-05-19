/*
 * Creation and writing of log files
 * 2025 Aethari
 */

#ifndef LOG_H
#define LOG_H

/// Creates a log file at the exe's directory
/// Should only be called once, at the top of the 
/// main function. Sets log_path (defined in log.c)
/// to the absolute path of the file created.
void log_init();

/// Gets the path to the current log file and returns a pointer to it
char *log_get_path();

/// Clears the log file, sparing no content
///
/// Parameters:
/// - path: A string representing a filepath to the log file
void log_clear(char path[]);

/// Writes a message to the log file
///
/// Parameters:
/// - path: A string representing a filepath to the log file
/// - msg: The message to be written to the log file
void log_write(char path[], char msg[]);

/// Writes a message to the log file and prints to the terminal
///
/// Parameters:
/// - path: A string representing a filepath to the log file
/// - msg: The message to be written to the log file and printed to the terminal
void log_pwrite(char path[], char msg[]);

#endif
