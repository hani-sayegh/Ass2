#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>


class StopWord
{
	friend std::istream & operator>>(std::istream & is, StopWord & stw);
public:
	StopWord();
	~StopWord();
	void addStopWord(std::string stw);
	//void byAlpha();
	bool findElement(std::string stw);
private:
	std::vector<std::string> stopWords;
};

