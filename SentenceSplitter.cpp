#include "SentenceSplitter.h"
#include <fstream>
#include <string>
#include <algorithm>

SentenceSplitter::SentenceSplitter()
{
}


SentenceSplitter::~SentenceSplitter()
{
}

std::vector<std::vector<std::string>> SentenceSplitter::splitter(Document doc)
{
	std::ifstream ifs(doc.getDocName().c_str());
	std::string word;

	std::vector<std::vector<std::string>> temp;
	std::vector<std::string> sentence;

	int sentenceNumber = 0;
	while (ifs >> word)
	{
		std::transform(word.begin(), word.end(), word.begin(), ::tolower);

		if (endOfSentence(word))
		{
			sentence.push_back(word.substr(0, word.size() - 1));
			temp.push_back(sentence);
			++sentenceNumber;
			sentence.clear();
		}
		else
		{
			sentence.push_back(word);
		}
	}

	/*for (std::vector<std::string> me : temp)
	{
		for (std::string you: me)
		{
			std::cout << you << std::endl;
		}
	}*/
	return temp;
}

bool SentenceSplitter::endOfSentence(std::string token)
{
	char charachter = token[token.size() - 1]; //Howcome size works with no -1.

	switch (charachter)
	{
	case '?':
		return true;
	case '.':
		return true;
	case '!':
		return true;
	case ',':
		return true;
	default:
		return false;
	}
}
