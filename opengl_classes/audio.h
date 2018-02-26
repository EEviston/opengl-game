#pragma once

#include <windows.h>
#include "SOIL.h"
#include "al.h"
#include "alc.h" 
#include "alut.h"

#define NUM_BUFFERS 12
#define NUM_SOURCES 12

class Audio
{
public:
	Audio();
	void setListener();
	void loadFile(ALbyte *file, int b_index);
	void setSource(int s_index, int b_index, float gain, float pitch, bool looped);
	void playSound(int s_index, int b_index);
	void pauseSound(int s_index, int b_index);

	bool keyDown;

private:
	
	ALsizei size, freq;
	ALenum format;
	ALvoid *data;
	ALboolean loop;
	ALCcontext *Context;
	ALCdevice *Device;
	// Buffers hold sound data.
	ALuint buffer[NUM_BUFFERS];
	// Sources are points emitting sound.
	ALuint source[NUM_SOURCES];

	ALfloat SourcePos[3];
	ALfloat SourceVel[3];

	ALfloat ListenerPos[3];
	ALfloat ListenerVel[3];
	ALfloat ListenerOri[6];

	

	void Init();
};