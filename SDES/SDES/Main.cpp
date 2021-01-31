#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;

#include <bitset>
using std::bitset;

void Encryption(char input[], char key[]);
void Decryption(char input[], char key[]);
bool BitCheck(const string &  bits);


int main()
{
	int  menu = 3;
	bool done = false;

	string  inputStr,  keyStr = " ";
	

	cout << "SDES Cipher" << endl;
	cout << "Would you like to encrypt or decrypt?" << endl;
	cout << "Please enter 1 for encrypt.\n"
		<< "Please enter 2 for decrypt.\n" << endl;

	cin >> menu;
	do
	{
		switch (menu)
		{
		case 1:
			cout << "Enter the binary you would to encrypt" << endl;
			cin >> inputStr;

			cout << "Enter the key" << endl;
			cin >> keyStr;

			if (BitCheck(inputStr) == true && BitCheck(keyStr) == true)
			{
				if (inputStr.length() == 8)
				{
					if (keyStr.length() == 10)
					{
						char input_array[9];
						strcpy(input_array, inputStr.c_str());
						
						char key_array[11];
						strcpy(key_array, keyStr.c_str());

						
						Encryption(inputStr, keyStr);

						
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
			}
			else
			{
				done = false;
			}

			break;

		case 2:
			cout << "Enter the binary you would to decrypt" << endl;
			cin >> inputStr;

			cout << "Enter the key" << endl;
			cin >> keyStr;

			if (BitCheck(inputStr) == true && BitCheck(keyStr) == true)
			{
				if (inputStr.length() == 8)
				{
					if (keyStr.length() == 10)
					{
						char input_array[9];
						strcpy(input_array, inputStr.c_str());
						char key_array[11];
						strcpy(key_array, keyStr.c_str());

						done = true;

						Encryption(inputStr, keyStr);
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
			}
			break;

		default:
			cout << "Invalid Choice" << endl;
		}
	} while (done == false);

	return 0;
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
