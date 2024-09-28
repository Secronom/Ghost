#pragma once

#include "../EntityLivingBase.h"
#include "InventoryPlayer.h"
#include "../../../../strayCache.h"

struct CEntityPlayer : CEntityLivingBase
{
	CEntityPlayer();
	CEntityPlayer(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	CInventoryPlayer GetInventory();
};

