#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "Header.h"
using namespace std;


int main(int argc, char* argv[]) {

    map<string, string> argmap;
    vector<pair<int, char>> mistakes;

    bool op = false;

    argmap["-i"] = "";
    argmap["-k"] = "";
    argmap["-o"] = "";
    string flag = "";
    string value = "";
    string plaintext, key, cypher, original_text;

    //If info or not enough flags, end program
    if (start_prog(argc)) {
        return 1;
    }

    for (int i = 1; i <= 6; i += 2) {
        if (string(argv[i]) == "--de" || string(argv[i]) == "--en") {
            argmap["op"] = string(argv[i]);
            op = true; //Correct operation flag found
            i--;
        }
        else {
            flag = argv[i];
            value = argv[i + 1];
            if (argmap.find(flag) == argmap.end()) {
                cout << "Flag " << flag << " does not exist!" << endl;
                return -1;
            }
            else {
                argmap[flag] = value;
            }
        }
    }
            //Fail fast principle, check if operation is a correct flag
            if (!op) {
                cout << "Invalid operation flags! Known flags: --en --de";
                return 1;
            }


            key = fix_strings(read_file(argmap["-k"]), &mistakes, true);
            plaintext = fix_strings(read_file(argmap["-i"]), &mistakes, false);

            //Protect from user who didn't read documentation, avoid infinite loop
            if (key == "") {
                cout << "After conversion key file is empty! Unable to encode and decode using an empty string. Please change the key file to contain at least one letter." << endl;
                return 1;
            }
            if (plaintext == "") {
                cout << "After conversion input file is empty! Unable to encode and decode using an empty string. Please change the input file to contain at least one letter." << endl;
                return 1;
            }

            key = make_key(plaintext, key);


            if (argmap["op"] == "--en") {
                cypher = unfix_strings(encode(plaintext, key), &mistakes);
                write_file(argmap["-o"], cypher);
                cout << "Successfuly encoded file \"" << argmap["-i"] << "\"!";
            }

            else { //argmap["op"] == "--de"
                cypher = plaintext;
                original_text = unfix_strings(decode(cypher, key), &mistakes);
                write_file(argmap["-o"], original_text);
                cout << "Successfuly decoded file \"" << argmap["-i"] << "\"!";
            }


            return 0;
        }
    