#include "Font.h"
Font::Font(Game* game, SDL_Texture* sheet, int num_charsX, int num_charsY, int char_width, int char_height)
{
this->game = game;
this->sheet = sheet;
this->num_charsX = num_charsX;
this->num_charsY = num_charsY;
this->char_width = char_width;
this->char_height = char_height;
}
/* Next SRC and DST are used to render from the image*/
/* For X and Y, Well, for X, we simply cast character to int, and make a modula operation by number of characters on X axis of the sheet. For Y, we cast too, but divie by number of character on the X axis of the sheet.*/
/* We then multiply both values by character size depending on the x or y*/
void Font::RenderChar(float x, float y, unsigned char data)
{
SDL_Rect src_rect, dst_rect;
src_rect.x = (data % num_charsX) * char_width;
src_rect.y = (data / num_charsX) * char_height;
src_rect.w = char_width;
src_rect.h = char_height;
dst_rect.x = x;
dst_rect.y = y;
dst_rect.w = char_width;
dst_rect.h = char_height;
SDL_RenderCopy(game->getRenderer(), sheet, &src_rect, &dst_rect);
}
void Font::RenderString(float x, float y, std::string data)
{
for(int i=0; i<data.length(); i++)
{
RenderChar(x + i*char_width, y, data.at(i));
}
}