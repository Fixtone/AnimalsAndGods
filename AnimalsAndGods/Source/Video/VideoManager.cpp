#include "stdafx.h"
#include "../../Header/Video/VideoManager.h"

using namespace Video;

template<> VideoManager* Ogre::Singleton<VideoManager>::msSingleton = 0;
VideoManager* VideoManager::getSingletonPtr(void)
{
	return msSingleton;
}
VideoManager& VideoManager::getSingleton(void)
{  
	assert( msSingleton );  return ( *msSingleton );  
}

VideoManager::VideoManager(){}

VideoManager::~VideoManager(){}

bool VideoManager::InitializeVideoManager()
{
	try
	{
		return true;
	}	
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}	

}

bool VideoManager::ClearVideoManager()
{
	try
	{
		return true;
	}	
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}	
}

bool VideoManager::PlayVideo(VideoInfo aVideoInfo)
{
	// Set the material name to play on
	// IMPORTANT: The material has to exist!
	FFMPEG_PLAYER->setMaterialName(aVideoInfo.videoMaterialName);

	// Set the texture unit name to play on
	// IMPORTANT: The material above must have a texture unit with that name!
	FFMPEG_PLAYER->setTextureUnitName(aVideoInfo.videoTextureUnitName);

	// Set the buffer target for the video player.
	// This is the time the buffer will fill before starting playback, and also the time it will always 
	// try to hold in the buffers.
	// As soon as both the audio and the video buffers hold the target time, decoding is stopped until 
	// at least one of the buffers
	// hold less than the target time.
	FFMPEG_PLAYER->setBufferTarget(aVideoInfo.bufferTarget);

	// Set the name of the video file
	FFMPEG_PLAYER->setVideoFilename(aVideoInfo.videoName);


	// Should the video loop?
	FFMPEG_PLAYER->setIsLooping(aVideoInfo.lopping);

	// Set the forced number of audio channels
	// If this is not set, the number of channels of the video file will be used (which will in most 
	// cases be stereo)
	// You can set this to 0 manually to force using the video's number of channels.
	// Any number higher than 2 will most likely break something
	// IMPORTANT: OpenAL needs to have mono sound for 3D audio effects
	FFMPEG_PLAYER->setForcedAudioChannels(aVideoInfo.forcedAudioChannelsNumber);

	// Set the log level of the player's own log file.
	FFMPEG_PLAYER->setLogLevel(LOGLEVEL_NORMAL);

	// Play the video
	// Remember: this is video only, no audio
	if (!FFMPEG_PLAYER->startPlaying())
	{
		// print error
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, "FFMPEG_PLAYER->startPlaying() Error");
		return false;
	}
	else
	{
		return true;
	}
}

bool VideoManager::StopVideo()
{	
	FFMPEG_PLAYER->stopVideo();
	return true;
}