#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <map>

std::string bpath = "/sys/class/power_supply/hidpp_battery_1/voltage_now";
// battery voltage to percentage charge table
std::map<float, int> table{
    {4.186,100},
    {4.156,99},
    {4.143,98},
    {4.133,97},
    {4.122,96},
    {4.113,95},
    {4.103,94},
    {4.094,93},
    {4.086,92},
    {4.076,91},
    {4.067,90},
    {4.060,89},
    {4.051,88},
    {4.043,87},
    {4.036,86},
    {4.027,85},
    {4.019,84},
    {4.012,83},
    {4.004,82},
    {3.997,81},
    {3.989,80},
    {3.983,79},
    {3.976,78},
    {3.969,77},
    {3.961,76},
    {3.955,75},
    {3.949,74},
    {3.942,73},
    {3.935,72},
    {3.929,71},
    {3.922,70},
    {3.916,69},
    {3.909,68},
    {3.902,67},
    {3.896,66},
    {3.890,65},
    {3.883,64},
    {3.877,63},
    {3.870,62},
    {3.865,61},
    {3.859,60},
    {3.853,59},
    {3.848,58},
    {3.842,57},
    {3.837,56},
    {3.833,55},
    {3.828,54},
    {3.824,53},
    {3.819,52},
    {3.815,51},
    {3.811,50},
    {3.808,49},
    {3.804,48},
    {3.800,47},
    {3.797,46},
    {3.793,45},
    {3.790,44},
    {3.787,43},
    {3.784,42},
    {3.781,41},
    {3.778,40},
    {3.775,39},
    {3.772,38},
    {3.770,37},
    {3.767,36},
    {3.764,35},
    {3.762,34},
    {3.759,33},
    {3.757,32},
    {3.754,31},
    {3.751,30},
    {3.748,29},
    {3.744,28},
    {3.741,27},
    {3.737,26},
    {3.734,25},
    {3.730,24},
    {3.726,23},
    {3.724,22},
    {3.720,21},
    {3.717,20},
    {3.714,19},
    {3.710,18},
    {3.706,17},
    {3.702,16},
    {3.697,15},
    {3.693,14},
    {3.688,13},
    {3.683,12},
    {3.677,11},
    {3.671,10},
    {3.666,9},
    {3.662,8},
    {3.658,7},
    {3.654,6},
    {3.646,5},
    {3.633,4},
    {3.612,3},
    {3.579,2},
    {3.537,1},
    {3.500,0}
};

int main(int argc, char** argv){
    std::ifstream mfile (bpath);
    std::string line;
    if(mfile.is_open()){
        // grab the line
        getline(mfile, line);

        // line now contains the int-formatted battery voltage
        // e.g.: 4056000 means 4.056V or 4056mV
        // so let's convert that to a float in volts
        float v = std::stof(line) / 1000000;

        // find the lowest value in the table that isn't less than the current voltage
        std::map<float, int>::iterator mit = table.lower_bound(v);
        std::pair<float, int> match = {mit->first, mit->second};

        // finally, print the results
        // if there are no arguments, i.e. run in default mode
        if(argc == 1)
            std::cout << match.second << "%" << std::endl;
        else{
            if(strcmp(argv[1], "voltage") == 0)
                std::cout << v << "V" << std::endl;
            else if(strcmp(argv[1], "percentage") == 0)
                std::cout << match.second << "%" << std::endl;
            else if(strcmp(argv[1], "both") == 0)
                std::cout << v << "V " << match.second << "%" << std::endl;
        }
        mfile.close();
        return 0;
    }
    else{
        std::cout << "Unable to open battery path.";
        return 1;
    }
}
