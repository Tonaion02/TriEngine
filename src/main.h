#ifndef CLASS_MYEVENTHANDLER
#define CLASS_MYEVENTHANDLER

#include "PrecompiledHeaders.h"

#include <ncine/IAppEventHandler.h>
#include <ncine/IInputEventHandler.h>

#include "StaticImage.h"
#include "Image.h"
#include "Animation/Animation.h"

#include "Renderer/DebugLayer.h"
#include "Renderer/Options.h"
#include "Renderer/Renderer.h"
#include "Renderer/Camera.h"
#include "Renderer/DebugLayer.h"

#include "Input/CoolDownCommand.h"
#include "Input/Input.h"

#include "world/Level.h"

#include "Menu/Menu.h"

#include "Player.h"

#include "ncine/MeshSprite.h"

#include "ncine/TextNode.h"

namespace ncine {

	class AppConfiguration;

}

namespace nc = ncine;

/// My nCine event handler
class MyEventHandler :
	public nc::IAppEventHandler,
	public nc::IInputEventHandler
{
public:
	void onInit() override;
	void onPreInit(nc::AppConfiguration &config) override;
	void onFrameStart() override;

	void onKeyPressed(const nc::KeyboardEvent &event) override;
	void onKeyReleased(const nc::KeyboardEvent &event) override;

	void onMouseButtonPressed(const nc::MouseEvent &event) override;
	void onMouseButtonReleased(const nc::MouseEvent& event) override;
	void onMouseMoved(const nc::MouseState &state) override;
	
	void logic();
	void draw();

private:
	std::string path;

	Level level;

	nctl::UniquePtr<nc::Texture> texture;
	Image im, im2;

	StaticAnimation animation;
	DinamicAnimation mAnimation;

	bool withDebugLayer=true;

	Menu menu;
	Page page;
	Button button;

	int idMouse;
	//nctl::UniquePtr<nc::Font> font;
	//nctl::UniquePtr<nc::TextNode> debugText;
	//nctl::String debugString;

	//DebugLayer debugLayer;
};

#endif

