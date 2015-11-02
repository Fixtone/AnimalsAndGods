#include "stdafx.h"
#include "../../Header/Mind/MindManager.h"

using namespace Mind;

template<> MindManager* Ogre::Singleton<MindManager>::msSingleton = 0;
MindManager* MindManager::getSingletonPtr(void)
{
	return msSingleton;
}
 
MindManager& MindManager::getSingleton(void)
{  
	assert(msSingleton);
	return *msSingleton;
}

MindManager::MindManager()
: _ThougtId(0)
, _ThougtBetweenTime(0)
, _FinishThoughts(false)
{
}

MindManager::~MindManager()
{
}

void MindManager::initialiseManager()
{
}

void MindManager::clearManager()
{
}

void MindManager::configureMind()
{
	_ThougtId = 0;
	_FinishThoughts = false;

	MindLoader* mindLoader = new MindLoader();
	_MindsData.push_back(mindLoader->loadMind("PlayerMind.xml","Play"));

	_ThougtBetweenTime = _MindsData[0].mMind["ESP"][_ThougtId]->getThoughtTime();

}

void MindManager::releaseMind()
{	
	_MindsData.clear();
}

bool MindManager::frameStartedMind(const Ogre::Real aElapsedTime)
{
	try
	{
		/*BOOST_FOREACH(MapGameObjectTrain::value_type& gameObjectTrain, _MapGameObjectTrain)
			gameObjectTrain.second->frameStarted(aElapsedTime);*/
	
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[frameStartedGON]: " + e.getDescription());
		return false;
	}	
}

bool MindManager::frameEndedMind(const Ogre::Real aElapsedTime)
{
	try
	{
		/*BOOST_FOREACH(MapGameObjectTrain::value_type& gameObjectTrain, _MapGameObjectTrain)
			gameObjectTrain.second->frameEnded(aElapsedTime);		*/

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[frameEndedGON]: " + e.getDescription());
		return false;
	}	
}

bool MindManager::updateMind(const Ogre::Real aElapsedTime)
{
	if(!_FinishThoughts)
	{
		for(Ogre::uint i = 0; i<_MindsData.size(); i++)
		{
			_ThougtBetweenTime -= aElapsedTime;

			if(_ThougtBetweenTime<=0)
			{
				_ThougtId++;

				if(_ThougtId < _MindsData[i].mMind["ESP"].size())
				{
					_ThougtBetweenTime =  _MindsData[i].mMind["ESP"][_ThougtId]->getThoughtTime();			
					_LineOne->text(_MindsData[i].mMind["ESP"][_ThougtId]->getThoughtText()[0]);
					_LineTwo->text(_MindsData[i].mMind["ESP"][_ThougtId]->getThoughtText()[1]);
					_LineThree->text(_MindsData[i].mMind["ESP"][_ThougtId]->getThoughtText()[2]);
				}
				else
				{
					_FinishThoughts = true;
				}
			}		
		}
	}
	
	return true;
	
}

void MindManager::setGui3DPanelMindThoughts(Gui3D::ScreenPanel* aGui3DPanelMindThoughts)
{
	_Gui3DPanelMindThoughts = aGui3DPanelMindThoughts;

	_LineOne = _Gui3DPanelMindThoughts->makeCaption(2, 4 + 0, 780, 80, "", Gorilla::TextAlign_Centre, Gorilla::VerticalAlign_Top);
	_LineTwo = _Gui3DPanelMindThoughts->makeCaption(2, 4 + 25, 780, 80, "", Gorilla::TextAlign_Centre, Gorilla::VerticalAlign_Top);
	_LineThree = _Gui3DPanelMindThoughts->makeCaption(2, 4 + 50, 780, 80, "", Gorilla::TextAlign_Centre, Gorilla::VerticalAlign_Top);	

	//_UICaptionMindThoughts->setCaption(_MapMindThoughts["ESP"][0]->getThoughtText());
	_LineOne->text(_MindsData[0].mMind["ESP"][_ThougtId]->getThoughtText()[0]);
	_LineTwo->text(_MindsData[0].mMind["ESP"][_ThougtId]->getThoughtText()[1]);
	_LineThree->text(_MindsData[0].mMind["ESP"][_ThougtId]->getThoughtText()[2]);
}

bool MindManager::isFinishThoughts()
{
	return _FinishThoughts;
}