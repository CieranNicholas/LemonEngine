#include <Lemon/Game/LemGame.h>
#include <iostream>
int main()
{
	try
	{
		LemGame game;
		game.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}