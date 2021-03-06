#include "SFApp.h"
bool tr=true;
bool fa=false;
int north=1;
int west = 2;
int east = 3;
int south = 4;
int score = 0;
SFApp::SFApp(std::shared_ptr<SFWindow> window) : fire(0), is_running(true), sf_window(window) {


	int canvas_w, canvas_h;
	SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);

	app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);
	player  = make_shared<SFAsset>(SFASSET_PLAYER, sf_window);
	auto player_pos = Point2(100.0f, 88.0f);
	player->SetPosition(player_pos);

	const int number_of_walls = 3;
	for(int i=0; i<number_of_walls; i++) {
		// place an alien at width/number_of_walls * i
		auto wall = make_shared<SFAsset>(SFASSET_WALL, sf_window);
		auto pos   = Point2((canvas_w  /number_of_walls) * i, 150.0f);
		wall->SetPosition(pos);
		walls.push_back(wall);
	}

	const int number_of_aliens = 5;
	const int number_of_aliens2 = 4;
	const int number_of_aliens3 = 3;
	for(int i=0; i<number_of_aliens; i++) 
	{
		for(int i=0; i<number_of_aliens2; i++) 
		{
			for(int i=0; i<number_of_aliens3; i++) 
			{
				// place an alien at width/number_of_aliens * i
				auto alien = make_shared<SFAsset>(SFASSET_ALIEN,sf_window);
				auto pos   = Point2((canvas_w/number_of_aliens3) * i, 450.0f);
				alien->SetPosition(pos);
				aliens.push_back(alien);
			}
			auto alien = make_shared<SFAsset>(SFASSET_ALIEN,sf_window);
			auto pos   = Point2((canvas_w/number_of_aliens2) * i, 420.0f);
			alien->SetPosition(pos);
			aliens.push_back(alien);
		}
		auto alien = make_shared<SFAsset>(SFASSET_ALIEN,sf_window);
		auto pos   = Point2((canvas_w/number_of_aliens) * i, 390.0f);
		alien->SetPosition(pos);
		aliens.push_back(alien);
	}

	auto coin = make_shared<SFAsset>(SFASSET_COIN, sf_window);
	auto pos  = Point2((200), 100);
	coin->SetPosition(pos);
	coins.push_back(coin);



}


SFApp::~SFApp() {
}

/**
* Handle all events that come from SDL.
* These are timer or keyboard events.
*/


void SFApp::OnEvent(SFEvent& event) {
	SFEVENT the_event = event.GetCode();
	switch (the_event) {
	case SFEVENT_QUIT:
		is_running = false;
		break;
	case SFEVENT_UPDATE:
		OnUpdateWorld();
		OnRender();
		break;
	case SFEVENT_PLAYER_LEFT:
		player->GoWest();
		movement=west;
		break;
	case SFEVENT_PLAYER_RIGHT:
		player->GoEast();
		movement=east;
		break;
	case SFEVENT_PLAYER_UP:
		player->GoN();
		movement=north;
		break;
	case SFEVENT_PLAYER_DOWN:
		player->GoS();
		movement=south;
		break;
	case SFEVENT_FIRE:
		fire ++;
		FireProjectile();
		break;
	}
}

int SFApp::OnExecute() {
	// Execute the app
	SDL_Event event;
	while (SDL_WaitEvent(&event) && is_running) {
		// if this is an update event, then handle it in SFApp,
		// otherwise punt it to the SFEventDispacher.
		SFEvent sfevent((const SDL_Event) event);
		OnEvent(sfevent);
	}
	return 0;
}

void SFApp::OnUpdateWorld() {
	// Update projectile positions
	for(auto p: projectiles) {
		p->GoNorth();
	}

	for(auto c: coins) {
		c->GoNorth();
	}

	// Update enemy positions
	for(auto a : aliens) {
		a->Down();

	}




	// Update enemy positions
	for(auto b : walls) {
		if(b->CollidesWith(player)) {
			b->HandleCollision();
			player->HandleCollision();
			score -= 10;
			cout << "-10 score, dont hit walls Total score is "<< score <<endl;
		}
	}



	// Detect collisions
	for(auto p : projectiles) {
		for(auto a : aliens) {
			for(auto b : walls) {
				if(p->CollidesWith(a)) {
					p->HandleCollision();
					a->HandleCollision();
					score += 10;
					cout << "+10 score, well done.  Total score is "<< score <<endl;

				}
				if(p->CollidesWith(b)) {
					p->HandleCollision();
					b->HandleCollision();

				}
			}
		}
	}
	for(auto b : walls)  {
		if(b->CollidesWith(player))  {
			switch(movement){
			case 1:
				player->GoS();
				break;
			case 2:
				player->GoEast();
				break;
			case 3:
				player->GoWest();
				break;
			case 4:
				player->GoN();
				break;
			}
		}

	}

	// remove dead aliens (the long way)
	list<shared_ptr<SFAsset>> tmp;
	for(auto a : aliens) {
		if(a->IsAlive()) {
			tmp.push_back(a);
		}
	}
	aliens.clear();
	aliens = list<shared_ptr<SFAsset>>(tmp);


}

void SFApp::OnRender() {
	SDL_RenderClear(sf_window->getRenderer());

	// draw the player
	player->OnRender();

	for(auto p: projectiles) {
		if(p->IsAlive()) {p->OnRender();}
	}

	for(auto a: aliens) {
		if(a->IsAlive()) {a->OnRender();}
	}

	for(auto a: walls) {
		if(a->IsAlive()) {a->OnRender();}
	}

	for(auto c: coins) {
		c->OnRender();
	}



	// Switch the off-screen buffer to be on-screen
	SDL_RenderPresent(sf_window->getRenderer());
}

void SFApp::FireProjectile() {
	auto pb = make_shared<SFAsset>(SFASSET_PROJECTILE, sf_window);
	auto v  = player->GetPosition();
	pb->SetPosition(v);
	projectiles.push_back(pb);
}