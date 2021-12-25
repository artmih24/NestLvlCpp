#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main() { 
	int i = 0;
	while (i++ < 10)
		cout << "hello world" << endl; //0
	while (i++ < 10)
		while (i++ < 10)
			cout << "hello world" << endl; //1
	while (i++ < 10){
		while (i++ < 10)
			cout << "hello world" << endl; //1
		while (i++ < 10)
			cout << "hello world" << endl; //1
		while (i++ < 10){
			while (i++ < 10)
				cout << "hello world" << endl; //2
			while (i++ < 10)
				cout << "hello world" << endl; //2
		}
		while (i++ < 10)
			while (i++ < 10)
				cout << "hello world" << endl; //2
	}
	while (i++ < 10)
		while (i++ < 10)
			while (i++ < 10)
				cout << "hello world" << endl; //2
}