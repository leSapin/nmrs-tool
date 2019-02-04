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

  bool          SetFlag(int status, int flag);
  void          SetFIDPath(std::string new_path);
  DataContainer ExtractFIDData();

 private:
  std::string fid_path_;
  std::ifstream fid_file_;

  float           SwapFloat(float value);
  FileHeaderData  DecodeFileHeader();
  BlockHeaderData DecodeBlockHeader(long block_offset);
};

#endif // FID_DECODER_HPP
