#pragma once

struct Velocity
{
    inline static bool Enabled = false;       // Whether anti-kb is enabled on injection
    inline static float KnockbackPercent = 0.0f;  // Control the percentage of knockback

    static void Update();
    static void RenderMenu();

};
