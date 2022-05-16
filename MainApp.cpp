#include "MainApp.h"

void MainApp::init(int argc, vector<string>&& argv){
    vector<string> input;
    string config;
    bool inputFound = false;
    // string output;
    char flag = 'i';
    for(int i=0; i < argc;i++){
        if(argv[i] == "-i"){
            inputFound = true;
            // if(flag == 'c' && config == ""){
            //     std::cerr << "ERROR: -c flag found but no config filepath supplied\n";
            //     exit(1);
            // }if(flag == 'o' && output == ""){
            //     std::cerr << "ERROR: -o flag found but no output filepath supplied\n";
            //     exit(1);
            // }
            // flag = 'i';
            // continue;
            i++;
            while(argv[i] != "-c" && argv[i] != "-o"){
                try{
                    fr.readInputFile(argv[i]);
                }catch(FileReader::FileReaderException &e){
                    cerr << e.getError();
                    exit(1);
                }
                i++;
                if(i >= argc)
                    break;
            }
        }else if(i < argc && argv[i] == "-c"){
            // if(flag == 'i' && input.size() == 0){
            //     std::cerr << "ERROR: -i flag found but no input file paths supplied\n";
            //     exit(1);
            // }if(flag == 'o' && output == ""){
            //     std::cerr << "ERROR: -o flag found but no output filepath supplied\n";
            //     exit(1);
            // }
            // flag = 'c';
            i++;
            try{
                fr.readConfigFile(argv[i]);
            }catch(FileReader::FileReaderException &e){
                cerr << e.getError();
                exit(1);
            }
        }else if(i < argc && argv[i] == "-o"){
            i++;
            // if(flag == 'i' && input.size() == 0){
            //     std::cerr << "ERROR: -i flag found but no input file paths supplied\n";
            //     exit(1);
            // }if(flag == 'c' && config == ""){
            //     std::cerr << "ERROR: -c flag found but no config filepath supplied\n";
            //     exit(1);
            // }
            // flag = 'o';
            // continue;
            if(i >= argc){
                cerr << "ERROR: -o flag found but no output file path supplied\n";
                exit(1);
            }else{
                output.open(argv[i]);
            }
            
        }
        // switch(flag) {
        //     case 'i':
        //         input.push_back(s);
        //         break;
        //     case 'c':
        //         if(config != ""){
        //             std::cerr << "ERROR: only one config file allowed\n";
        //             exit(1);
        //         }
        //         config = s;
        //         break;
        //     case 'o':
        //         if(output != ""){
        //             std::cerr << "ERROR: only one output file allowed\n";
        //             exit(1);
        //         }
        //         output = s;
        
    }
    if(!inputFound){
        std::cerr << "ERROR: at least one input file required\n";
        exit(1);
    }
    if(!output.is_open()){
        output.open("output.dat");
    }
} 



void MainApp::start() {
        int command;
        while(command != UI::EXIT){
            command = userInterface.getCommand();
        }
}