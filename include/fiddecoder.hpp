/*
 * fiddecoder.hpp
 *
 * FIDDecoder parses the fid file, performs DC drift correction,
 * first point correction and applies the weighting function.
 *
 */

#ifndef FID_DECODER_HPP
#define FID_DECODER_HPP

#include <string>
#include <fstream>

#include "datacontainer.hpp"

class FIDDecoder {
 public:
  FIDDecoder();

  void SetFIDPath(std::string new_path);
  DataContainer ExtractFIDData();

 private:
  std::string fid_path_;
  std::ifstream fid_file_;

  FileHeaderData DecodeFileHeader();
  BlockHeaderData DecodeBlockHeader(long block_offset);
  float SwapFloat(float value);
};

#endif // FID_DECODER_HPP
