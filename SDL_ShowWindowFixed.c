/*
    This is a modified version of SDL_ShowWindow() which has a workaround for a bug introduced with Windows 7 up through
    Windows 11 where ShowWindow() shows a white window initially, regardless of what color it was set to previously.

    See the research and workarounds here:
	https://stackoverflow.com/questions/69715610/how-to-initialize-the-background-color-of-win32-app-to-something-other-than-whit

    This code uses Ralf's solution from that thread which works quite well.

    First, you'll need to call this code before calling SDL_ShowWindowFixed():

    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(window, &wmInfo);

    After that you can use SDL_ShowWindowFixed() anywhere you'd use SDL_ShowWindow().
*/

// Modified version of WIN_ShowWindow() in SDL_windowswindow.c
void SDL_ShowWindowFixed(SDL_Window *window)
{
    HWND hwnd = wmInfo.info.win.window;
    DWORD style;
    int nCmdShow = nCmdShow = SDL_GetHintBoolean("SDL_WINDOW_NO_ACTIVATION_WHEN_SHOWN", SDL_FALSE) ? SW_SHOWNA : SW_SHOW;
    style = GetWindowLong(hwnd, GWL_EXSTYLE);
    if (style & WS_EX_NOACTIVATE) {
        nCmdShow = SW_SHOWNOACTIVATE;
    }

    SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW);
    RedrawWindow(hwnd, NULL, 0, RDW_INVALIDATE |  RDW_ERASE);    

    ShowWindow(hwnd, nCmdShow);    
}
