#ifndef Thought_H
#define Thought_H

class Thought
{
	public:		

		Thought(Ogre::int32 aThoughtId, const std::vector<Ogre::String> &aThoughtText, const Ogre::Real aTime);
		~Thought();		

		std::vector<Ogre::String> getThoughtText();
		Ogre::String			  getThoughtText(int aLine);
		Ogre::Real				  getThoughtTime();

	private:					
				
		Ogre::int32					_ThoughtId;
		std::vector<Ogre::String>	_ThoughtText;	
		Ogre::Real 					_ThoughtTime;
};

#endif