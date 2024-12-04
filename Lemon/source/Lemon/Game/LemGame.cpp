#include <Lemon/Game/LemGame.h>
#include <Lemon/Graphics/LemGraphicsEngine.h>
#include <Lemon/Window/LemWindow.h>
#include <Windows.h>

LemGame::LemGame()
{
	m_graphicsEngine = std::make_unique<LemGraphicsEngine>();
	m_window = std::make_unique<LemWindow>();

	m_window->makeCurrentContext();
}

LemGame::~LemGame()
{

}

void LemGame::onCreate()
{

}

void LemGame::onUpdate()
{
	m_graphicsEngine->clear(LemVec4(.5,0,.5, 1));

	m_window->present(false);
}

void LemGame::onDestroy()
{
}

void LemGame::quit()
{
	m_isRunning = false;
}
