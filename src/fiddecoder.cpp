/*
 * fiddecoder.cpp
 *
 * FIDDecoder parses the fid file, performs DC drift correction,
 * first point correction and applies the weighting function.
 *
 */

#include "fiddecoder.hpp"

using namespace std;

FIDDecoder::FIDDecoder() {
  fid_path_ = "";
}

float FIDDecoder::SwapFloat(float value) {
  // Convert mid-little endian to little endian float
  union {uint8_t b[4]; float inFloat; } in;
  union {uint8_t b[4]; float outFloat;} out;
  in.inFloat = value;

  out.b[0] = in.b[1];
  out.b[1] = in.b[0];
  out.b[2] = in.b[3];
  out.b[3] = in.b[2];

  return out.outFloat;
}

void FIDDecoder::SetFIDPath(string new_path) {
  fid_path_ = new_path;
}

// Varian devices store data in big-endian format
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
  res.status = tmp_16;

  fid_file_.read(reinterpret_cast<char*>(&tmp_16), 2);
  res.index = __builtin_bswap16(tmp_16);

  fid_file_.read(reinterpret_cast<char*>(&tmp_16), 2);
  res.mode = tmp_16;

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

bool FIDDecoder::SetFlag(int status, int flag) {
  return (status & (1 << flag));
}

DataContainer FIDDecoder::ExtractFIDData() {
  DataContainer res;

  fid_file_.open(fid_path_ + "/fid", ios::binary | ios::in);
  if (!fid_file_) {return res;}

  FileHeaderData header = DecodeFileHeader();

  // Bytes per block - block header size
  int fid_bytes = (header.bbytes - 28 ) * header.nblocks;
  int arr_size = ((fid_bytes / sizeof(float)));

  res.SetSize(arr_size, header.nblocks * header.nbheaders);
  res.SetFHeader(header);
  FileStatus fstatus = {SetFlag(header.status, 0),
                        SetFlag(header.status, 1),
                        SetFlag(header.status, 2),
                        SetFlag(header.status, 3),
                        SetFlag(header.status, 4),
                        SetFlag(header.status, 5),
                        SetFlag(header.status, 7),
                        SetFlag(header.status, 8),
                        SetFlag(header.status, 9),
                        SetFlag(header.status, 11),
                        SetFlag(header.status, 12),
                        SetFlag(header.status, 13),
                        SetFlag(header.status, 14)};
  res.SetFStatus(fstatus);

  float tmp_float;
  int bheader_pos = 0;

  for (int i = 0; i < header.nblocks; ++i) {
    for (int k = 0; k < header.nbheaders; ++k) {
      res.SetBHeader(bheader_pos, DecodeBlockHeader(fid_file_.tellg()));
      ++bheader_pos;
    }

    for (int j = 0; j < arr_size / header.nblocks; ++j) {
      fid_file_.read(reinterpret_cast<char*>(&tmp_float), 4);
      res.PushFloat(SwapFloat(tmp_float));
    }
  }

  fid_file_.close();

  return res;
}
