/*
 * interface.cpp
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

#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Window.H>
#include <iostream>

#include "interface.hpp"

using namespace std;

Interface::Interface(int w, int h, const char* l)
          : Fl_Window(w, h, l),
            spectrum_win_(0, 30, 600, 370, l),
            numeric_win_(603, 33, 194, 364)     {

  Fl_Menu_Item menu_items[] = {
   {"&File",  0, 0, 0, FL_SUBMENU},
    {"&Open", FL_COMMAND + 'o', nullptr},
    {"&Info", FL_COMMAND + 'i', nullptr},
    {"&Exit", FL_COMMAND + 'e', nullptr},
    {0},
   {"&Export",    0, 0, 0, FL_SUBMENU},
    {"&Spectrum (.png)", FL_COMMAND + 's', nullptr},
    {"&Numeric (.csv)",  FL_COMMAND + 'n', nullptr},
    {0},
   {"&Help",   0, 0, 0, FL_SUBMENU},
    {"&About", FL_COMMAND + 'a', nullptr},
    {0},
   {0}
  };

  menu_bar_ = new Fl_Menu_Bar(0, 0, w, 30);
  menu_bar_->copy(menu_items);

  cout << analyzer_.CreateFIDData() << endl;

  end();
}

