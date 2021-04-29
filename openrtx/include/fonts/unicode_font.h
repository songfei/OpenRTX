
#include <stdint.h>

#define FONT_TYPE_NORMAL    1
#define FONT_TYPE_BLOCK     2

typedef struct {
    uint8_t magic[8];
    uint32_t fileSize;

    uint8_t majorVersion;
    uint8_t minorVersion;

    uint8_t fontType;
    uint8_t fontId;
    
    uint32_t firstCode;
    uint32_t lastCode;

    uint8_t fontSize;
    uint8_t bitPerPixel;

    uint8_t yAdvance;
}
__attribute__((packed)) FontCommonHeader;
 

// Normal Font Header (32byte)
typedef struct {
    FontCommonHeader common;

    uint8_t reserved[5];
}
__attribute__((packed)) NormalFontFileHeader;



typedef struct {
    uint8_t width;
    uint8_t height;
    int8_t xOffset;
    int8_t yOffset;
    uint8_t xAdvance;
} 
__attribute__((packed)) GlyphInfo;



typedef struct {
    GlyphInfo info;
    uint8_t bitmap[0];
} 
__attribute__((packed)) Glyph;


//  BlockFontFileHeader (36 byte)
typedef struct {
    FontCommonHeader common;
    GlyphInfo glyphInfo;

    uint8_t reserved[4];
}
__attribute__((packed)) BlockFontFileHeader;



struct Font{
    FontCommonHeader common;
    struct Font* next;
};

typedef struct Font Font;

typedef struct {
    Font font;

    uint32_t codeTableAddress;
    uint32_t baseAddress;
} NormalFont;

typedef struct {
    Font font;

    GlyphInfo glyphInfo;

    uint32_t baseAddress;
} BlockFont;