/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"


int main()
{
    set_time(1633874297);  // Set RTC time to Wed, 28 Oct 2009 11:35:37

    while (true) {
        time_t seconds = time(NULL);
        printf("Time as a basic string = %s\r\n", ctime(&seconds));

        char buffer[32];
        strftime(buffer, 32, "%I:%M %p\r\n", localtime(&seconds));
        printf("Time as a custom formatted string = %s\r\n", buffer);
        wait(1);
    }
}
