#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

//The test task result is located at author's Git repository

//Reverses the positions of two characters
void Swap(char &first, char &second)
{
	char temp = first;
	first = second;
	second = temp;
}
//Turns the c-string massive backwards
void Reverse(char *arr, int size)
{
	for (int i = 0; i <= size / 2; i++)
		Swap(arr[i], arr[size - i]);
}
//This method should revert the word sequences. (e.g. "word1 word2 word3" -> "word3 word2 word1")
void revertWords(char* arr)
{
	if (&arr[0] == nullptr)
		return;
	int size = 0;
	int wordStartIndex;
	int wordEndIndex;

	for (wordStartIndex = 0; arr[wordStartIndex] == ' '; wordStartIndex++) {}
	wordEndIndex = wordStartIndex;

	while (arr[size++] != '\0')
	{
		if ((arr[size - 1] == ' ') && (arr[size] != ' '))
		{
			wordEndIndex = size - 1;
			Reverse(&(arr[wordStartIndex]), wordEndIndex - wordStartIndex - 1);
			wordStartIndex = wordEndIndex + 1;
		}
	}
	size -= 2;
	wordEndIndex = size;
	Reverse(&(arr[wordStartIndex]), wordEndIndex - wordStartIndex);

	Reverse(arr, size);
}

//Revert words using previous method and return the longest.
std::string processWords(std::string &input)//!!!
{
	revertWords(&input[0]);

	string theLongest;
	int wordStartIndex;
	int wordEndIndex;
	int maxWordStartIndex;
	int maxWordEndIndex;

	for (maxWordStartIndex = 0; input[maxWordStartIndex] == ' '; maxWordStartIndex++) {}
	maxWordEndIndex = wordEndIndex = wordStartIndex = maxWordStartIndex;

	for (int i = 1; i < input.length(); i++)
	{
		if ((input[i] == ' ') && (input[i - 1] != ' '))
		{
			wordEndIndex = i - 1;
			if (maxWordEndIndex - maxWordStartIndex < wordEndIndex - wordStartIndex)
			{
				maxWordEndIndex = wordEndIndex;
				maxWordStartIndex = wordStartIndex;
			}
			wordStartIndex = wordEndIndex + 1;

			while ((input[wordStartIndex] == ' ') && (i < input.length()))
				//while (input[wordStartIndex] == ' ')
			{
				wordStartIndex++;
				i = wordStartIndex;
			}
		}
	}
	return input.substr(maxWordStartIndex, maxWordEndIndex - maxWordStartIndex + 1);
}

//Create a method to generate an array of random length (10-20) random signed integer numbers.
//Print the generated sequence in console.
signed int* arr;
void intGenerator(signed int* arr)
{
	srand(time(0));
	int size = 10 + rand() % 11;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(1, RAND_MAX);

	for (int i = 0; i < size; i++)
	{
		arr[i] = (rand() % 2) ? (-1)*dis(gen) : dis(gen);
		cout << arr[i] << " ";
	}
	arr[size + 1] = 0;
	cout << endl;
}

//Using the result of previous method, find the minimal value in the array.
signed int signedMin(signed int* arr)
{
	arr = new signed int();

	intGenerator(arr);

	int tempMin = arr[0];
	for (int i = 1; arr[i] != 0; i++)
	{
		if (arr[i] < tempMin)
			tempMin = arr[i];
	}
	return tempMin;
};

int main() //DO NOT MODIFY THIS BLOCK
{
	std::cout << "Test started" << std::endl;
	std::cout << "Please input a text with several words" << std::endl;
	std::string input;
	std::getline(std::cin, input);
	std::cout << "Input text: " << input << std::endl;
	std::cout << "Longest word: " << processWords(input) << std::endl;
	std::cout << "Reverted text: " << input << std::endl;
	std::cout << "Minimal is : " << signedMin(arr) << std::endl;
	std::cout << std::endl << "Test ended";
	delete[] arr;
	return 0;
}