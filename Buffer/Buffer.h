#pragma once

#ifdef BUFFER_EXPORTS
#define BUFFER_API __declspec(dllexport)
#else
#define BUFFER_API __declspec(dllimport)
#endif // BUFFER_EXPORTS


/**
buffer.cpp
Writer : Audio buffer from UDP Server
Listener : RtAudio

When buffer[0] is being written, listener waits.
When buffer[1] is being written, listener reads buffer[0]
   .
   .
   .
so on and so off.
 */
#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>


class BUFFER_API Buffer {
private:
	int bufferSize = 256; // one frame takes 2 Byte [int16]
	int nBuffers = 4;

	short **buffer_;
	short * nullBuffer;

	short* writerPointer = nullptr;
	short* listenerPointer = nullptr;

	int writerCounter = 0;
	int listenerCounter = 0;




public:
	Buffer();

	~Buffer();
	short* getWriterPointer();
	short* getlistenerPointer();

	size_t getMaxSizeInBytes();
	size_t getBufferSize();
};

#endif // !BUFFER_H