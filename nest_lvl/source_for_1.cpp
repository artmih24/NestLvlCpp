#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main() { 
	string str1 = "qwerty", str2 = "for (;;)";
	char char1 = 'c', char2 = 'h';
	for (int i = 0; i < 5; i++) 
		for (int j = 0; j < 5; i++)
			cout << "Hello, world!" << endl;//1
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; i++)
			for (int k = 0; k < 5; i++)
				for (int l = 0; l < 5; i++)
					cout << "Hello, world!" << endl;//3
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; i++)
			cout << "Hello, world!" << endl;//1
		for (int k = 0; k < 5; i++)
			for (int l = 0; l < 5; i++)
				cout << "Hello, world!" << endl;//2
		for (int i = 0; i < 5; i++){
			for (int j = 0; j < 5; i++)
				cout << "Hello, world!" << endl;//2
			for (int k = 0; k < 5; i++)
				for (int l = 0; l < 5; i++)
					cout << "Hello, world!" << endl;//3
		}
	}
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; i++)
			for (int k = 0; k < 5; i++)
				for (int l = 0; l < 5; i++)
					cout << "Hello, world!" << endl;//3
		for (int j = 0; j < 5; i++)
			for (int k = 0; k < 5; i++)
				for (int l = 0; l < 5; i++)
					cout << "Hello, world!" << endl;//3
	}
    system("pause");
    return 0; 
}