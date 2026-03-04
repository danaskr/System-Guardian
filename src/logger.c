#include <stdio.h>
#include <time.h>

void log_data(double cpu, double mem) {

    FILE *fp = fopen("guardian.log", "a");
    if (!fp) return;

    time_t now = time(NULL);

    fprintf(fp, "%sCPU: %.2f%% | MEM: %.2f%%\n",
            ctime(&now), cpu, mem);

    fclose(fp);
}