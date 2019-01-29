/*
 * interface.hpp
 *
 * Holds the GUI which consists of the top bar, side panel,
 * and the graph window. Top bar contains buttons to open and
 * analyze a new FID 'new', and an 'export' button to export
 * the graph as an image or the numerical results as a csv file.
 * Side panel contains the numerical results gathered from the
 * spectrogram. The graph window is an OpenGL context for drawing
 * and displaying the spectrogram.
 *
 */

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <FL/Fl_Window.H>

#include "analyzer.hpp"
#include "spectrumwin.hpp"
#include "numericwin.hpp"
#include "nmrmlparser.hpp"

struct Fl_Menu_Bar;

class Interface : public Fl_Window {
 public:
  Interface(int w, int h, const char* l);

 private:
  SpectrumWin spectrum_win_;
  NumericWin numeric_win_;
  Analyzer analyzer_;

  Fl_Menu_Bar *menu_bar_;
};

#endif // INTERFACE_HPP
