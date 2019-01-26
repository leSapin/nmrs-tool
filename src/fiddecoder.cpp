/*
 * fiddecoder.cpp
 *
 * FIDDecoder parses the fid file, performs DC drift correction,
 * first point correction and applies the weighting function.
 *
 */

#include "fiddecoder.hpp"

using namespace std;

FIDDecoder::FIDDecoder(string fid_path) : fid_path_(fid_path) {

}

FIDDecoder::~FIDDecoder() {

}

FileHeaderData FIDDecoder::DecodeFileHeader() {
  FileHeaderData res;
  uint32_t tmp_32;
  uint16_t tmp_16;

  fid_file_.read(reinterpret_cast<char*>(&tmp_32), 4);
  res.nblocks = __builtin_bswap32(tmp_32);

  fid_file_.read(reinterpret_cast<char*>(&tmp_32), 4);
  res.ntraces = __builtin_bswap32(tmp_32);

  fid_file_.read(reinterpret_cast<char*>(&tmp_32), 4);
  res.np = __builtin_bswap32(tmp_32);

  fid_file_.read(reinterpret_cast<char*>(&tmp_32), 4);
  res.ebytes = __builtin_bswap32(tmp_32);

  fid_file_.read(reinterpret_cast<char*>(&tmp_32), 4);
  res.tbytes = __builtin_bswap32(tmp_32);

  fid_file_.read(reinterpret_cast<char*>(&tmp_32), 4);
  res.bbytes = __builtin_bswap32(tmp_32);

  fid_file_.read(reinterpret_cast<char*>(&tmp_16), 2);
  res.vers_id = __builtin_bswap16(tmp_16);

  fid_file_.read(reinterpret_cast<char*>(&tmp_16), 2);
  res.status = __builtin_bswap16(tmp_16);

  fid_file_.read(reinterpret_cast<char*>(&tmp_32), 4);
  res.nbheaders = __builtin_bswap32(tmp_32);

  return res;
}

BlockHeaderData FIDDecoder::DecodeBlockHeader(long block_offset) {
  BlockHeaderData res;
  float tmp_float;
  uint32_t tmp_32;
  uint16_t tmp_16;

  fid_file_.seekg(block_offset, fid_file_.beg);

  fid_file_.read(reinterpret_cast<char*>(&tmp_16), 2);
  res.scale = __builtin_bswap16(tmp_16);

  fid_file_.read(reinterpret_cast<char*>(&tmp_16), 2);
  res.status = __builtin_bswap16(tmp_16);

  fid_file_.read(reinterpret_cast<char*>(&tmp_16), 2);
  res.index = __builtin_bswap16(tmp_16);

  fid_file_.read(reinterpret_cast<char*>(&tmp_16), 2);
  res.mode = __builtin_bswap16(tmp_16);

  fid_file_.read(reinterpret_cast<char*>(&tmp_32), 4);
  res.ctcount = __builtin_bswap32(tmp_32);

  fid_file_.read(reinterpret_cast<char*>(&tmp_float), 4);
  res.lpval = __builtin_bswap32(tmp_float);

  fid_file_.read(reinterpret_cast<char*>(&tmp_float), 4);
  res.rpval = __builtin_bswap32(tmp_float);

  fid_file_.read(reinterpret_cast<char*>(&tmp_float), 4);
  res.lvl = __builtin_bswap32(tmp_float);

  fid_file_.read(reinterpret_cast<char*>(&tmp_float), 4);
  res.tlt = __builtin_bswap32(tmp_float);

  return res;
}

DataContainer FIDDecoder::ExtractFIDData() {
  DataContainer res (52, true);
  fid_file_.open(fid_path_ + "/fid", ios::binary | ios::in);

  if (!fid_file_) {
    return res;
  }

  FileHeaderData header_data = DecodeFileHeader();

  for (int i = 0; i < header_data.nblocks; ++i) {
    auto cur_blockh = DecodeBlockHeader(fid_file_.tellg());
  }

  fid_file_.close();

  return res;
}
