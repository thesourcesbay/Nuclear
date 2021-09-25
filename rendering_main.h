#include "nuclear.cpp"

void drawRect(const FVector2D initial_pos, float w, float h, const FLinearColor color, float thickness = 1.f)
{
	K2_DrawLine(GCanvas, initial_pos, FVector2D(initial_pos.X + w, initial_pos.Y), thickness, color);
	K2_DrawLine(GCanvas, initial_pos, FVector2D(initial_pos.X, initial_pos.Y + h), thickness, color);
	K2_DrawLine(GCanvas, FVector2D(initial_pos.X + w, initial_pos.Y), FVector2D(initial_pos.X + w, initial_pos.Y + h), thickness, color);
	K2_DrawLine(GCanvas, FVector2D(initial_pos.X, initial_pos.Y + h), FVector2D(initial_pos.X + w, initial_pos.Y + h), thickness, color);
}

void drawFilledRect(const FVector2D& initial_pos, float w, float h, const FLinearColor& color)
{
	for (float i = 0.f; i < h; i += 1.f)
		K2_DrawLine(GCanvas, FVector2D(initial_pos.X, initial_pos.Y + i), FVector2D(initial_pos.X + w, initial_pos.Y + i), 1.f, color);
}

void K2_DrawBox(UObject* canvas, const struct FVector2D& ScreenPosition, const struct FVector2D& ScreenSize, float Thickness)
{
	static UFunction* fn = 0; if (!fn) fn = FindFunction(E("Function Engine.Canvas.K2_DrawBox"));

	struct
	{
		struct FVector2D               ScreenPosition;
		struct FVector2D               ScreenSize;
		float                          Thickness;
	} params;

	params.ScreenPosition = ScreenPosition;
	params.ScreenSize = ScreenSize;
	params.Thickness = Thickness;

	ProcessEvent(canvas, fn, &params);
}

void MwMenuDraw()
{
#define MENU_OUTLINE_THICC 2
	drawFilledRect(g_MenuInitialPos, g_MenuW - MENU_OUTLINE_THICC, g_MenuH - MENU_OUTLINE_THICC, SkeetMenuBg);
	MenuDrawTabs();
	MenuDrawItemsFor(g_MenuIndex);
	if (g_MX && g_MY)
	{
		K2_DrawBox(GCanvas, { (float)g_MX - 2, (float)g_MY - 1 }, { 4, 4 }, 4);
	}
}
