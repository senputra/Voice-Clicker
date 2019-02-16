#pragma once
#ifndef PLAYBACKENGINE_H
#define PLAYBACKENGINE_H

// Platform-dependent sleep routines.
#if defined( __WINDOWS_ASIO__ ) || defined( __WINDOWS_DS__ ) || defined( __WINDOWS_WASAPI__ )
#define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds ) 
#else // Unix variants
#include <unistd.h>
#define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif

#include "RtAudio.h"
#include "Buffer.h"

class PlaybackEngine
{
public:
	PlaybackEngine(Buffer *buffer);
	int getDataFromUDP(void *outputBuffer, unsigned int nBufferFrames, RtAudioStreamStatus status);

private:
	void setupPlaybackStream();

private:
	Buffer *buffer_ = nullptr;

	void postProcessing(short * outputBuffer, short* udpBuffer, unsigned int nBufferFrames);

	double RC = 1.0 / (15000 * 2 * 3.14);
	double dt = 1.0 / 48000;
	double alpha = dt / (RC + dt);
	double outputBufferPreviousI = 0;
	double temp = 0;
};
#endif // !PLAYBACKENGINE_H

