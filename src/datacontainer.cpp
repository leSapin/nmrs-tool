/*
 * datacontainer.cpp
 *
 * For holding the raw FID data or the fourier transformed
 * spectrum. Holds an array of pairs. Pairs have 32-bit floats,
 * which can represent real or imaginary numbers.
 *
 */

#include "datacontainer.hpp"

DataContainer::DataContainer(int arr_size, int bheaders_size) {
  index_     = 0;
  capacity_  = arr_size;
  bheaders_  = new BlockHeaderData[bheaders_size];
  array_     = new float[arr_size];
  finalized_ = false;
}

DataContainer::~DataContainer() {
  delete[] array_;
  delete[] bheaders_;
}

DataContainer::DataContainer(DataContainer&& other) {
  file_header_ = other.file_header_;
  capacity_    = other.capacity_;
  array_       = other.array_;
  index_       = other.index_;
  bheaders_    = other.bheaders_;
  fstatus_     = other.fstatus_;
  finalized_   = other.finalized_;

  other.file_header_ = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  other.fstatus_     = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  other.capacity_    = 0;
  other.index_       = 0;
  other.array_       = nullptr;
  other.bheaders_    = nullptr;
  other.finalized_   = false;
}

DataContainer& DataContainer::operator=(DataContainer&& other) {
  if (this != &other) {
    delete[] array_;
    delete[] bheaders_;

    file_header_ = other.file_header_;
    capacity_    = other.capacity_;
    array_       = other.array_;
    index_       = other.index_;
    bheaders_    = other.bheaders_;
    fstatus_     = other.fstatus_;
    finalized_   = other.finalized_;

    other.file_header_ = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    other.fstatus_     = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    other.capacity_    = 0;
    other.index_       = 0;
    other.array_       = nullptr;
    other.bheaders_    = nullptr;
    other.finalized_   = false;
  }
  return *this;
}

const float* DataContainer::ViewData() {
  return array_;
}

bool DataContainer::IsEmpty() {
  return (index_ == 0);
}

void DataContainer::Finalize() {
  finalized_ = true;
}

bool DataContainer::AddVal(float val) {
  if (index_ < capacity_ && !finalized_) {
    array_[index_] = val;
    ++index_;
    return true;
  }

  return false;
}

int DataContainer::Filled() {
  return index_;
}

int DataContainer::Capacity() {
  return capacity_;
}

void DataContainer::SetBHeader(int pos, BlockHeaderData bheader) {
  if (!finalized_) {
    bheaders_[pos] = bheader;
  }
}

void DataContainer::SetFStatus(FileStatus status) {
  if (!finalized_) {
    fstatus_ = status;
  }
}

void DataContainer::SetFHeader(FileHeaderData header) {
  if (!finalized_) {
    file_header_ = header;
  }
}

bool DataContainer::CheckFlag(int flag_num) {
  switch (flag_num) {
    case 1:  return fstatus_.s_data;
    case 2:  return fstatus_.s_spec;
    case 3:  return fstatus_.s_32;
    case 4:  return fstatus_.s_float;
    case 5:  return fstatus_.s_cmplx;
    case 6:  return fstatus_.s_hypercmplx;
    case 7:  return fstatus_.s_acqpar;
    case 8:  return fstatus_.s_secnd;
    case 9:  return fstatus_.s_transf;
    case 10: return fstatus_.s_np;
    case 11: return fstatus_.s_nf;
    case 12: return fstatus_.s_ni;
    case 13: return fstatus_.s_ni2;
  }
  return 0;
}
