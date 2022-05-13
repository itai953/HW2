#include "MainApp.h"

void MainApp::init(int argc, vector<string>&& argv){
    vector<string> input;
    string config;
    string output;
    char flag = 'i';
    for(auto s: argv){
        if(s == "-i"){
            if(flag == 'c' && config == ""){
                std::cerr << "ERROR: -c flag found but no config filepath supplied\n";
                exit(1);
            }if(flag == 'o' && output == ""){
                std::cerr << "ERROR: -o flag found but no output filepath supplied\n";
                exit(1);
            }
            flag = 'i';
            continue;
        }else if(s == "-c"){
            if(flag == 'i' && input.size() == 0){
                std::cerr << "ERROR: -i flag found but no input file paths supplied\n";
                exit(1);
            }if(flag == 'o' && output == ""){
                std::cerr << "ERROR: -o flag found but no output filepath supplied\n";
                exit(1);
            }
            flag = 'c';
            continue;
        }else if(s == "-o"){
            if(flag == 'i' && input.size() == 0){
                std::cerr << "ERROR: -i flag found but no input file paths supplied\n";
                exit(1);
            }if(flag == 'c' && config == ""){
                std::cerr << "ERROR: -c flag found but no config filepath supplied\n";
                exit(1);
            }
            flag = 'o';
            continue;
        }
        switch(flag) {
            case 'i':
                input.push_back(s);
                break;
            case 'c':
                if(config != ""){
                    std::cerr << "ERROR: only one config file allowed\n";
                    exit(1);
                }
                config = s;
                break;
            case 'o':
                if(output != ""){
                    std::cerr << "ERROR: only one output file allowed\n";
                    exit(1);
                }
                output = s;
        }
    }
    if(input.size() == 0){
        std::cerr << "ERROR: at least one input file required\n";
        exit(1);
    }
} 