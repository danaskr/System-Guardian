#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#include "cpu.h"
#include "memory.h"
#include "logger.h"
#include "config.h"

// Flag set by signal handler to request a clean exit
static volatile int running = 1;

/*
 * Signal handler for SIGINT (Ctrl+C) and SIGTERM.
 * Sets the running flag to 0 so the main loop exits gracefully
 * instead of terminating mid-operation.
 */
void handle_exit(int sig) {
    (void)sig; // suppress unused parameter warning
    running = 0;
}

int main() {

    // Register signal handlers for clean shutdown
    signal(SIGINT,  handle_exit);
    signal(SIGTERM, handle_exit);

    printf("System Guardian started. Press Ctrl+C to stop.\n");
    printf("Thresholds — CPU: %.0f%% | Memory: %.0f%%\n\n",
           CPU_THRESHOLD, MEM_THRESHOLD);

    while (running) {
        // get_cpu_usage() internally sleeps MONITOR_INTERVAL seconds
        // between its two /proc/stat samples — no extra sleep needed here
        double cpu = get_cpu_usage();
        double mem = get_memory_usage();

        if (cpu < 0 || mem < 0) {
            fprintf(stderr, "Error reading system stats.\n");
            continue;
        }

        printf("CPU: %.2f%% | Memory: %.2f%%\n", cpu, mem);

        // Log every reading to file
        log_data(cpu, mem);

        // Check thresholds and alert
        if (cpu > CPU_THRESHOLD)
            printf("  ALERT: High CPU usage! (%.2f%% > %.0f%%)\n",
                   cpu, CPU_THRESHOLD);

        if (mem > MEM_THRESHOLD)
            printf("  ALERT: High Memory usage! (%.2f%% > %.0f%%)\n",
                   mem, MEM_THRESHOLD);
    }

    printf("\nSystem Guardian stopped. Log saved to guardian.log\n");
    return 0;
}