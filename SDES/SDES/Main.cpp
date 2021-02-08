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
void Decryption(char userInput[], char key1[], char key2[]);
bool BitCheck(const string& bits);
char* Swap(char key[]);
char* PtSwap(char pt[]);
void InversePtSwap(char XorStep1[], char XorStep2[], char Result[]);
void EPSwap(char splitPT[], char result[]);
char* Shift1(char key[]);
char* Shift3(char key[]);
void XorWithKey(char plaintext[], char key[], char result[]);
void SBoxZero(char splitPT[], char result[]);
void SBoxOne(char splitPT[], char result[]);
void P4Swap(char SBoxResult1[], char SBoxResult2[], char Result[]);
void Xor4Bit(char SplitPT1[], char P4Result[], char result[]);


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int  menu = 3;
	bool done = false;

	string inputStr = " ";
	string TenBitKey = " ";
	string EightBitKey1 = " ";
	string EightBitKey2 = " ";
	char TenBitKeyRay[11] = { '/0' };
	char EightBitKeyRay1[9] = { '/0' };
	char EightBitKeyRay2[9] = { '/0' };
	char pt_array[9] = { '/0' };


	cout << "SDES Cipher" << endl;
	cout << "Would you like to encrypt or decrypt?" << endl;
	cout << "Please enter 1 for encrypt.\n"
		<< "Please enter 2 for decrypt.\n" << endl;

	//ENCRYPTION
	//cout << "Enter 10-bit key." << endl;
	//cin >> TenBitKey;

	//cout << "Enter 8-bit Plaintext." << endl;
	//cin >> inputStr;

	//strcpy(TenBitKeyRay, TenBitKey.c_str());
	//strcpy(pt_array, inputStr.c_str());

	//Encryption(pt_array, TenBitKeyRay);


	////DECRYPTION
	//cout << "Enter 8-bit key 1." << endl;
	//cin >> EightBitKey1;

	//cout << "Enter 8-bit key 2." << endl;
	//cin >> EightBitKey2;

	//cout << "Enter 8-bit Ciphertext." << endl;
	//cin >> inputStr;

	//strcpy(EightBitKeyRay1, EightBitKey1.c_str());
	//strcpy(EightBitKeyRay2, EightBitKey2.c_str());
	//strcpy(pt_array, inputStr.c_str());

	//Decryption(pt_array, EightBitKeyRay1, EightBitKeyRay2);

	cin >> menu;
	do
	{
		switch (menu)
		{
		case 1:
			cout << "Enter 10-bit key." << endl;
			cin >> TenBitKey;

			cout << "Enter 8-bit Plaintext." << endl;
			cin >> inputStr;

			if (BitCheck(inputStr) == true && BitCheck(TenBitKey) == true)
			{
				if (inputStr.length() == 8 && TenBitKey.length() == 10)
				{
					strcpy(pt_array, inputStr.c_str());

					strcpy(TenBitKeyRay, TenBitKey.c_str());

					Encryption(pt_array, TenBitKeyRay);

					done = true;

				}
				else
				{
					done = false;
				}
			}
			else
			{
				done = false;
			}
			break;

		case 2:
			cout << "Enter 8-bit key 1." << endl;
			cin >> EightBitKey1;

			cout << "Enter 8-bit key 2." << endl;
			cin >> EightBitKey2;

			cout << "Enter 8-bit Ciphertext." << endl;
			cin >> inputStr;

			if (BitCheck(inputStr) == true && BitCheck(EightBitKey1) == true && BitCheck(EightBitKey2) == true)
			{
				if (inputStr.length() == 8 && EightBitKey1.length() == 10 && EightBitKey2.length() == 10)
				{
					strcpy(EightBitKeyRay1, EightBitKey1.c_str());
					strcpy(EightBitKeyRay2, EightBitKey2.c_str());
					strcpy(pt_array, inputStr.c_str());

					Decryption(pt_array, EightBitKeyRay1, EightBitKeyRay2);

					done = true;
				}
				else
				{
					done = false;
				}
			}
			break;

		default:
			cout << "Invalid Choice" << endl;
		}
	} while (done == false);

	system("pause");

	return 0;
}

void Encryption(char userInput[], char userKey[])
{

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
	char P4Result[4] = { '/0' };
	char Xor4BitResultStep1[4] = { '/0' };
	char Xor4BitResultStep2[4] = { '/0' };
	char EncryptedPT[8] = { '/0' };

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
	Swap(key1);
	Shift1(key1);

	cout << "Key 1 is: ";
	for (int i = 0; i < 8; ++i) {
		finalKey1[i] = key1[i];
		cout << finalKey1[i];
	}
	cout << "\n" << endl;

	//FUNCTION CALLS TO GENERATE KEY 2
	Swap(key2);
	Shift3(key2);

	cout << "Key 2 is: ";
	for (int i = 0; i < 8; ++i) {
		finalKey2[i] = key2[i];
		cout << finalKey2[i];
	}
	cout << "\n" << endl;

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

	//P4 SWAP FUNCTION CALL
	P4Swap(SBoxResult1, SBoxResult2, P4Result);

	//XOR FUNCTION CALL "FINAL PART FIRST HALF OF ENCRYPTION"
	Xor4Bit(splitPT1, P4Result, Xor4BitResultStep1);


	//PART 2


	//XOR PART 2 OF PLAINTEXT WITH KEY 1
	XorWithKey(Xor4BitResultStep1, finalKey2, XorPT2);

	//SPLIT XOR'D PLAINTEXT INTO 2 PARTS
	cout << "Pre Sbox Split Part 3: ";
	for (int i = 0; i < 4; ++i) {
		SBoxSplit1[i] = XorPT2[i];
		cout << SBoxSplit1[i];
	}
	cout << endl;

	cout << "Pre Sbox Split Part 4: ";
	for (int i = 4, k = 0; i < 8; ++i, ++k) {
		SBoxSplit2[k] = XorPT2[i];
		cout << SBoxSplit2[k];
	}
	cout << endl;

	//SBOX FUCNTION CALL
	SBoxZero(SBoxSplit1, SBoxResult1);
	SBoxOne(SBoxSplit2, SBoxResult2);

	//P4 SWAP FUNCTION CALL
	P4Swap(SBoxResult1, SBoxResult2, P4Result);

	//XOR FUNCTION CALL "FINAL PART FIRST HALF OF ENCRYPTION"
	Xor4Bit(splitPT2, P4Result, Xor4BitResultStep2);

	//FINAL INVERSE SWAP FUNCTION CALL
	InversePtSwap(Xor4BitResultStep2, Xor4BitResultStep1, EncryptedPT);

	//COUT CIPHERTEXT TO USER
	cout << "Your encrypted Ciphertext is: ";
	for (int i = 0; i < 8; ++i) {
		cout << EncryptedPT[i];
	}
	cout << "\n" << endl;
}

void Decryption(char userInput[], char userKey1[], char userKey2[])
{

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
	char P4Result[4] = { '/0' };
	char Xor4BitResultStep1[4] = { '/0' };
	char Xor4BitResultStep2[4] = { '/0' };
	char EncryptedPT[8] = { '/0' };

	//COPY USERKEY TO KEY1 AND KEY2
	for (int i = 0; i < 8; ++i) {
		finalKey1[i] = userKey1[i];
		finalKey2[i] = userKey2[i];
	}

	//COPY USERINPUT TO PLAINTEXT
	for (int i = 0; i < 8; ++i) {
		plaintext[i] = userInput[i];
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
	XorWithKey(splitPT2, finalKey2, XorPT2);

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

	//P4 SWAP FUNCTION CALL
	P4Swap(SBoxResult1, SBoxResult2, P4Result);

	//XOR FUNCTION CALL "FINAL PART FIRST HALF OF ENCRYPTION"
	Xor4Bit(splitPT1, P4Result, Xor4BitResultStep1);


	//PART 2


	//XOR PART 2 OF PLAINTEXT WITH KEY 1
	XorWithKey(Xor4BitResultStep1, finalKey1, XorPT2);

	//SPLIT XOR'D PLAINTEXT INTO 2 PARTS
	cout << "Pre Sbox Split Part 3: ";
	for (int i = 0; i < 4; ++i) {
		SBoxSplit1[i] = XorPT2[i];
		cout << SBoxSplit1[i];
	}
	cout << endl;

	cout << "Pre Sbox Split Part 4: ";
	for (int i = 4, k = 0; i < 8; ++i, ++k) {
		SBoxSplit2[k] = XorPT2[i];
		cout << SBoxSplit2[k];
	}
	cout << endl;

	//SBOX FUCNTION CALL
	SBoxZero(SBoxSplit1, SBoxResult1);
	SBoxOne(SBoxSplit2, SBoxResult2);

	//P4 SWAP FUNCTION CALL
	P4Swap(SBoxResult1, SBoxResult2, P4Result);

	//XOR FUNCTION CALL "FINAL PART FIRST HALF OF ENCRYPTION"
	Xor4Bit(splitPT2, P4Result, Xor4BitResultStep2);

	//FINAL INVERSE SWAP FUNCTION CALL
	InversePtSwap(Xor4BitResultStep2, Xor4BitResultStep1, EncryptedPT);

	//COUT CIPHERTEXT TO USER
	cout << "Your decrypted Ciphertext is: ";
	for (int i = 0; i < 8; ++i) {
		cout << EncryptedPT[i];
	}
	cout << "\n" << endl;
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

void InversePtSwap(char XorStep1[], char XorStep2[], char Result[]) {

	char temp[8] = { '/0' };

	//INVERSE SWAP OF PLAINTEXT 4 1 3 5 7 2 8 6
	for (int i = 0, j = 4; i < 4; ++i, ++j) {
		temp[i] = XorStep1[i];
		temp[j] = XorStep2[i];
	}

	swap(Result[0], temp[3]);
	swap(Result[1], temp[0]);
	swap(Result[2], temp[2]);
	swap(Result[3], temp[4]);
	swap(Result[4], temp[6]);
	swap(Result[5], temp[1]);
	swap(Result[6], temp[7]);
	swap(Result[7], temp[5]);

	cout << "Inverse IP Swap: ";
	for (int i = 0; i < 8; ++i) {
		cout << Result[i];
	}
	cout << endl;
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

	//cout << "Merged Key: ";
	//for (int i = 0; i < 10; ++i) {
	//	cout << mergedKeys[i];
	//}
	//cout << endl;


	// P8 SWAP 
	swap(key[0], mergedKeys[5]);
	swap(key[1], mergedKeys[2]);
	swap(key[2], mergedKeys[6]);
	swap(key[3], mergedKeys[3]);
	swap(key[4], mergedKeys[7]);
	swap(key[5], mergedKeys[4]);
	swap(key[6], mergedKeys[9]);
	swap(key[7], mergedKeys[8]);

	//cout << "P8 Swap & Returned Key 1: ";
	//for (int i = 0; i < 8; ++i) {
	//	cout << key[i];
	//}
	//cout << endl;

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

	int SBox0[4][4] = { 1,0,3,2,3,2,1,0,0,2,1,3,3,1,3,2 };
	const char* bits[4] = { "00","01","10","11" };
	char temp[] = "0";
	char row[3] = "0";
	char col[3] = "0";
	int lr, lc;

	//COPY 1ST POSTION AND 4TH POSITION OF SPLIT PLAINTEXT INTO NEW CHAR ARRAY
	row[0] = splitPT[0];
	temp[0] = splitPT[3];
	strcat(row, temp);

	//COPY 2ND POSTION AND 3RD POSITION OF SPLIT PLAINTEXT INTO NEW CHAR ARRAY
	col[0] = splitPT[1];
	temp[0] = splitPT[2];
	strcat(col, temp);

	//STRING COMPARE THE ROW AND COLUMN TO THE CONSTANT BITS VARIABLE TO FIND THE ROW AND COLUMN POSITION INT
	for (int i = 0; i < 4; ++i) {
		if (strcmp(row, bits[i]) == 0) {
			lr = i;
		}
		if (strcmp(col, bits[i]) == 0) {
			lc = i;
		}
	}

	//ASSIGN THE CORRECT VARIABLES TO RESULT BASED ON POSITION IN SBOX MATRIX
	if (SBox0[lr][lc] == 0) {
		result[0] = '0';
		result[1] = '0';
	}
	else if (SBox0[lr][lc] == 1) {
		result[0] = '0';
		result[1] = '1';
	}
	else if (SBox0[lr][lc] == 2) {
		result[0] = '1';
		result[1] = '0';
	}
	else if (SBox0[lr][lc] == 3) {
		result[0] = '1';
		result[1] = '1';
	}

	cout << "Post S-Box Zero: ";
	for (int i = 0; i < 2; ++i) {
		cout << result[i];
	}
	cout << endl;
}

void SBoxOne(char splitPT[], char result[]) {

	int SBox1[4][4] = { 0,1,2,3,2,0,1,3,3,0,1,0,2,1,0,3 };
	const char* bits[4] = { "00","01","10","11" };
	char temp[] = "0";
	char row[3] = "0";
	char col[3] = "0";
	int lr, lc;

	//COPY 1ST POSTION AND 4TH POSITION OF SPLIT PLAINTEXT INTO NEW CHAR ARRAY
	row[0] = splitPT[0];
	temp[0] = splitPT[3];
	strcat(row, temp);

	//COPY 2ND POSTION AND 3RD POSITION OF SPLIT PLAINTEXT INTO NEW CHAR ARRAY
	col[0] = splitPT[1];
	temp[0] = splitPT[2];
	strcat(col, temp);

	//STRING COMPARE THE ROW AND COLUMN TO THE CONSTANT BITS VARIABLE TO FIND THE ROW AND COLUMN POSITION INT
	for (int i = 0; i < 4; ++i) {
		if (strcmp(row, bits[i]) == 0) {
			lr = i;
		}
		if (strcmp(col, bits[i]) == 0) {
			lc = i;
		}
	}

	//ASSIGN THE CORRECT VARIABLES TO RESULT BASED ON POSITION IN SBOX MATRIX
	if (SBox1[lr][lc] == 0) {
		result[0] = '0';
		result[1] = '0';
	}
	else if (SBox1[lr][lc] == 1) {
		result[0] = '0';
		result[1] = '1';
	}
	else if (SBox1[lr][lc] == 2) {
		result[0] = '1';
		result[1] = '0';
	}
	else if (SBox1[lr][lc] == 3) {
		result[0] = '1';
		result[1] = '1';
	}

	cout << "Post S-Box One: ";
	for (int i = 0; i < 2; ++i) {
		cout << result[i];
	}
	cout << endl;
}

void P4Swap(char SBoxResult1[], char SBoxResult2[], char Result[]) {

	Result[0] = SBoxResult1[1];
	Result[1] = SBoxResult2[1];
	Result[2] = SBoxResult2[0];
	Result[3] = SBoxResult1[0];


	cout << "P4 Swap Result: ";
	for (int i = 0; i < 4; ++i) {
		cout << Result[i];
	}
	cout << endl;
}

void Xor4Bit(char SplitPT1[], char P4Result[], char result[]) {

	cout << "XOR Result: ";
	for (int i = 0; i < 4; ++i) {
		if ((SplitPT1[i] == '0' && P4Result[i] == '0') || (SplitPT1[i] == '1' && P4Result[i] == '1')) {
			result[i] = '0';
		}
		else if ((SplitPT1[i] == '0' && P4Result[i] == '1') || (SplitPT1[i] == '1' && P4Result[i] == '0')) {
			result[i] = '1';
		}
		cout << result[i];
	}
	cout << endl;
}

//char* InversePermutation(char input[])
//{
//	char swappedKey[10] = { '\0' };
//
//	swap(swappedKey[0], input[3]);
//	swap(swappedKey[1], input[0]);
//	swap(swappedKey[2], input[2]);
//	swap(swappedKey[3], input[4]);
//	swap(swappedKey[4], input[6]);
//	swap(swappedKey[5], input[1]);
//	swap(swappedKey[6], input[7]);
//	swap(swappedKey[7], input[5]);
//
//
//
//	return swappedKey;
//}


bool BitCheck(const string& bits)
{
	const char* m_bits[2] = { "0","1" };
	char temp[10] = { "0" };
	bool pass = false;

	//PUT BITS PASSED IN INTO AN ARRAY
	strcpy(temp, bits.c_str());

	//COMPARE EACH BIT FROM THE STRING PASSED IN AGAINST SMALLER ARRAY WITH 1 AND 0 IN IT
	for (int i = 0; i < 2; i++)
	{
		if (strcmp(temp, m_bits[i]) == 0)
		{
			pass = true;
		}
		else
		{
			pass = false;
		}
	}

	return pass;
}
