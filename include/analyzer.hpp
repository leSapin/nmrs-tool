/*
 * analyzer.hpp
 *
 * Performs fourier transform and numerical
 * analysis on the FID data.
 *
 */

#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include "fiddecoder.hpp"

class Analyzer {
 public:
  Analyzer();

  bool CreateFIDData();

  void FourierTransform();
  void DoNumericAnalysis();

 private:
  FIDDecoder    fid_decoder_;
  DataContainer fid_data_;
};

#endif // ANALYZER_HPP
