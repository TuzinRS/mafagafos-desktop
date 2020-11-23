#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "api/scene.h"

int G_CMD_THREAD;

SDL_Window* G_WINDOW;
int G_WINDOW_WIDTH;
int G_WINDOW_HEIGHT;
scene* G_SCENE = NULL;
bool G_APP_RUNNING = false;

void debug(const char *fmt, ...) {
	//
	//
	va_list ap;
    va_start(ap, fmt);
    const char *p = fmt;
   	
   	printf("\x1b[36m[D] ");
    while (*p != '\0') {
    	char ch = *p++;    // Get the next character of the format string

        if (ch != '%') {   // Not a format character? Just print it
            putchar(ch);
            continue;
        }
        char fmt = *p++;
        if (fmt == 'd' || 'i') {
            int n = va_arg(ap, int);
            printf("%d",n);
		}
        if (fmt == 'c') {
            char c = va_arg(ap, char);
            putchar(c);

        } else if (fmt == 's') {
            char *str = va_arg(ap, char *);
            printf(str);

        } else {
            // Unrecognized format character
        }
    }
    printf("\n\x1b[0m");
}

//glog because confliting types
void glog(const char *fmt, ...) {
	//
	//
	va_list ap;
    va_start(ap, fmt);
    const char *p = fmt;
   	
   	printf("[L] ");
    while (*p != '\0') {
    	char ch = *p++;    // Get the next character of the format string

        if (ch != '%') {   // Not a format character? Just print it
            putchar(ch);
            continue;
        }
        char fmt = *p++;
        if (fmt == 'd' || 'i') {
            int n = va_arg(ap, int);
            printf("%d",n);
		}
        if (fmt == 'c') {
            char c = va_arg(ap, char);
            putchar(c);

        } else if (fmt == 's') {
            char *str = va_arg(ap, char *);
            printf(str);

        } else {
            // Unrecognized format character
        }
    }
    printf("\n");
}

void warn(const char *fmt, ...) {
	//
	//
	va_list ap;
    va_start(ap, fmt);
    const char *p = fmt;
   	
   	printf("\x1b[33m[W] ");
    while (*p != '\0') {
    	char ch = *p++;    // Get the next character of the format string

        if (ch != '%') {   // Not a format character? Just print it
            putchar(ch);
            continue;
        }
        char fmt = *p++;
        if (fmt == 'd' || 'i') {
            int n = va_arg(ap, int);
            printf("%d",n);
		}
        if (fmt == 'c') {
            char c = va_arg(ap, char);
            putchar(c);

        } else if (fmt == 's') {
            char *str = va_arg(ap, char *);
            printf(str);

        } else {
            // Unrecognized format character
        }
    }
    printf("\n\x1b[0m");
}

void error(const char *fmt, ...) {
	//
	//
	va_list ap;
    va_start(ap, fmt);
    const char *p = fmt;
   	
   	printf("\x1b[31m[E] ");
    while (*p != '\0') {
    	char ch = *p++;    // Get the next character of the format string

        if (ch != '%') {   // Not a format character? Just print it
            putchar(ch);
            continue;
        }
        char fmt = *p++;
        if (fmt == 'd' || 'i') {
            int n = va_arg(ap, int);
            printf("%d",n);
		}
        if (fmt == 'c') {
            char c = va_arg(ap, char);
            putchar(c);

        } else if (fmt == 's') {
            char *str = va_arg(ap, char *);
            printf(str);

        } else {
            // Unrecognized format character
        }
    }
    printf("\n\x1b[0m");
}

void succ(const char *fmt, ...) {
	//
	//
	va_list ap;
    va_start(ap, fmt);
    const char *p = fmt;
   	
   	printf("\x1b[32m[S] ");
    while (*p != '\0') {
    	char ch = *p++;    // Get the next character of the format string

        if (ch != '%') {   // Not a format character? Just print it
            putchar(ch);
            continue;
        }
        char fmt = *p++;
        if (fmt == 'd' || 'i') {
            int n = va_arg(ap, int);
            printf("%d",n);
		}
        if (fmt == 'c') {
            char c = va_arg(ap, char);
            putchar(c);

        } else if (fmt == 's') {
            char *str = va_arg(ap, char *);
            printf(str);

        } else {
            // Unrecognized format character
        }
    }
    printf("\n\x1b[0m");
}

void info(const char *fmt, ...) {
	//
	//
	va_list ap;
    va_start(ap, fmt);
    const char *p = fmt;
   	
   	printf("\x1b[34m[I] ");
    while (*p != '\0') {
    	char ch = *p++;    // Get the next character of the format string

        if (ch != '%') {   // Not a format character? Just print it
            putchar(ch);
            continue;
        }
        char fmt = *p++;
        if (fmt == 'd' || 'i') {
            int n = va_arg(ap, int);
            printf("%d",n);
		}
        if (fmt == 'c') {
            char c = va_arg(ap, char);
            putchar(c);

        } else if (fmt == 's') {
            char *str = va_arg(ap, char *);
            printf(str);

        } else {
            // Unrecognized format character
        }
    }
    printf("\n\x1b[0m");
}
