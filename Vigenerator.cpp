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
<<<<<<< Updated upstream
    string input, output, key_file_name, operation, plaintext, key, cypher, original_text;
    vector<pair<char*, char*>> args;
=======

    string plaintext, key, cypher, original_text;
    
>>>>>>> Stashed changes

    if (argc == 0) {//REMEMBER TO CHANGE TO 1
        cout << "PROGRAM INFO GOES HERE" << endl;
        return 0;
    }
<<<<<<< Updated upstream
=======
    
    
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
>>>>>>> Stashed changes

    //    if (argc != 8) {
    //        cout << "Not enough flags!" << endl;
    //        return -1;
    //    }

<<<<<<< Updated upstream
    for (int i = 2; i < argc; i += 2) {
        args.push_back({ argv[i],argv[i + 1] });   //vector of a pair: <flag, value>
    }
    for (int i = 0; i < argc; i++) {
        operation = argv[i];
        if (operation == "--en") {
            break;
        }
        else if (operation == "--de") {
            break;
        }
    }

    //maybe use a map
    for (auto& i : args) {
        flag = i.first;
        value = i.second;

        if (argmap.find(flag) == argmap.end()) {
            cout << "Flag " << flag << " does not exist!" << std::endl;
            return -1;
        }
        else {
            argmap[flag] = value;
        }
    }

    key = read_file(argmap["-k"]);
    plaintext = read_file(argmap["-i"]);
    cout << plaintext << endl;
=======
    //Fail fast principle, check if operation is a correct flag
    if (!op) {
        cout << "Invalid operation flags! Known flags: --en --de";
    }


    key = fix_strings(read_file(argmap["-k"]), &mistakes, true);
    plaintext = fix_strings(read_file(argmap["-i"]), &mistakes, false);

    //Protect from user who didn't read documentation
    if (key == "") {
        cout << "After conversion key file is empty! Unable to encode and decode using na empty string. Please change the key file to contain at least one letter." << endl;
        return 1;
    }
    if (plaintext == "") {
        cout << "After conversion text file is empty! Unable to encode and decode using na empty string. Please change the key file to contain at least one letter." << endl;
        return 1;
    }

>>>>>>> Stashed changes
    key = make_key(plaintext, key);
    cout << key << endl;




    if (operation == "--en") {
        cypher = encode(plaintext, key);
        cout << cypher << endl;
    }
<<<<<<< Updated upstream
    else if (operation == "--de") {
=======
    else { //argmap["op"] == "--de"
>>>>>>> Stashed changes
        cypher = plaintext;
        original_text = decode(cypher, key);
    }
    

    cout << decode(cypher, key);


    return 0;
}