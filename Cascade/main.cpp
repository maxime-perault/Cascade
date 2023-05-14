
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>

struct structContext
{
    SDL_Window*     window;
    SDL_GLContext   gl_context;
    INT32           sucessFlag;
};

//---------------------------------------------------------------------------
static structContext SetupContext(void)
{
    structContext context{};
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("SDL_Init Fail: %s\n", SDL_GetError());
        context.sucessFlag = -1;
        return context;
    }

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    context.window = SDL_CreateWindow("Cascade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    context.gl_context = SDL_GL_CreateContext(context.window);
    SDL_GL_MakeCurrent(context.window, context.gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(context.window, context.gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    context.sucessFlag = 0;

    return context;
}

//---------------------------------------------------------------------------
static ImGuiIO& GetIO(void)
{
    ImGuiIO& io = ImGui::GetIO(); //(void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    return io;
}

//---------------------------------------------------------------------------
static void ManageEvent(const structContext& context, const ImGuiIO& io, const SDL_Event& event, bool& shouldQuit)
{
    shouldQuit = false;
    switch (event.type)
    {
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                {
                    shouldQuit = true;
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case SDL_QUIT:
        {
            shouldQuit = true;
            break;
        }
        default:
            break;
    }
    
    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && (event.window.windowID == SDL_GetWindowID(context.window)))
        shouldQuit = true;
}

//---------------------------------------------------------------------------
static void NewFrame(const ImGuiIO& io)
{
    ImGui_ImplSDL2_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(0.45f, 0.55f, 0.60f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

//---------------------------------------------------------------------------
static void DrawImGuiLayer(const ImGuiIO& io)
{
    ImGui::NewFrame();

    ImGui::Begin("Debug");
        ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

//---------------------------------------------------------------------------
static void SwapBuffers(const structContext& context)
{
    SDL_GL_SwapWindow(context.window);
}

//---------------------------------------------------------------------------
static void DestroyContexts(const structContext& context)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(context.gl_context);
    SDL_DestroyWindow(context.window);
    SDL_Quit();
}

//---------------------------------------------------------------------------
int main(int, char**)
{
    structContext context{};

    if ((context = SetupContext()).sucessFlag != 0)
    {
        return 0;
    }

    ImGuiIO&    io                  {GetIO()};
    bool        mustQuit            {};
    SDL_Event   event               {};

    while (!mustQuit)
    {
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);

            ManageEvent(context, io, event, mustQuit);
        }

        NewFrame(io);
        DrawImGuiLayer(io);
        SwapBuffers(context);
    }

    DestroyContexts(context);

    return 0;
}
