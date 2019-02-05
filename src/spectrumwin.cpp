/*
 * spectrumwin.cpp
 *
 * FLTK OpenGL window for drawing the FID spectrum.
 *
 */

#include <FL/gl.h>
#include <FL/glu.h>

#include "spectrumwin.hpp"

SpectrumWin::SpectrumWin(int x, int y, int w, int h, const char *l)
            : Fl_Gl_Window(x, y, w, h, l) {
  mode(FL_RGB | FL_ALPHA | FL_DEPTH | FL_DOUBLE);
  first_draw_ = true;
  data_src_   = nullptr;
}

void SpectrumWin::SetView(float i) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 10, 0, 10, 1, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 0, 5, 0, 0, 0, 0, 1.0f, 0);
}

void SpectrumWin::draw() {
  if (first_draw_) {
    first_draw_ = false;
    InitGL();
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  SetView(0.5f);

   glBegin(GL_QUADS);
      // front
      glColor3f(1, 0, 0);
      glVertex3f(-1, 1, 1);
      glVertex3f(-1, -1, 1);
      glVertex3f(1, -1, 1);
      glVertex3f(1, 1, 1);

      // back
      glColor3f(0, 1, 0);
      glVertex3f(-1, 1, -1);
      glVertex3f(1, 1, -1);
      glVertex3f(1, -1, -1);
      glVertex3f(-1, -1, -1);

      // top
      glColor3f(0, 0, 1);
      glVertex3f(-1, 1, -1);
      glVertex3f(-1, 1, 1);
      glVertex3f(1, 1, 1);
      glVertex3f(1, 1, -1);

      // bottom
      glColor3f(1, 1, 0);
      glVertex3f(-1, -1, -1);
      glVertex3f(1, -1, -1);
      glVertex3f(1, -1, 1);
      glVertex3f(-1, -1, 1);

      // left
      glColor3f(0, 1, 1);
      glVertex3f(-1, 1, -1);
      glVertex3f(-1, -1, -1);
      glVertex3f(-1, -1, 1);
      glVertex3f(-1, 1, 1);

      // right
      glColor3f(1, 0, 1);
      glVertex3f(1, 1, 1);
      glVertex3f(1, -1, 1);
      glVertex3f(1, -1, -1);
      glVertex3f(1, 1, -1);
   glEnd();
}

void SpectrumWin::resize(int x, int y, int w, int h) {
  Fl_Gl_Window::resize(x, y, w, h);
  redraw();
}

void SpectrumWin::InitGL() {
  glClearColor(.175f, .616f, .645f, 0.5f);
  glColor3f(50, 50, 50);
  glEnable(GL_DEPTH_TEST);
}
