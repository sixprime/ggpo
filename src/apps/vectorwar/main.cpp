#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#if defined(_DEBUG)
#   include <crtdbg.h>
#endif
#include "vectorwar.h"
#include "ggpo_perfmon.h"

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_ERASEBKGND:
        return 1;
    case WM_KEYDOWN:
        if (wParam == 'P')
        {
            ggpoutil_perfmon_toggle();
        }
        else if (wParam == VK_ESCAPE)
        {
            VectorWar_Exit();
            PostQuitMessage(0);
        }
        else if (wParam >= VK_F1 && wParam <= VK_F12)
        {
            VectorWar_DisconnectPlayer((int)(wParam - VK_F1));
        }
        return 0;
    case WM_PAINT:
        VectorWar_DrawCurrentFrame();
        ValidateRect(hwnd, NULL);
        return 0;
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    }
    return CallWindowProc(DefWindowProc, hwnd, uMsg, wParam, lParam);
}

HWND CreateMainWindow(HINSTANCE hInstance, int player_id)
{
    HWND hwnd;
    WNDCLASSEX wndclass = { 0 };
    RECT rc;
    int width = 640, height = 480;
    WCHAR titlebuf[128];

    wsprintf(titlebuf, L"(pid:%d) ggpo sdk sample: vector war [player %d]", GetProcessID(), player_id);
    wndclass.cbSize = sizeof(wndclass);
    wndclass.lpfnWndProc = MainWindowProc;
    wndclass.lpszClassName = L"vwwnd";
    RegisterClassEx(&wndclass);
    hwnd = CreateWindow(L"vwwnd",
        titlebuf,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        NULL, NULL, hInstance, NULL);

    GetClientRect(hwnd, &rc);
    SetWindowPos(hwnd, NULL, 0, 0, width + (width - (rc.right - rc.left)), height + (height - (rc.bottom - rc.top)), SWP_NOMOVE);
    return hwnd;
}

void
RunMainLoop(HWND hwnd)
{
    MSG msg = { 0 };
    uint32_t start, next, now;

    start = next = now = GetCurrentTimeMS();
    while (1)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
            {
                return;
            }
        }
        now = GetCurrentTimeMS();
        VectorWar_Idle(max(0, next - now - 1));
        if (now >= next)
        {
            VectorWar_RunFrame(hwnd);
            next = now + (1000 / 60);
        }
    }
}

void
Syntax()
{
    MessageBox(NULL,
        L"Syntax: vectorwar.exe <relay_ip> <num_players> <base_port> <player_position[1..num_players]>)*\n",
        L"Could not start", MB_OK);
}

//int main()
//{
//    return wWinMain(GetModuleHandle(NULL), NULL, GetCommandLine(), SW_SHOWNORMAL);
//}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
    int offset = 1;
    WSADATA wd = { 0 };

    WSAStartup(MAKEWORD(2, 2), &wd);
    POINT window_offsets[] = {
       { 64,  64 },   // player 1
       { 740, 64 },   // player 2
       { 64,  600 },  // player 3
       { 740, 600 },  // player 4
    };

#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    if (__argc != 4) {
        Syntax();
        return 1;
    }

    // before :  VectorWar.exe 7000 3 127.0.0.1:7001 local 127.0.0.1:7003
    // after :   VectorWar.exe 127.0.0.1:56789 3 2
    // TODO(amp) : spectator mode

    // relay ip and port
    char buffer[64] = { 0 };
    wcstombs(buffer, __wargv[offset++], ARRAY_SIZE(buffer) - 1);
    //memcpy(buffer, __argv[offset++], ARRAY_SIZE(buffer) - 1);
    char relay_ip[32] = { 0 };
    unsigned short relay_port = 0;
    sscanf(buffer, "%[^:]:%hd", relay_ip, &relay_port);

    // num_players
    int num_players = _wtoi(__wargv[offset++]);
    //int num_players = atoi(__argv[offset++]);

    // player_position
    int player_position = _wtoi(__wargv[offset++]);
    //int player_position = atoi(__argv[offset++]);

    GGPOPlayer players[GGPO_MAX_PLAYERS];
    for (int i = 0; i < num_players; ++i)
    {
        players[i].size = sizeof(players[i]);
        players[i].player_num = i + 1;
        players[i].type = players[i].player_num == player_position ? GGPO_PLAYERTYPE_LOCAL : GGPO_PLAYERTYPE_REMOTE;
    }

    HWND hwnd = CreateMainWindow(hInstance, player_position);

    int local_player = player_position - 1;
    if (local_player < sizeof(window_offsets) / sizeof(window_offsets[0])) {
        ::SetWindowPos(hwnd, NULL, window_offsets[local_player].x, window_offsets[local_player].y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }

    int num_spectators = 0;
    VectorWar_Init(hwnd, relay_ip, relay_port, (unsigned short)player_position, num_players, players, num_spectators);

    RunMainLoop(hwnd);
    VectorWar_Exit();
    WSACleanup();
    DestroyWindow(hwnd);
    return 0;
}
