//#include <fstream>
//#include <vector>
//#include <string>
//#include <iostream>
//#include "Document.h"
//#include <algorithm>
//
//
//int main()
//{
//	std::ifstream ifs("fileNames.txt"); //Contains documents to read in.
//	std::string fileName;              //Contains the current document. 
//
//	std::vector<std::string> fileNames;
//	std::vector<std::string> index;    //Contains all different tokens. 
//	std::vector<Document> documents; //Contains the different Document objects.
//
//	while (ifs >> fileName) //While a document exists.
//	{
//		Document stud;
//		stud.setDocName(fileName);
//		documents.push_back(stud);
//
//		fileNames.push_back(fileName);
//		std::ifstream ifs2(fileName.c_str()); //Open the current document.
//		std::string   word, finalWord;       //Contains current word in document.
//		while (ifs2 >> word)
//		{
//			//Change to lower case.
//			/*	std::transform(word.begin(), word.end(), word.begin(), change_case);
//				finalWord = removePunc(word);*/
//
//			bool duplicate = false;
//
//			//Checks for duplicate by comparing current word to rest of index.			
//			for (int i = 0; i != index.size(); ++i)
//			{
//				if (word == index[i])
//				{
//					duplicate = true;
//					break;
//				}
//			}
//			//If not a duplicate then add to the index.
//			if (!duplicate)
//			{
//				index.push_back(word);
//			}
//		}
//	}
//
//	//	//@ this point the whole index should have been created.
//
//	//	/*************************************************************/
//
//
//	std::string word2, finalWord2;
//
//
//	int pos = 0;
//	for (std::string fileName : fileNames)
//	{
//		std::ifstream ifs3(fileName.c_str()); //Open the current document.
//		
//
//		//Go through each word in index, increment the actual index as necessary.
//		for (int i = 0; i != index.size(); ++i)
//		{
//			std::string currentWord = index[i]; //Current word in index. 
//
//			int frequency = 0;
//			
//			//Compares all tokens in document with the current word in index,
//			//if a match is found, then increment frequency.
//			while (ifs3 >> word2)
//			{
//				//Convert to lowercase.
//				/*std::transform(word2.begin(), word2.end(), word2.begin(), change_case);
//				finalWord2 = removePunc(word2);*/
//				if (word2 == currentWord)
//				{
//					++frequency;
//				}
//			}
//			//Puch frequency of current word to document vector.
//
//			documents[pos].addFrequency(frequency);
//
//			//Must reset the stream since eof.
//			ifs3.clear();
//			ifs3.seekg(0, std::ios::beg);
//		}
//		//Push back docVec to documentVectors.
//		++pos;
//	}
//	
//	//	//@ this point each document should have its own vector.
//
//	std::cout << "Enter your query:-" << std::endl;
//
//	std::vector<std::string> totalQuery; //Contains all tokens of the query.
//	std::string token;             //Takes one token of a query at a time.
//	while (std::cin >> token)     //How to not use control z?
//	{
//		//Convert to lower case.
//		//std::transform(token.begin(), token.end(), token.begin(), change_case);
//		//Push the current token.
//		totalQuery.push_back(token);
//	}
//
//
//	std::vector<int> queryVector; //Contains vector for query.
//
//	//This creates vector for the query.
//	for (int i = 0; i != index.size(); ++i)
//	{
//		std::string currentWord = index[i];
//		int frequency = 0;
//		for (int j = 0; j != totalQuery.size(); ++j)
//		{
//			if (totalQuery[j] == index[i]) //.equals() for string?
//			{
//				++frequency;
//			}
//		}
//		queryVector.push_back(frequency);
//	}
//
//	//@ this point the query has its own vector.
//	/*********************************************************************/
//
//	//Using formula to create value for each document.
//	for (Document& doc : documents)
//	{
//		
//		int numerator = 0;
//		//Does seem to give warning for reuse of i when bulding, can u change settings?
//		for (int i = 0; i != queryVector.size(); ++i)
//		{
//			numerator += queryVector[i] * doc.vectorMagAt(i);
//		}
//
//		double queryDistance = 0.0;
//		for (int i = 0; i != queryVector.size(); ++i)
//		{
//			queryDistance += pow(queryVector[i], 2);	//#include ????
//		}
//		queryDistance = sqrt(queryDistance);
//		/*****************************************************************/
//		double docVectorDistance = 0;
//		for (int i = 0; i != queryVector.size(); ++i)
//		{
//			docVectorDistance += pow(doc.vectorMagAt(i), 2);	//#include ????
//		}
//		docVectorDistance = sqrt(docVectorDistance);
//
//		double denominator = docVectorDistance * queryDistance;
//
//		double cosineSimilarity = numerator / denominator;
//
//		doc.setCosSimValue(cosineSimilarity);
//	}
//	/******************************************************************/
//	for (Document doc : documents)
//	{
//		std::cout << "I am: " << doc.getCosSimValue() << std::endl;
//	}
//
//	sort(documents.begin(), documents.end(), byCosSimValue); //Why not by reference? Maybe
//
//	int top = 2;
//	std::cout << "Top " << top << " Documents:-\n" << std::endl;
//	for (Document doc : documents)
//	{
//		if (0 == top)
//		{
//			break;
//		}
//		std::cout << doc.getDocName() << " -- " << doc.getCosSimValue() << std::endl;
//		--top;
//	}
//
//
//	system("pause");
//	return 0;
//}