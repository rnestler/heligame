#include "game.h"

#include "backend.h"
#include "DIO.h"
#include "displayNeu.h"
#include "SoftTimer.h"

#define N_HIGHSCORE 10

typedef enum GameState {
	EStateMenu,
	EStateGame,
	EStateHighScore
}GameState;

typedef enum GameEvent {
	EEventEntry,
	EEventExit,
	EEventRun
}GameEvent;

struct Game {
	GameState state;
	Wall wall;
	Heli heli;
	Landscape landscape;

	unsigned menuitem;
	int scapeSize;
	Uint32 startTicks;
	Uint32 oldTime;
	Uint32 difficultyTimer;

	unsigned highscore[N_HIGHSCORE];
};

void change_state(Game *game, GameState new);

void game_state_menu(Game *game, GameEvent event)
{
	if(event == EEventEntry) {
		DisplayClrArea (0, 0, 160, 80);
		MIODispWriteText("> Start",1,1);
		MIODispWriteText("  Highscore",2,1);
		game->menuitem=1;
		return;
	} else if(event == EEventExit) {
		return;
	} else if(event == EEventRun) {
		static const unsigned nitem=2;
		static int old=0;
		switch(game->menuitem) {
			case 1:
				if(DIORead(USW0)) {
					change_state(game, EStateGame);
				}
				break;
			case 2:
				if(DIORead(USW0)) {
					change_state(game, EStateHighScore);
				}
				break;
			default:
				game->menuitem = 1;
		}
		int new = DIORead(USW1);
		if(new && old==0) {
			MIODispWriteText(" ",game->menuitem,1);
			game->menuitem = (game->menuitem%nitem)+1;
			MIODispWriteText(">",game->menuitem,1);
		}
		old = new;
	}
}

void game_state_game(Game *game, GameEvent event)
{
	if(event == EEventEntry) {
		rangeYHight = 1;
		DisplayClrArea (0, 0, 160, 80);
		initLandscape(&game->landscape, 70);
		heli_init(&game->heli);
		wall_init(&game->wall, 10, getYRoof(&game->landscape, 159), getYBottom(&game->landscape, 159) );

		game->scapeSize=70;
		game->startTicks = SDL_GetTicks();
		game->oldTime = game->startTicks;
		game->difficultyTimer = game->startTicks;
		return;
	} 
	if(event == EEventExit) {
		return;
	}
	if(event == EEventRun) {
		Uint32 time = SDL_GetTicks();
		Uint32 diffTime = time-game->oldTime;
		game->oldTime=time;
		char buf[10];
		//sprintf(buf, "%i", (diffTime));
		sprintf(buf, "%i", (time-game->startTicks)/100);
		MIODispWriteText(buf, 9, 0);

		if((time - game->difficultyTimer) >1000) {
			game->difficultyTimer = time;
			rangeYHight++;
			if(rangeYHight > 40 ) game->scapeSize = 40;
			game->scapeSize--;
			if(game->scapeSize < 10 ) game->scapeSize = 10;
		}

		heli_clear(&game->heli);
		if(DIORead(USW0)) {
			heli_update(&game->heli, 0.001, diffTime); // - means up
		}
		else {
			heli_update(&game->heli, -0.001, diffTime); // + means down
		}
		heli_draw(&game->heli);

		landscapeFlow(&game->landscape, game->scapeSize);

		wall_clear(&game->wall);
		wall_update(&game->wall, diffTime);
		if(game->wall.x <=0 ) {
			int length;
			int ymin, ymax;
			ymin = getYBottom(&game->landscape, 160);
			ymax = getYRoof(&game->landscape, 160);
			length = game->wall.y2-game->wall.y1+1;
			// it should at least be possible ;)
			if(length>(ymax-ymin-20) ) {
				length = ymax-ymin-20;
				if(length<1) length = 1;
			}
			wall_init(&game->wall, length, ymax, ymin );
		}
		wall_draw(&game->wall);
		if(heli_check_collision(&game->heli, game->wall.x, game->wall.y1, game->wall.x, game->wall.y2)) {
			change_state(game, EStateHighScore);
		}
		if(touch(&game->landscape, game->heli.x, game->heli.y+heliRadius)) {
			change_state(game, EStateHighScore);
		}
		if(touch(&game->landscape, game->heli.x, game->heli.y-heliRadius)) {
			change_state(game, EStateHighScore);
		}
	}
}

void game_state_highscore(Game *game, GameEvent event)
{
	if(event == EEventEntry) {
		Uint32 time = SDL_GetTicks();
		Uint32 score = time-game->startTicks;
		char buf[10];
		int found = 0;
		for(unsigned i=0; i<N_HIGHSCORE; ++i) {
			if(score > game->highscore[i] && found==0) {
				game->highscore[i] = score;
				found = 1;
				sprintf(buf, ">%i. %4i", i+1, score);
			}
			else {
				sprintf(buf, " %i. %4i", i+1, game->highscore[i]);
			}
			MIODispWriteText(buf, i, 0);
		}
	} else if(event == EEventExit) {
	}
	else if(event == EEventRun) {
		if(DIORead(USW0)) {
			change_state(game, EStateMenu);
		}
	}
}

void change_state(Game *game, GameState new)
{
	// call exit handler
	switch(game->state) {
		case EStateMenu:
			game_state_menu(game, EEventExit);
			break;
		case EStateGame:
			game_state_game(game, EEventExit);
			break;
		case EStateHighScore:
			game_state_highscore(game, EEventExit);
			break;
		default:
			// should never happen
			exit(-1);
	}
	game->state = new;
	// call entry handler
	switch(game->state) {
		case EStateMenu:
			game_state_menu(game, EEventEntry);
			break;
		case EStateGame:
			game_state_game(game, EEventEntry);
			break;
		case EStateHighScore:
			game_state_highscore(game, EEventEntry);
			break;
		default:
			// should never happen
			exit(-1);
	}
}

Game* game_init()
{
	Game* game = malloc(sizeof(Game));
	for(unsigned i=0; i< N_HIGHSCORE; ++i) {
		game->highscore[i] = 0;
	}
	game->state = EStateMenu;
	game_state_menu(game, EEventEntry);
	return game;
}

void game_run(Game *game)
{
	DelayMs(10);
	switch(game->state) {
		case EStateMenu:
			game_state_menu(game, EEventRun);
			break;
		case EStateGame:
			game_state_game(game, EEventRun);
			break;
		case EStateHighScore:
			game_state_highscore(game, EEventRun);
			break;
		default:
			exit(-1);
	}
}

