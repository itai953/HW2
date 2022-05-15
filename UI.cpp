#include "UI.h"

int UI::getCommand(){
    cout << "Please enter next command to execute (EXIT to quit): ";
    srcNode = destNode = filepath = "";
    string command;
    std::getline(cin,command);
    return parseCommand(command);
}


int UI::parseCommand(const string& cmd){
     std::stringstream ss(cmd);
     string command;
     ss >>command;
     if(command == "load"){
        ss >> filepath;
        if(filepath == ""){
            cout << "ERROR: no filepath supplied\n";
        }
        return LOAD;
    }else if(command == "outbound"){
        ss >> srcNode;
        if(srcNode == ""){
            //TODO error handling
        }
        return OUTBOUND;
    }else if(command == "inbound"){
        ss >> destNode;
        if(destNode == ""){
            //TODO error handling
        }
        return INBOUND;
    }else if(command == "uniExpress"){
        ss >> srcNode;
        ss >> destNode;
        if(srcNode == "" || destNode == ""){
            //TODO error handling
        }
        return UNIEXPRESS;
    }else if(command == "multiExpress"){
        ss >> srcNode;
        ss >> destNode;
        if(srcNode == "" || destNode == ""){
            //TODO error handling
        }
        return MULTIEXPRESS;
    }else if(command == "EXIT"){
        return EXIT;
    }else {
        std::cerr << "ERROR: unrecognized command\n";
        return -1;
    }
}