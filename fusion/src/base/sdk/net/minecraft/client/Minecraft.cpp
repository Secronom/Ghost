#include "Minecraft.h"
#include "../../../../java/java.h"
#include "../../../../util/logger.h"

#include "../entity/EntityLivingBase.h"

CMinecraft::CMinecraft()
{
	Java::AssignClass("net.minecraft.client.Minecraft", this->Class);

	this->MethodIDs["getMinecraft"] = Java::Env->GetStaticMethodID(this->GetClass(), "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
	this->Instance = Java::Env->CallStaticObjectMethod(this->GetClass(), this->MethodIDs["getMinecraft"]);

	this->FieldIDs["thePlayer"] = Java::Env->GetFieldID(this->GetClass(), "thePlayer", "Lnet/minecraft/client/entity/EntityPlayerSP;");
	this->thePlayer = new CEntityPlayerSP();

	this->FieldIDs["theWorld"] = Java::Env->GetFieldID(this->GetClass(), "theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;");
	this->theWorld = new CWorldClient();

	this->activeRenderInfo = new CActiveRenderInfo();

	this->FieldIDs["renderManager"] = Java::Env->GetFieldID(this->GetClass(), "renderManager", "Lnet/minecraft/client/renderer/entity/RenderManager;");
	this->renderManager = new CRenderManager();

	this->FieldIDs["timer"] = Java::Env->GetFieldID(this->GetClass(), "timer", "Lnet/minecraft/util/Timer;");
	this->timer = new CTimer();

	this->FieldIDs["gameSettings"] = Java::Env->GetFieldID(this->GetClass(), "gameSettings", "Lnet/minecraft/client/settings/GameSettings;");
	this->gameSettings = new CGameSettings();

	this->MethodIDs["getRenderViewEntity"] = Java::Env->GetMethodID(this->GetClass(), "getRenderViewEntity", "()Lnet/minecraft/entity/Entity;");
	this->FieldIDs["objectMouseOver"] = Java::Env->GetFieldID(this->GetClass(), "objectMouseOver", "Lnet/minecraft/util/MovingObjectPosition;");

	this->FieldIDs["currentScreen"] = Java::Env->GetFieldID(this->GetClass(), "currentScreen", "Lnet/minecraft/client/gui/GuiScreen;");

	// not used lol
	this->MethodIDs["clickMouse"] = Java::Env->GetMethodID(this->GetClass(), "clickMouse", "()V");
}

jclass CMinecraft::GetClass()
{
	return this->Class;
}

jobject CMinecraft::GetInstance()
{
	return this->Instance;
}

CEntity CMinecraft::GetRenderViewEntity()
{
	return CEntity(Java::Env->CallObjectMethod(this->GetInstance(), this->MethodIDs["getRenderViewEntity"]));
}

bool CMinecraft::IsInGuiState()
{
	jobject currentScreen = Java::Env->GetObjectField(this->GetInstance(), this->FieldIDs["currentScreen"]);

	//Checks if ANY GUI is open
	if (currentScreen != NULL)
	{
		return true; 
	}
	else
	{
		return false;
	}
}


void CMinecraft::ClickMouse()
{
	Java::Env->CallVoidMethod(this->GetInstance(), this->MethodIDs["clickMouse"]);
}

CMovingObjectPosition CMinecraft::GetMouseOver()
{
	return CMovingObjectPosition(Java::Env->GetObjectField(this->Instance, this->FieldIDs["objectMouseOver"]));
}

CEntityPlayerSP* CMinecraft::GetPlayer()
{
	// Retrieve the player instance from the Java field 'thePlayer'
	jobject playerObject = Java::Env->GetObjectField(this->GetInstance(), this->FieldIDs["thePlayer"]);

	if (playerObject == NULL)
	{
		return nullptr;
	}

	return new CEntityPlayerSP(playerObject);
}

void CMinecraft::ApplyPlayerVelocity(float velocityX, float velocityY, float velocityZ)
{
	// Retrieve the player instance using GetPlayer()
	CEntityPlayerSP* player = GetPlayer();
	if (player != nullptr)
	{
		// Apply the velocity to the player using the SetVelocity method
		player->SetVelocity(velocityX, velocityY, velocityZ);
	}
}












