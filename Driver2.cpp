#include <iostream>
#include <fstream>
#include "SentenceSplitter.h" //Why need pragma once????
#include <string>
#include <unordered_map>
#include "StopWord.h"
#include <algorithm>
#include "Document.h"

std::string removePunc(std::string token)
{
	std::string newString;
	for (int i = 0; i < token.size(); i++)
	{
		if (!((token[i] < 97 && token[i] != 43) || token[i] > 122))
		{
			newString += token[i];
		}
	}
	return newString;
}
int main()
{
	std::ifstream ifs("StopWords.txt"); //Contains the different stop words in sorted order.
	std::string sw; //Stop word.

	StopWord test;
	/*
	std::vector<std::string> myVec;
	myVec.push_back("a");
	myVec.push_back("b");
	myVec.push_back("c");
	myVec.push_back("d");
	myVec.push_back("e");

	if (std::binary_search (myVec.begin(), myVec.end(), "ab"))
	std::cout << "found!\n"; else std::cout << "not found.\n";*/

	//Add stop words to the stop word object.
	while (ifs >> sw)
	{
		if (sw.length() != 1)
		{
			test.addStopWord(sw);
		}
	}

	std::ifstream ifs2("fileNames.txt"); //Contains documents to read in.
	std::string fileName;              //Contains the current document. 

	std::vector<std::string> index;    //Contains all different tokens. 
	std::vector<Document> documents; //Contains the different Document objects.

	while (ifs2 >> fileName) //While a document exists.
	{
		Document stud;
		stud.setDocName(fileName);
		documents.push_back(stud);

		std::ifstream ifs2(fileName.c_str()); //Open the current document.
		std::string   word, finalWord;       //Contains current word in document.
		while (ifs2 >> word)
		{
			//Change to lower case.
			std::transform(word.begin(), word.end(), word.begin(), ::tolower);
			finalWord = removePunc(word);

			if (!test.findElement(finalWord))
			{
				bool duplicate = false;

				//Checks for duplicate by comparing current word to rest of index.			
				for (int i = 0; i != index.size(); ++i)
				{
					if (finalWord == index[i])
					{
						duplicate = true;
						break;
					}
				}
				//If not a duplicate then add to the index.
				if (!duplicate)
				{
					index.push_back(finalWord);
				}
			}
		}
	}
	/**************************Should have index by now**********************************/

	std::string word2, finalWord2;


	for (Document& doc : documents)
	{
		std::ifstream ifs3(doc.getDocName().c_str()); //Open the current document.


		//Go through each word in index, increment the actual index as necessary.
		for (int i = 0; i != index.size(); ++i)
		{
			std::string currentWord = index[i]; //Current word in index. 

			int frequency = 0;

			//Compares all tokens in document with the current word in index,
			//if a match is found, then increment frequency.
			while (ifs3 >> word2)
			{
				//Convert to lowercase.
				std::transform(word2.begin(), word2.end(), word2.begin(), ::tolower);
				finalWord2 = removePunc(word2);
				if (finalWord2 == currentWord)
				{
					++frequency;
				}
			}
			//Puch frequency of current word to document vector.

			doc.addFrequency(frequency);

			//Must reset the stream since eof.
			ifs3.clear();
			ifs3.seekg(0, std::ios::beg);
		}
		//Push back docVec to documentVectors.
	}

	//@ this point each document should have its own vector.



	int docNum = documents.size();
	for (int i = 0; i != index.size(); ++i)
	{
		int diffDocFreq = 0;
		for (Document& doc : documents)
		{
			if (doc.getFreqValue(i) > 0)
			{
				++diffDocFreq;
			}
		}
		for (Document& doc : documents)
		{
			double weightedValue = 0;
			if (doc.getFreqValue(i) != 0)
			{
				weightedValue =
					((1.0 + log10(doc.getFreqValue(i))) * log10(docNum / diffDocFreq));
			}

			doc.addWeight(weightedValue);
		}
	}

	/**************We now have a weighted vector for each doc*****************/



	std::vector<Document> sentenceDocuments; //Vector of documents.

	int pos = 0;
	for (Document& doc : documents)
	{
		SentenceSplitter theSplitter;
		std::vector<std::vector<std::string>> theSentences = theSplitter.splitter(doc);

		//While there exists a sentence push back a new document object.
		for (int i = 0; i < theSentences.size(); ++i)
		{
			Document senDoc;
			senDoc.setTheSentence(theSentences.at(i));
			sentenceDocuments.push_back(senDoc);

			for (int j = 0; j != index.size(); ++j)
			{
				std::string currentWord = index.at(j);
				int freq = 0;
				for (std::string& sentenceWord : theSentences.at(i))
				{
					if (currentWord == sentenceWord)
					{
						++freq;
					}
				}
				sentenceDocuments.at(pos).addFrequency(freq);
			}
			++pos;
		}
	}
	/***********We now have a frequency vector for each sentence doc************/

	int docNum2 = sentenceDocuments.size();
	for (int i = 0; i != index.size(); ++i)
	{
		int diffDocFreq = 0;
		for (Document& doc : sentenceDocuments)
		{
			if (doc.getFreqValue(i) > 0)
			{
				++diffDocFreq;
			}
		}
		for (Document& doc : sentenceDocuments)
		{
			double weightedValue = 0;
			if (doc.getFreqValue(i) != 0)
			{
				weightedValue =
					((1.0 + log10(doc.getFreqValue(i))) * log10(docNum2 / diffDocFreq));
			}

			doc.addWeight(weightedValue);
		}
	}
	/**************We now have a weighted vector for each docSentence*****************/



	std::cout << "Enter your query:-" << std::endl;

	std::vector<std::string> totalQuery; //Contains all tokens of the query.
	std::string token, finalToken;             //Takes one token of a query at a time.
	while (std::cin >> token)     //How to not use control z?
	{
		//Convert to lower case.
		std::transform(token.begin(), token.end(), token.begin(), ::tolower);
		finalToken = removePunc(token);

		//Push the current token.
		totalQuery.push_back(finalToken);
	}


	std::vector<int> queryVector; //Contains vector for query.

	//This creates vector for the query.
	for (int i = 0; i != index.size(); ++i)
	{
		std::string currentWord = index[i];
		int frequency = 0;
		for (int j = 0; j != totalQuery.size(); ++j)
		{
			if (totalQuery[j] == index[i]) //.equals() for string?
			{
				++frequency;
			}
		}
		queryVector.push_back(frequency);
	}

	/*sentenceDocuments.push_back(queryVector);
	int docNum3 = sentenceDocuments.size();
	for (int i = 0; i != index.size(); ++i)
	{
	int diffDocFreq = 0;
	for (Document& doc : sentenceDocuments)
	{
	if (doc.getFreqValue(i) > 0)
	{
	++diffDocFreq;
	}
	}

	double weightedValue = 0;
	if (sentenceDocuments.at(docNum3 - 1).getFreqValue(i) != 0)
	{
	weightedValue =
	((1.0 + log10(sentenceDocuments.at(docNum3 - 1).getFreqValue(i))) * log10(docNum3 / diffDocFreq));
	}

	sentenceDocuments.at(docNum3 - 1).addWeight(weightedValue);
	}*/

	//@ this point the query has its own vector.
	/*********************************************************************/

	//Using formula to create value for each document.
	for (Document& doc : sentenceDocuments)
	{

		double numerator = 0;
		//Does seem to give warning for reuse of i when bulding, can u change settings?
		for (int i = 0; i != queryVector.size(); ++i)
		{
			numerator += queryVector[i] * doc.getWeightAt(i);
		}

		double queryDistance = 0.0;
		for (int i = 0; i != queryVector.size(); ++i)
		{
			queryDistance += pow(queryVector[i], 2);	//#include ????
		}
		queryDistance = sqrt(queryDistance);
		/*****************************************************************/
		double docVectorDistance = 0;
		for (int i = 0; i != queryVector.size(); ++i)
		{
			docVectorDistance += pow(doc.getWeightAt(i), 2);	//#include ????
		}
		docVectorDistance = sqrt(docVectorDistance);

		double denominator = docVectorDistance * queryDistance;

		double cosineSimilarity = numerator / denominator;

		doc.setCosSimValue(cosineSimilarity);
	}
	/******************************************************************/

	/*for (Document doc : sentenceDocuments)
	{
	std::cout << "i am: " << doc.getCosSimValue() << std::endl;
	}
	*/

	sort(sentenceDocuments.begin(), sentenceDocuments.end(), byCosSimValue); //Why not by reference? Maybe

	int top = 10;
	std::cout << "Top " << top << " Documents:-\n" << std::endl;
	for (Document doc : sentenceDocuments)
	{
		if (0 == top)
		{
			break;
		}
		std::cout << " -- " << doc << std::endl;
		--top;
	}


	system("pause");
	return 0;
}