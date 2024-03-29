#include <iostream>
#include <cmath>
using namespace std;

enum Genre {ACTION, COMEDY, DRAMA, ROMANCE, THRILLER};

class Time { 
public:
    int h;
    int m;
};

class Movie { 
public: 
    string title;
    Genre genre;     // only one genre per movie
    int duration;    // in minutes
};

class TimeSlot { 
public: 
    Movie movie;     // what movie
    Time startTime;  // when it starts
};

void printTime(Time time) {
    cout << time.h << ":" << time.m;
}

void printMovie(Movie mv){
    string g;
    switch (mv.genre) {
        case ACTION   : g = "ACTION"; break;
        case COMEDY   : g = "COMEDY"; break;
        case DRAMA    : g = "DRAMA";  break;
        case ROMANCE  : g = "ROMANCE"; break;
        case THRILLER : g = "THRILLER"; break;
    }
    cout << mv.title << " " << g << " (" << mv.duration << " min)";
}
void printTimeSlot(TimeSlot ts);
int minutesSinceMidnight(Time time);
int minutesUntil(Time earlier, Time later);
Time addMinutes(Time time0, int min);
TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie);
bool timeOverlap(TimeSlot ts1, TimeSlot ts2); 
TimeSlot earlierStart(TimeSlot ts1,TimeSlot ts2);

int main(){
    /*
    Time t1 = {2,10};
    Time t2 = {7,50};
    cout << minutesSinceMidnight(t1) << endl;
    cout << minutesSinceMidnight(t2) << endl;
    cout << minutesUntil(t1,t2) << endl;
    cout << minutesUntil({9,2},{1,39}) << endl;
    cout <<   minutesUntil({7,20}, {7, 55}) << endl;
    cout <<   minutesUntil({0,41}, {15, 4}) << endl;
    */
    /*
    //testing addMinutes
    Time t3 = {8,10};
    Time t4 = addMinutes(t3,75); 
    Time t5 = {24,10};
    Time t6 = addMinutes(t5,50);
    cout << t4.h << " " << t4.m << endl;
    cout << t6.h << " " << t6.m << endl;
    */
    
    Movie movie1 = {"Back to the Future", COMEDY, 116};
    Movie movie2 = {"Black Panther", ACTION, 134};
    Movie movie3 = {"Julius Caesar",ROMANCE,90};
    Movie movie4 = {"Never gonna give you up", ROMANCE,90};
    Movie bananas = {"bananas", ACTION, 130};

    TimeSlot testing = {bananas,{14,10}};
    TimeSlot morning = {movie1, {9, 15}};  
    TimeSlot daytime = {movie2, {12, 15}}; 
    TimeSlot evening = {movie2, {16, 45}};
    TimeSlot late1 = {movie3,{10,10}}; 
    TimeSlot late2 = {movie4,{11,30}};

    cout << timeOverlap(late1,late2) << endl; 

    //TimeSlot testEarly = earlierStart(testing, daytime);
    //printTimeSlot(testing);

    //printMovie(movie1);
    /* testing print time slot
    cout << "\n";
    printTimeSlot(morning);
    printTimeSlot(daytime);
    printTimeSlot(evening);
    printTimeSlot(late1);
    printTimeSlot(late2);
    */

    
    TimeSlot t1 = scheduleAfter(testing,movie4);
    printTimeSlot(t1);
    
    return 0;
}

int minutesSinceMidnight(Time time){
    return (time.h * 60) + time.m;
}
int minutesUntil(Time earlier, Time later){
    // if earlier's time is more late than later
    if((later.h < earlier.h) || ((later.h <= earlier.h) && (later.m < earlier.m))){
        return (((later.h - earlier.h) * 60) + (later.m - earlier.m));
    }
    //if earlier's minute is greater than later's minute,
    //substracting them won't work -> 1:41 to 2:04 != hour(2-1)  : minute(abs(4-41)), you get 1 hour 37 mins inbetween
    //Adds 1 hour to earlier.h but earlier.m subtracts 60 and gets added to later.m
    //ex: 2:41 to 3:04, hours(3 - (2+1)), minutes((60-41) + 4) -> 0 hours 23 mins
    if(earlier.m > later.m){
        return (abs((earlier.h+1) - later.h) * 60) + abs(later.m + abs(earlier.m-60));
    }
    return (abs(earlier.h - later.h) * 60) + abs(earlier.m - later.m);
}

Time addMinutes(Time time0, int min){
    int minutes = time0.m + min; 
    int hours = time0.h;
    if(minutes >=60){
        hours += minutes/60;
        minutes = minutes%60;
    }
    if(hours > 24){
        hours = 0;
    }
    return {hours,minutes};
}

void printTimeSlot(TimeSlot ts){
    string g;
    switch (ts.movie.genre) { // g becomes the genre
        case ACTION   : g = "ACTION"; break;
        case COMEDY   : g = "COMEDY"; break;
        case DRAMA    : g = "DRAMA";  break;
        case ROMANCE  : g = "ROMANCE"; break;
        case THRILLER : g = "THRILLER"; break;
    }
    Time end = addMinutes(ts.startTime,ts.movie.duration); // the ending time for the movie
    cout << ts.movie.title << " " << g << " (" << ts.movie.duration << "min) [starts at " << ts.startTime.h << ":" << ts.startTime.m << ", ends by " << end.h << ":" << end.m << "]\n";;
}

//makes a new timeslot for nextMovie, scheduled right after the timeslot ts
TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie){
    TimeSlot ret = {nextMovie,addMinutes(ts.startTime,ts.movie.duration)};
    return ret;
}

TimeSlot earlierStart(TimeSlot ts1,TimeSlot ts2){
    Time startTime1 = ts1.startTime;
    Time startTime2 = ts2.startTime; 
    if((startTime1.h == startTime2.h) && (startTime1.m < startTime2.m)){
        return ts1;
    }else if(startTime1.h < startTime2.h){
        return ts1;
    }
    return ts2;
}

TimeSlot laterStart(TimeSlot ts1,TimeSlot ts2){
    Time startTime1 = ts1.startTime;
    Time startTime2 = ts2.startTime; 
    if((startTime1.h == startTime2.h) && (startTime1.m < startTime2.m)){
        return ts2;
    }else if(startTime1.h < startTime2.h){
        return ts2;
    }
    return ts1;
}

bool timeOverlap(TimeSlot ts1, TimeSlot ts2){
    Time startTime1 = ts1.startTime;
    Time startTime2 = ts2.startTime;
    TimeSlot earlier = earlierStart(ts1,ts2);
    TimeSlot later = laterStart(ts1,ts2);

    int between = minutesUntil(earlier.startTime,later.startTime);
    if(between < earlier.movie.duration){
        return true;
    }
    return false;
}