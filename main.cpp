
#include <windows.h>
#include <iostream>
#include <string>

#include <fstream>
#include <sstream>
#include "basic_constructor.h"
#include <vector>
#include <glad/glad.h>
#include <GL/gl.h>


#define RESOLUTION_X 720
#define RESOLUTION_y 720


HDC   ghDC = NULL;
HGLRC ghRC = NULL;
GLuint shaderProgram = 0;
GLuint VBO = 0, VAO = 0;

RECT rect;

std::vector<float> vertices = {
        

        
        
    };



std::string parsefile(const char* filepath)
{
    
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filepath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();

}

GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed: " << infoLog << "\n";
    }
    return shader;
}

GLuint createShaderProgram(const char* vertexSrc, const char* fragmentSrc) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Program linking failed: " << infoLog << "\n";
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void debugger(std::string message)
{
    MessageBoxA(NULL, message.c_str(), "Info", MB_OK);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_LBUTTONDOWN: {
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);


            Circle createnew;
            createnew.posX = LOWORD(lParam);
            createnew.posY = HIWORD(lParam);
            createnew.scale = 1.0f;
            createnew.draw(vertices,rect);
            
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STREAM_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);


            //debugger(std::to_string( pt.x));
            break;
        }
        case WM_CREATE: {
            // Get device context
            ghDC = GetDC(hwnd);
            if (!ghDC) {
                debugger("GetDC failed");
                PostQuitMessage(0);
                return -1;
            }

            PIXELFORMATDESCRIPTOR pfd = {
                sizeof(PIXELFORMATDESCRIPTOR),
                1,
                PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
                PFD_TYPE_RGBA,
                32, // color bits
                0,0,0,0,0,0,
                0,
                0,
                0,
                0,0,0,0,
                16, // depth bits
                0,
                0,
                PFD_MAIN_PLANE,
                0,
                0,0,0
            };

            int pf = ChoosePixelFormat(ghDC, &pfd);
            if (pf == 0 || !SetPixelFormat(ghDC, pf, &pfd)) {
                debugger("SetPixelFormat failed");
                PostQuitMessage(0);
                return -1;
            }

            ghRC = wglCreateContext(ghDC);
            if (!ghRC) {
                debugger("wglCreateContext failed");
                PostQuitMessage(0);
                return -1;
            }

            if (!wglMakeCurrent(ghDC, ghRC)) {
                debugger("wglMakeCurrent failed");
                PostQuitMessage(0);
                return -1;
            }

            if (!gladLoadGL()) {
                debugger("Failed to initialize glad");
                PostQuitMessage(0);
                return -1;
            }

            // Setup viewport and background color
            
            GetClientRect(hwnd, &rect);
            glViewport(0, 0, rect.right, rect.bottom);
            glClearColor(0.1f, 0.125f, 0.173f, 1.0f);



            std::string vert = parsefile("triangleVert.glsl");
            std::string frag = parsefile("triangleFrag.glsl");

            shaderProgram = createShaderProgram(vert.c_str(), frag.c_str());    
            break;

        }

        case WM_PAINT: {
            // Drawing code goes here
            glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

            

            glClearColor(0.1f, 0.125f, 0.173f, 1.0f);
                
            

            SwapBuffers(ghDC); 
            break;
        }

        case WM_SIZE: {
            if (ghRC) {
                int width = LOWORD(lParam);
                int height = HIWORD(lParam);
                if (ghRC) {
                    glViewport(0, 0, width, height);
                }
                break;
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
    gladLoadGL();


    // createtriangle(
    //     0.4f, 0.4f, 0.0f,
    //     -0.4f, 0.4f, 0.0f,
    //     0.4f, -0.4f, 0.0f
    // );

    // createtriangle(
    //     0.4f, 0.4f, 0.0f,
    //     -0.4f, -0.4f, 0.0f,
    //     0.4f, -0.4f, 0.0f
    // );


    

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float)*2, vertices.data(), GL_STREAM_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    

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

        // Render
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()/2);
        glBindVertexArray(0);

        SwapBuffers(ghDC);

        Sleep(8);
    }


    return (int)msg.wParam;
}




int Update()
{
    
    return 1;
}


