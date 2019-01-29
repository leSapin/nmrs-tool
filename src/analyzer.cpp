/*
 * analyzer.hpp
 *
 * Performs fourier transform and numerical
 * analysis on the FID data.
 *
 */

#include "analyzer.hpp"
#include <fstream>

Analyzer::Analyzer() : fid_decoder_() {}

bool Analyzer::CreateFIDData() {
  fid_decoder_.SetFIDPath("/home/rob/Code/nmrs-tool/bin/myfid.fid");
  fid_data_ = fid_decoder_.ExtractFIDData();

  return (fid_data_.IsEmpty());
}
