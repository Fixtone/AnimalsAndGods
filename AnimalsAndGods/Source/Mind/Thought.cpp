#include "stdafx.h"
#include "..\..\Header\Mind\Thought.h"

Thought::Thought(Ogre::int32 aThoughtId, const std::vector<Ogre::String> &aThoughtText, const Ogre::Real aTime)
: _ThoughtId(aThoughtId)
, _ThoughtText(aThoughtText)
, _ThoughtTime(aTime)
{
}

Thought::~Thought()
{
}

std::vector<Ogre::String> Thought::getThoughtText()
{
	return _ThoughtText;
}

Ogre::String Thought::getThoughtText(int aLine)
{
	return _ThoughtText[aLine];
}

Ogre::Real Thought::getThoughtTime()
{
	return _ThoughtTime;
}