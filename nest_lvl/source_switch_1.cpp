#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main() { 
	int i = 0;
	switch (i){
		case 1:
			cout << "Hello, world!" << endl;
		case 2:
			cout << "Hello, world!" << endl;
		case 3:
			cout << "Hello, world!" << endl;
		case 4:
			cout << "Hello, world!" << endl;
		default:
			cout << "Hello, world!" << endl;
	}
	switch (i){
		case 1:
			switch (i){
				case 1:
					cout << "Hello, world!" << endl;
				case 2:
					cout << "Hello, world!" << endl;
				case 3:
					cout << "Hello, world!" << endl;
				case 4:
					cout << "Hello, world!" << endl;
				default:
					cout << "Hello, world!" << endl;
			}
		case 2:
			cout << "Hello, world!" << endl;
		case 3:
			cout << "Hello, world!" << endl;
		case 4:
			cout << "Hello, world!" << endl;
		default:
			cout << "Hello, world!" << endl;
	}
	switch (i){
		case 1:
			switch (i){
				case 1:
					cout << "Hello, world!" << endl;
				case 2:
					cout << "Hello, world!" << endl;
				case 3:
					cout << "Hello, world!" << endl;
				case 4:
					cout << "Hello, world!" << endl;
				default:
					cout << "Hello, world!" << endl;
			}
		case 2:
			cout << "Hello, world!" << endl;
		case 3:
			cout << "Hello, world!" << endl;
		case 4:
			switch (i){
				case 1:
					cout << "Hello, world!" << endl;
				case 2:
					cout << "Hello, world!" << endl;
				case 3:
					cout << "Hello, world!" << endl;
				case 4:
					cout << "Hello, world!" << endl;
				default:
					cout << "Hello, world!" << endl;
			}
		default:
			cout << "Hello, world!" << endl;
	}
	switch (i){
		case 1:
			switch (i){
				case 1:
					switch (i){
						case 1:
							cout << "Hello, world!" << endl;
						case 2:
							cout << "Hello, world!" << endl;
						case 3:
							cout << "Hello, world!" << endl;
						case 4:
							cout << "Hello, world!" << endl;
						default:
							cout << "Hello, world!" << endl;
					}
				case 2:
					cout << "Hello, world!" << endl;
				case 3:
					cout << "Hello, world!" << endl;
				case 4:
					switch (i){
						case 1:
							cout << "Hello, world!" << endl;
						case 2:
							cout << "Hello, world!" << endl;
						case 3:
							cout << "Hello, world!" << endl;
						case 4:
							cout << "Hello, world!" << endl;
						default:
							cout << "Hello, world!" << endl;
					}
				default:
					cout << "Hello, world!" << endl;
			}
		case 2:
			cout << "Hello, world!" << endl;
		case 3:
			cout << "Hello, world!" << endl;
		case 4:
			switch (i){
				case 1:
					cout << "Hello, world!" << endl;
				case 2:
					cout << "Hello, world!" << endl;
				case 3:
					cout << "Hello, world!" << endl;
				case 4:
					cout << "Hello, world!" << endl;
				default:
					cout << "Hello, world!" << endl;
			}
		default:
			cout << "Hello, world!" << endl;
	}
}