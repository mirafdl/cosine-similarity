#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

const int MAX_TOKENS = 400;
const char* DEFAULT_STOPWORDS_FILENAME = "stopwords.txt";
const char* CHARS_TO_REMOVE = ".,:;\"()";

std::string readInputFile(const char* filename) {
  std::string text;
  std::ifstream file(filename);
  std::getline(file, text);
  file.close();
  return text;
}


std::string* tokenize(std::string text, int& size) {
  std::string* tokens = new std::string[200];
  std::stringstream stream(text);
  size = 0;
  while (stream.good() && size < 200) {
    stream >> tokens[size++];
  }
  return tokens;
}

bool inArray(std::string str, std::string* strArray, int strArraySize) {
  for (int i = 0; i < strArraySize; ++i) {
    if (str == strArray[i]) {
      return true;
    }
  }
  return false;
}

// tahseb tikrar ta3 kol kalma 
int frequency(std::string token, std::string* tokens, int tokensSize) {
  int freq = 0;
  for (int i = 0; i < tokensSize; ++i) {
    if (token == tokens[i]) {
      ++freq;
    }
  }
  return freq;
}

int dotProduct(int* v1, int* v2, int size) {
  int prod = 0;
  for (int i = 0; i < size; ++i) {
    prod += v1[i] * v2[i];
  }
  return prod;
}

double magnitude(int* v, int size) {
  return std::sqrt(dotProduct(v, v, size));
}

double cosineSimilarity(std::string* tokens1, int tokens1Size,
                        std::string* tokens2, int tokens2Size) {

  // lista ta3 kamel el kalmat      
  std::string* distinctTokens = new std::string[tokens1Size + tokens2Size];
  int distinctTokensSize = 0;
  for (int i = 0; i < tokens1Size; ++i) {
    if (!inArray(tokens1[i], distinctTokens, distinctTokensSize)) {
      distinctTokens[distinctTokensSize++] = tokens1[i];
    }
  }
  for (int i = 0; i < tokens2Size; ++i) {
    if (!inArray(tokens2[i], distinctTokens, distinctTokensSize)) {
      distinctTokens[distinctTokensSize++] = tokens2[i];
    }
  }
  int* frequencies1 = new int[distinctTokensSize];
  int* frequencies2 = new int[distinctTokensSize];
  // kol kalma 
  for (int i = 0; i < distinctTokensSize; ++i) {
    frequencies1[i] = frequency(distinctTokens[i], tokens1, tokens1Size);
    frequencies2[i] = frequency(distinctTokens[i], tokens2, tokens2Size);
  }
  delete[] distinctTokens;
  double sim = dotProduct(
    frequencies1, frequencies2, distinctTokensSize) /
    (magnitude(frequencies1, distinctTokensSize) *
    magnitude(frequencies2, distinctTokensSize));
  delete[] frequencies1;
  delete[] frequencies2;
  return sim;
}

int main(int argc, char** argv) {
  std::string text1 = readInputFile(argv[1]);
  std::string text2 = readInputFile(argv[2]);
  
  int tokens1Size;
  std::string* tokens1 = tokenize(text1, tokens1Size);
  
  int tokens2Size;
  std::string* tokens2 = tokenize(text2, tokens2Size);
  double similarity = cosineSimilarity(
    tokens1, tokens1Size,
    tokens2, tokens2Size);
  delete[] tokens1;
  delete[] tokens2;
  std::cout << "similarity: " <<similarity;
  return 0;
}
