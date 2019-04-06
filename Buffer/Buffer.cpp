// Buffer.cpp : Defines the exported functions for the DLL application.
//

#include "Buffer.h"

Buffer::Buffer() {
	buffer_ = new int16_t*[nBuffers];
	for (int i = 0; i < nBuffers; i++) {
		buffer_[i] = new int16_t[bufferSize];
		memset(buffer_[i], 0, bufferSize * 2);
	}

	nullBuffer = new int16_t[bufferSize];
	memset(nullBuffer, 0, bufferSize * 2);

};

Buffer::~Buffer() {
	for (int i = 0; i < nBuffers; i++) {
		delete buffer_[i];
	}
	delete nullBuffer;
};
short* Buffer::getWriterPointer() {
	if (writerCounter == nBuffers) {
		writerCounter = 0;
	}
	//printf("%d \n", writerCounter);
	return buffer_[writerCounter++];
}
short* Buffer::getlistenerPointer() {
	/*if (listenerCounter == writerCounter) {
		return nullBuffer;
	}*/
	if (listenerCounter == nBuffers) {
		listenerCounter = 0;
	}
	return buffer_[listenerCounter++];

}

size_t Buffer::getMaxSizeInBytes() {
	return bufferSize * 2;
}
size_t Buffer::getBufferSize() {
	return bufferSize;
}
