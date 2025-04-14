#ifndef LOG_H
#define LOG_H

/// Creates a log file at the exe's directory
/// Should only be called once, at the top of the 
/// main function
void log_init();

/// Writes a message to the log file
void log_write(char path[], char msg[]);

/// Writes a message to the log file and prints
void log_pwrite(char path[], char msg[]);

#endif
