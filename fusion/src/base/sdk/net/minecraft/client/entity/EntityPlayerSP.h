#pragma once
#include "../../entity/player/EntityPlayer.h"

struct CEntityPlayerSP : CEntityPlayer
{
	CEntityPlayerSP();

	jclass GetClass();
	jobject GetInstance();
	jobject playerObject; // Store the jobject for future use

	// Constructor that accepts a jobject
	CEntityPlayerSP(jobject obj)
	{
		this->playerObject = obj;
	}

	void SetVelocity(float velocityX, float velocityY, float velocityZ);

};