#ifndef FONT_H
#define FONT_H
#include "Game.h"
class Font
{
private:
Game* game;
SDL_Texture*sheet;
/*number of characters*/
int num_charsX;
int num_charsY;
/*size of characters*/
int char_width;
int char_height;
public:
Font(Game* game, SDL_Texture* sheet, int num_charsX, int num_charsY, int char_width, int char_height);
/* puts single character on screen at place defined, ASII value*/
void RenderChar(float x, float y, unsigned char data);
/* use above to render a string*/
void RenderString(float x, float y, std::string data);
};
#endif