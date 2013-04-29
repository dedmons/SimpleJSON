#include <string.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>

#include "../JSON.h"

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::duration<double, std::milli> Milli;

void print(std::string s){
  std::cout << s << std::endl;
}

int main(){
  std::ifstream t("test.json");
  std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

  auto start = Clock::now();
  JSONValue *value = JSON::Parse(str.c_str());
  auto end = Clock::now();

  if (value != NULL){
    print("");
    print("Parsing File: PASS");
    std::cout << "Time: " << std::chrono::duration_cast<Milli>(end-start).count() << std::endl;
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

  if (value->HasChildAtPath("Fields.obj.#0.vals.#1")){
    print("Has value at 'Fields.obj.#0.vals.#1'");
    print(value->ChildAtPath("Fields.obj.#0.vals.#1")->Stringify());
  }
  else
    print("Error: Should have value at 'Fields.obj.#0.vals.#1'");

  if (! value->HasChildAtPath("Fields.obj.#2.vals.#1"))
    print("Dose not have value at 'Fields.obj.#2.vals.#1'");
  else
    print("Error: Should not have value at 'Fields.obj.#2.vals.#1'");

  print(value->ChildAtPath("Fields.obj.#0")->Stringify());

  if (value) delete value;

  return 0;
}
