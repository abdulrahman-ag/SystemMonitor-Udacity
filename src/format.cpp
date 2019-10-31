#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    
    string timeString = "";
    int minutes, hours;
    minutes = seconds/60;
    hours = minutes/60;

    if(hours < 10){
        timeString+= "0";
    }

    timeString += std::to_string(hours) + ":";

    if(minutes%60 < 10){
        timeString+= "0";
    }

    timeString += std::to_string(minutes%60) + ":";

    if(seconds%60 < 10){
        timeString+= "0";
    }

    timeString += std::to_string(seconds%60);

    return timeString;
}