#ifndef GameObject_H
#define GameObject_H

#include "../../stdafx.h"

class GameObject
{
	public:				

		GameObject(Ogre::int32 aGameObjectId)		
		: mGameObjectId(aGameObjectId)	 
		{}		

		~GameObject()
		{}

	protected:
		
		Ogre::int32				mGameObjectId;	

 };
#endif