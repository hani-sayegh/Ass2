#pragma once

#include <vector>
#include <iostream>

class Document
{
	friend std::ostream & operator<<(std::ostream & os, const Document & doc);
	friend bool byCosSimValue(const Document & left, const Document & right);

public:
	Document();
	~Document();
	void addFrequency(int& frequency);
	int vectorMagAt(int& index);
	void setCosSimValue(double value);
	double  getCosSimValue();
	void setDocName(const std::string value);
	int getFreqValue(int i);
	std::string getDocName();
	void Document::addWeight(double weight);
	double getWeightAt(int i);
	void setTheSentence(std::vector<std::string> sentence);
	std::vector<std::string> getSentence();
private:
	std::vector<int> mathVec;
	std::vector<double> weightedMathVec;
	std::string docName;
	std::vector<std::string> theSentence;
	double cosSimValue;
};

