#ifndef SFAPP_H
#define SFAPP_H

#include <memory>   // Pull in std::shared_ptr
#include <iostream> // Pull in std::cerr, std::endl
#include <list>     // Pull in list
#include <sstream>
#include <SDL.h> 
#include <SDL_ttf.h> 

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFAsset.h"

/**
* Represents the StarshipFontana application.  It has responsibilities for
* * Creating and destroying the app window
* * Processing game events
*/


class SFApp {
public:
	SFApp(std::shared_ptr<SFWindow>);
	virtual ~SFApp();
	void    OnEvent(SFEvent &);
	int     OnExecute();
	void    OnUpdateWorld();
	void    OnRender();
	void    FireProjectile();

	int score;
	bool score_changed;
	SDL_Renderer* renderer;
	/* Fonts */
	std::string fonts[1];                   // font names
	SDL_Color dark_font;                    // dark font color
	SDL_Color light_font;                   // light font color
	SDL_Texture*    font_score;  // holds text indicating score
	 SDL_Texture*    font_winner;

private:
	SDL_Surface           * surface;
	bool                    is_running;
	shared_ptr<SFWindow>       sf_window;
	shared_ptr<SFAsset> player;
	shared_ptr<SFBoundingBox>  app_box;
	list<shared_ptr<SFAsset> > projectiles;
	list<shared_ptr<SFAsset> > aliens;
	list<shared_ptr<SFAsset> > coins;
	list<shared_ptr<SFAsset> > walls;

	int fire;
	int movement;


	SFError OnInit();
};
#endif
