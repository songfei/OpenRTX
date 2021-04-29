
#ifndef UTF8_H
#define UTF8_H

#include <stdint.h>
#include <stddef.h>

size_t utf8_decode(char *buffer, uint32_t *chars, size_t size);

#endif