//multigrid.
#undef MMNOTIMER

#include <cstdlib>
#include <stdlib.h>
#include <windows.h>                    // Header File For Windows
#include <stdio.h>                      // Header File For Standard Input / Output
#include <stdarg.h>                     // Header File For Variable Argument Routines
#include <vector>
#include <gl\gl.h>
#include <gl\glu.h>
#include <string>

#include "window.hpp"
#include "object.hpp"
#include "enemy.hpp"
#include "pinwheel.hpp"
#include "diamond.hpp"
#include "greensquare.hpp"
#include "purplesquare.hpp"
#include "purplesquare2.hpp"
#include "blackhole.hpp"
#include "player.hpp"
#include "shot.hpp"
using namespace std;

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "winmm.lib")

HGLRC             hRC = NULL;
HDC               hDC = NULL;
HWND              hWnd = NULL;
HINSTANCE         hInstance;

char title [] = "MultiGrid";
bool keys[256];
bool active = true;
bool fullscreen = true;
bool alive = false;
double move_speed = .05;
int adjust = 7;                     // speed adjustment For slow video cards
int ct = 0;                         // ct is cpu cycle waste

Window window;

Player player1;
Player player2;

vector<Pinwheel> pinwheel_list;
vector<Pinwheel>::iterator pinwheel_iter;
vector<Diamond> diamond_list;
vector<Diamond>::iterator diamond_iter;
vector<GreenSquare> greensquare_list;
vector<GreenSquare>::iterator greensquare_iter;
vector<PurpleSquare> purplesquare_list;
vector<PurpleSquare>::iterator purplesquare_iter;
vector<PurpleSquare2> purplesquare2_list;
vector<PurpleSquare2>::iterator purplesquare2_iter;
vector<BlackHole> blackhole_list;
vector<BlackHole>::iterator blackhole_iter;

vector<Shot> shot_list;
vector<Shot>::iterator shot_iter;

// timer struct.
struct {
  __int64       frequency;                        // frequency
  float         resolution;                       // resolution
  unsigned long mm_timer_start;                   // multimedia timer start value
  unsigned long mm_timer_elapsed;                 // multimedia timer elapsed time
  bool          performance_timer;                // using the performance timer?
  __int64       performance_timer_start;          // performance timer start value
  __int64       performance_timer_elapsed;        // performance timer elapsed time
} timer;

int steps[11] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20 };          // stepping values for slow video adjustment

// initialize our timer
void TimerInit(void) {
  memset(&timer, 0, sizeof(timer)); // clear our timer structure

  // check to see if a performance counter is available
  // if one is available the timer frequency will be updated
  if (!QueryPerformanceFrequency((LARGE_INTEGER *) &timer.frequency)) {
    // no performace counter available
    timer.performance_timer = false;
    timer.mm_timer_start = timeGetTime();
    timer.resolution = 1.0f/1000.0f;
    timer.frequency = 1000;
    timer.mm_timer_elapsed  = timer.mm_timer_start;
  }
  else {
    // performance counter is available, use it instead of the multimedia timer
    // get the current time and store it in performance_timer_start
    QueryPerformanceCounter((LARGE_INTEGER *) &timer.performance_timer_start);
    timer.performance_timer = true;
    timer.resolution = (float) (((double)1.0f) / ((double)timer.frequency));
    timer.performance_timer_elapsed = timer.performance_timer_start;
  }
}

// time in milliseconds
float TimerGetTime() {
  __int64 time;

  if (timer.performance_timer) {
    QueryPerformanceCounter((LARGE_INTEGER *) &time);
    return ((float) (time - timer.performance_timer_start) * timer.resolution) * 1000.0f;
  }
  else {
    // Return The Current Time Minus The Start Time Multiplied By The Resolution And 1000 (To Get MS)
    return((float) (timeGetTime() - timer.mm_timer_start) * timer.resolution) * 1000.0f;
  }
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// resizes the window.
GLvoid ReSizeGLScene(GLsizei width, GLsizei height) {
  if (height == 0) {
    height = 1;
  }

  glViewport(0, 0, width, height);        // resize the window.

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //calculate aspect ratio of window.
  gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int InitGL() {
  glShadeModel(GL_SMOOTH);

  //screen clears black.
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  return true;
}

int DrawGLScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //draw grid.
    window.draw_grid();
    
    //draw player.
    player1.draw(window.get_x(),window.get_y());
    
    //draw shots if necessary.
    for (shot_iter = shot_list.begin(); shot_iter != shot_list.end(); shot_iter++) {
      if ((*shot_iter).on_screen(window.get_x(), window.get_y())) {
        (*shot_iter).draw(window.get_x(), window.get_y());
      }
    }    
    //draw pinwheel(s) if necessary.
    for (pinwheel_iter = pinwheel_list.begin(); pinwheel_iter != pinwheel_list.end(); pinwheel_iter++) {
      if ((*pinwheel_iter).on_screen(window.get_x(), window.get_y())) {
        (*pinwheel_iter).draw(window.get_x(), window.get_y());
      }
    }
    //draw diamond(s) if necessary.
    for (diamond_iter = diamond_list.begin(); diamond_iter != diamond_list.end(); diamond_iter++) {
      if ((*diamond_iter).on_screen(window.get_x(), window.get_y())) {
        (*diamond_iter).draw(window.get_x(), window.get_y());
      }
    }
    //draw green square(s) if necessary.
    for (greensquare_iter = greensquare_list.begin(); greensquare_iter != greensquare_list.end(); greensquare_iter++) {
      if ((*greensquare_iter).on_screen(window.get_x(), window.get_y())) {
        (*greensquare_iter).draw(window.get_x(), window.get_y());
      }
    }
    //draw purple square(s) if necessary.
    for (purplesquare_iter = purplesquare_list.begin(); purplesquare_iter != purplesquare_list.end(); purplesquare_iter++) {
      if ((*purplesquare_iter).on_screen(window.get_x(), window.get_y())) {
        (*purplesquare_iter).draw(window.get_x(), window.get_y());
      }
    }
    //draw small purple square(s) if necessary.
    for (purplesquare2_iter = purplesquare2_list.begin(); purplesquare2_iter != purplesquare2_list.end(); purplesquare2_iter++) {
      if ((*purplesquare2_iter).on_screen(window.get_x(), window.get_y())) {
        (*purplesquare2_iter).draw(window.get_x(), window.get_y());
      }
    }
    //draw black hole(s) if necessary.
    for (blackhole_iter = blackhole_list.begin(); blackhole_iter != blackhole_list.end(); blackhole_iter++) {
      if ((*blackhole_iter).on_screen(window.get_x(), window.get_y())) {
        (*blackhole_iter).draw(window.get_x(), window.get_y());
      }
    }

    //draw borders if necessary.
    window.draw_borders();
    
    return true;
}

GLvoid KillGLWindow() {
  if (fullscreen) {
    ChangeDisplaySettings(NULL,0);
    ShowCursor(true);
  }
  if(hRC) {
    if (!wglMakeCurrent(NULL,NULL)) {
      MessageBox(NULL,"Release of DC and RC failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
    }
    if (!wglDeleteContext(hRC)) {
      MessageBox(NULL,"Release Rendering Context failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
    }
    hRC = NULL;
  }
  if (hDC && !ReleaseDC(hWnd, hDC)) {
    MessageBox(NULL,"Release Device Context failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
    hDC = NULL;
  }
  if (hWnd && !DestroyWindow(hWnd)) {
    MessageBox(NULL,"Could not release hWnd.","SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
    hWnd = NULL;
  }
  if(!UnregisterClass("OpenGL",hInstance)) {
    MessageBox(NULL,"Could not unregister class.","SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
    hInstance = NULL;
  }
}

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag) {
  GLuint PixelFormat;
  WNDCLASS wc;
  DWORD dwExStyle;
  DWORD dwStyle;

  RECT WindowRect;
  WindowRect.left = (long) 0;
  WindowRect.right = (long) width;
  WindowRect.top = (long) 0;
  WindowRect.bottom = (long) height;

  fullscreen = fullscreenflag;

  hInstance = GetModuleHandle(NULL);
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = (WNDPROC) WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = "OpenGL";

  if (!RegisterClass(&wc)) {
    MessageBox(NULL,"Failed to register the window class.","ERROR",MB_OK | MB_ICONEXCLAMATION);
    return false;
  }
  if (fullscreen) {
    DEVMODE dmScreenSettings;
    memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
    dmScreenSettings.dmSize = sizeof(dmScreenSettings);
    dmScreenSettings.dmPelsWidth = width;
    dmScreenSettings.dmPelsHeight = height;
    dmScreenSettings.dmBitsPerPel = bits;
    dmScreenSettings.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

    if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
      if (MessageBox(NULL, "The requested fullscreen mode is not supported by \nyour video card. Use Windowed Mode instead?", "NeHe GL", MB_YESNO|MB_ICONEXCLAMATION) == IDYES) {
        fullscreen = false;
      }
      else {
        MessageBox(NULL, "Program will now close.", "ERROR", MB_OK|MB_ICONSTOP);
        return false;
      }
    }
  }
  if (fullscreen) {
    dwExStyle = WS_EX_APPWINDOW;
    dwStyle = WS_POPUP;
    ShowCursor(false);
  }
  else {
    dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    dwStyle = WS_OVERLAPPEDWINDOW;
  }
  AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);

  if (!(hWnd = CreateWindowEx(  dwExStyle,
                                "OpenGL",
                                title,
                                WS_CLIPSIBLINGS |
                                WS_CLIPCHILDREN |
                                dwStyle,
                                0,0,
                                WindowRect.right-WindowRect.left,
                                WindowRect.bottom-WindowRect.top,
                                NULL,
                                NULL,
                                hInstance,
                                NULL))) {
    KillGLWindow();
    MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
    return false;
  }
  static PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW |
    PFD_SUPPORT_OPENGL |
    PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,
    bits,
    0,0,0,0,0,0,
    0,
    0,
    0,
    0,0,0,0,
    16,
    0,
    0,
    PFD_MAIN_PLANE,
    0,
    0,0,0
  };
  if (!(hDC = GetDC(hWnd))) {
    KillGLWindow();
    MessageBox(NULL, "Can't create a GL devide context.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
    return false;
  }
  if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd))) {
    KillGLWindow();
    MessageBox(NULL, "Can't find a suitable pixel format.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
    return false;
  }
  if (!SetPixelFormat(hDC, PixelFormat, &pfd)) {
    KillGLWindow();
    MessageBox(NULL, "Can't set the pixel format.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
    return false;
  }
  if (!(hRC = wglCreateContext(hDC))) {
    KillGLWindow();
    MessageBox(NULL, "Can't create a GL rendering context.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
    return false;
  }
  if (!wglMakeCurrent(hDC, hRC)) {
    KillGLWindow();
    MessageBox(NULL, "Can't activate the GL rendering context.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
    return false;
  }
  ShowWindow(hWnd, SW_SHOW);
  SetForegroundWindow(hWnd);
  SetFocus(hWnd);
  ReSizeGLScene(width, height);
  if (!InitGL()) {
    KillGLWindow();
    MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
    return false;
  }
  return true;
}

LRESULT CALLBACK WndProc(HWND hWnd,
                         UINT uMsg,
                         WPARAM wParam,
                         LPARAM lParam) {
  switch (uMsg) {
    case WM_ACTIVATE: {
      if (!HIWORD(wParam)) {
        active = true;
      }
      else {
        active = false;
      }
      return 0;
    }
    case WM_SYSCOMMAND: {
      switch (wParam) {
        case SC_SCREENSAVE:
        case SC_MONITORPOWER:
          return 0;
      }
      break;
    }
    case WM_CLOSE: {
      PostQuitMessage(0);
      return 0;
    }
    case WM_KEYDOWN: {
      keys[wParam] = true;
      return 0;
    }
    case WM_KEYUP: {
      keys[wParam] = false;
      return 0;
    }
    case WM_SIZE: {
      ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));
      return 0;
    }
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void KillPlayer() {
  //player has died. kill all enemies, display death animation and recenter.
  player1.set_x(0.0);
  player1.set_y(0.0);
  player1.set_lives(player1.get_lives() - 1);

  //erase all enemies.
  pinwheel_list.clear();
  pinwheel_iter = pinwheel_list.begin();
  diamond_list.clear();
  diamond_iter = diamond_list.begin();
  greensquare_list.clear();
  greensquare_iter = greensquare_list.begin();
  purplesquare_list.clear();
  purplesquare_iter = purplesquare_list.begin();
  purplesquare2_list.clear();
  purplesquare2_iter = purplesquare2_list.begin();

  //indicate to main loop that we've died to allow us to enter that pocket.
  alive = false;
}

bool CheckSafeSpawn(float new_x, float new_y) {
  //checks if a given set of coordinates are safe to spawn at.    
  //check pinwheel locations.
  for (pinwheel_iter = pinwheel_list.begin(); pinwheel_iter != pinwheel_list.end(); pinwheel_iter++) {
    if ((fabs((*pinwheel_iter).get_x() - new_x) < 1) && (fabs((*pinwheel_iter).get_y() - new_y) < 1) ) {
      return false;
    }
  }
  //draw diamond(s) if necessary.
  for (diamond_iter = diamond_list.begin(); diamond_iter != diamond_list.end(); diamond_iter++) {
    if ((fabs((*diamond_iter).get_x() - new_x) < 1) && (fabs((*diamond_iter).get_y() - new_y) < 1) ) {
      return false;
    }
  }
  //draw green square(s) if necessary.
  for (greensquare_iter = greensquare_list.begin(); greensquare_iter != greensquare_list.end(); greensquare_iter++) {
    if ((fabs((*greensquare_iter).get_x() - new_x) < 1) && (fabs((*greensquare_iter).get_y() - new_y) < 1) ) {
      return false;
    }
  }
  //draw purple square(s) if necessary.
  for (purplesquare_iter = purplesquare_list.begin(); purplesquare_iter != purplesquare_list.end(); purplesquare_iter++) {
    if ((fabs((*purplesquare_iter).get_x() - new_x) < 1) && (fabs((*purplesquare_iter).get_y() - new_y) < 1) ) {
      return false;
    }
  }
  //draw small purple square(s) if necessary.
  for (purplesquare2_iter = purplesquare2_list.begin(); purplesquare2_iter != purplesquare2_list.end(); purplesquare2_iter++) {
    if ((fabs((*purplesquare2_iter).get_x() - new_x) < 1) && (fabs((*purplesquare2_iter).get_y() - new_y) < 1) ) {
      return false;
    }
  }
  //draw black hole(s) if necessary.
  for (blackhole_iter = blackhole_list.begin(); blackhole_iter != blackhole_list.end(); blackhole_iter++) {
    if ((fabs((*blackhole_iter).get_x() - new_x) < 1) && (fabs((*blackhole_iter).get_y() - new_y) < 1) ) {
      return false;
    }
  }

  //otherwise everything is fine.
  return true;
}

void SpawnPinwheels(int num_pinwheels) {
     //spawns a certain number of pinwheels at a safe distance from the player.
  for (int i = 0; i < num_pinwheels; i++) {
    Pinwheel pinwheel1(0.0, 0.0);
    pinwheel1.spawn(player1.get_x(), player1.get_y());
    pinwheel_list.push_back(pinwheel1);
  }
}
void SpawnDiamonds(int num_diamonds) {
     //spawns a certain number of diamonds at a safe distance from the player.
  for (int i = 0; i < num_diamonds; i++) {
    Diamond diamond1(0.0, 0.0, 0.0, 0.0);
    diamond1.spawn(player1.get_x(), player1.get_y());
    diamond_list.push_back(diamond1);
  }
}
void SpawnGreenSquares(int num_greensquares) {
     //spawns a certain number of green squares at a safe distance from the player.
  for (int i = 0; i < num_greensquares; i++) {
    GreenSquare greensquare1(0.0, 0.0, 0.0, 0.0);
    greensquare1.spawn(player1.get_x(), player1.get_y());
    greensquare_list.push_back(greensquare1);
  }
}
void SpawnPurpleSquares(int num_purplesquares) {
     //spawns a certain number of pinwheels at a safe distance from the player.
  for (int i = 0; i < num_purplesquares; i++) {
    PurpleSquare purplesquare1(0.0, 0.0, 0.0, 0.0);
    purplesquare1.spawn(player1.get_x(), player1.get_y());
    purplesquare_list.push_back(purplesquare1);
  }
}

int WINAPI WinMain( HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int nCmdShow) {
  //mode should be set to -1 to trigger opening animation
  int mode = -1;

  //multiplier is determined by score.
  double multiplier = 1.00, score = 0.00;
  MSG msg;
  bool done = false, alive = true, firstShot = false;

  SpawnPinwheels(3);
  SpawnDiamonds(3);
  SpawnGreenSquares(3);
  SpawnPurpleSquares(3);

  shot_iter = shot_list.begin();
  pinwheel_iter = pinwheel_list.begin();
  diamond_iter = diamond_list.begin();
  greensquare_iter = greensquare_list.begin();
  purplesquare_iter = purplesquare_list.begin();
  purplesquare2_iter = purplesquare2_list.begin();
  blackhole_iter = blackhole_list.begin();

  /*   assume not fullscreen for now.
  if (MessageBox(NULL,"Would you like to run in fullscreen mode?","Start Fullscreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
  {
      fullscreen=false;
  }
  */

  fullscreen = false;
  if (!CreateGLWindow(title, 640, 480, 16, fullscreen)) {
    return 0;
  }

  TimerInit();

  // main game loop.
  while (!done) {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT) {
        done = true;
      } else {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    } else {
      if (!alive && player1.get_lives() == 0) {
        //echo game over message.

        mode = 0;
      }

      float start = TimerGetTime();             // Grab Timer Value Before We Draw
      if ((active && !DrawGLScene()) || keys[VK_ESCAPE]) {
        done = true;
      } else {
        SwapBuffers(hDC);
      }

      switch (mode) {
        case -1 :
          //put intro animation here.

          mode = 0;
          break;
        case 0 :
          //put main menu here.

          //right now, just redirect to single player mode.
          mode = 1;
          break;
        case 1 :
          //single player start.
          while(TimerGetTime() < start + float(steps[adjust] * 2.0f)) {
             // Waste cycles On fast systems
          }
          ct++;
          if (ct % 30 == 0) {
            SpawnPinwheels(1);
          }
          if (ct % 60 == 0) {
            SpawnDiamonds(1);       
          }
          if (ct % 90 == 0) {
            SpawnGreenSquares(1);       
          }
          if (ct % 120 == 0) {
            SpawnPurpleSquares(1);       
          }

          // monitor player1 movement.
          if (keys[VK_UP] || keys[VK_DOWN] || keys[VK_LEFT] || keys[VK_RIGHT]) {
            player1.move( static_cast<int>(keys[VK_RIGHT]) - static_cast<int>(keys[VK_LEFT]), static_cast<int>(keys[VK_UP]) - static_cast<int>(keys[VK_DOWN]) );
          }

          // monitor shot keys.
          if (keys['W'] || keys['A'] || keys['S'] || keys['D']) {
            player1.shoot( static_cast<int>(keys['D']) - static_cast<int>(keys['A']), static_cast<int>(keys['W']) - static_cast<int>(keys['S']), 1 );
          }

          // increment shot timer.
          player1.set_shot_timer(player1.get_shot_timer() - 1);

          // recenter window if necessary.
          if ((window.get_x() < player1.get_x() && player1.get_x() <= 5.1) || (window.get_x() > player1.get_x() && player1.get_x() >= -5.1)) {
            window.set_x(player1.get_x());
          }
          if ((window.get_y() < player1.get_y() && player1.get_y() <= 5.1) || (window.get_y() > player1.get_y() && player1.get_y() >= -5.1)) {
            window.set_y(player1.get_y());
          }

          // move pinwheel(s) and check for death.
          for (pinwheel_iter = pinwheel_list.begin(); pinwheel_iter != pinwheel_list.end(); pinwheel_iter++) {
            (*pinwheel_iter).move(player1.get_x(), player1.get_y(), move_speed);
            if ( (*pinwheel_iter).check_collisions(player1.get_x(), player1.get_y()) ) {
              KillPlayer();
              break;
            }
          }
          // move diamond(s) and check for death.
          for (diamond_iter = diamond_list.begin(); diamond_iter != diamond_list.end(); diamond_iter++) {
            (*diamond_iter).move(player1.get_x(), player1.get_y(), move_speed);
            if ( (*diamond_iter).check_collisions(player1.get_x(), player1.get_y()) ) {
              KillPlayer();
              break;
            }
          }
          // move green square(s) and check for death.
          for (greensquare_iter = greensquare_list.begin(); greensquare_iter != greensquare_list.end(); greensquare_iter++) {
            (*greensquare_iter).move(player1.get_x(), player1.get_y(), move_speed);
            if ( (*greensquare_iter).check_collisions(player1.get_x(), player1.get_y()) ) {
              KillPlayer();
              break;
            }
          }
          // move purple square(s) and check for death.
          for (purplesquare_iter = purplesquare_list.begin(); purplesquare_iter != purplesquare_list.end(); purplesquare_iter++) {
            (*purplesquare_iter).move(player1.get_x(), player1.get_y(), move_speed);
            if ( (*purplesquare_iter).check_collisions(player1.get_x(), player1.get_y()) ) {
              KillPlayer();
              break;
            }
          }
          // move small purple square(s) and check for death.
          for (purplesquare2_iter = purplesquare2_list.begin(); purplesquare2_iter != purplesquare2_list.end(); purplesquare2_iter++) {
            (*purplesquare2_iter).move(player1.get_x(), player1.get_y(), move_speed);
            if ( (*purplesquare2_iter).check_collisions(player1.get_x(), player1.get_y()) ) {
                KillPlayer();
                break;
             }
          }
          // move black hole(s) and check for death.
          for (blackhole_iter = blackhole_list.begin(); blackhole_iter != blackhole_list.end(); blackhole_iter++) {
            (*blackhole_iter).move(move_speed);
            if ( (*blackhole_iter).check_collisions(player1.get_x(), player1.get_y()) ) {
              KillPlayer();
              break;
            }
          }

          // move shot(s).
          for (shot_iter = shot_list.begin(); shot_iter != shot_list.end();) {
            (*shot_iter).move(move_speed);
            if ((*shot_iter).check_collisions()) {
              shot_iter = shot_list.erase(shot_iter);     // we kill this shot because it has collided with something.
            } else if(shot_iter != shot_list.end()) {
              shot_iter++;
            }
          }
          break;
        case 2:
          // multiplayer.

          break;
        case 3:
          // high scores.
          break;
        case 4:
          // options.
          break;
        case 5:
          // exit.
          done = true;
          break;
        case 42:
          // game over message.
          break;
        default:
          // default animation.
          break;
      }
      // toggle fullscreen if necessary.
      if (keys[VK_F1]) {
        keys[VK_F1] = false;
        KillGLWindow();
        fullscreen = !fullscreen;
        if (!CreateGLWindow(title, 640, 480, 16, fullscreen)) {
          return 0;
        }
      }
    }
  }
  KillGLWindow();
  return (msg.wParam);
}