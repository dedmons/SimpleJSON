#include <string.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>

// #include "JSON.h"

void print(std::string s){
  std::cout << s << std::endl;
}

int main(){
  std::cout << __cplusplus << std::endl;

#ifdef __clang__
  print("Using Clang");

  #if defined(__has_include) && __has_include(<unordered_map>)
    std::cout << "Has unordered_map" << std::endl;
  #else
    std::cout << "No unordered_map" << std::endl;
  #endif

#endif
  // std::ifstream t("test.json");
  // std::string str((std::istreambuf_iterator<char>(t)),
  //                  std::istreambuf_iterator<char>());

  // JSONValue *value = JSON::Parse(str.c_str());
  // if (value != NULL){
  //   std::cout << "PASS" << std::endl;
  //   std::cout << value->Child("Fields")->Child("B")->Stringify() << std::endl;
  // }
  // else
  //   std::cout << "FAIL" << std::endl;


  // std::istringstream f("object.loc.1.x,4,7");
  // std::string s;

  // while (std::getline(f,s,'.')){
  //   std::cout << s << std::endl;
  // }

  // if (value) delete value;

  return 0;
}