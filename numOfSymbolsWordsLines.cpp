#include "pch.h"
#include <fstream>
#include <iostream>


/*Напишете програма, която да прочита текстовия файл “input.txt” и да извежда на стандартния изход броя символи, думи и редове в него. 
Думите представляват последователности от ASCII символи, които са разделени с интервали, табулации или нови редове. 
Пример: Файлът input.txt има следното съдържание (без кавичките): “firstWord secondWord thirdWord fourthWord” 
Резултатът от изпълнението на програмата ви върху дадения примерен файл трябва да бъде следният: Number of symbols: 42 Number of words: 4 Number of new lines: 2
*/



void count(const char *name)
{
	std::ifstream in(name);

	if (in)
	{
		size_t lines = 1;
		size_t words = 0;
		size_t sym = 0;

		char c;

		bool inWord = false;

		while (in)
		{
			in.read(&c, 1);
			if (in)
			{
				if (c == '\n')
				{
					++lines;
					++sym;
					inWord = false;
				}

				else if (inWord == false && c != '\t' && c != ' ')
				{
					++words;
					inWord = true;
				}

				else if (c == ' ')
				{
					inWord = false;
				}

				else if (c == '\t')
				{
					++sym;
					inWord = false;
				}

				++sym;
			}
		}

		std::cout << "Number of symbols: " << sym << "Number of words: " << words << "Number of new lines: " << lines << '\n';

	}

	in.close();
}

int main()
{




	return 0;
}

