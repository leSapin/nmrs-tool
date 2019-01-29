/*
 * datacontainer.cpp
 *
 * For holding the raw FID data or the fourier transformed
 * spectrum. Holds an array of pairs. Pairs have 32-bit floats,
 * which can represent real or imaginary numbers.
 *
 */

#include "datacontainer.hpp"
#include <iostream>

DataContainer::DataContainer() {
  bheaders_ = nullptr;
  array_    = nullptr;
  index_    = 0;
}

DataContainer::~DataContainer() {
  delete[] array_;
  delete[] bheaders_;
}

DataContainer::DataContainer(DataContainer&& other) {
  file_header_ = other.file_header_;
  capacity_    = other.capacity_;
  array_       = other.array_;
  is_real_     = other.is_real_;
  index_       = other.index_;
  bheaders_    = other.bheaders_;

  other.file_header_ = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  other.capacity_    = 0;
  other.index_       = 0;
  other.array_       = nullptr;
  other.bheaders_    = nullptr;
}

DataContainer& DataContainer::operator=(DataContainer&& other) {
  if (this != &other) {
    delete[] array_;
    delete[] bheaders_;

    file_header_ = other.file_header_;
    capacity_    = other.capacity_;
    array_       = other.array_;
    is_real_     = other.is_real_;
    index_       = other.index_;
    bheaders_    = other.bheaders_;


    other.file_header_ = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    other.capacity_    = 0;
    other.index_       = 0;
    other.array_       = nullptr;
    other.bheaders_    = nullptr;
  }
  return *this;
}

void DataContainer::SetSize(int arr_size, int bheaders_size ) {
  capacity_ = arr_size;
  array_    = new float[arr_size];
  bheaders_ = new BlockHeaderData[bheaders_size];
}

void DataContainer::SetIsReal(bool is_real) {
  is_real_ = is_real;
}

void DataContainer::SetFHeader(FileHeaderData header) {
  file_header_ = header;
}

bool DataContainer::IsEmpty() {
  return (index_ == 0);
}

bool DataContainer::PushFloat(float val) {
  if (index_ < capacity_) {
    array_[index_] = val;
    ++index_;
    return true;
  }

  return false;
}

int DataContainer::GetLength() {
  return index_;
}

int DataContainer::GetCapacity() {
  return capacity_;
}

float DataContainer::PullFloat() {
  --index_;
  return array_[index_+1];
}

void DataContainer::SetBHeader(int pos, BlockHeaderData bheader) {
  bheaders_[pos] = bheader;
}

