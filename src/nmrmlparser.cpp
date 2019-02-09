/*
 * nmrmlparser.hpp
 *
 */

#include "nmrmlparser.hpp"
#include "datacontainer.hpp"
#include "fiddecoder.hpp"

using namespace std;

NMRMLParser::NMRMLParser() {
  decoder_    = new FIDDecoder();
  nmrml_path_ = "";
}

NMRMLParser::~NMRMLParser() {
  delete decoder_;
}

DataContainer NMRMLParser::RetFID() {
  return decoder_->ExtractFIDData(nmrml_path_);
}

void NMRMLParser::SetPath(string path) {
  nmrml_path_ = path;
}
