#ifndef BATTLECATSTAT_CPP
#define BATTLECATSTAT_CPP


#include<iostream>
#include<string>
#include<time.h>
#include<cstdlib>
#include <bits/stdc++.h>


    int question = 0, uber = 0, super = 0, rare = 0;                //Holds amount of times there was a pull for the rank
    int forCutter = 1, appender = 0;                                //Cuts done on for loop iterations in Compare, Used to mark the i where there is a match in Compare

    std::string unitPick;                                           //UnitPick variable used for function passing

std::string UnitPick() {                                            //Picks a unit based on random percent
    int QUESTION = 3, UBER = 50, SUPER = 250, RARE = 697, pull = 0;                                 //pull = Rare 1, Super 2, Uber 3, Question 4
    int percent = 0, random = 0, THOUSAND = 1000;                                                   //Thousand = holds max percentage 100.0%
                                                                                                    //percent = holds random number, random = used in ranked unit selection (in switch)
    percent = rand() % THOUSAND + 1;        //Draws number between 1-1000 (1-100.0)

    if     ( percent <= RARE) pull = 1;                                                             //Pulls ranks for unit switch pull
    else if((percent > RARE)            && (percent <= RARE+SUPER))               pull = 2;
    else if((percent > RARE+SUPER)      && (percent <= RARE+SUPER+UBER))          pull = 3;
    else if((percent > RARE+SUPER+UBER) && (percent <= RARE+SUPER+UBER+QUESTION)) pull = 4;
    else pull = 0;

    std::string  uberUnit  [8]  = {"u01","u02","u03","u04","u05","u06","u07","u08"},                //Each unit in each rank

                 superUnit [22] = {"s01","s02","s03","s04","s05","s06","s07","s80","s09","s10",
                                   "s11","s12","s13","s14","s15","s16","s17","s18","s19",
                                   "s20","s21","s22"},

                 rareUnit  [25] = {"r01","r02","r03","r04","r05","r06","r07","r08","r09","r10",
                                   "r11","r12","r13","r14","r15","r16","r17","r18","r19",
                                   "r20","r21","r22","r23","r24","r25"};

    switch (pull) {                                                                                 //Chooses a unit from the rank drawn based on random percent
    case 1:
        rare++;                                                                                     //Increments the amount of times the rank has been pulled
        random = rand() % 25;                                                                       //Selects which ranked unit is chosen
        return rareUnit[random];                                                                    //Returns the selected unit as string value

    case 2:
        super++;
        random = rand() % 22;
        return superUnit[random];

    case 3:
        uber++;
        random = rand() % 8;
        return uberUnit[random];

    case 4:
        question++;
        return "?01";

    } // switch(percent)
    return "Error";
} //UnitPick

bool Compare(std::string Units[],std::string unitPick) {     //bools whether the unitPick matches Unit array
    bool compared;
    std::cout << "Compare\n";  //delete
    for(int i=0;i<forCutter;i++) {                                          //Goes through Unit array and compares the unitPick to each cell
        if(Units[i] == unitPick) {                                  //breaks and copies i into append if a match is found
                appender = i;
                forCutter++;
                return compared = true;
        }                                                           //Compare for
        //std::cout << Units[i] << "|" << unitPick << std::endl;
    }
    forCutter++;

    return compared = false;                                        //Considered false if there is no match
}                                                                   //Compare

void TicketPuller(int t, std::string Units[]) {                     //Randomly picks a ranked unit t amount of times
    srand(time(nullptr));                                           //RNG seed


    Units[0] = UnitPick();                                          //First Unit array cell is filled with draw
    for(int j=1; j<t; j++) {                                        //from second cell compares unitPick to Unit array
        unitPick = UnitPick();                                      //Used for function passing

        if(Compare(Units,unitPick)) {                             //If Compare is true then cell in Unit array will use appender
            Units[appender] += "#";                                 //to add # to that cell denoting another draw
        }                                                           //if

        else Units[j] = unitPick;                                   //If compare is false then the UnitPick will into the j cell

    }                                                               //for
                                                     //Prints in drawn order or descending order
} // TicketPuller

void RankCounter() {                                                //Counts how many times a certain rank is drawn
    std::cout << std::endl;
    std::cout << "Question:\t" << question << std::endl;
    std::cout << "Uber:\t\t"     << uber     << std::endl;
    std::cout << "Super:\t\t"    << super    << std::endl;
    std::cout << "Rare:\t\t"     << rare     << std::endl;
    std::cout << std::endl;
}                                                                   //RankCounter

void Print(int t, std::string Units[]) {                            //Prints ticket draws in orders depending on user
    int output = 1;
    //*
    std::cout << "Choose output:\n"
                 "1: Drawn order\n"
                 "2: Descending Order\n";
    std::cin >> output;
    //*/
    switch(output) {
    case 1:
        std::cout << "Drawn Order" << std::endl;
        for(int i=0; i<t; i++) {
                std::cout << "Ticket " << i+1 << ":\t" << Units[i] << std::endl;
        } //for
    break;

    case 2:
       std::cout << "Descending Order" << std::endl;
            int n = sizeof(Units)/sizeof(Units[0]);

    std::sort(Units, Units+n, std::greater<std::string>());                                                 //lower if in ascending order
    for(int i = 0; i<t; ++i) {
            std::cout << "Ticket " << i+1 << ":\t" << Units[i] << std::endl;
    } //for
    break;

    }
}//Print(t,Units);

#endif
