
#ifndef LOGGING_H
#define LOGGING_H

#if ENABLE_LOGGING
    #define LOG(fmt, ...) xil_printf("LOG: " fmt , ##__VA_ARGS__)
#else
    #define LOG(fmt, ...)
#endif

#endif /* LOGGING_H */