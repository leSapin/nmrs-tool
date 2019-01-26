/*
 * datacontainer.cpp
 *
 * For holding the raw FID data or the fourier transformed
 * spectrum. Holds an array of pairs. Pairs have 32-bit floats,
 * which can represent real or imaginary numbers.
 *
 */

#include "datacontainer.hpp"

DataContainer::DataContainer(long cont_size, bool is_real) {
  cont_size_ = cont_size;
  is_real_ = is_real;

  cont_array_ = new DataPair[cont_size_];
}

DataContainer::~DataContainer() {
  delete cont_array_;
}


void DataContainer::AddPair(float e1, float e2) {

}

DataPair DataContainer::GetPair(int index) {

}
