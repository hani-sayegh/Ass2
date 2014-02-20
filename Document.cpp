#include "Document.h"
#include <string>

Document::Document()
{

}

void Document::addFrequency(int& frequency)
{
	mathVec.push_back(frequency);
}

std::ostream & operator<<(std::ostream & os, const Document & doc)
{

	for (std::vector<std::string>::const_iterator it = doc.theSentence.begin(); it != doc.theSentence.end(); ++it)
		os << *it << " ";
	return os;
}

int Document::vectorMagAt(int& index)
{
	return mathVec.at(index);
}

void Document::setCosSimValue(double value)
{
	cosSimValue = value;
}

double Document::getCosSimValue()
{
	return cosSimValue;
}

void Document::setDocName(const std::string name)
{
	docName = name;
}
std::string Document::getDocName()
{
	return docName;
}

bool byCosSimValue(const Document & left, const Document & right)
{
	return left.cosSimValue > right.cosSimValue;
}

void Document::addWeight(double weight)
{
	
		weightedMathVec.push_back(weight);
}

double Document::getWeightAt(int i)
{
	return weightedMathVec.at(i);
}

int Document::getFreqValue(int i)
{
	return mathVec.at(i);
}

void Document::setTheSentence(std::vector<std::string> sentence)
{
	theSentence = sentence;
}

std::vector<std::string> Document::getSentence()
{
	return theSentence;
}


Document::~Document()
{
}