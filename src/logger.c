#include <stdio.h>
#include <string.h>
#include <time.h>
#include "logger.h"

#define LOG_FILE "guardian.log"

/*
 * Appends a timestamped CPU and memory reading to the log file.
 * Uses strftime() for clean, consistent timestamp formatting,
 * avoiding the trailing newline bug in ctime().
 */
void log_data(double cpu, double mem) {

    FILE *fp = fopen(LOG_FILE, "a");
    if (!fp) return;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[32];

    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);

    fprintf(fp, "[%s] CPU: %.2f%% | MEM: %.2f%%\n", timestamp, cpu, mem);

    fclose(fp);
}