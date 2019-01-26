/*
 * spectrumwin.hpp
 *
 * FLTK OpenGL window for drawing the FID spectrum.
 *
 */

#ifndef SPECTRUM_WIN_HPP
#define SPECTRUM_WIN_HPP

#include <FL/Fl_Gl_Window.H>

class SpectrumWin : public Fl_Gl_Window {
 public:
  SpectrumWin(int x, int y, int w, int h, const char *l);

 private:
  void draw();                             // FLTK callback
  void resize(int x, int y, int w, int h); // FLTK callback
  void FixViewport(int w, int h);
};



#endif // SPECTRUM_WIN_HPP
