#ifndef INPUT_H
#define INPUT_H

int read_int(const char *prompt);
float read_float(const char *prompt);

void read_string(
    const char *prompt,
    char *buffer,
    int size
);

#endif