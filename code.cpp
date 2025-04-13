#include <windows.h>
#include <tchar.h> // For Unicode support

// Window Procedure function declaration
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Define the window class
    const TCHAR CLASS_NAME[] = _T("HelloWorldWindowClass");

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    // Register the window class
    if (!RegisterClass(&wc)) {
        MessageBox(NULL, _T("Failed to register window class!"), _T("Error"), MB_ICONERROR);
        return 0;
    }

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles
        CLASS_NAME,                     // Window class
        _T("Hello World!"),             // Window title
        WS_OVERLAPPEDWINDOW,            // Window style
        CW_USEDEFAULT, CW_USEDEFAULT,   // Position
        500, 300,                       // Size
        NULL,                           // Parent window
        NULL,                           // Menu
        hInstance,                      // Instance handle
        NULL                            // Additional application data
    );

    if (hwnd == NULL) {
        MessageBox(NULL, _T("Failed to create window!"), _T("Error"), MB_ICONERROR);
        return 0;
    }

    // Show the window
    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Window Procedure function definition
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Draw "Hello World!" text
        const TCHAR* text = _T("Hello World!");
        TextOut(hdc, 50, 50, text, _tcslen(text));

        EndPaint(hwnd, &ps);
        return 0; // Ensure a return value
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
