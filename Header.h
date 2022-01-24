#pragma once
#include <string>

using namespace std;
/**@file Header.h*/


/**Display info about the program.
* If program is activated without any parameters, program info is displayed. Also, if there are not enough parameters, the program closes
* @param argc number of parameters
*/
int start_prog(int argc);

<<<<<<< Updated upstream
string fix_strings(string base);
=======

/**Delete forbidden characters from a string.
* The function takes the string and character by character checks for non-alphabets. If found, it saves the position and character into a vector and then passes that character. It returns a new string without forbidden characters.
* @param base string with possibly forbidden characters
* @param mistakes[] vector of a pair of int (position of the character in the string) and char (the forbidden character)
* @param ignore boolean value, used to ignore (true) saving the forbidden characters of the key, as they will not be used anywhere later, or force (false) the function to save them
*/
string fix_strings(string base, vector<pair<int, char>> mistakes[], bool ignore);


/**Return characters that were deleted using the fix_strings function.
* Function takes an encoded string and adress of a vector containing information about the deleted characters
* @remark Function uses an overload of std::string.insert() to insert only one character
* @param toFix a string to have returned it's forbidden characters
* @param mistakes[] vector of a pair of int (position of the character in the string) and char (the forbidden character)
*/
string unfix_strings(string toFix, vector<pair<int, char>> mistakes[]);
>>>>>>> Stashed changes


/**Read contents from file.
* Function takes a string and tries to open a file which name is that string. If it succeeds, it reads it line by line and accumulates it in a string which it returns at the end
* @param filename name of the file which has to be opened and read
*/
string read_file(string filename);


/**Write a string to file.
* Function takes provided string, if needed creates and writes it to file of given name
* @param filename name of the file that has to be created or written
* @param contents contents of the file that are to be saved
*/
void write_file(string filename, string contents);


/**Modify key length.
* Function modifies key so that it's length is equal to plaintext length. Returns the modified key string.
* @param plaintext string which is taken from original text file
* @param key string which is used as a cypher key, taken from key file
*/
string make_key(string plaintext, string key);


/**Encrypt original text using the key.
* The function changes characters into numbers, while encoding them in a cypher, character by character. It then changes the coded numbers into chars. It's done using a modulo operation as an offset from 'A' for standard alphabet where A=0, B=1, C=2...
* @param plaintext string which is taken from original text file
* @param key string which is used as a cypher key, the same length as original text
*/
string encode(string plaintext, string key);

/**Decrypt cypher using key.
* The function changes characters into numbers, while decoding them from a cypher, character by character. It then changes the numbers into chars. It's done using a modulo operation as an offset from 'A' for standard alphabet where A=0, B=1, C=2...
* @param cypher string encoded using the Vigenere algorithm
* @param key string which is used as a cypher key, the same length as original text
*/
string decode(string cypher, string key);