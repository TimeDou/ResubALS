#include "cmdline.hpp"
#include "header.h"
#include "my_abc.h"


using namespace abc;
using namespace boost;
using namespace cmdline;
using namespace std;


parser CommPars(int argc, char * argv[]) {
    parser option;
    option.add<string>("input", '\0', "path to accurate circuit", true);
    option.add<string>("standCell", '\0', "path to standard cell library", false, "./input/standard-cell/nangate_45nm_typ.lib");
    option.parse_check(argc, argv);
    return option;
}

int main(int argc, char * argv[]) {
    // start abc engine
    GlobStartAbc();

    // parse options
    parser option = CommPars(argc, argv);
    string inputCircuit = option.get <string> ("input");
    string standCellPath = option.get <string> ("standCell");
    // load standard cell
    NetMan abcMan;
    if (standCellPath != "")
        abcMan.ReadStandCell(standCellPath);
    abcMan.ReadNet(inputCircuit, false);
    abcMan.CompileWithYosys(standCellPath);

    // stop abc engine
    GlobStopAbc();
    return 0;
}
