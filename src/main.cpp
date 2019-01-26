/*
 * main.cxx
 *
 */


#include <FL/Fl.H>
#include "interface.hpp"

int main(int argc, char **argv)
{
  Interface user_interface(800, 400, "nmrs-tool");
  user_interface.resizable(user_interface);
  user_interface.show();
  return(Fl::run());
}

