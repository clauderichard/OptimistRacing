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

#pragma once

#include <string>
#include <allegro5\allegro.h>
#include <allegro5\allegro_audio.h>

// Types of bgm the game can have.
// The first one should be actual music,
// the latter ones should be ambient sound.
enum E_BGM {
	BGM_MUSIC = 0,
	BGM_NUM
};

// Types of sound effects the game can have.
enum E_SFX {
	SFX_JUMP = 0,
	SFX_SPIKE,
	SFX_TELEPORT,
	SFX_GET_UPGRADE,
	SFX_NUM
};

#define NUM_SFX_SIMULTANEOUS 3

float f_blend_pan( float pan1, float pan2 );



class AudioStream {

public:
	AudioStream( const std::string& filepath );
	~AudioStream();
	
	void setLoop( double begin, double end );
	void unloop();
	void setVolume( float volume );
	float getVolume();
	void setPan( float pan );
	float getPan();

	void play();
	void pause();
	void stop();

private:
	ALLEGRO_AUDIO_STREAM* mStream;
	std::string mFilepath;
	bool mLoopSpecified;
	double mLoopBegin;
	double mLoopEnd;

	void makeStream();

};



// One instance of a sound effect. You can't make this loop.
class SampleInstance {

public:
	SampleInstance( ALLEGRO_SAMPLE* sample );
	~SampleInstance();

	void setVolume( float volume );
	float getVolume();
	void setPan( float pan );
	float getPan();

	void play();
	void pause();
	void stop();

	bool isPlaying();
	bool isPaused();
	bool isStopped();

private:
	ALLEGRO_SAMPLE_INSTANCE* mInstance;

	// These are used for pausing and playing the audio
	bool mPaused;
	int mPosition;

};



// This class represents a set of instances for one sound effect,
// so you can hear several enemies die at the same time! Isn't that great?!
class SampleInstanceSet
{

public:

	// In the constructor we load the sample and make an array of instances.
	SampleInstanceSet( std::string thefilepath, int numInstances );
	~SampleInstanceSet();

	void setVolume( float volume );
	float getVolume();
	void setPan( float pan );
	float getPan();

	// Plays one of the instances.
	// If overload then plays the first non-playing instance, if possible.
	// Otherwise plays the first instance, but only if nothing is playing.
	void play( bool overload ); // use default volume and pan
	void play( bool overload, float volume, float pan ); // specify relative volume and pan
	// Pauses every instance at once.
	// When you play it again, all the paused instances resume.
	void pause();
	void unpause();
	// Stops every instance at once.
	// When you play it again, the first instance starts from the beginning.
	void stop();

private:

	// The music information is stored in this sample.
	ALLEGRO_SAMPLE* m_sample;

	// This is an array of instances.
	// Several instances can play the same sample.
	int m_numInstances;
	SampleInstance** mInstances;

	// How do we want to play this?
	float m_pan; // Default pan, -1.0 = left only, +1.0 = right only.
	float m_volume; // Default volume
	float* m_volumes; // Each instance can have a different volume relative to the base m_volume.
	float* m_pans; // Each instance can have a different pan relative to m_pan.

};



class Audio {

public:

	// The constructor sets the folder where the audio files are
	Audio(std::string folder);
	// The destructor destroys the samples and sample instances.
	~Audio();

	// Loads the music file in filename into the sound effect at index type.
	// If filename is the same as the previous, then doesn't change anything.
	// If it's different, then stops all instances of that sfx/bgm.
	void set_bgm( int bgm, std::string name, float volume, float pan );
	void set_bgm( int bgm, std::string name );
	void set_bgm_withloop( int bgm, std::string name, float loopbegin, float loopend, float volume, float pan );
	void set_bgm_withloop( int bgm, std::string name, float loopbegin, float loopend );
	void set_sfx( int sfx, std::string name, float volume, float pan );
	void set_sfx( int sfx, std::string name );

	// Get and set volumes
	void set_bgm_volume( float volume );
	float get_bgm_volume();
	void set_sfx_volume( float volume );
	float get_sfx_volume();
	void set_bgm_volume( int bgm, float volume );
	float get_bgm_volume( int bgm );
	void set_sfx_volume( int sfx, float volume );
	float get_sfx_volume( int sfx );
	
	// play, pause, stop.
	void play_bgm( int bgm, float volume, float pan );
	void play_bgm( int bgm );
	void pause_bgm( int bgm );
	void stop_bgm( int bgm );
	void play_sfx( int type, bool overload, float volume, float pan );
	void play_sfx( int type, bool overload );
	void pause_sfx( int type );
	void stop_sfx( int type );

private:

	std::string name_to_filename( std::string name );

	// The folder where all the audio files are.
	// The files are all .ogg
	std::string				m_folder;
	// Names of the audio files
	std::string*			m_bgm_names;
	std::string*			m_sfx_names;

	// the bgm streams
	AudioStream**			m_bgm;
	// One-dimensional array of pointers to sound effects.
	SampleInstanceSet**	m_sfx;

	float					m_bgm_volume;
	float					m_sfx_volume;
	float*					m_bgm_volumes;
	float*					m_sfx_volumes;
};