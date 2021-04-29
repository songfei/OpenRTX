/***************************************************************************
 *   Copyright (C) 2020 by Federico Izzo IU2NUO, Niccolò Izzo IU2KIN and   *
 *                         Silvano Seva IU2KWO                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   As a special exception, if other files instantiate templates or use   *
 *   macros or inline functions from this file, or you compile this file   *
 *   and link it with other works to produce a work based on this file,    *
 *   this file does not by itself cause the resulting work to be covered   *
 *   by the GNU General Public License. However the source code for this   *
 *   file must still be made available in accordance with the GNU General  *
 *   Public License. This exception does not invalidate any other reasons  *
 *   why a work based on this file might be covered by the GNU General     *
 *   Public License.                                                       *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

/**
 * Testing module for SDL-based display driver, serves both to check that
 * everything is fine and as a simple example on how to use both the driver and
 * the SDL platform.
 *
 * To adjust screen dimensions you have to adjust the corresponding constants in
 * the driver source file.
 */

#include <interfaces/display.h>
#include <interfaces/graphics.h>
#include <interfaces/nvmem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#undef main     //necessary to avoid conflicts with SDL_main


void drawRect(int x, int y, int width, int height, uint16_t color)
{
    int x_max = x + width;
    int y_max = y + height;
    uint16_t *buf = (uint16_t *)(display_getFrameBuffer());

    for(int i=y; i < y_max; i++)
    {
        for(int j=x; j < x_max; j++)
        {
            buf[j + i * SCREEN_WIDTH] = color;
        }
    }
}

int main()
{
    nvm_init();
    gfx_init();
    //display_setBacklightLevel(254);

    // /* Horizontal red line */
    // drawRect(0, 10, SCREEN_WIDTH, 20, 0xF800);

    // /* Vertical blue line */
    // drawRect(10, 0, 20, SCREEN_HEIGHT, 0x001F);

    // /* Vertical green line */
    // drawRect(80, 0, 20, SCREEN_HEIGHT, 0x07e0);

    point_t center = {10, 10};
    point_t center2 = {10, 30};
    point_t center3 = {10, 50};
    point_t center4 = {10,70};
    point_t center5 = {10, 90};
    point_t center6 = {10, 110};
    color_t red =    {0, 0,   0  , 255};

    //gfx_drawCircle(center, 30, red);

    // gfx_print(center, FONT_SIZE_9PT, TEXT_ALIGN_LEFT, red, "hellow, world!");

    gfx_drawUTF8Text(center, 1, red, "红稣手黄藤酒");
    gfx_drawUTF8Text(center2, 1, red, "满城春色宫墙柳");
    gfx_drawUTF8Text(center3, 1, red, "东风恶欢情薄");
    gfx_drawUTF8Text(center4, 1, red, "一怀愁绪");
    gfx_drawUTF8Text(center5, 1, red, "几年离索");
    gfx_drawUTF8Text(center6, 1, red, "错错错");



    /*
     * Use SDL event listener to check if window close button has been pressed,
     * in this case quit.
     */
    SDL_Event eventListener;

    while(1)
    {
        display_render();
        SDL_PollEvent(&eventListener);
        if(eventListener.type == SDL_QUIT) break;
    }
    
    display_terminate();
    return 0;
}
