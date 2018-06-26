/*	Copyright (C) 2012  Claude Richard
 *
 *	Optimist Racing is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Optimist Racing is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Optimist Racing.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * This is the main program.
 * It has a loop that deals with the event queue, and updates and renders the game.
 * Right now there are a lot of hardcoded things in here,
 * which should be moved to different objects as the objects are developed,
 * e.g. applying forces based on keyboard input.
 */

// NOTE: I am currently making the switch from Glut to Allegro for the main loop and input handling.

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include "Lagrange.hpp"
#include "Bezier.hpp"
#include "Audio.hpp"
#include "Globals.hpp"
#include "Primitive.hpp"
#include "InputTracker.hpp"
#include "Material.hpp"
#include "Grid.hpp"
#include "ElectricColour.hpp"
#include "Camera.hpp"
#include "World.hpp"
#include "Data.hpp"
#include "StoryMenu.hpp"
#include "DataTracker.hpp"
#include "LuaGame.hpp"
#include <iostream>
//#include <FTGL/ftgl.h>

/// Frames per second
#define G_FPS 60
/// The number of milliseconds for each frame; frames-per-second = 1000 / this.
#define MILLISECONDS_PER_FRAME 16
/// The height of the game window
#define WINDOW_HEIGHT 400
/// The width of the game window
#define WINDOW_WIDTH 400
/// At every (this) milliseconds, the value of FPS stored in current_fps is updated.
#define MILLISECONDS_PER_FPS_UPDATE 300
/// screen color (black)
#define G_SCREEN_COLOR al_map_rgb(0,0,0)

enum E_BUTTONS {
	BUTTON_DOWN = 0,
	BUTTON_UP,
	BUTTON_SKID_LEFT,
	BUTTON_SKID_RIGHT,
	BUTTON_NUM
};


//FTGLPixmapFont* font;
//GameFlow* game = new GameFlow();
//double counter = 0;

/// keyboard input
GameButtonInputTracker* ki;

/// The physics world, which also handles rendering.
World* gWorld;

/// Used for timing the main loop. Todo: some better algorithm.
int framecount;
/// Used for timing the main loop. Todo: some better algorithm.
int lastupdatemill;
/// Used for timing the main loop. Todo: some better algorithm.
int lastframemill;
/// The value of frames-per-second that was last computed. Todo: some better algorithm.
double current_fps;

/// The data tracker (tracks which universe, world, and level you're at, and stores info on them)
DataTracker* dataTracker;
/// Should we exit the game?
bool g_done;
/// a font for displaying simple instructions
ALLEGRO_FONT* font;

// mouse
MouseInputTracker* mouse;
// story menu
StoryMenu* storymenu;
// in the story menu?
bool instorymenu;


/// This function gets called at each frame.
void main_step_and_render( int i )
{
	// Render the world
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	glClear( GL_COLOR_BUFFER_BIT );
	glClear( GL_DEPTH_BUFFER_BIT );

	if (instorymenu) {
		int ret = storymenu->step( 1.0/G_FPS );
		storymenu->glRender();
		if (ret>=0) {
			WorldData* wor = dataTracker->loadWorld( ret+1 );
			LevelData* lev = dataTracker->loadLevel( 1 );
			gWorld = new World( dataTracker->getUniverse(), wor, lev );
			instorymenu = false;
		}
	} else {

		// Set the force
		if (ki->isButtonPressed( BUTTON_SKID_LEFT )) {
			gWorld->setForceRight( -1 );
		} else if (ki->isButtonPressed( BUTTON_SKID_RIGHT )) {
			gWorld->setForceRight( 1 );
		} else {
			gWorld->setForceRight( 0 );
		}
		if (ki->isButtonPressed( BUTTON_UP )) {
			gWorld->setForceUp( 1 );
		} else if (ki->isButtonPressed( BUTTON_DOWN )) {
			gWorld->setForceUp( -1 );
		} else {
			gWorld->setForceUp( 0 );
		}

		// Timestep in the world
		int numsteps = 10;
		double seconds = 1.0 / G_FPS / numsteps;
		for (int i=0; i<numsteps; i++) {
			gWorld->step( seconds );
		}
		if (gWorld->getFinished()) {
			delete gWorld;
			if (dataTracker->isLastLevelInUniverse()) {
				//glutLeaveMainLoop();
				g_done = true;
				return;
			}
			LevelData* lev = dataTracker->loadNextLevel();
			gWorld = new World( dataTracker->getUniverse(), dataTracker->getWorld(), lev );
		}
	
		//int beforerender = glutGet( GLUT_ELAPSED_TIME );
		for (int i=0; i<1; i++) {
			gWorld->glRender();
		}
		//int afterrender = glutGet( GLUT_ELAPSED_TIME );
		//int rendermill = afterrender - beforerender;
	

		//// Set the font size and render a small text.
		//font->FaceSize(72);
		//font->Render("Hello world!");
	
	}


	glFlush();
	
	//al_draw_text( font, al_map_rgb(1,0.5,1), 10, 10, 0, "use arrows to apply a force to the bottom sphere");
	//al_draw_text( font, al_map_rgb(1,0.5,1), 10, 30, 0, "caution: right and left arrows also apply a torque!");

	framecount ++;
	int mill = glutGet( GLUT_ELAPSED_TIME );
	if ( mill - lastupdatemill >= MILLISECONDS_PER_FPS_UPDATE ) {
		current_fps = framecount*1000.0 / MILLISECONDS_PER_FPS_UPDATE;
		//std::cerr << current_fps << std::endl;
		framecount = 0;
		lastupdatemill = mill;
	}
	

	// Wait for the next frame
	int milltonext = std::max(MILLISECONDS_PER_FRAME - (mill - lastframemill), 1 );
	lastframemill = mill;
	//glutTimerFunc( milltonext, main_step_and_render, 1 );

}


/**
 * \brief		The main function of the program.
 * \details		This function opens up a window and starts running the game until you x out of it.
 * \param		argc	The number of arguments from the command line.
 * \param		argv	The array of string argument from the command line, argv[0] = executablename.
 * \return		0 if it runs and finishes well, something else otherwise.
 * \throw		An error whenever something goes wrong.
 */
//int main_glut( int argc, char** argv ) {
//
//	// Initialize Allegro 5
//	//	al_init();
//	//	// TODO: adjust the number of samples
//	//	al_install_audio();
//	//	al_init_acodec_addon();
//	//	al_reserve_samples(1);
//
//	// Initialize GLUT
//	glutInit( &argc, argv );
//
//	// Initialize the GLUT window
//	glutInitDisplayMode( GLUT_SINGLE );
//	glutInitWindowSize( WINDOW_HEIGHT, WINDOW_WIDTH );
//	glutInitWindowPosition( 100, 100 );
//	glutCreateWindow( "Optimist Racing" );
//
//	// Add a timer event to the main loop
//	glutTimerFunc( MILLISECONDS_PER_FRAME, main_step_and_render, 1 );
//
//	// Add keyboard events to the main loop
//	glutKeyboardFunc( main_key_down );
//	glutSpecialFunc(main_special_key_down);
//	glutKeyboardUpFunc(main_key_up); 
//	glutSpecialUpFunc(main_special_key_up);
//	glutIgnoreKeyRepeat(true);
//
//	// set up the game
//	dataTracker = new DataTracker( "universe" );
//	dataTracker->loadWorld(1);
//	dataTracker->loadLevel(3);
//	gWorld = new World( dataTracker->getUniverse(), dataTracker->getWorld(), dataTracker->getLevel() );
//
//	// set up the frame
//	int mill = glutGet( GLUT_ELAPSED_TIME );
//	framecount = 0;
//	lastupdatemill = mill;
//	lastframemill = mill;
//	current_fps = 60;
//
//	/// Todo: test out fonts somewhere else.
//	//// Create a pixmap font from a TrueType file.
//	//font = new FTGLPixmapFont("fonts/Arial.ttf");
//	//// If something went wrong, bail out.
//	//if(font->Error()) return -1;
//
//	// Start running the GLUT main loop
//	glutMainLoop();
//
//	// Shutdown Allegro 5
//	//	// TODO: do the following 2 lines maybe.
//	//	//al_getridof_samples();
//	//	//al_shutdown_acodec_addon();
//	//	al_uninstall_audio();
//	//	al_uninstall_system();
//
//	// Return 0 to indicate that everything ended properly.
//	return 0;
//
//}

int main_allegro( int argc, char** argv ) {

	ki = new GameButtonInputTracker( ALLEGRO_KEY_MAX, BUTTON_NUM );
	ki->setMap( BUTTON_UP, ALLEGRO_KEY_UP );
	ki->setMap( BUTTON_DOWN, ALLEGRO_KEY_DOWN );
	ki->setMap( BUTTON_SKID_RIGHT, ALLEGRO_KEY_RIGHT );
	ki->setMap( BUTTON_SKID_LEFT, ALLEGRO_KEY_LEFT );

	mouse = new MouseInputTracker( 3 );
	instorymenu = true;

	// Initialize Allegro 5
	ALLEGRO_DISPLAY * display;
	if(!al_init()){  
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();

	font = al_load_font( "fonts/arial.ttf", 10, 0 );

	al_set_new_display_flags(ALLEGRO_OPENGL);
	al_set_new_display_option( ALLEGRO_DEPTH_SIZE, 16, ALLEGRO_REQUIRE );
	display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT); 
	if(!display){ 
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	//	// TODO: adjust the number of samples
	//	al_install_audio();
	//	al_init_acodec_addon();
	//	al_reserve_samples(1);

	// set up the game
	dataTracker = new DataTracker( "universe" );
	dataTracker->loadWorld(1);
	dataTracker->loadLevel(1);
	//gWorld = new World( dataTracker->getUniverse(), dataTracker->getWorld(), dataTracker->getLevel() );
	//instorymenu = false;
	storymenu = new StoryMenu( dataTracker->getUniverse(), mouse, WINDOW_WIDTH, WINDOW_HEIGHT );

	// Allegro objects used to run main (the screen is above).
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / G_FPS);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	
	// Add event sources to the event queue.
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	// Variables used to run main.
	g_done = false;
	bool redraw = true;

	//_gameState->draw_on_screen();
	//al_flip_display();

	gAudio = new Audio( "sounds" );
	gAudio->set_bgm( BGM_MUSIC, "FFC Overworld" );
	gAudio->set_sfx( SFX_JUMP, "FreezeMagic" );
	gAudio->set_sfx( SFX_SPIKE, "KirbyStyleLaser" );
	gAudio->set_sfx( SFX_TELEPORT, "TornadoMagic", 0.7, 0 );
	gAudio->set_sfx( SFX_GET_UPGRADE, "Powerup" );
	gAudio->play_bgm( BGM_MUSIC );

	al_start_timer(timer);

	while(!g_done) {

		// Get the next event from the event queue.
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		// Deal with the event appropriately.
		switch(ev.type) {
		case ALLEGRO_EVENT_KEY_DOWN:
			// You just pressed a key.
			ki->pressKey( ev.keyboard.keycode );
			//g_input_manager->m_key_manager.press(ev.keyboard.keycode);
			break;
		case ALLEGRO_EVENT_KEY_UP:
			// You just released a key.
			ki->releaseKey( ev.keyboard.keycode );
			//g_input_manager->m_key_manager.release(ev.keyboard.keycode);
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			mouse->pressKey( ev.mouse.button-1 );
			//g_input_manager->m_mouse_manager.press(static_cast<E_MOUSEBUTTON>(ev.mouse.button-1));
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			mouse->releaseKey( ev.mouse.button-1 );
			//g_input_manager->m_mouse_manager.release(static_cast<E_MOUSEBUTTON>(ev.mouse.button-1));
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:
			mouse->setPosition( ev.mouse.x, ev.mouse.y );
			//g_input_manager->m_mouse_manager.set_position( ev.mouse.x, ev.mouse.y );
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			// You just pushed the x button in the corner.
			g_done = true;
			break;
		case ALLEGRO_EVENT_TIMER:
			// It's time to update and render the game.
			redraw = true;
			break;
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {

			// Indicate that we don't need to redraw until the timer ticks again.
			redraw = false;
		
			// Update and render the game
			main_step_and_render(0);
			// We need the following to actually display the result of render().
			al_flip_display();
			al_clear_to_color( G_SCREEN_COLOR );

			//g_input_manager->m_button_manager.reset_counts();
			ki->resetCounts();
			mouse->resetCounts();

		}
	}

	gAudio->stop_bgm( BGM_MUSIC );

	// Destroy globals, then shutdown Allegro
	//g_destroy_globals();
	//g_shutdown_allegro();
	al_destroy_font( font );
	
	al_uninstall_audio();
	al_shutdown_image_addon();
	al_shutdown_ttf_addon();
	al_shutdown_font_addon();
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_uninstall_system();

	// Return 0 to indicate that everything ended properly.
	return 0;

}

int main( int argc, char** argv )
{
	// return main_glut(argc,argv);
	return main_allegro( argc, argv );
}


/// Todo: put the todo section at the end of this file in a specification document.

// TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO

//Data & more algebra/basicphysics
//  SpatialAlgebra, SolidObject, use this everywhere
//  Story - design the format and implement

//Efficiency/capacity & main loop timing
//  Make TrackFloorRenderer more efficient by combining several quads into one whenever possible
//    and by using glDrawArrays or glDrawElements instead of just quads
//  Adjust timing loop so that lags don't get fast-forwarded too much
//    including pausing by clicking outside the window for a while
//    and including loading a new level

//Physics World
//  Perfect the physics engine when you're supposed to die

//Menus
// Incorporate story into gameplay - after completing a section (bunch of levels),
//   you see some story text with pictures or something (or a 3D animation?)
//   The ending is the last story thingy, after which you reset the game or something.
// Coin challenge - after you finish the game, you can re-do any level while collecting up to 3 coins per level
//   In save file, keep track of max number of coins caught-in-one-run-and-finished-the-level for each level
//   Unlock new awesome levels this way (bonus section 9)
//   Coin challenge is unlocked when you finish the game (bad ending)
// Main menu - include Story mode, Coin Challenge mode (after you finish the game),
//   Save file management, Options(keyboard controls, audio volumes, window size, etc)
// Pause/unpause

//Design
//  Music: 2 for menus,
//           Regular menu - Sad Prelude
//           Coin challenge - Jazz'n Jism
//         1 for Tutorial - Awaken
//         2 for each Section(1 for story mode, 1 for coin mode),
//           Desert - The Desert, Egyptian Psycho
//           Forest - Through the Forest, Plantazoid
//           Waterfall - Misty Waterfall part 2, Misty Waterfall part 1
//           Ocean - FFC Overworld, FFC Battle
//           Ice - Crystals (extended), Dashing through the Cold Wind
//           Sky - Questioning Purpose, Equilibrium
//           Space - New Beginning Part 2 (modified?), Continuum of the 5th dimension
//           Sun - The First Battle, FFC Final Boss (finish it)
//           Bonus - Tavern of Drinking enhanced big band style
//         5 for storysections
//           Beginning - FFC Overture
//           Switch sections - The Other Side
//           Bad Ending - Accepting Death
//           Good Ending - Ultimate / FFC Ending (finish it)
//           Bonus Ending (finish all bonus)- Continuum
//  Sfx: Pause/unpause, Menu mouseover/mouseout/click,
//       Gliding (faster='louder'), Drown, Headsmash,
//       Painterget, Endget, Levelstart
//  Design the main character (images + dimensions/mass)
//  Design the levels (40 normal + x bonus)
//  Design each section (bonus has several SectionData)
//  Design the story

// Publish the game as binaries!
// TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO