#include <Lemon/Game/LemGame.h>
#include <Windows.h>

void LemGame::run()
{
    onCreate();
    while (m_isRunning)
    {
        MSG msg = {};
        if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                m_isRunning = false;
                continue;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        onUpdate();
        Sleep(1);
    }

    onDestroy();
}