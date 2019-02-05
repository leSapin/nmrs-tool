/*
 * spectrumwin.hpp
 *
 * FLTK OpenGL window for drawing the FID spectrum.
 *
 */

#ifndef SPECTRUM_WIN_HPP
#define SPECTRUM_WIN_HPP

#include <FL/Fl_Gl_Window.H>

struct Axes {
  int yaxis;
  int xaxis;

  float xvals[10];
  float yvals[10];
};

class SpectrumWin : public Fl_Gl_Window {
 public:
  SpectrumWin(int x, int y, int w, int h, const char *l);

  void InitGL();

  void SetView(float i);
  void SetSource(float* arr, int len);

 private:
  void draw();
  void resize(int x, int y, int w, int h);
  void FixViewport(int w, int h);

  bool   first_draw_;
  int    data_len_;
  float* data_src_;
};



#endif // SPECTRUM_WIN_HPP
