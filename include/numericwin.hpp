/*
 * numericwin.hpp
 *
 * NumericWin displays the numeric results
 * of the spectrum analysis.
 *
 */

#ifndef NUMERIC_WIN_HPP
#define NUMERIC_WIN_HPP

struct Fl_Text_Buffer;
struct Fl_Text_Display;

class NumericWin{
 public:
  NumericWin(int x, int y, int w, int h);

 private:
  Fl_Text_Buffer *buff;
  Fl_Text_Display *disp;
};

#endif // NUMERIC_WIN_HPP
