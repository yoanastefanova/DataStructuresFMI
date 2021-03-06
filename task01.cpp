#include "pch.h"
#include <fstream>
#include <iostream>

/*
Task 1: Напишете функция, която:

-приема ред от стандартния вход, записва го във файл и след това извежда съдържанието на файла;
-по подаден поток и име на файл, намира колко реда има файла;
-пресмята големината на подаден текстов файл;
-чете от файл с 4 реда от по 2 числа и пресмята лицето на правоъгълника, получен от тези точки;
-чете символ от стандартния изход и извежда всички срещания (ред и колона) на символа във файл.
*/

//Write in console, write in file, print file's content

void writeInFileandPrint(const char *_name)
{
	std::ofstream out(_name);

	if (out)
	{
		char textInput[512];

		while (std::cin.get(textInput, '\n'))//взима символите от cin и ги слага в textInput, докато срещне нов ред
		{
			out << textInput;//символите от textInput се записват във файла out 
		}
	}

	out.close();

	std::ifstream in(_name);

	if (in)
	{
		char text[512];

		while (in.get(text, '\n'))//взима елементите от файла и ги записва в text, докато не срещне нов ред
		{
			std::cout << text;
		}
	}

	in.close();
}

//By given stream and file's name ---> how many rows does the file have?

size_t rowsInFile(std::ifstream &in, const char *_name)
{
	size_t counter = 1;

	if (in)
	{
		char c;

		while (in)
		{
			in.read(&c, 1); // Extracts n characters from the stream and stores them in the array pointed to by c.

			if (in)
			{
				if (c == '\n')
				{
					++counter;
				}
			}
		}

		in.close();

		return counter;
	}

	std::cout << "Could not open file!\n";

	return -1;
}



//Get the size of a text file

std::streamoff fileSize(const char *_name)
{
	std::ifstream in(_name);

	if (in)
	{
		in.seekg(0, std::ios::end);
		return in.tellg();
	}

	std::cout<<"Could not open file!\n";

	return -1;
}


//Read from a file with 4 rows with 2 numbers. Calculate the area of a rectangle made by these points.
	

unsigned max(const float &n1, const float &n2, const float &n3, const float &n4)
{
	float max1 = (n1 < n2 ? n2 : n1);
	float max2 = (n3 < n4 ? n4 : n3);
	return (max1 < max2 ? max2 : max1);
}

unsigned min(const float &n1, const float &n2, const float &n3, const float &n4)
{
	float min1 = (n1 < n2 ? n1 : n2);
	float min2 = (n3 < n4 ? n3 : n4);
	return (min1 < min2 ? min1 : min2);
}



size_t find_area(const char* path)
{
	std::ifstream fin(path);

	if (fin)
	{
		size_t area;

		float arr[8];

		for (size_t i = 0; i < 8; i++)
		{
			fin >> arr[i];
		}

		fin.close();

		float max_y = max(arr[1], arr[3], arr[5], arr[7]);
		float min_y = min(arr[1], arr[3], arr[5], arr[7]);

		float max_x = max(arr[0], arr[2], arr[4], arr[6]);
		float min_x = min(arr[0], arr[2], arr[4], arr[6]);

		return (max_y - min_y) * (max_x - min_x);
	}

	std::cout << "Could not open file!\n";

	return 0;
}


//Read symbol from the console and output the row and column number of all the places where it could be found in a file


void findSym(const char *_name)
{
	char curSym;

	char sym;

	std::cin.clear();
	std::cout << "Enter symbol: ";
	std::cin >> sym;

	std::ifstream in(_name);

	if (in)
	{
		size_t numRow = 1;
		size_t numCol = 1;

		for (; in; ++numCol)
		{
			in.read(&curSym, 1);

			if (in)
			{
				if (curSym == sym)
				{
					std::cout << "\nRow: " << numRow << "\nColumn: " << numCol << '\n';
				}

				else if (curSym == '\n')
				{
					numCol = 0;
					numRow = numRow + 1;
				}

			}
		}

		in.close();
		return;
	}


	std::cout << "Could not open file!\n";
}

int main()
{



	return 0;
}

