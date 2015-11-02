#ifndef VideoManager_H_
#define VideoManager_H_

#include "FFmpegVideoPlayer.h"

namespace Video
{
	class VideoManager : public Ogre::Singleton<VideoManager>
	{
		public:

			struct VideoInfo
			{
				Ogre::String	videoMaterialName;
				Ogre::String	videoTextureUnitName;
				float			bufferTarget;
				Ogre::String	videoName;
				bool			lopping;
				int				forcedAudioChannelsNumber;
			};

			VideoManager();
			~VideoManager();

			static VideoManager& getSingleton(void);
			static VideoManager* getSingletonPtr(void);

			bool InitializeVideoManager();
			bool ClearVideoManager();

			bool PlayVideo(VideoInfo aVideoInfo);	
			bool StopVideo();
			
	};
}
#endif