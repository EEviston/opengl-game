#include "audio.h"
#include <stdio.h>

Audio::Audio()
{
	Init();
}

void Audio::Init()
{
	// Position of the source sound.
	SourcePos[0] = 0.0;
	SourcePos[1] = 0.0;
	SourcePos[2] = 0.0;
	// Velocity of the source sound.
	SourceVel[0] = 0.0;
	SourceVel[1] = 0.0;
	SourceVel[2] = 0.0;
	
	// Position of the listener.
	ListenerPos[0] = 0.0;
	ListenerPos[1] = 0.0;
	ListenerPos[2] = 0.0;
	// Velocity of the listener.
	ListenerVel[0] = 0.0;
	ListenerVel[1] = 0.0;
	ListenerVel[2] = 0.0;

	// Orientation of the listener. (first 3 elements are "at", second 3 are "up")
	ListenerOri[0] = 0.0;
	ListenerOri[1] = 0.0;
	ListenerOri[2] = 0.0;
	ListenerOri[3] = 0.0;
	ListenerOri[4] = 1.0;
	ListenerOri[5] = 0.0;

	Device = alcOpenDevice((ALchar*)"DirectSound3D");
	if (Device == NULL)
	{
		exit(-1);
	}

	//Create context(s)
	Context = alcCreateContext(Device, NULL);
	//Set active context
	alcMakeContextCurrent(Context);

	setListener();
	alGenSources(NUM_SOURCES, source);
	alGetError();
	alGenBuffers(NUM_BUFFERS, buffer);

	if (alGetError() != AL_NO_ERROR)
	{
		printf("- Error creating buffers !!\n");
		exit(1);
	}
	else
	{
		printf("init() - No errors yet.");
	}

}

void Audio::setListener()
{
	alListenerfv(AL_POSITION, ListenerPos);
	alListenerfv(AL_VELOCITY, ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
	printf("listeners set");
}

void Audio::loadFile(ALbyte *file, int b_index)
{
	alutLoadWAVFile(file, &format, &data, &size, &freq, &loop);
	alBufferData(buffer[b_index], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);
}

void Audio::setSource(int s_index, int b_index, float gain, float pitch, bool looped) 
{
	alSourcef(source[s_index], AL_PITCH, pitch);
	alSourcef(source[s_index], AL_GAIN, gain);
	alSourcefv(source[s_index], AL_POSITION, SourcePos);
	alSourcefv(source[s_index], AL_VELOCITY, SourceVel);
	alSourcei(source[s_index], AL_BUFFER, buffer[b_index]);
	if (looped == true)
		alSourcei(source[s_index], AL_LOOPING, AL_TRUE);
	else
		alSourcei(source[s_index], AL_LOOPING, AL_FALSE);

	printf("s_index = %d and b_index = %d", s_index, b_index);
}

void Audio::playSound(int s_index, int b_index)
{
	alSourcePlay(source[s_index]);
}

void Audio::pauseSound(int s_index, int b_index)
{
	alSourcePause(source[s_index]);
}