#pragma once
#include <vector>
#include "Document.h"

class SentenceSplitter
{
public:
	SentenceSplitter();
	~SentenceSplitter();
	std::vector<std::vector<std::string>> splitter(Document doc);
	bool endOfSentence(std::string token);
private:
	std::vector<std::vector<std::string>> sentences;
};

