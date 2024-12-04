#pragma once
class LemWindow
{
public:
	LemWindow();
	~LemWindow();

	void makeCurrentContext();
	void present(bool vsync);
private:
	void* m_handle = nullptr;
	void* m_context = nullptr;
};

