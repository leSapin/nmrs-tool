/*
 * nmrlparser.hpp
 *
 */

#ifndef NMRML_PARSER_HPP
#define NMRML_PARSER_HPP

#include <string>

class FIDDecoder;
class DataContainer;

class NMRMLParser {
 public:
  NMRMLParser();
  ~NMRMLParser();

  void SetPath(std::string path);

  DataContainer RetFID();
  void ParseNMRML(); // TODO

 private:
  std::string nmrml_path_;
  FIDDecoder* decoder_;
};

#endif // NMRL_PARSER_HPP
