#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

// Brainfuck -> PhantomFuck  (UTF-8 for each zero-width code point)
static const std::unordered_map<char, std::string> BF_TO_PF = {
  // U+200B = "\xE2\x80\x8B"
  // U+200C = "\xE2\x80\x8C"
  // U+200D = "\xE2\x80\x8D"

  // > => (U+200B U+200B)
  {'>', "\xE2\x80\x8B\xE2\x80\x8B"},

  // < => (U+200B U+200C)
  {'<', "\xE2\x80\x8B\xE2\x80\x8C"},

  // + => (U+200B U+200D)
  {'+', "\xE2\x80\x8B\xE2\x80\x8D"},

  // - => (U+200C U+200B)
  {'-', "\xE2\x80\x8C\xE2\x80\x8B"},

  // . => (U+200C U+200C)
  {'.', "\xE2\x80\x8C\xE2\x80\x8C"},

  // , => (U+200C U+200D)
  {',', "\xE2\x80\x8C\xE2\x80\x8D"},

  // [ => (U+200D U+200B)
  {'[', "\xE2\x80\x8D\xE2\x80\x8B"},

  // ] => (U+200D U+200C)
  {']', "\xE2\x80\x8D\xE2\x80\x8C"}
};

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <input.bf> <output.phf>\n";
    return 1;
  }

  std::ifstream inFile(argv[1], std::ios::in | std::ios::binary);
  if (!inFile.is_open()) {
    std::cerr << "Could not open input file: " << argv[1] << "\n";
    return 1;
  }

  std::ofstream outFile(argv[2], std::ios::out | std::ios::binary);
  if (!outFile.is_open()) {
    std::cerr << "Could not open output file: " << argv[2] << "\n";
    return 1;
  }

  char c;
  while (inFile.get(c)) {
    auto it = BF_TO_PF.find(c);
    if (it != BF_TO_PF.end()) {
      outFile << it->second;
    }
  }

  inFile.close();
  outFile.close();
  std::cout << "Translation complete. Output written to: " << argv[2] << "\n";
  return 0;
}
