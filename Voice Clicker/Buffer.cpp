

#include"Buffer.h"

short* Buffer::getWriterPointer() {
	//std::cout << "get writer pointer asdfasdf::" << writerCounter << std::endl;
	/*if (listenerCounter == writerCounter) {
		return writerPointer + (bufferSize*(writerCounter - 1));
	}*/
	if (writerCounter == nBuffers - 1) {
		writerCounter = 0;
		return writerPointer + (bufferSize*(nBuffers - 1));
	}
	else {
		writerCounter += 1;
		return writerPointer + (bufferSize*(writerCounter - 1));
	}
}


short* Buffer::getlistenerPointer() {
	//std::cout << "get listener pointer asdfasdf::" << listenerCounter << std::endl;
	if (listenerCounter == writerCounter) {
		std::cout << "CLASHHH::" << listenerCounter << std::endl;
		//return listenerPointer + (bufferSize*(listenerCounter - 1));
		return nullBuffer_;
	} else if (listenerCounter == nBuffers - 1) {
		listenerCounter = 0;
		return listenerPointer + (bufferSize*(nBuffers - 1));
	}
	else {
		listenerCounter += 1;
		return listenerPointer + (bufferSize*(listenerCounter - 1));
	}
}
