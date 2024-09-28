#include "EntityPlayerSP.h"
#include "../../../../sdk.h"
#include "../../../../../java/java.h"
#include "../../../../../util/logger.h"
#include "X:\Code\Visual Studio\Projects\Ghost\fusion\src\base\moduleManager\modules\combat\velocity.h"
#include "../../entity/Entity.h"
#define PI 3.141592653589793238462643383279502884197


// Constructor for CEntityPlayerSP
CEntityPlayerSP::CEntityPlayerSP() : CEntityPlayer()
{
    // Assign the Java class for EntityPlayerSP
    Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", this->Class);
}

// Returns the Java class reference
jclass CEntityPlayerSP::GetClass()
{
    return this->Class;
}

// Returns the instance of the player (thePlayer)
jobject CEntityPlayerSP::GetInstance()
{
    // Retrieve the "thePlayer" field from Minecraft's instance
    jobject playerInstance = Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["thePlayer"]);
    this->Instance = playerInstance; // Store it in case it's needed later
    return playerInstance;
}

// Set velocity method (modify player's motionX, motionY, motionZ)
void CEntityPlayerSP::SetVelocity(float velocityX, float velocityY, float velocityZ)
{
    jobject player = this->GetInstance();
    if (player == nullptr)
    {
        return;
    }

    jclass playerClass = Java::Env->GetObjectClass(player);

    // Set motionX field
    jfieldID motionXField = Java::Env->GetFieldID(playerClass, "motionX", "D");
    if (motionXField != nullptr)
        Java::Env->SetDoubleField(player, motionXField, velocityX);

    // Set motionY field
    jfieldID motionYField = Java::Env->GetFieldID(playerClass, "motionY", "D");
    if (motionYField != nullptr)
        Java::Env->SetDoubleField(player, motionYField, velocityY);

    // Set motionZ field
    jfieldID motionZField = Java::Env->GetFieldID(playerClass, "motionZ", "D");
    if (motionZField != nullptr)
        Java::Env->SetDoubleField(player, motionZField, velocityZ);
}
