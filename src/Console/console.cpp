//
// Created by arseny on 31/01/2020.
//

#include <iostream>
#include "../moex/MoexReader.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: sync_client <server> <path>\n";
        std::cout << "Example:\n";
        std::cout << "  " << argv[0] << " www.boost.org /LICENSE_1_0.txt\n";
        //return 1;
    }
    else {
	    std::string url = argv[1];
	    std::string app = argv[2];
    }

    MoexReader moex;

    moex.ReadSome();

    return 0;
}
