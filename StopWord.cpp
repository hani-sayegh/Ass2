#include "StopWord.h"
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>


StopWord::StopWord()
{
}


StopWord::~StopWord()
{
}

void StopWord:: addStopWord(std::string stw)
{
	stopWords.push_back(stw);
}

bool StopWord:: findElement(std::string stw)
{
	return std::binary_search (stopWords.begin(), stopWords.end(), stw);
}



//	 void StopWord::byAlpha()
//	 {
//sort(stopWords.begin(), stopWords.end()); //Why not by reference? Maybe
//	 }

//std::istream & operator>>(std::istream & ifs, StopWord & stw)
//{
//
//	if (ifs >> stud.name)
//	{
//		ifs >> stud.midterm >> stud.final;
//		int mark;
//		stud.assignments.clear();
//		while (ifs >> mark)
//			stud.assignments.push_back(mark);
//		ifs.clear();
//	}
//	return ifs;
//}