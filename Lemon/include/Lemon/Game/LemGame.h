#pragma once

#include <memory>

class LemGraphicsEngine;
class LemWindow;

class LemGame
{
public:
	LemGame();
	~LemGame();

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	
	void run();
	void quit();

protected:
	bool m_isRunning{ true };
	std::unique_ptr<LemGraphicsEngine> m_graphicsEngine;
	std::unique_ptr<LemWindow> m_window;
};

