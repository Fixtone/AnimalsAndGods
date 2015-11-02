#ifndef IReactive_H
#define IReactive_H

#include "../../stdafx.h"

class IReactive
{
	public:

		virtual ~IReactive(){}
		virtual void hit(int aDamage) = 0;
};
#endif