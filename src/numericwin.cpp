/*
 * numericwin.cpp
 *
 * NumericWin displays the numeric results
 * of the spectrum analysis.
 *
 */

#include "numericwin.hpp"
#include <FL/Fl_Text_Display.H>

NumericWin::NumericWin(int x, int y, int w, int h) {

  buff = new Fl_Text_Buffer();
  disp = new Fl_Text_Display(x, y, w, h);
  disp->buffer(buff);
  buff->text("asdasd sad adsa sd asd \n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n \
  asda sdas asd asd as\n ");
  disp->color(FL_GRAY);
}


