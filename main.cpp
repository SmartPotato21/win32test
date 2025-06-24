#include <GL/gl.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include "basic_constructor.h"
#include <vector>

#define RESOLUTION_X 720
#define RESOLUTION_y 720


HDC   ghDC = NULL;
HGLRC ghRC = NULL;


void debugger(std::string message)
{
    MessageBoxA(NULL, message.c_str(), "Info", MB_OK);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            // Get device context
            ghDC = GetDC(hwnd);

            // Set up pixel format for OpenGL
            PIXELFORMATDESCRIPTOR pfd = {
                sizeof(PIXELFORMATDESCRIPTOR),
                1,                                // Version Number
                PFD_DRAW_TO_WINDOW |              // Format Must Support Window
                PFD_SUPPORT_OPENGL |              // Format Must Support OpenGL
                PFD_DOUBLEBUFFER,                 // Must Support Double Buffering
                PFD_TYPE_RGBA,                    // Request An RGBA Format
                32,                               // Select Our Color Depth
                0, 0, 0, 0, 0, 0,                  // Color Bits Ignored
                0,                                // No Alpha Buffer
                0,                                // Shift Bit Ignored
                0,                                // No Accumulation Buffer
                0, 0, 0, 0,                       // Accumulation Bits Ignored
                16,                               // 16Bit Z-Buffer (Depth Buffer)
                0,                                // No Stencil Buffer
                0,                                // No Aux Buffer
                PFD_MAIN_PLANE,                   // Main[] Drawing Layer
                0,                                // Reserved
                0, 0, 0                           // Layer Masks Ignored
            };

            int pixelFormat = ChoosePixelFormat(ghDC, &pfd);
            if (pixelFormat == 0) {
                debugger("ChoosePixelFormat failed!");
                PostQuitMessage(0);
                return -1;
            }

            if (!SetPixelFormat(ghDC, pixelFormat, &pfd)) {
                debugger("SetPixelFormat failed!");
                PostQuitMessage(0);
                return -1;
            }

            // Create and make current the rendering context
            ghRC = wglCreateContext(ghDC);
            if (!ghRC) {
                debugger("wglCreateContext failed!");
                PostQuitMessage(0);
                return -1;
            }

            if (!wglMakeCurrent(ghDC, ghRC)) {
                debugger("wglMakeCurrent failed!");
                PostQuitMessage(0);
                return -1;
            }

            // Set up basic OpenGL view
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, 800, 600, 0, 1, -1); // Orthographic projection (0,0 top-left)
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glViewport(0, 0, 800, 600); // Set viewport to window size
            glClearColor(0.102f, 0.125f, 0.173f, 1.0f); // Set background color 

            break;
        }

        case WM_PAINT: {
            // Drawing code goes here
            glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

            

            
                
            glEnd();

            SwapBuffers(ghDC); 
            break;
        }

        case WM_SIZE: {
            if (ghRC) {
                glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glOrtho(0, LOWORD(lParam), HIWORD(lParam), 0, 1, -1);
                glMatrixMode(GL_MODELVIEW);
            }
            break;
        }

        case WM_DESTROY:
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(ghRC);
            ReleaseDC(hwnd, ghDC);
            PostQuitMessage(0);
            return 0;
        }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


HWND windowCreate(HINSTANCE hInstance, int nCmdShow) {
    const char CLASS_NAME[] = "MyWindowClass";

    WNDCLASSA wc = {};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    //wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

    if (!RegisterClassA(&wc)) {
        debugger("Failed to register window class!");
        return nullptr;
    }

    HWND hwnd = CreateWindowExA(
        0,
        CLASS_NAME,
        "OpenGL Rectangle",
        WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, RESOLUTION_X, RESOLUTION_y,
        nullptr, nullptr, hInstance, nullptr
    );

    if (hwnd == nullptr) {
        debugger("Failed to create window!");
        return nullptr;
    }

    ShowWindow(hwnd, nCmdShow);
    //UpdateWindow(hwnd);

    return hwnd;
}
using namespace std;

template<class T>
string toString(const T &value) {
    ostringstream os;
    os << value;
    return os.str();
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {

    HWND hwnd = windowCreate(hInst, nCmdShow);

    if (hwnd == nullptr) {
        return -1;
    }

    MSG msg = {};
    bool running = true;

    vector<Box> boxes;
    

    while (running) 
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
        {
            if (msg.message == WM_QUIT) {
                running = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // UPDATE LOGIC
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);
            Box mybox(1);
            mybox.scale = 0.1f;
            mybox.posX = (float)pt.x;
            mybox.posY = (float)pt.y;
            boxes.push_back(mybox);
        }

        // RENDER
        glClear(GL_COLOR_BUFFER_BIT);
        //debugger(toString(objs.size()));
        for(Box obj : boxes){
            obj.draw();
        }

                     // <--- This is the dynamic render
        SwapBuffers(ghDC);

        Sleep(8); // ~120 FPS
    }

    return (int)msg.wParam;
}


int Update()
{
    
    return 1;
}
