#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;

void Encryption();
void Decryption();

int main()
{
	int  menu = 3;
	cout << "Caesar Cipher" << endl;
	cout << "Would you like to encrypt or decrypt?" << endl;
	cout << "Please enter 1 for encrypt.\n"
		 << "Please enter 2 for decrypt.\n" << endl;

	cin >> menu;

	switch (menu)
	{
	case 1:
		Encryption();
		break;

	case 2:
		Decryption();
		break;

	default:
		cout << "Invalid Choice" << endl;
	}

	return 0;
}

void Encryption()
{
	//might have to use a different var type
	string encrypt_binary = " ";
	string key = " ";

	
	cout << "Enter the binary you would to encrypt" << endl;
	cin >> encrypt_binary;

	cout << "Enter the key" << endl;
	cin >> key;
}

void Decryption()
{
	//might have to use a different var type
	string decrypt_binary = " ";
	string key = " ";

	
	cout << "Enter the binary you would to decrypt" << endl;
	cin >> decrypt_binary;

	cout << "Enter the key" << endl;
	cin >> key;
}