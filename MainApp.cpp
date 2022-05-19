#include "MainApp.h"

void MainApp::updateConfigData() {
    Edge::updateStopTimes(Vertex::BUS, 1);
    Edge::updateStopTimes(Vertex::TRAM, 2);
    Edge::updateStopTimes(Vertex::SPRINTER, 3);
    Edge::updateStopTimes(Vertex::RAIL, 5);
    Edge::updateStopTimes(Vertex::TRANSIT, 0);
    Edge::updateTransitTimes(Vertex::CENTRAL, 10);
    Edge::updateTransitTimes(Vertex::STAD, 5);
    Edge::updateTransitTimes(Vertex::INTERCITY, 15);
    Edge::updateTransitTimes(Vertex::TRANSIT, 0);
}

void MainApp::init(int argc, vector<string>& argv){
    vector<string> input;
    string config;
    bool inputFound = false;
    bool configFound = false;
    char flag = 'i';
    updateConfigData();
    for(int i=0; i < argc;i++){
        if(argv[i] == "-i"){
            inputFound = true;
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
        i--;
        }else if(i < argc && argv[i] == "-c"){
            i++;
            configFound = true;
            try{
                fr.readConfigFile(argv[i]);
            }catch(FileReader::FileReaderException &e){
                cerr << e.getError();
                exit(1);
            }
        }else if(i < argc && argv[i] == "-o"){
            i++;
            if(i >= argc){
                cerr << "ERROR: -o flag found but no output file path supplied\n";
                exit(1);
            }else{
                output.open(argv[i]);
            }
            
        }
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
        string src,dest;
        while(command != UI::EXIT){
            command = userInterface.getCommand();
            switch(command){
                case UI::LOAD:
                    try{
                        fr.readInputFile(userInterface.getFilePath());
                    }catch (FileReader::FileReaderException &e){
                        cerr<<e.getError();
                    }
                    break;
                case UI::OUTBOUND:
                    src = userInterface.getSrcNode();
                    g.outbound(src,fr.getSType(src));
                    break;
                case UI::INBOUND:
                    dest = userInterface.getDestNode();
                    gT.outbound(dest,fr.getSType(dest));
                    break;
                case UI::UNIEXPRESS:
                    src = userInterface.getSrcNode();
                    dest = userInterface.getDestNode();
                    g.uniExpress(src,dest,fr.getSType(src),fr.getSType(dest));
                    break;
                case UI::MULTIEXPRESS:
                    src = userInterface.getSrcNode();
                    dest = userInterface.getDestNode();
                    g.multiExpress(src,dest);
                    break;
                case UI::PRINT:
                g.print(output);
                break;
            }
        }
}