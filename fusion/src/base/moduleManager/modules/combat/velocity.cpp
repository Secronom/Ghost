#include "velocity.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"
#include "../../../sdk/sdk.h"
#include "../../../sdk/net/minecraft/client/Minecraft.h"
#include "../../../sdk/net/minecraft/entity/player/EntityPlayer.h"
#include "../../../../../src/base/util/logger.h"


void Velocity::Update()
{
    //If velocity isnt enabled, exit
    if (!Velocity::Enabled) return;

    // Check if the player has taken damage (this method needs to be implemented)
    if (Velocity::Enabled)
    {

        // Calculate the knockback multiplier based on the slider
        float knockbackMultiplier = Velocity::KnockbackPercent / 100.0f;

        // Retrieve the default knockback values (you might have to implement this)
        float velocityX = 0.1f;  // Placeholder for the default X knockback
        float velocityY = 0.1f;  // Placeholder for the default Y knockback
        float velocityZ = 0.1f;  // Placeholder for the default Z knockback

        // Apply the knockback reduction
        velocityX = velocityX * knockbackMultiplier;
        velocityY = velocityY * knockbackMultiplier;
        velocityZ = velocityZ * knockbackMultiplier;

        CMinecraft* minecraft = SDK::Minecraft;
        if (minecraft)
        {
            minecraft->ApplyPlayerVelocity(velocityX, velocityY, velocityZ);
        }
    }
}

void Velocity::RenderMenu()
{
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

    if (ImGui::BeginChild("velocity", ImVec2(425, 75)))
    {
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
        Menu::DoToggleButtonStuff(111222, "Toggle Velocity", &Velocity::Enabled);

        ImGui::Separator();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
        Menu::DoSliderStuff(222333, "KB Reduction Amount [0 = No KB]", &Velocity::KnockbackPercent, 0, 100);

    }
    ImGui::EndChild();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}
