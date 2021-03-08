#include "main.h"

#include <ncine/Application.h>
#include <ncine/AppConfiguration.h>

#include "world/Level.h"





nctl::UniquePtr<nc::IAppEventHandler> createAppEventHandler()
{
	return nctl::makeUnique<MyEventHandler>();
}

void MyEventHandler::onPreInit(nc::AppConfiguration &config)
{
#if defined(__ANDROID__)
	config.dataPath() = "asset::";
#elif defined(__EMSCRIPTEN__)
	config.dataPath() = "/";
#else
#ifdef PACKAGE_DEFAULT_DATA_DIR
	config.dataPath() = PACKAGE_DEFAULT_DATA_DIR;
#else
	config.dataPath() = "data/";
#endif
#endif

	config.resolution = nc::Vector2i(1500, 720);
	config.windowTitle = "TriEngine";
	config.windowIconFilename = "icon48.png";
	config.withVSync = true;

	GeneralOptions::s_generalOptions = new GeneralOptions();
	GeneralOptions::s_generalOptions->readFromFile("../triEngine-data/data/options.txt");
	GeneralOptions::setBaseFilePath("../triEngine-data/data/");
	GeneralOptions::setLevelFilePath(GeneralOptions::getBaseFilePath() + "levels/");
}





void MyEventHandler::onInit()
{
	Renderer::Renderer(2);
	Renderer::constructDebugLayer("../triEngine-data/data/fonts/OpenSans-Regular32_256.fnt", "../triEngine-data/data/fonts/OpenSans-Regular32_256.png");

	Player::Player("../triEngine-data/data/save0.txt");

	level = Level(GeneralOptions::getLevelFilePath() + "level0.txt",
		GeneralOptions::getTileWidht(), GeneralOptions::getTileHeight(),
		GeneralOptions::getLevelFilePath(), false);

	Camera::Camera(Player::getPosX(), Player::getPosY(), level.getMaxX() * GeneralOptions::getTileWidht(), level.getMaxY() * GeneralOptions::getTileHeight());

	animation = StaticAnimation({ "../triEngine-data/data/images/surfForBlit2.png" , "../triEngine-data/data/images/surfer.png" }, 3.0f, { 24, 456 }, 1);
	mAnimation = DinamicAnimation({ "../triEngine-data/data/images/surfForBlit2.png" , "../triEngine-data/data/images/surfer.png" }, 1.5f, { 24, 24 }, 1, 3.0f, { 48, 0 });

	Renderer::attachLayer();

	animation.start();
	mAnimation.start();

	im = Image(TextureLoader::getTexture("../triEngine-data/data/images/surfForBlit2.png"), Renderer::getLayer(1));

	Camera::updatePos(Player::getPosImage());

	Renderer::debugLayer.addDebugString("1");
	Renderer::debugLayer.addDebugString("item: ");
	Renderer::debugLayer.addDebugString("sliding: ");

	button = Button(0, { 200, 200 }, { 400, 400 }, TypeButton::Normal, "../triEngine-data/data/images/surfForBlit2.png");
	
	std::vector<Button> buttons;
	buttons.push_back(button);
	buttons.push_back(Button(0, { 500, 200 }, { 700, 400 }, TypeButton::Normal, "../triEngine-data/data/images/surfForBlit2.png"));

	page = Page(buttons, { 0, 0, 0, 255 }, { "../triEngine-data/data/images/alberodimerda.png" }, { {0,0} });
	menu = Menu("../triEngine-data/data/menu/menu0.txt");
}

void MyEventHandler::onFrameStart()
{
	Image::resetAllCondition();

	//EXPLORING

	if (Player::getStatusGame() == Player::StatusGame::exploring)
	{
		nc::theApplication().gfxDevice().setClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		Camera::RenderData renderData = Camera::renderingInfo();
		for (int i = 0; i < level.m_images.size(); i++)
		{
			level.m_images[i].draw(nc::theApplication().width() / 2, nc::theApplication().height() / 2, renderData.xI, renderData.yI, nc::theApplication().width(), nc::theApplication().height(), Renderer::getLayerFromH(i));
		}

		animation.animate();
		mAnimation.animate();

		if (Player::getStatusStaticAnimation() == Player::StatusStaticAnimation::collect)
		{
			Player::collecting();
		}
		if (Player::getStatusMoving() == Player::StatusMoving::moving)
		{
			Player::move();
			Camera::updatePos(Player::getPosImage());
		}
		if (Player::getStatusMoving() == Player::StatusMoving::stop && Player::getStatusStaticAnimation() == Player::StatusStaticAnimation::end)
		{
			if (Input::isPressed(nc::KeySym::W))
			{
				Player::updateDirection(Player::Direction::top);
				Player::startMove(level);
			}
			else if (Input::isPressed(nc::KeySym::S))
			{
				Player::updateDirection(Player::Direction::down);
				Player::startMove(level);
			}
			else if (Input::isPressed(nc::KeySym::A))
			{
				Player::updateDirection(Player::Direction::left);
				Player::startMove(level);
			}
			else if (Input::isPressed(nc::KeySym::D))
			{
				Player::updateDirection(Player::Direction::right);
				Player::startMove(level);
			}
			else if (Input::isPressed(nc::KeySym::B))
			{
				Player::tryToInteract(level);
			}
			else if (Input::isRealesed(nc::KeySym::P))
			{
				withDebugLayer = !withDebugLayer;
			}
			else if (Input::isRealesed(nc::KeySym::M))
			{
				Player::updateStatusGame(Player::StatusGame::menu);
			}
		}

		if (withDebugLayer)
		{
			Renderer::debugLayer.setDrawEnableTrue();
		}
		else
		{
			Renderer::debugLayer.setDrawEnableFalse();
		}

		nc::Vector2i pos = Camera::getCameraPosInProspective();
		pos.y += GeneralOptions::getTileHeight() / 2;
		Player::getImage().draw(pos, Renderer::getDinamicLayerFromH(2));

		animation.getImage().draw(Camera::getPosFromCamera(animation.getPos()), Renderer::getDinamicLayerFromH(animation.getH()));
		mAnimation.getImage().draw(Camera::getPosFromCamera(mAnimation.getPos()), Renderer::getDinamicLayerFromH(mAnimation.getH()));

		Renderer::debugLayer.setDebugString(("x: " + std::to_string(Input::getMousePos().x) + " y: " + std::to_string(Input::getMousePos().y)).c_str(), 0);
		//Renderer::debugLayer.setDebugString(("x: " + std::to_string(Player::getPosImage().x) + " y: " + std::to_string(Player::getPosImage().y)).c_str(), 0);
	}

	else if (Player::getStatusGame() == Player::StatusGame::menu)
	{
		nc::theApplication().gfxDevice().setClearColor(0.1f, 0.1f, 0.6f, 1.0f);

		Renderer::debugLayer.setDebugString("we", 2);

		if (Input::isPressed(Input::KeyMouse::leftKey))
		{
			Renderer::debugLayer.setDebugString("wewe", 2);
			//if (button.isInAreaButton(Input::getMousePos()))
			//{
			//	idMouse = !((bool)idMouse);
			//}
			if (menu.m_pages[menu.getIndexCurrentPage()].isButtonPressed())
			{
				switch (menu.m_pages[menu.getIndexCurrentPage()].getLastButtonPressed().getTypeButton())
				{
				case TypeButton::Normal:
					switch (menu.m_pages[menu.getIndexCurrentPage()].getLastButtonPressed().getIdButton())
					{
					case 0:
						idMouse = 1;
						break;

					case 1:
						idMouse = 2;
						break;
					}
				break;

				case TypeButton::MoveableButton:
					//nc::Vector2i sliding = Input::getMouseSliding();
					menu.m_pages[menu.getIndexCurrentPage()].getLastButtonPressed().moveX(Input::getMouseSliding().x);
					menu.m_pages[menu.getIndexCurrentPage()].getLastButtonPressed().moveY(Input::getMouseSliding().y);
				break;
				}
			}
		}

		menu.m_pages[menu.getIndexCurrentPage()].draw();

		Renderer::debugLayer.setDebugString(("x: " + std::to_string(Input::getMousePos().x) + " y: " + std::to_string(Input::getMousePos().y)).c_str(), 0);
		Renderer::debugLayer.setDebugString("mouseState: " + std::to_string(idMouse), 1);
		//Renderer::debugLayer.setDebugString("slidingX: " + std::to_string(Input::getMouseSliding().x) + "slidingY: " + std::to_string(Input::getMouseSliding().y), 2);
	}

	Input::clearReleasedKey();
	Input::clearMouseEvent();
}





void MyEventHandler::logic()
{

}

void MyEventHandler::draw()
{

}





void MyEventHandler::onKeyReleased(const nc::KeyboardEvent &event)
{
	Input::deleteEvent(event);
}

void MyEventHandler::onKeyPressed(const nc::KeyboardEvent &event)
{
	Input::saveEvent(event);
}

void MyEventHandler::onMouseButtonPressed(const nc::MouseEvent &event)
{
	Input::saveEvent(event);
}

void MyEventHandler::onMouseButtonReleased(const nc::MouseEvent& event)
{
	Input::deleteEvent(event);
}

void MyEventHandler::onMouseMoved(const nc::MouseState &state)
{
	Input::updateMousePos(state);
}