#include "moduleManager.h"

#include "modules/visual/esp.h"
#include "modules/combat/aimAssist.h"
#include "modules/combat/reach.h"
#include "modules/combat/velocity.h"
#include "modules/clicker/leftAutoClicker.h"
#include "modules/clicker/rightAutoClicker.h"
#include "commonData.h"

void ModuleManager::Init()
{
}

void ModuleManager::UpdateModules()
{
	if (!CommonData::SanityCheck()) return;

	CommonData::UpdateData();
	Esp::Update();

	Reach::Update();
	Velocity::Update();

	AimAssist::Update();

	LeftAutoClicker::Update();
	RightAutoClicker::Update();
}
