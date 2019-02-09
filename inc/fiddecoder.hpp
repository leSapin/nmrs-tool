/*
 * fiddecoder.hpp
 *
 * FIDDecoder parses the fid file, performs DC drift correction,
 * first point correction and applies the weighting function.
 *
 */

#ifndef FID_DECODER_HPP
#define FID_DECODER_HPP

#include <fstream>

class  DataContainer;
struct FileHeaderData;
struct BlockHeaderData;

class FIDDecoder {
 public:
  FIDDecoder();

  bool          SetFlag(int status, int flag);
  DataContainer ExtractFIDData(std::string path);

 private:
  std::ifstream fid_file_;

  float           SwapFloat(float value);
  FileHeaderData  DecodeFileHeader();
  BlockHeaderData DecodeBlockHeader(long block_offset);
};

#endif // FID_DECODER_HPP
