#include "menu.h"
#include "../util/logger.h"
#include "../../../ext/imgui/imgui.h"
#include "../../../ext/imgui/imgui_internal.h"
#include "../../../ext/imgui/imgui_impl_win32.h"
#include "../../../ext/imgui/imgui_impl_opengl2.h"

void Menu::Init()
{
	Menu::Title = "Misfit";
	Menu::Initialized = false;
	Menu::Open = false;
	Menu::Keybind = VK_OEM_1;


	Menu::PlaceHooks();
}

void Menu::ToggleButton(const char* format, bool* value)
{
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	float height = ImGui::GetFrameHeight() - 5;
	float width = height * 1.65f;
	float radius = height * 0.50f;

	if (ImGui::InvisibleButton(format, ImVec2(width, height)))
		*value = !*value;
	ImU32 col_circle;
	ImU32 col_bg;
	if (ImGui::IsItemHovered()) 
	{
		col_circle = *value ? IM_COL32(222, 222, 222, 255) : IM_COL32(230, 230, 230, 255);
		col_bg = *value ? IM_COL32(255, 0, 0, 255) : IM_COL32(255, 100, 100, 255);
	}
	else 
	{
		col_circle = *value ? IM_COL32(222, 222, 222, 255) : IM_COL32(60, 60, 60, 255);
		col_bg = *value ? IM_COL32(230, 0, 0, 255) : IM_COL32(255, 50, 50, 255);
	}

	float offsetX = 8;
	float offsetY = 3;

	draw_list->AddRectFilled(ImVec2(p.x + offsetX, p.y + offsetY), ImVec2(p.x + width + offsetX, p.y + height + offsetY), col_bg, height * 0.5f);
	draw_list->AddCircleFilled(ImVec2(*value ? (p.x + width - radius + offsetX) : (p.x + radius + offsetX), p.y + radius + offsetY), radius - 1.5f, col_circle);
}

bool Menu::TabButton(const char* format, ImVec4 color)
{
	ImGui::PushStyleColor(ImGuiCol_Button, color);
	bool result = ImGui::Button(format, ImVec2(100, 35));
	ImGui::PopStyleColor();
	return result;
}

void Menu::DoSliderStuff(int id, const char* text, float* bruh, float min, float max) {
	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);

	ImGui::PushID(id);
	ImGui::SetCursorPos(ImVec2(20, ImGui::GetCursorPosY() + 5));
	ImGui::Text(text);
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 230 - textSize.x - 20);

	// Push custom colors for slider
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));       //Light gray when not active
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f)); //Slightly lighter gray when hovered
	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));  //White when being dragged

	// Set custom colors for the grab bar (shows the previous value)
	ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.7f, 0.0f, 0.0f, 1.0f));    //Darker red for inactive
	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.9f, 0.0f, 0.0f, 1.0f)); //Brighter red for active

	ImGui::SliderFloat("", bruh, min, max);

	//Pop color styles (5 in total: 3 for the slider background and 2 for the grab colors)
	ImGui::PopStyleColor(5);

	ImGui::SameLine();
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3);
	ImGui::PopID();

	ImGui::PushID(id - 9);
	ImGui::InputFloat("", bruh);
	ImGui::PopStyleVar();
	ImGui::PopID();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5);
}

void Menu::DoToggleButtonStuff(int id, const char* text, bool* bruh) {
	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);

	ImGui::SetCursorPos(ImVec2(20, ImGui::GetCursorPosY() + 5));

	ImGui::PushID(id);
	ImGui::Text(text);
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 340 - textSize.x);
	Menu::ToggleButton(text, bruh);
	ImGui::PopID();
}

void Menu::GlitchText(const char* text, ImVec2 pos)
{
	// Red Glitch Text Shadow Thing
	ImVec2 pos_one = ImVec2(pos.x - (1 + (rand() % 3)), pos.y - (rand() % 2));
	ImGui::GetWindowDrawList()->AddText(Menu::FontBold, 38, pos_one, ImColor(235, 5, 90, 100 + (rand() % 60)), text);

	// Real Text
	ImGui::GetWindowDrawList()->AddText(Menu::FontBold, 38, pos, ImColor(255, 0, 0), text); // Changed to red
}

void Menu::Kill()
{
	Menu::Open = false;
	Menu::RemoveHooks();
	wglMakeCurrent(Menu::HandleDeviceContext, Menu::OriginalGLContext);
	wglDeleteContext(Menu::MenuGLContext);
	ImGui::DestroyContext();
}

void Menu::PlaceHooks()
{
	Menu::Hook_wglSwapBuffers();
	//Menu::Hook_tick();
}

void Menu::RemoveHooks()
{
	Menu::Unhook_wndProc();
	Menu::Unhook_wglSwapBuffers();
}
