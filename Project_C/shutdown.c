#include <stdio.h>
#include <stdlib.h>
//#include <android/log.h>
//#include <utils/Log.h>
#include <ALog.h>
#include <sys/reboot.h>
#ifndef LOG_TAG
#define LOG_TAG "dxyh"
#endif
int main(int argc, char **argv)
{
    int retval;
    if ((retval = __reboot(LINUX_REBOOT_MAGIC1, LINUX_REBOOT_MAGIC2,
                    RB_POWER_OFF, NULL)) < 0) {
        LOGE("Try to shutdown the machine failed!");
        exit(EXIT_FAILURE);
    }
    return 0;
}