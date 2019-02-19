// PlaybackEngine.cpp : Defines the exported functions for the DLL application.
//
#include "PlaybackEngine.h"

int udp(void *outputBuffer, void * /*inputBuffer*/, unsigned int nBufferFrames,
	double /*streamTime*/, RtAudioStreamStatus status, void *userData) {

	//std::cout << "shit getDataFromUDP " << std::endl;
	return reinterpret_cast<PlaybackEngine*>(userData)->PlaybackEngine::getDataFromUDP(outputBuffer, nBufferFrames, status);
}

void errorCallback(RtAudioError::Type type, const std::string &errorText)
{
	// This example error handling function does exactly the same thing
	// as the embedded RtAudio::error() function.
	std::cout << "in errorCallback" << std::endl;
	if (type == RtAudioError::WARNING)
		std::cerr << '\n' << errorText << "\n\n";
	else if (type != RtAudioError::WARNING)
		throw(RtAudioError(errorText, type));
}

void PlaybackEngine::setupPlaybackStream() {
	RtAudio dac;

	// Set our stream parameters for output only.
	unsigned int bufferFrames = 192;
	//unsigned int bufferFrames = 768;
	unsigned int sampleRate = 48000;

	RtAudio::StreamParameters oParams;
	oParams.deviceId = dac.getDefaultOutputDevice();
	oParams.nChannels = 2;
	oParams.firstChannel = 0;

	dac.showWarnings(true);

	try {
		dac.openStream(&oParams, NULL, RTAUDIO_SINT16, sampleRate, &bufferFrames, &udp, this, NULL, &errorCallback);
		dac.startStream();
		if (dac.isStreamOpen()) {
			std::cout << "Stream is open" << std::endl;
		}
	}
	catch (RtAudioError& e) {
		e.printMessage();
		std::cout << "Stream is wrong" << std::endl;
	}

	char input;
	std::cout << "\nPlaying ... press <enter> to quit.\n";
	std::cin.get(input);
}

int PlaybackEngine::getDataFromUDP(void *outputBuffer, unsigned int nBufferFrames, RtAudioStreamStatus status) {

	//memcpy(reinterpret_cast<short*>(outputBuffer), buffer_->getlistenerPointer(), nBufferFrames);

	postProcessing(reinterpret_cast<short*>(outputBuffer), buffer_->getlistenerPointer(), nBufferFrames);


	//std::cout << "shitasdas " << std::endl;
	return 0;
}




void PlaybackEngine::postProcessing(short * outputBuffer, short* udpBuffer, unsigned int nBufferFrames) {
	/*memcpy(reinterpret_cast<short*>(outputBuffer), udpBuffer, nBufferFrames);
	std::cout << alpha << std::endl;*/
	for (int i = 0; i < nBufferFrames * 2; i += 2) {
		outputBufferPreviousI = (int)(outputBufferPreviousI + (alpha*(udpBuffer[i / 2] - outputBufferPreviousI)));
		temp = outputBufferPreviousI;
		//temp = udpBuffer[i/2];
		if (temp > SHRT_MAX) {
			outputBuffer[i] = SHRT_MAX;
			outputBuffer[i + 1] = SHRT_MAX;
		}
		else if (temp < SHRT_MIN) {
			outputBuffer[i] = SHRT_MIN;
			outputBuffer[i + 1] = SHRT_MIN;
		}
		else {
			outputBuffer[i] = temp;
			outputBuffer[i + 1] = temp;
		}
	}
	//temp = outputBuffer[nBufferFrames - 1];
	//memcpy(outputBuffer, udpBuffer, nBufferFrames*2);
}

PlaybackEngine::PlaybackEngine(Buffer *buffer)
{
	buffer_ = buffer;

	setupPlaybackStream();
}



