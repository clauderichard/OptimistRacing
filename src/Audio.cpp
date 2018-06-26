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

#include "Audio.hpp"
#include <allegro5\allegro_acodec.h>


float f_blend_pan( float pan1, float pan2 )
{
	return pan1 + pan2;
}

AudioStream::AudioStream( const std::string& filepath )
	: mFilepath( filepath )
	, mLoopSpecified( false )
{
	makeStream();
	pause();
}

AudioStream::~AudioStream()
{
	al_destroy_audio_stream( mStream );
}

void AudioStream::setLoop( double begin, double end )
{
	mLoopSpecified = true;
	mLoopBegin = begin;
	mLoopEnd = end;
	al_set_audio_stream_playmode( mStream, ALLEGRO_PLAYMODE_LOOP );
	al_set_audio_stream_loop_secs( mStream, mLoopBegin, mLoopEnd );
}

void AudioStream::unloop()
{
	al_set_audio_stream_playmode( mStream, ALLEGRO_PLAYMODE_ONCE );
}

void AudioStream::setVolume( float volume )
{
	al_set_audio_stream_gain( mStream, volume );
}

float AudioStream::getVolume()
{
	return al_get_audio_stream_gain( mStream );
}

void AudioStream::setPan( float pan )
{
	al_set_audio_stream_pan( mStream, pan );
}

float AudioStream::getPan()
{
	return al_get_audio_stream_pan( mStream );
}

void AudioStream::play()
{
	al_set_audio_stream_playing( mStream, true );
}

void AudioStream::pause()
{
	al_set_audio_stream_playing( mStream, false );
}

void AudioStream::stop()
{
	//al_set_audio_stream_loop_secs( m_stream, 0.0, 6.0 );
	//al_set_audio_stream_playing( m_stream, false );
	//al_rewind_audio_stream( m_stream );
	//al_drain_audio_stream( m_stream );
	//al_set_audio_stream_loop_secs( m_stream, 3.0, 6.0 );
	al_destroy_audio_stream( mStream );
	makeStream();
	pause();

}

void AudioStream::makeStream()
{
	mStream = al_load_audio_stream( mFilepath.c_str(), 100, 20 );
	al_set_audio_stream_playmode( mStream, ALLEGRO_PLAYMODE_LOOP );
	al_attach_audio_stream_to_mixer( mStream, al_get_default_mixer() );
	if ( mLoopSpecified ) al_set_audio_stream_loop_secs( mStream, mLoopBegin, mLoopEnd );
}



SampleInstance::SampleInstance( ALLEGRO_SAMPLE* sample )
{
	mInstance = al_create_sample_instance( sample );
	al_attach_sample_instance_to_mixer( mInstance, al_get_default_mixer());
	mPaused = true;
	mPosition = 0;
}

SampleInstance::~SampleInstance()
{
	al_detach_sample_instance( mInstance );
	al_destroy_sample_instance( mInstance );
}

void SampleInstance::setVolume( float volume )
{
	al_set_sample_instance_gain( mInstance, volume );
}

float SampleInstance::getVolume()
{
	return al_get_sample_instance_gain( mInstance );
}

void SampleInstance::setPan( float pan )
{
	al_set_sample_instance_pan( mInstance, pan );
}

float SampleInstance::getPan()
{
	return al_get_sample_instance_pan( mInstance );
}

void SampleInstance::play()
{
	// only do something if it's not already playing
	if (!mPaused) return;

	al_set_sample_instance_position( mInstance, mPosition );
	al_play_sample_instance( mInstance );
	mPaused = false;
}

void SampleInstance::pause()
{
	if ( ! mPaused ) {
		mPaused = true;
		mPosition = al_get_sample_instance_position( mInstance );
		al_stop_sample_instance( mInstance );
	}
}

void SampleInstance::stop()
{
	mPosition = 0;
	if ( ! mPaused ) {
		mPaused = true;
		al_stop_sample_instance( mInstance );
	}
}

bool SampleInstance::isPlaying()
{
	return !mPaused;
}

bool SampleInstance::isPaused()
{
	return (mPaused && mPosition!=0);
}

bool SampleInstance::isStopped()
{
	return (mPaused && mPosition==0) || !al_get_sample_instance_playing( mInstance );
}



SampleInstanceSet::SampleInstanceSet( std::string thefilepath, int numInstances )
	: m_numInstances( numInstances )
	, m_volume( 1 )
	, m_pan( 0 )
{
	m_sample = al_load_sample(thefilepath.c_str());
	mInstances = new SampleInstance*[m_numInstances];
	m_volumes = new float[m_numInstances];
	m_pans = new float[m_numInstances];
	for (int i=0; i<m_numInstances; i++) {
		m_volumes[i] = 1;
		m_pans[i] = 0;
		mInstances[i] = new SampleInstance( m_sample );
		mInstances[i]->setVolume( m_volumes[i]*m_volume );
		mInstances[i]->setPan( f_blend_pan( m_pans[i], m_pan ) );
	}
}

SampleInstanceSet::~SampleInstanceSet() {
	// Destroy the instances.
	for ( int i = 0; i < m_numInstances; i ++ )
	{
		delete mInstances[i];
	}
	// Destroy the sample.
	al_destroy_sample( m_sample );
	// Delete the arrays.
	delete[] mInstances;
	delete[] m_volumes;
	delete[] m_pans;
}

void SampleInstanceSet::setVolume( float volume )
{
	m_volume = volume;
	for (int i=0; i<m_numInstances; i++) {
		mInstances[i]->setVolume( m_volumes[i]*m_volume );
	}
}

float SampleInstanceSet::getVolume()
{
	return m_volume;
}

void SampleInstanceSet::setPan( float pan )
{
	m_pan = pan;
	for (int i=0; i<m_numInstances; i++) {
		mInstances[i]->setPan( f_blend_pan( m_pans[i], m_pan ) );
	}
}

float SampleInstanceSet::getPan()
{
	return m_pan;
}

void SampleInstanceSet::play(bool overload) {
	play( overload, 1, 0 );
}

void SampleInstanceSet::play( bool overload, float volume, float pan ) {
	if (overload) {
		// play the first stopped one if possible
		for (int i=0; i<m_numInstances; i++) {
			if ( !mInstances[i]->isStopped() ) continue;
			m_volumes[i] = volume;
			m_pans[i] = pan;
			mInstances[i]->stop();
			mInstances[i]->setVolume( m_volumes[i]*m_volume );
			mInstances[i]->setPan( f_blend_pan( m_pans[i], m_pan ) );
			mInstances[i]->play();
			break;
		}
	} else {
		// if one is playing or paused then do nothing
		for (int i=0; i<m_numInstances; i++) {
			if ( !mInstances[i]->isStopped() ) return;
		}
		// otherwise play the first non-playing one (first one)
		mInstances[0]->stop();
		mInstances[0]->play();
	}
}

void SampleInstanceSet::pause()
{
	// pause all playing ones
	for (int i=0; i<m_numInstances; i++) {
		if ( mInstances[i]->isPlaying() ) {
			mInstances[i]->pause();
		}
	}
}

void SampleInstanceSet::unpause()
{
	// unpause all the paused ones
	for (int i=0; i<m_numInstances; i++) {
		if ( mInstances[i]->isPaused() ) {
			mInstances[i]->play();
		}
	}
}

void SampleInstanceSet::stop()
{
	// stop all instances
	for (int i=0; i<m_numInstances; i++) {
		mInstances[i]->stop();
	}
}



Audio::Audio( std::string folder )
	: m_folder( folder )
	, m_bgm_volume( 1 )
	, m_sfx_volume( 1 )
{

	// Number of samples to reserve
	int n = BGM_NUM + SFX_NUM*NUM_SFX_SIMULTANEOUS;
	al_reserve_samples( n );

	// set bgm and sfx array
	m_bgm = new AudioStream*[ BGM_NUM ];
	m_sfx = new SampleInstanceSet*[ SFX_NUM ];
	m_bgm_names = new std::string[ BGM_NUM ];
	m_sfx_names = new std::string[ SFX_NUM ];
	m_bgm_volumes = new float[ BGM_NUM ];
	m_sfx_volumes = new float[ SFX_NUM ]; 
	for (int i=0; i<BGM_NUM; i++) {
		m_bgm[i] = NULL;
		m_bgm_names[i] = "";
		m_bgm_volumes[i] = 1;
	}
	for (int i=0; i<SFX_NUM; i++) {
		m_sfx[i] = NULL;
		m_sfx_names[i] = "";
		m_sfx_volumes[i] = 1;
	}
}

Audio::~Audio() {
	for (int i=0; i<BGM_NUM; i++) {
		if (m_bgm[i] != NULL) delete m_bgm[i];
	}
	for (int i=0; i<SFX_NUM; i++) {
		if (m_sfx[i] != NULL) delete m_sfx[i];
	}
	delete[] m_bgm;
	delete[] m_sfx;
	delete[] m_bgm_names;
	delete[] m_sfx_names;
	delete[] m_bgm_volumes;
	delete[] m_sfx_volumes;
}

void Audio::set_bgm( int bgm, std::string name, float volume, float pan )
{
	if ( name != m_bgm_names[bgm] ) {
		if (m_bgm[bgm]!=NULL) delete m_bgm[bgm];
		m_bgm[bgm] = new AudioStream( name_to_filename( name ) );
	}
	m_bgm_volumes[bgm] = volume;
	m_bgm[bgm]->setVolume( volume*m_bgm_volume );
	m_bgm[bgm]->setPan( pan );
}

void Audio::set_bgm( int bgm, std::string name )
{
	set_bgm( bgm, name, 1, 0 );
}

void Audio::set_bgm_withloop( int bgm, std::string name, float loopbegin, float loopend, float volume, float pan )
{
	if ( name != m_bgm_names[bgm] ) {
		if (m_bgm[bgm]!=NULL) delete m_bgm[bgm];
		m_bgm[bgm] = new AudioStream( name_to_filename( name ) );
	}
	m_bgm_volumes[bgm] = volume;
	m_bgm[bgm]->setVolume( volume*m_bgm_volume );
	m_bgm[bgm]->setPan( pan );
	m_bgm[bgm]->setLoop( loopbegin, loopend );
}

void Audio::set_bgm_withloop( int bgm, std::string name, float loopbegin, float loopend )
{
	set_bgm_withloop( bgm, name, loopbegin, loopend, 1, 0 );
}

void Audio::set_sfx( int type, std::string name, float volume, float pan )
{
	if ( name != m_sfx_names[type] ) {
		if ( m_sfx[type] != NULL ) delete m_sfx[type];
		m_sfx[type] = new SampleInstanceSet( name_to_filename( name ), NUM_SFX_SIMULTANEOUS );
	}
	m_sfx_volumes[type] = volume;
	m_sfx[type]->setVolume( volume*m_sfx_volume );
	m_sfx[type]->setPan( pan );
}

void Audio::set_sfx( int type, std::string name)
{
	set_sfx( type, name, 1, 0 );
}

void Audio::set_bgm_volume( float volume )
{
	m_bgm_volume = volume;
	for (int i=0; i<BGM_NUM; i++) {
		if (m_bgm[i]!=NULL) m_bgm[i]->setVolume( m_bgm_volumes[i]*m_bgm_volume );
	}
}

float Audio::get_bgm_volume()
{
	return m_bgm_volume;
}

void Audio::set_sfx_volume( float volume )
{
	m_sfx_volume = volume;
	for (int i=0; i<SFX_NUM; i++) {
		if (m_sfx[i]!=NULL) m_sfx[i]->setVolume( m_sfx_volumes[i]*m_sfx_volume );
	}
}

float Audio::get_sfx_volume()
{
	return m_sfx_volume;
}

void Audio::set_bgm_volume( int bgm, float volume )
{
	m_bgm_volumes[bgm] = volume;
	m_bgm[bgm]->setVolume( volume*m_bgm_volume );
}

float Audio::get_bgm_volume( int bgm )
{
	return m_bgm_volumes[bgm];
}

void Audio::set_sfx_volume( int sfx, float volume )
{
	m_sfx_volumes[sfx] = volume;
	m_sfx[sfx]->setVolume( volume*m_sfx_volume );
}

float Audio::get_sfx_volume( int sfx )
{
	return m_sfx_volumes[sfx];
}

void Audio::play_bgm( int bgm, float volume, float pan )
{
	m_bgm_volumes[bgm] = volume;
	m_bgm[bgm]->setVolume( volume*m_bgm_volume );
	m_bgm[bgm]->setPan( pan );
	m_bgm[bgm]->play();
}

void Audio::play_bgm( int bgm )
{
	play_bgm( bgm, 1, 0 );
}

void Audio::pause_bgm( int bgm )
{
	m_bgm[bgm]->pause();
}

void Audio::stop_bgm( int bgm )
{
	m_bgm[bgm]->stop();
}

void Audio::play_sfx( int type, bool overload, float volume, float pan )
{
	m_sfx[ type ]->play( overload, volume, pan );
}

void Audio::play_sfx( int type, bool overload )
{
	play_sfx( type, overload, 1, 0 );
}

void Audio::pause_sfx( int type )
{
	m_sfx[ type ]->pause();
}

void Audio::stop_sfx(int type)
{
	m_sfx[ type ]->stop();
}

std::string Audio::name_to_filename( std::string name )
{
	return m_folder + "/" + name + ".ogg";
}