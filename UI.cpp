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
            cout << "ERROR correct usage is: outbound <station_name>\n";
            return -1;
        }
        return OUTBOUND;
    }else if(command == "inbound"){
        ss >> destNode;
        if(destNode == ""){
            cout << "ERROR correct usage is: inbound <station_name>\n";
            return -1;
        }
        return INBOUND;
    }else if(command == "uniExpress"){
        ss >> srcNode;
        ss >> destNode;
        if(srcNode == "" || destNode == ""){
            cout << "ERROR correct usage is: uniExpress <src_station> <dest_station>\n";
            return -1;
        }
        return UNIEXPRESS;
    }else if(command == "multiExpress"){
        ss >> srcNode;
        ss >> destNode;
        if(srcNode == "" || destNode == ""){
            cout << "ERROR correct usgae is: multiExpress <src_station> <dest_station>\n";
            return -1;
        }
        return MULTIEXPRESS;
    } else if(command == "print"){
         return PRINT;
     }else if(command == "EXIT"){
        return EXIT;
    }
    else {
        cout << "ERROR: unrecognized command\n";
        cout << "supported commands are:\n"; 
        cout << "1. load <filename>\n";
        cout << "2. outbound <station_name>\n";
        cout << "3. inbound <station_name>\n";
        cout << "4. uniExpress <src_station> <dest_station>\n";
        cout << "5. multiExpress <src_station> <dest_station>\n";
        cout << "6. print\n";
        cout << "7. EXIT to terminate program\n";
        return -1;
    }
}