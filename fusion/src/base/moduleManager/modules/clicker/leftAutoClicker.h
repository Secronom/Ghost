#pragma once
struct LeftAutoClicker
{
	inline static bool Enabled = false; //autoclicker enabled on injection?
	inline static float leftMaxCps = 16; //Default max
	inline static float leftMinCps = 12; //Default min
	inline static bool ignoreBlocks = true; //On by default
	inline static bool enableInAllGUIs = true; //On by default

	static void Update();
	static void RenderMenu();
};

