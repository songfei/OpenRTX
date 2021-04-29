#include "utf8.h"

size_t utf8_decode(char *buffer, uint32_t *chars, size_t size)
{
    int cnt = 0;

    while (*buffer != '\0') {

        // 4 bytes
        if ((*buffer & 0xf0) == 0xf0) {
            chars[cnt] = (*buffer & 0x7) << 18;
            buffer++;
            chars[cnt] |= (*buffer & 0x3f) << 12;
            buffer++;
            chars[cnt] |= (*buffer & 0x3f) << 6;
            buffer++;
            chars[cnt] |= *buffer & 0x3f;

        // 3 bytes
        } else if ((*buffer & 0xe0) == 0xe0) {
            chars[cnt] = (*buffer & 0xf) << 12;
            buffer++;
            chars[cnt] |= (*buffer & 0x3f) << 6;
            buffer++;
            chars[cnt] |= *buffer & 0x3f;

        // 2 bytes
        } else if ((*buffer & 0xc0) == 0xc0) {
            chars[cnt] = (*buffer & 0x1f) << 6;
            buffer++;
            chars[cnt] |= *buffer & 0x3f;

        // 1 byte
        } else if (*buffer <= 0x7f) {
            chars[cnt] = *buffer;

        }

        cnt++;  // advance to the next character
        buffer++;
        if(cnt > size) {
            break;
        }
    }

    return cnt;
}