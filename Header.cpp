#include "Header.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
using namespace std;

int start_prog(int argc) {
    if (argc == 1) { 
        cout << "This program encrypts or decrypts text files using the Vigenere cipher method." << endl;
        cout << "It accepts the following flags:" << endl;
        cout << "--en: encode flag" << endl;
        cout << "--de: decode flag" << endl;
        cout << "-i: input file name" << endl;
        cout << "-o: output file name" << endl;
        cout << "-k: key file name" << endl;
        cout << "Example command:" << endl << "Vigenerator.exe --en -i Input.txt -k Key.txt -o Out.txt";
        return 1;
    }

    if (argc != 8) {
        cout << "Not enough or too many flags!" << endl;
        return 1;
    }

    return 0;
}

string read_file(string filename, queue<int>&newlines, bool ignore) {
    ifstream current_file;
    string contents = "";
    string line = "";

    current_file.open(filename);

    if (!current_file) {
        cout << "Source file \"" << filename << "\" could not be opened!" << endl;
    }
    else {
        if (ignore) { //ignore key newlines
            contents = "";
            while (getline(current_file, line)) {
                contents += line;               
            }
        }
        else {
            contents = "";
            while (getline(current_file, line)) {
                contents += line;
                newlines.push(int(line.length()));
            }
        }
    }
    current_file.close();
    return contents;
}

string fix_strings(string base, vector<pair<int, char>> &mistakes, bool ignore) {
    int iterator = 0;
    string output;
    //Ignore for key file
    if (ignore) {
        while (iterator < base.length()) {
            if (isalpha(base[iterator])) {
                output += base[iterator];
                iterator++;
            }
            else {
                
                iterator++;
                continue;
            }

        }
    }
    else {
        while (iterator < base.length()) {
            if (isalpha(base[iterator])) {
                output += base[iterator];
                iterator++;
            }
            else {
                mistakes.push_back({ iterator, base[iterator] });
                iterator++;
                continue;
            }

        }
    }
    return output;
}

string unfix_strings(string toFix, vector<pair<int, char>>& mistakes, queue<int>& newlines) {
    vector<pair<int, char>>::iterator it;
    vector<int>::iterator nl;
    int test=0;
    //return previous characters
    for (it = mistakes.begin(); it != mistakes.end(); it++) {
        toFix.insert(it->first, 1, it->second); //Overload to accept single char
    }
    
    //return newlines
    int pos = 0;
    int corr = 0;
    int size = newlines.size() - 1;

    while (size>0) {     
        pos += newlines.front() + corr;
        corr = 1; //Correction for additional character in \n
        toFix.insert(pos, "\n");
        newlines.pop();        
        size--;
    }
        
    
    
    return toFix;
}

void write_file(string filename, string contents) {
    ofstream outfile;
    outfile.open(filename);
    if (!outfile) {
        cout << "File \"" << filename << "\" could not be created or opened!" << endl;
    }
    else {
        outfile << contents;
    }
    outfile.close();
}

string make_key(string plaintext, string key) {
    int text_length = plaintext.size();
    int iterator = 0;


    while (key.size() < plaintext.size()) {
        key.push_back(key[iterator]);
        iterator++;
    }
    return key;
}


string encode(string plaintext, string key) {
    char number_cypher;
    string cypher;
    bool Lowercase = 0;
    for (int i = 0; i < plaintext.size(); i++) {

        if (islower(plaintext[i])) {
            Lowercase = true;
        }
        else {
            Lowercase = false;
        }

        key[i] = toupper(key[i]);
        plaintext[i] = toupper(plaintext[i]);

        number_cypher = (plaintext[i] + key[i]) % 26; //characters stored and added as numbers an moduloed 26 for range [0-25]


        //converts number cypher (offset from A) into ascii characters
        number_cypher += 'A';
        if (Lowercase) {
            number_cypher = tolower(number_cypher);
        }

        cypher.push_back(number_cypher);
    }
    return cypher;
}

string decode(string cypher, string key) {
    char cypher_number;
    string original_text;
    bool Lowercase = 0;
    for (int i = 0; i < cypher.size(); i++) {

        if (islower(cypher[i])) {
            Lowercase = true;
        }
        else {
            Lowercase = false;
        }
        key[i] = toupper(key[i]);
        cypher[i] = toupper(cypher[i]);
        cypher_number = (cypher[i] - key[i] + 26) % 26; //characters subtracted as numbers, added 26 and moduloed 26 for range [0-25]

        //convert into ascii characters
        cypher_number += 'A';
        if (Lowercase) {
            cypher_number = tolower(cypher_number);
        }

        original_text.push_back(cypher_number);
    }
    return original_text;
}