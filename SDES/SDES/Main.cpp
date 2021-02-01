#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;

#include <utility>
using std::swap;

#include <string>
using std::getline;

#include <bitset>
using std::bitset;

void Encryption(char input[], char key[]);
void Decryption(char input[], char key[]);
bool BitCheck(const string& bits);
char* GenerateKeys(char key[]);
char* Shift(char input[]);

int main()
{
	int  menu = 3;
	bool done = false;

	string  inputStr, keyStr = " ";


	cout << "SDES Cipher" << endl;
	cout << "Would you like to encrypt or decrypt?" << endl;
	cout << "Please enter 1 for encrypt.\n"
		<< "Please enter 2 for decrypt.\n" << endl;

	cout << "Enter key." << endl;
	cin >> keyStr;

	char key_array[11];
	strcpy(key_array, keyStr.c_str());

	GenerateKeys(key_array);

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

	return 0;
}

char* GenerateKeys(char key[]) {
	/*a.Swap bits like this.
		(k1, k2, k3, k4, k5, k6, k7, k8, k9, k10) TO(k3, k5, k2, k7, k4, k10, k1, k9, k8, k6)
		b.Split new key into 2 arrays of 5 Key1[] Key2[]
		c.Perform same shift on each key.
		d.Combine both keys into 1 array Key3[]
		e.Split Key3[] from(k1, k2, k3, k4, k5, k6, k7, k8, k9, k10) which should still be the same order from before split, to(k6, k3, k7, k4, k8, k5, k10, k9) which is KEY 1.
		f.Perform another shift on Key1[] and Key2[] from before then perform step d and e again.*/

	char keyRay1[10] = { '0','1','2','3','4','5','6','7','8','9' };
	char keyRay2[10] = { '0','1','2','3','4','5','6','7','8','9' };



	swap(keyRay1[0], key[2]);
	swap(keyRay1[1], key[4]);
	swap(keyRay1[2], key[1]);
	swap(keyRay1[3], key[6]);
	swap(keyRay1[4], key[3]);
	swap(keyRay1[5], key[9]);
	swap(keyRay1[6], key[0]);
	swap(keyRay1[7], key[8]);
	swap(keyRay1[8], key[7]);
	swap(keyRay1[9], key[5]);

	Shift(keyRay1);

		//keyRay1 = keyRay3[5] and keyRay4[5]

		return keyRay1, keyRay2;
}

char* Shift(char input[]) {

	// FIX THIS JANKY SHIT
	char shiftKeyRay1[5] = { '/0' };
	char shiftKeyRay2[5] = { '/0' };
	int arrSize = (sizeof(input) / sizeof(input[0]));
	int maxSize = arrSize * 2;
	int i,k;

	

	for (i = 0; i <= arrSize; ++i) {
		shiftKeyRay1[i] = input[i];
		cout << shiftKeyRay1[i];
	}
	cout << endl;
	for (i = arrSize, k = 0; i <= maxSize ; ++i, ++k) {
		shiftKeyRay2[k] = input[i];
		cout << shiftKeyRay2[k];
	}
	cout << endl;

	return input;
}

void Encryption(char input[], char key[])
{
	//might have to use a different var type
	string encrypt_binary = input;
	string encryptKey = key;




	//set check to make sure input is all ones and zero's


}

void Decryption(char input[], char key[])
{
	//might have to use a different var type
	string decrypt_binary = input;
	string userKey = key;


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
