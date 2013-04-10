#include <string.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>

#include "../JSON.h"

void print(std::string s){
  std::cout << s << std::endl;
}

int main(){
  std::cout << __cplusplus << std::endl;

#ifdef __clang__
  print("Built With Clang");
  #if defined(__has_include) && __has_include(<unordered_map>)
    print("Using std::unordered_map");
  #else
    print("Using std::map");
  #endif
#else 
  print("Built With GCC");
  #define GCC_VERSION (__GNUC__ * 10000 \
                        + __GNUC_MINOR__ * 100 \
                        + __GNUC_PATCHLEVEL__)
  #if GCC_VERSION >= 40600
    print("GCC Version >= 4.6.0");
    print("Using std::unordered_map");
  #else
    print("GCC Version < 4.6.0");
    print("Using std::map");
  #endif
#endif



  std::ifstream t("test.json");
  std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

  JSONValue *value = JSON::Parse(str.c_str());
  if (value != NULL){
    print("");
    print("Parsing File: PASS");
    print("");
  }
  else{
    std::cout << "FAIL" << std::endl;
    return 1;
  }


  print("Value at Fields->B");
  print(value->Child("Fields")->Child("B")->Stringify());
  print("");
  print("Value at Fields->B->#2");
  print(value->ChildAtPath("Fields.B.#2")->Stringify());
  print("");
  print(value->ChildAtPath("Fields.obj")->Stringify());
  print("");

  if (value->HasChildAtPath("Fields.obj"))
    print("Has value at 'Fields.obj.#0.vals.#1'");
  else
    print("Error: Should have value at 'Fields.obj.#0.vals.#1'");

  if (! value->HasChildAtPath("Fields.obj.#2.vals.#1"))
    print("Dose not have value at 'Fields.obj.#2.vals.#1'");
  else
    print("Error: Should not have value at 'Fields.obj.#2.vals.#1'");

  if (value) delete value;

  return 0;
}
