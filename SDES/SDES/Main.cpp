#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
//using std::to_string;

#include <utility>
using std::swap;

#include <string>
using std::getline;

#include <bitset>
using std::bitset;

void Encryption(char userInput[], char key[]);
void Decryption(char input[], char key[]);
bool BitCheck(const string& bits);
char* Swap(char key[]);
char* PtSwap(char pt[]);
void EPSwap(char splitPT[], char result[]);
char* Shift1(char key[]);
char* Shift3(char key[]);
void XorWithKey(char plaintext[], char key[], char result[]);
void SBoxZero(char splitPT[], char result[]);
void SBoxOne(char splitPT[], char result[]);


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//int  menu = 3;
	//bool done = false;

	string inputStr = " ";
	string keyStr = " ";
	char key_array[11] = { '/0' };
	char pt_array[9] = { '/0' };

	/*
	cout << "SDES Cipher" << endl;
	cout << "Would you like to encrypt or decrypt?" << endl;
	cout << "Please enter 1 for encrypt.\n"
		<< "Please enter 2 for decrypt.\n" << endl;
	*/

	cout << "Enter 10-bit key." << endl;
	cin >> keyStr;

	cout << "Enter 8-bit Plaintext." << endl;
	cin >> inputStr;

	strcpy(key_array, keyStr.c_str());
	strcpy(pt_array, inputStr.c_str());

	Encryption(pt_array, key_array);

	//cin >> menu;
	//do
	//{
	//	switch (menu)
	//	{
	//	case 1:
	//		cout << "Enter the binary you would to encrypt" << endl;
	//		cin >> inputStr;

	//		cout << "Enter the key" << endl;
	//		cin >> keyStr;

	//		if (BitCheck(inputStr) == true && BitCheck(keyStr) == true)
	//		{
	//			if (inputStr.length() == 8)
	//			{
	//				if (keyStr.length() == 10)
	//				{
	//					char input_array[9];
	//					strcpy(input_array, inputStr.c_str());
	//					
	//					char key_array[11];
	//					strcpy(key_array, keyStr.c_str());

	//					
	//					Encryption(inputStr, keyStr);

	//					
	//					done = true;
	//				}
	//				else
	//				{
	//					done = false;
	//				}
	//			}
	//			else
	//			{
	//				done = false;
	//			}
	//		}
	//		else
	//		{
	//			done = false;
	//		}

	//		break;

	//	case 2:
	//		cout << "Enter the binary you would to decrypt" << endl;
	//		cin >> inputStr;

	//		cout << "Enter the key" << endl;
	//		cin >> keyStr;

	//		if (BitCheck(inputStr) == true && BitCheck(keyStr) == true)
	//		{
	//			if (inputStr.length() == 8)
	//			{
	//				if (keyStr.length() == 10)
	//				{
	//					char input_array[9];
	//					strcpy(input_array, inputStr.c_str());
	//					char key_array[11];
	//					strcpy(key_array, keyStr.c_str());

	//					done = true;

	//					Encryption(inputStr, keyStr);
	//				}
	//				else
	//				{
	//					done = false;
	//				}
	//			}
	//			else
	//			{
	//				done = false;
	//			}
	//		}
	//		break;

	//	default:
	//		cout << "Invalid Choice" << endl;
	//	}
	//} while (done == false);

	system("pause");

	return 0;
}

void Encryption(char userInput[], char userKey[])
{
	/*
		P10 = (k3, k5, k2, k7, k4, k10, k1, k9, k8, k6)
		P8  = (k6, k3, k7, k4, k8, k5, k10, k9) which is KEY 1.
	*/

	char key1[10] = { '/0' };
	char key2[10] = { '/0' };
	char finalKey1[8] = { '/0' };
	char finalKey2[8] = { '/0' };
	char plaintext[8] = { '/0' };
	char splitPT1[4] = { '/0' };
	char splitPT2[4] = { '/0' };
	char XorPT2[8] = { '/0' };
	char SBoxSplit1[4] = { '/0' };
	char SBoxSplit2[4] = { '/0' };
	char SBoxResult1[2] = { '/0' };
	char SBoxResult2[2] = { '/0' };

	//COPY USERKEY TO KEY1 AND KEY2
	for (int i = 0; i < 10; ++i) {
		key1[i] = userKey[i];
		key2[i] = userKey[i];
	}

	//COPY USERINPUT TO PLAINTEXT
	for (int i = 0; i < 8; ++i) {
		plaintext[i] = userInput[i];
	}

	//FUNCTION CALLS TO GENERATE KEY 1
	cout << "~~ Generating Key 1 ~~" << endl;
	Swap(key1);
	Shift1(key1);

	//FUNCTION CALLS TO GENERATE KEY 2
	cout << "~~ Generating Key 2 ~~" << endl;
	Swap(key2);
	Shift3(key2);

	for (int i = 0; i < 8; ++i) {
		finalKey1[i] = key1[i];
		finalKey2[i] = key2[i];
	}

	//BEGIN ENCRYPTING plaintext with key1 and key2
	PtSwap(plaintext);

	//SPLIT PLAINTEXT INTO 2 PARTS
	cout << "Split Part 1: ";
	for (int i = 0; i < 4; ++i) {
		splitPT1[i] = plaintext[i];
		cout << splitPT1[i];
	}
	cout << endl;

	cout << "Split Part 2: ";
	for (int i = 4, k = 0; i < 8; ++i, ++k) {
		splitPT2[k] = plaintext[i];
		cout << splitPT2[k];
	}
	cout << endl;

	//XOR PART 2 OF PLAINTEXT WITH KEY 1
	XorWithKey(splitPT2, finalKey1, XorPT2);

	//SPLIT XOR'D PLAINTEXT INTO 2 PARTS
	cout << "Pre Sbox Split Part 1: ";
	for (int i = 0; i < 4; ++i) {
		SBoxSplit1[i] = XorPT2[i];
		cout << SBoxSplit1[i];
	}
	cout << endl;

	cout << "Pre Sbox Split Part 2: ";
	for (int i = 4, k = 0; i < 8; ++i, ++k) {
		SBoxSplit2[k] = XorPT2[i];
		cout << SBoxSplit2[k];
	}
	cout << endl;

	//SBOX FUCNTION CALL
	SBoxZero(SBoxSplit1, SBoxResult1);
	SBoxOne(SBoxSplit2, SBoxResult2);


}

void Decryption(char input[], char key[])
{
	//might have to use a different var type
	string decrypt_binary = input;
	string userKey = key;

}

char* Swap(char key[]) {

	char swappedKey[10] = { '/0' };

	swap(swappedKey[0], key[2]);
	swap(swappedKey[1], key[4]);
	swap(swappedKey[2], key[1]);
	swap(swappedKey[3], key[6]);
	swap(swappedKey[4], key[3]);
	swap(swappedKey[5], key[9]);
	swap(swappedKey[6], key[0]);
	swap(swappedKey[7], key[8]);
	swap(swappedKey[8], key[7]);
	swap(swappedKey[9], key[5]);

	cout << "P10 Swap: ";
	for (int i = 0; i < 10; ++i) {
		key[i] = swappedKey[i];
		cout << key[i];
	}
	cout << endl;

	return key;
}

char* PtSwap(char pt[]) {

	char swappedPt[8] = { '/0' };

	swap(swappedPt[0], pt[1]);
	swap(swappedPt[1], pt[5]);
	swap(swappedPt[2], pt[2]);
	swap(swappedPt[3], pt[0]);
	swap(swappedPt[4], pt[3]);
	swap(swappedPt[5], pt[7]);
	swap(swappedPt[6], pt[4]);
	swap(swappedPt[7], pt[6]);

	cout << "IP Swap: ";
	for (int i = 0; i < 8; ++i) {
		pt[i] = swappedPt[i];
		cout << pt[i];
	}
	cout << endl;

	return pt;
}

void EPSwap(char splitPT[], char Result[]) {

	Result[0] = splitPT[3];
	Result[1] = splitPT[0];
	Result[2] = splitPT[1];
	Result[3] = splitPT[2];
	Result[4] = splitPT[1];
	Result[5] = splitPT[2];
	Result[6] = splitPT[3];
	Result[7] = splitPT[0];

	cout << "EP Swap: ";
	for (int i = 0; i < 8; ++i) {
		cout << Result[i];
	}
	cout << endl;

}

char* Shift1(char key[]) {

	char shiftedKey[8] = { '/0' };
	char splitKey1[5] = { '/0' };
	char splitKey2[5] = { '/0' };
	char shiftKey1[5] = { '/0' };
	char shiftKey2[5] = { '/0' };
	char mergedKeys[10] = { '/0' };

	// SPLIT KEY INTO TWO PARTS
	cout << "Split Part 1: ";
	for (int i = 0; i < 5; ++i) {
		splitKey1[i] = key[i];
		cout << splitKey1[i];
	}
	cout << endl;

	cout << "Split Part 2: ";
	for (int i = 5, k = 0; i < 10; ++i, ++k) {
		splitKey2[k] = key[i];
		cout << splitKey2[k];
	}
	cout << endl;


	// CIRCLE LEFT SHIFT BOTH KEY PARTS
	for (int i = 1, k = 0; i < 5; ++i, ++k) {
		shiftKey1[k] = splitKey1[i];
		shiftKey2[k] = splitKey2[i];
	}
	shiftKey1[4] = splitKey1[0];
	shiftKey2[4] = splitKey2[0];

	cout << "Circle Left Shift Part 1: ";
	for (int i = 0; i < 5; ++i) {
		cout << shiftKey1[i];
	}
	cout << endl;
	cout << "Circle Left Shift Part 2: ";
	for (int i = 0; i < 5; ++i) {
		cout << shiftKey2[i];
	}
	cout << endl;


	// MERGE SHIFTED KEYS
	for (int i = 0, k = 0, j = 5; i < 5; ++i, ++k, ++j) {
		mergedKeys[i] = shiftKey1[k];
		mergedKeys[j] = shiftKey2[k];
	}

	cout << "Merged Key: ";
	for (int i = 0; i < 10; ++i) {
		cout << mergedKeys[i];
	}
	cout << endl;


	// P8 SWAP 
	swap(key[0], mergedKeys[5]);
	swap(key[1], mergedKeys[2]);
	swap(key[2], mergedKeys[6]);
	swap(key[3], mergedKeys[3]);
	swap(key[4], mergedKeys[7]);
	swap(key[5], mergedKeys[4]);
	swap(key[6], mergedKeys[9]);
	swap(key[7], mergedKeys[8]);

	cout << "P8 Swap & Returned Key 1: ";
	for (int i = 0; i < 8; ++i) {
		cout << key[i];
	}
	cout << endl;

	return key;
}

char* Shift3(char key[]) {

	char shiftedKey[8] = { '/0' };
	char splitKey1[5] = { '/0' };
	char splitKey2[5] = { '/0' };
	char shiftKey1[5] = { '/0' };
	char shiftKey2[5] = { '/0' };
	char mergedKeys[10] = { '/0' };

	// SPLIT KEY INTO TWO PARTS
	cout << "Split Part 1: ";
	for (int i = 0; i < 5; ++i) {
		splitKey1[i] = key[i];
		cout << splitKey1[i];
	}
	cout << endl;

	cout << "Split Part 2: ";
	for (int i = 5, k = 0; i < 10; ++i, ++k) {
		splitKey2[k] = key[i];
		cout << splitKey2[k];
	}
	cout << endl;


	// CIRCLE LEFT SHIFT 3 BOTH KEY PARTS
	for (int i = 0, k = 2; i < 3; ++i, ++k) {
		shiftKey1[k] = splitKey1[i];
		shiftKey2[k] = splitKey2[i];
	}
	shiftKey1[0] = splitKey1[3];
	shiftKey2[0] = splitKey2[3];
	shiftKey1[1] = splitKey1[4];
	shiftKey2[1] = splitKey2[4];

	cout << "Circle Left Shift Part 1: ";
	for (int i = 0; i < 5; ++i) {
		cout << shiftKey1[i];
	}
	cout << endl;
	cout << "Circle Left Shift Part 2: ";
	for (int i = 0; i < 5; ++i) {
		cout << shiftKey2[i];
	}
	cout << endl;


	// MERGE SHIFTED KEYS
	for (int i = 0, k = 0, j = 5; i < 5; ++i, ++k, ++j) {
		mergedKeys[i] = shiftKey1[k];
		mergedKeys[j] = shiftKey2[k];
	}

	cout << "Merged Key: ";
	for (int i = 0; i < 10; ++i) {
		cout << mergedKeys[i];
	}
	cout << endl;


	// P8 SWAP 
	swap(key[0], mergedKeys[5]);
	swap(key[1], mergedKeys[2]);
	swap(key[2], mergedKeys[6]);
	swap(key[3], mergedKeys[3]);
	swap(key[4], mergedKeys[7]);
	swap(key[5], mergedKeys[4]);
	swap(key[6], mergedKeys[9]);
	swap(key[7], mergedKeys[8]);

	cout << "P8 Swap & Returned Key 1: ";
	for (int i = 0; i < 8; ++i) {
		cout << key[i];
	}
	cout << endl;

	return key;
}

void XorWithKey(char plaintext[], char key[], char result[]) {

	char EPPlaintext[4] = { '/0' };
	char EPPResult[8] = { '/0' };

	//COPY PASSED IN PLAINTEXT TO DISPOSABLE CHAR ARRAY
	for (int i = 0; i < 4; ++i) {
		EPPlaintext[i] = plaintext[i];
	}

	//FUNCTION CALL TO PERFORM EP SWAP
	EPSwap(EPPlaintext, EPPResult);

	cout << "XOR Result: ";
	for (int i = 0; i < 8; ++i) {
		if ((EPPResult[i] == '0' && key[i] == '0') || (EPPResult[i] == '1' && key[i] == '1')) {
			result[i] = '0';
		}
		else if ((EPPResult[i] == '0' && key[i] == '1') || (EPPResult[i] == '1' && key[i] == '0')) {
			result[i] = '1';
		}
		cout << result[i];
	}
	cout << endl;
}

void SBoxZero(char splitPT[], char result[]) {

	// split box into 2 4 bit arrays
	// use the sboxes from book on arrays
	// combine 2bit arrays into single 4 bit array
	// reposition 4bit array and return that
	int SBox0[4][4] = { 1,0,3,2,3,2,1,0,0,2,1,3,3,1,3,2 };
	//char* S0 = new char[3];
	const char *bits[4] = { "00","01","10","11" };
	char row[2];
	char col[2];
	int lr, lc, a;

	row[0] = splitPT[0];
	row[1] = splitPT[3];
	col[0] = splitPT[1];
	col[1] = splitPT[2];

	//CAN'T GET THEM TO COMPARE AND CHANGE LR AND LC....
	//Probably sothing to do with us not passing in a pointer for strcmp to work but that's a bit out of the question here.
	for (int i = 0; i < 4; ++i) {
		if (strcmp(row, bits[i]) == 0) {
			lr = i;
		}
		if (strcmp(col, bits[i]) == 0) {
			lc = i;
		}
	}

	//a = SBox0[lr][lc];
	//for (int i = 0; i < 3; ++i) {
	//	S0[i] = bits[a][i];
	//}

}

void SBoxOne(char splitPT[], char result[]) {

	// split box into 2 4 bit arrays
	// use the sboxes from book on arrays
	// combine 2bit arrays into single 4 bit array
	// reposition 4bit array and return that
	char S0[4] = { '\0' };
	char sBox1[4][4] = { '\0' };

	//CREATE S-BOX 1
	sBox1[0][0] = '0';
	sBox1[0][1] = '1';
	sBox1[0][2] = '2';
	sBox1[0][3] = '3';
	sBox1[1][0] = '2';
	sBox1[1][1] = '0';
	sBox1[1][2] = '1';
	sBox1[1][3] = '3';
	sBox1[2][0] = '3';
	sBox1[2][1] = '0';
	sBox1[2][2] = '1';
	sBox1[2][3] = '0';
	sBox1[3][0] = '2';
	sBox1[3][1] = '1';
	sBox1[3][2] = '0';
	sBox1[3][3] = '3';

	//DISPLAY S-BOX 1
	cout << "S1 BOX:" << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << sBox1[i][j];
		}
		cout << endl;
	}


}




//bool BitCheck(const string & bits)
//{
//	bool pass = false;
//
//	do
//	{
//
//		for (int i = 0; i < bits.length(); i++)
//		{
//
//			if ()
//			{
//
//			}
//
//		}
//	} while (pass == true);
//
//	return pass;
//}
