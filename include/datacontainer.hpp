/*
 * datacontainer.hpp
 *
 * For holding the raw FID data or the fourier transformed
 * spectrum. Holds an array of pairs. Pairs have 32-bit floats,
 * which can represent real or imaginary numbers.
 *
 */

#include <cstdint>

struct DataPair {
  float e1;
  float e2;
};

struct FileHeaderData { // From the VnmrJ User Programming manual
  uint32_t nblocks;     // number of blocks in file
  uint32_t ntraces;     // number of traces per block
  uint32_t np;          // number of elements per trace
  uint32_t ebytes;      // number of bytes per element
  uint32_t tbytes;      // number of bytes per trace
  uint32_t bbytes;      // number of bytes per block
  uint16_t vers_id;     // software version, file_id status bits
  uint16_t status;      // status of whole file
  uint32_t nbheaders;   // number of block headers per block
};

struct BlockHeaderData { // From the VnmrJ User Programming manual
  uint16_t scale;        // scaling factor
  uint16_t status;       // status of data in block
  uint16_t index;        // block index
  uint16_t mode;         // mode of data in block
  uint32_t ctcount;      // ct value for FID
  float lpval;           // f2 (2D-f1) left phase in phasefile
  float rpval;           // f2 (2D-f1) right phase in phasefile
  float lvl;             // level drift correction
  float tlt;             // tilt drift correction
};

class DataContainer {
 public:
  DataContainer(long cont_size, bool is_real);
  ~DataContainer();

  void AddPair(float e1, float e2);
  DataPair GetPair(int index);

 private:
  long cont_size_;
  bool is_real_;

  FileHeaderData fid_header_;
  DataPair* cont_array_;
};
