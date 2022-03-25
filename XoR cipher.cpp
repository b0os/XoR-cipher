// Program Name: XoR cipher.cpp
// Author: Ahmed Hashim > B0OS
/* Program Description: encrypt messages using XoR method cipher ,
   by doing a XoR with any character in the message with a secret
   key given from the user. */
// Purpose: To encrypt and decrypt messages
// Last Modification Date: 25/03/2022



#include <iostream>
#include <bitset>
#include <bits/stdc++.h>
#include<string>
using namespace std;



// Function to convert a char to its ASCII representation
string bin(char charToConvert) {
    string binNumber;
    binNumber = bitset<8>(charToConvert).to_string();
    return binNumber;
}


// Function to convert from Binary to Decimal system
int binToDec(string num) {
    int dec_value = 0;
    int base = 1;

    for (int i = num.length() - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    return dec_value;
}



// Function to convert text to its hexa representation
string txtToHex(const string& text){

    string txt4Bit , hexTxt , tempTxt; int decValue;

    for (char i : text) {

        // take the first character in the text and convert it to ASCII
        tempTxt = bin(i);

        for (int j = 0; j < tempTxt.length(); j += 4) {

            // take just 4 bits from the character ASCII to convert it to hexa
            txt4Bit = tempTxt[j] ;
            txt4Bit += tempTxt[j + 1];
            txt4Bit += tempTxt[j + 2];
            txt4Bit += tempTxt[j + 3];

            // Get the decimal value of the 4 bit
            decValue = binToDec(txt4Bit);


            // To check what is the hexa equivalent of the 4 bits we take
            switch (decValue) {

                case 0:
                    hexTxt += "0"; break;

                case 10:
                    hexTxt += "A"; break;

                case 11:
                    hexTxt += "B"; break;

                case 12:
                    hexTxt += "C"; break;

                case 13:
                    hexTxt += "D"; break;

                case 14:
                    hexTxt += "E"; break;

                case 15:
                    hexTxt += "F"; break;

                default:
                    hexTxt += to_string(decValue);

            }

        }

    }

    return hexTxt ;
}



/* This function do the XoR converting between the secret key and every
   character in the message */

string encrypt(char key, string oldText) {

    string keyInBinary; string binaryString = " ", temp, newMessage;
    keyInBinary = bin(key);

    for (int i = 0; i <= oldText.length()-1; i++) {

        // convert the first letter in message to binary and put it in temporary variable
        temp = bin(oldText[i]);

        for (int j = 0; j < 8 ; j++) {

            /* check the bits in the secret key and the bits of first letter
               in the message is equal or not , if equal add 0 to new string,
               else will add 1 to the string ( XoR operation ) */

            if(keyInBinary[j] == temp[j]) {
                binaryString += "0";
            }

            else {
                binaryString +="1";
            }

        }

        /* convert the binary string to its decimal value
         and add it as character to the cipher string */
        int x = binToDec(binaryString);
        newMessage += (char) x;
    }

    return newMessage;
}


// Function to convert from hexa to text in string representation
string hexToTxt(const string& hexx) {

    string convertedString;

    for (int i = 0; i < hexx.length(); i += 2) {

        string part = hexx.substr(i, 2);

        char ch = stoul(part, nullptr, 16);


        convertedString += ch;
    }
    return convertedString;
}



int main() {

    char choice, secretKey; string message;

    // Check what the user will do (encrypt , decrypt)
    cout << "\nWelcome to the messages cipher\n"
            "What do you want to do ?..\n"
            "1- Encrypt a message\n"
            "2- Decrypt a message\n";
    cin >> choice;

    // Encryption
    if (choice == '1'){

        cout << "Please enter a Secret key...";
        cin >> secretKey;
        cout << "Please enter a message to encrypt it... ";
        cin >> message;
        cout << "\nSecret key is:'" << secretKey <<"' = " << bin(secretKey) ;
        cout << "\nPlain text: " << message << endl;

        string cipherMessage = encrypt(secretKey,message);
        cout << "Cipher text is: " << cipherMessage << " in Hexa(" << txtToHex(cipherMessage) << ") " << endl ;


    }

    // Decryption
    else if (choice == '2') {

        char choice2 ;

        /* Check which the type of the encryption message the user want to decrypt
           (Normal text , text in hexa System */
        cout << "What is the type of the message you want to decrypt it?..\n"
                "1- Normal text\n"
                "2- Text in hexadecimal type\n";
        cin >> choice2;

        // Decryption for normal message
        if (choice2 == '1'){
            cout << "Please enter a Secret key...";
            cin >> secretKey;
            cout << "Please enter a message to decrypt it... ";
            cin >> message;
            cout << "\nSecret key is:'" << secretKey <<"' = " << bin(secretKey) ;
            cout << "\nCipher text: " << message << endl;

            string decCipherMss =  encrypt(secretKey, message);
            cout << "Decipher text is: " << decCipherMss;

        }

        // Decryption for text in hexa
        else if (choice2 == '2') {

            cout << "Please enter a Secret key...";
            cin >> secretKey;
            cout << "Please enter a hexa message to decrypt it... (Without spaces !!) \n";
            cin >> message;
            cout << "\nSecret key is:'" << secretKey << "' = " << bin(secretKey);
            cout << "\nCipher text in hexa: " << message << endl;

            string decCipherMss = encrypt(secretKey, hexToTxt(message));
            cout << "Decipher text is: " << decCipherMss << endl;
        }

    }


    return 0;
}






