#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <fstream>

static const size_t MEMORY_SIZE = 30000;

std::string readAll(std::istream& in) {
  std::string data;
  char c;
  while (in.get(c)) {
    data.push_back(c);
  }
  return data;
}

int main(int argc, char* argv[]) {
  std::ifstream file;
  if (argc > 1) {
    file.open(argv[1], std::ios::binary);
    if (!file.is_open()) {
      std::cerr << "Failed to open file: " << argv[1] << std::endl;
      return 1;
    }
  }
  std::istream& in = (argc > 1) ? file : std::cin;

  std::string codeUtf8 = readAll(in);

  auto getNextCharId = [&](size_t& index) -> int {
    while (index < codeUtf8.size() && codeUtf8[index] == ' ') {
      index++;
    }

    if (index + 3 > codeUtf8.size()) {
      return -1;
    }

    unsigned char b1 = static_cast<unsigned char>(codeUtf8[index + 0]);
    unsigned char b2 = static_cast<unsigned char>(codeUtf8[index + 1]);
    unsigned char b3 = static_cast<unsigned char>(codeUtf8[index + 2]);

    if (b1 == 0xE2 && b2 == 0x80) {
      if (b3 == 0x8B) {
        index += 3;
        return 1;
      }
      else if (b3 == 0x8C) {
        index += 3;
        return 2;
      }
      else if (b3 == 0x8D) {
        index += 3;
        return 3;
      }
    }

    index++;
    return 0;
  };


  std::vector<char> program;

  //   > => 1,1    (U+200B U+200B)
  //   < => 1,2    (U+200B U+200C)
  //   + => 1,3    (U+200B U+200D)
  //   - => 2,1    (U+200C U+200B)
  //   . => 2,2    (U+200C U+200C)
  //   , => 2,3    (U+200C U+200D)
  //   [ => 3,1    (U+200D U+200B)
  //   ] => 3,2    (U+200D U+200C)

  auto translatePairToBf = [&](int first, int second) -> char {
    if (first == 1 && second == 1) return '>';
    if (first == 1 && second == 2) return '<';
    if (first == 1 && second == 3) return '+';
    if (first == 2 && second == 1) return '-';
    if (first == 2 && second == 2) return '.';
    if (first == 2 && second == 3) return ',';
    if (first == 3 && second == 1) return '[';
    if (first == 3 && second == 2) return ']';
    // default
    return '\0';
  };

  for (size_t i = 0; i < codeUtf8.size();) {
    int c1 = getNextCharId(i);
    if (c1 <= 0) {
      continue;
    }
    int c2 = getNextCharId(i);
    if (c2 <= 0) {
      continue;
    }
    char bfCmd = translatePairToBf(c1, c2);
    if (bfCmd != '\0') {
      program.push_back(bfCmd);
    }
  }

  std::vector<size_t> jumpTable(program.size(), 0);
  {
    std::stack<size_t> s;
    for (size_t ip = 0; ip < program.size(); ip++) {
      if (program[ip] == '[') {
        s.push(ip);
      }
      else if (program[ip] == ']') {
        if (s.empty()) {
          std::cerr << "Unmatched ']' at position " << ip << std::endl;
          return 1;
        }
        size_t left = s.top();
        s.pop();
        jumpTable[left] = ip;
        jumpTable[ip] = left;
      }
    }
    if (!s.empty()) {
      std::cerr << "Unmatched '[' at position " << s.top() << std::endl;
      return 1;
    }
  }

  std::vector<unsigned char> mem(MEMORY_SIZE, 0);
  size_t ptr = 0;
  for (size_t ip = 0; ip < program.size(); ip++) {
    switch (program[ip]) {
    case '>':
      ptr = (ptr + 1) % MEMORY_SIZE;
      break;
    case '<':
      ptr = (ptr + MEMORY_SIZE - 1) % MEMORY_SIZE;
      break;
    case '+':
      mem[ptr]++;
      break;
    case '-':
      mem[ptr]--;
      break;
    case '.':
      std::cout << mem[ptr];
      break;
    case ',':
      mem[ptr] = static_cast<unsigned char>(std::cin.get());
      break;
    case '[':
      if (mem[ptr] == 0) {
        ip = jumpTable[ip];
      }
      break;
    case ']':
      if (mem[ptr] != 0) {
        ip = jumpTable[ip];
      }
      break;
    }
  }
  return 0;
}
