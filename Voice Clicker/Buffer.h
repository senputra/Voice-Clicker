#pragma once
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


class Buffer {
private:
	int bufferSize = 192; // one frame takes 2 Byte [int16]
	int nBuffers = 8;

	short **buffer_;
	short* writerPointer = nullptr;
	short* listenerPointer = nullptr;
	short* nullBuffer_;

	int writerCounter = 0;
	int listenerCounter = 0; 

	int* tempW = nullptr;
	int* tempL = nullptr;

	

public:
	Buffer() {
		buffer_ = new int16_t*[nBuffers];
		for (int i = 0; i < nBuffers; i++) {
			buffer_[i] = new int16_t[bufferSize];
			memset(buffer_[i], 0, bufferSize * 2);
		}
		/*printf("buffer \n");
		for (int i = 0; i < nBuffers; i++) {
			for (int j = 0; j < bufferSize; j++) {
				printf("%d",buffer_[i][j]);
			}
		}
		printf("nullptr \n");*/
		nullBuffer_ = new int16_t[bufferSize];
		memset(nullBuffer_, 0, bufferSize * 2);

		/*for (int j = 0; j < bufferSize * listenerBufferSize; j++) {
			printf("%d", nullBuffer_[j]);
		}*/
		/*
		std::cout << "new Buffer" << bufferSize * nBuffers << std::endl;
		std::cout << "HERE " << (short)*buffer_ << std::endl;
		std::cout << "new Buffer" << bufferSize * nBuffers << " pointer a " << listenerPointer << " pointer b " << writerPointer << std::endl;*/
	};

	~Buffer() {
		for (int i = 0; i < nBuffers; i++) {
			delete buffer_[i];
		}
		delete nullBuffer_;
	};
	short* getWriterPointer() {
		if (writerCounter == nBuffers) {
			writerCounter = 0;
		}
			//printf("%d \n", writerCounter);
		return buffer_[writerCounter++];
	}
	short* getlistenerPointer() {
		//if (listenerCounter == writerCounter) {
		//	//return (listenerCounter == 0) ? buffer_[nBuffers-1] : buffer_[listenerCounter-1];
		//	return nullBuffer_;
		//}
		if (listenerCounter == nBuffers) {
			listenerCounter = 0;
		}
		return buffer_[listenerCounter++];
		
	}

	size_t getMaxSizeInBytes() {
		return bufferSize * 2;
	}
};

#endif // !BUFFER_H