#include <stdio.h>
#include <stdlib.h>
#include "notifier.h"


void notify_alert(const char *title, const char *message) {

    char cmd[512];

    snprintf(cmd, sizeof(cmd),
             "notify-send -u critical -t 5000 \"%s\" \"%s\"",
             title, message);

    //silently ignore it so terminal output still works regardless.
    int ret = system(cmd);
    (void)ret;
}