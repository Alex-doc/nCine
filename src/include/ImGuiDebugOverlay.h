#ifndef CLASS_NCINE_IMGUIDEBUGOVERLAY
#define CLASS_NCINE_IMGUIDEBUGOVERLAY

#include "IDebugOverlay.h"
#include <nctl/UniquePtr.h>
#include <nctl/String.h>

namespace ncine {

class AppConfiguration;
class IInputEventHandler;

/// Overlay debug ImGui interface
class ImGuiDebugOverlay : public IDebugOverlay
{
  public:
	ImGuiDebugOverlay(const AppConfiguration &appCfg);

	void update();
	void updateFrameTimings();

  private:
	const float Margin = 10.0f;
	const float Transparency = 0.5f;

	struct ValuesType
	{
		enum
		{
			FRAME_TIME = 0,
			FRAME_START,
			UPDATE_VISIT_DRAW,
			UPDATE,
			VISIT,
			DRAW,
			IMGUI,
			FRAME_END,
			CULLED_NODES,
			VBO_USED,
			IBO_USED,
			UBO_USED,
			SPRITE_VERTICES,
			MESHSPRITE_VERTICES,
			PARTICLE_VERTICES,
			TEXT_VERTICES,
			IMGUI_VERTICES,
			TOTAL_VERTICES,
#ifdef WITH_LUA
			LUA_USED,
			LUA_OPERATIONS,
#endif
			COUNT
		};
	};

	bool disableAppInputEvents_;
	IInputEventHandler *appInputHandler_;
	bool lockOverlayPositions_;
	bool showTopLeftOverlay_;
	bool showTopRightOverlay_;
	bool showBottomLeftOverlay_;
	bool showBottomRightOverlay_;

	unsigned int numValues_;
	nctl::UniquePtr<float[]> plotValues_[ValuesType::COUNT];
	float maxFrameTime_;
	float maxUpdateVisitDraw_;
	unsigned int index_;
	bool plotAdditionalFrameValues_;
	bool plotOverlayValues_;

	void guiWindow();
	void guiConfigureGui();
	void guiPreprocessorDefines();
	void guiVersionStrings();
	void guiInitTimes();
	void guiLog();
	void guiGraphicsCapabilities();
	void guiApplicationConfiguration();
	void guiRenderingSettings();
	void guiWindowSettings();
	void guiInputState();

	void guiTopLeft();
	void guiTopRight();
	void guiBottomLeft();
	void guiBottomRight();
	void guiPlots();

	void initPlotValues();
	void updateOverlayTimings();

	/// Deleted copy constructor
	ImGuiDebugOverlay(const ImGuiDebugOverlay &) = delete;
	/// Deleted assignment operator
	ImGuiDebugOverlay &operator=(const ImGuiDebugOverlay &) = delete;
};

}

#endif