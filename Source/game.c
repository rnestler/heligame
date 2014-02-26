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
	EEventRun,
	EEventKeyDown,
	EEventKeyUp
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

	int keyState[4];
	int keys[4];
	int currentKey;

	unsigned highscore[N_HIGHSCORE];
};

void change_state(Game *game, GameState new);

void game_state_menu(Game *game, GameEvent event)
{
	static const unsigned nitem=2;
	if(event == EEventEntry) {
		DisplayClrArea (0, 0, 160, 80);
		MIODispWriteText("> Start",1,1);
		MIODispWriteText("  Highscore",2,1);
		game->menuitem=1;
		return;
	} else if(event == EEventExit) {
		return;
	} else if(event == EEventKeyDown) {
		switch(game->currentKey) {
			case USW0:
				switch(game->menuitem) {
					case 1:
						change_state(game, EStateGame);
						break;
					case 2:
						change_state(game, EStateHighScore);
						break;
				}
				break;
			case USW1:
				MIODispWriteText(" ",game->menuitem,1);
				game->menuitem = (game->menuitem%nitem)+1;
				MIODispWriteText(">",game->menuitem,1);
				break;
		} 
	}
	else if(event == EEventRun) {
	}
}

void game_state_game(Game *game, GameEvent event)
{
	if(event == EEventEntry) {
		DPRINT("game entry\n");
		rangeYHight = 1;
		DisplayClrArea (0, 0, 160, 80);
		initLandscape(&game->landscape, 70);
		heli_init(&game->heli);
		wall_init(&game->wall, 10, getYRoof(&game->landscape, 159), getYBottom(&game->landscape, 159) );

		game->scapeSize=70;
		game->startTicks = SDL_GetTicks();
		game->oldTime = game->startTicks;
		game->difficultyTimer = game->startTicks;
	} else if(event == EEventExit) {
		Uint32 time = SDL_GetTicks();
		Uint32 score = (time-game->startTicks)/100;
		DPRINT("Score: %i\n", score);
		for(unsigned i=0; i<N_HIGHSCORE; ++i) {
			if(score > game->highscore[i]) {
				for(unsigned j=N_HIGHSCORE-1; j>i; --j) {
					game->highscore[j] = game->highscore[j-1];
				}
				game->highscore[i] = score;
				break;
			}
		}
	} else if(event == EEventRun) {
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
		char buf[10];
		for(unsigned i=0; i<N_HIGHSCORE; ++i) {
			sprintf(buf, "%2u. %4i", i+1, game->highscore[i]);
			MIODispWriteText(buf, i, 0);
		}
	} else if(event == EEventExit) {
	} else if(event == EEventKeyDown) {
		if(game->currentKey == USW0) {
			change_state(game, EStateMenu);
		}
	}
	else if(event == EEventRun) {
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
	for(unsigned i=0; i<4; ++i) {
		game->keyState[i] = 0;
	}
	game->keys[0] = USW0;
	game->keys[1] = USW1;
	game->keys[2] = USW2;
	game->keys[3] = USW3;
	game->menuitem = 0;
	game->scapeSize = 0;
	game->startTicks = 0;
	game->oldTime = 0;
	game->difficultyTimer = 0;
	
	game->state = EStateMenu;
	game_state_menu(game, EEventEntry);

	return game;
}

void game_run(Game *game)
{
	GameEvent event = EEventRun;
	
	DelayMs(10);

	// check for key events
	for(unsigned i=0; i<4; ++i) {
		int state = DIORead(game->keys[i]);
		if(state && game->keyState[i]==0) {
			event = EEventKeyDown;
			game->currentKey = game->keys[i];
			game->keyState[i] = state;
			break;
		} else if(state == 0 && game->keyState[i]) {
			event = EEventKeyUp;
			game->currentKey = game->keys[i];
			game->keyState[i] = state;
			break;
		}
	}

	switch(game->state) {
		case EStateMenu:
			game_state_menu(game, event);
			break;
		case EStateGame:
			game_state_game(game, event);
			break;
		case EStateHighScore:
			game_state_highscore(game, event);
			break;
		default:
			exit(-1);
	}
}

