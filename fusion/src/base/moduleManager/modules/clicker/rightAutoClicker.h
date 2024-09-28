#pragma once
struct RightAutoClicker
{
	inline static bool Enabled = false;

	inline static float rightMaxCps = 8; // Default max
	inline static float rightMinCps = 4; // Default min
	inline static bool blocksOnly = true;

	static void Update();
	static void RenderMenu();
};

