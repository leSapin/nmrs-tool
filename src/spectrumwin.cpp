/*
 * spectrumwin.cpp
 *
 * FLTK OpenGL window for drawing the FID spectrum.
 *
 */

#include "spectrumwin.hpp"
#include <FL/gl.h>

SpectrumWin::SpectrumWin(int x, int y, int w, int h, const char *l)
            :Fl_Gl_Window(x, y, w, h, l) {
  end();
}

void SpectrumWin::FixViewport(int w, int h) {
  glLoadIdentity();
  glViewport(0, 0, w, h);
  glOrtho(-w, w, -h, h, -1, 1);
}

void SpectrumWin::draw() {
  if (!valid()) {
    valid(1);
    FixViewport(w(), h());
  }

  glClearColor(100, 200, 300, 0.5);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(50, 50, 50);

  glBegin(GL_LINE_STRIP);
  glVertex2f(w(), h());
  glVertex2f(-w(),-h());
  glEnd();

  glBegin(GL_LINE_STRIP);
  glVertex2f(w(),-h());
  glVertex2f(-w(), h());
  glEnd();
}

void SpectrumWin::resize(int x, int y, int w, int h) {
  Fl_Gl_Window::resize(x, y, w, h);
  FixViewport(w, h);
  redraw();
}
