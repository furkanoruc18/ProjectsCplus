#include "SeatOperations.h"

using namespace std;

SeatOperations::SeatOperations(int N, int M){

// we need create vector lines 0 and lines 1 of course until n and m size
    Person p;
    for(int i=1;i<N+1;i++) {
        p.seatNumber=i;  //seat number start 1 and till n
        p.line=1; //line is 1
        lines[0].push_back(p);  // create vector one by one
    }
    for(int i=1;i<M+1;i++) {
        p.seatNumber=i; //seat number start 1 and till n
        p.line=2; // line is 2
        lines[1].push_back(p);
    }

    for(int i= 1;i<=lines[1].size();i++) {   // define Person vector initilaze it but some station values change
        lines[1][i].type = 0;               //so it initilaze again
        lines[1][i].seatNumber=0;
        lines[1][i].orjinalseat=0;

    }
    for(int i= 1;i<=lines[0].size();i++) {
        lines[0][i].type = 0;
        lines[0][i].seatNumber=0;
        lines[0][i].orjinalseat=0;
    }


}

void SeatOperations::addNewPerson(int personType, const string& ticketInfo){


    int x=0,y=0;  // x is seaat number
//ticket info include seat number and A we split A
    for(char c:ticketInfo){
        if(c!='A'&&c!='B') {
            x = c - '0' + x*10; // and one by ıne value 1,2 v.s multiply 10
        }
    }


    int  type2Last=0;  // type 2 last send control 1 only type is 3 type2 last is 1
    if(personType==3)
        type2Last=1;



    if(ticketInfo[0]=='A'){ //for A
        y=x;
        x=x%lines[0].size();
        if(x==0) // and is mod 0  last seat
            x=lines[0].size();
//run control 1
        control1(lines[0],lines[1],x,personType,type2Last,x,1,y);  //it control is empty or not and recursively
    }
    else if(ticketInfo[0]=='B')
    {   y=x;
        x=x%lines[1].size();
        if(x==0)
            x=lines[1].size();
//for B run control2
        control2(lines[0],lines[1],x,personType,type2Last,x,2,y);  //it control is empty or not and recursively
    }



}

void SeatOperations::printAllSeats(ofstream& outFile){
    for(int i= 1;i<=lines[0].size();i++) {
        if (lines[0][i].type != 0) { // type is 0 dont need write seatnumber
            if(lines[0][i].line==1) { //if line is 1 so we are line A
                outFile << lines[0][i].type << " " << "A" << lines[0][i].orjinalseat << endl; //out of file
            }
            else if(lines[0][i].line==2){////if line is 2 so we are line B
                outFile << lines[0][i].type << " " << "B" << lines[0][i].orjinalseat<< endl; //out of file
            }
        }
        else
            outFile << lines[0][i].type <<endl;
    }
    for(int i= 1;i<=lines[1].size();i++) {
        if (lines[1][i].type != 0) {
            if (lines[1][i].line == 1) {
                outFile << lines[1][i].type << " " << "A" << lines[1][i].orjinalseat << endl; //out of file
            } else if (lines[1][i].line == 2) {
                outFile << lines[1][i].type << " " << "B" << lines[1][i].orjinalseat << endl; //out of file
            }
        }
        else
            outFile << lines[1][i].type <<endl;
    }

}
//check line1 for empty seat and place new person recursively

void SeatOperations::control1(vector<Person>& line1,vector<Person>& line2,int seat,int type,int type3LastOperation,int seatnumber,int lineN,int orjinalSeat){
    int seatt,seat2,type3last,lineNumber,orjinall;

    if(line1[seat].type==0)  // if type is 0 first statament and return break function because is empty
    {
        line1[seat].seatNumber=seatnumber; // seatnumber,type and type3LastOperation update
        line1[seat].type=type;
        line1[seat].type3LastOperation=type3LastOperation;
        line1[seat].line=lineN;
        line1[seat].orjinalseat=orjinalSeat;

        return;
    }
    else {  //and is not empty

        if(line1[seat].type==1)  //type is 1
        {
            type3last=line1[seat].type3LastOperation;
            line1[seat].type3LastOperation=type3LastOperation;

            seatt=int(line1[seat].orjinalseat%line2.size());//modulo line2 size for seatt
            line1[seat].type=type;
            seat2=line1[seat].seatNumber;
            lineNumber=line1[seat].line;
            line1[seat].line=lineN;
            line1[seat].seatNumber=seatnumber;
            orjinall=line1[seat].orjinalseat;
            line1[seat].orjinalseat=orjinalSeat;
            if(seatt!=0)
                control2(line1,line2,seatt,1,type3last,seat2,lineNumber,orjinall); //and for line 2 send conrol2 recursive function
            else
                control2(line1,line2,line2.size(),1,type3last,seat2,lineNumber,orjinall);

        }
        else if(line1[seat].type==2) //for type2
        {
            type3last=line1[seat].type3LastOperation;
            line1[seat].type=type;
            seat2=line1[seat].seatNumber;
            line1[seat].seatNumber=seatnumber;
            line1[seat].type3LastOperation=type3LastOperation;
            lineNumber=line1[seat].line;
            line1[seat].line=lineN;
            orjinall=line1[seat].orjinalseat;
            line1[seat].orjinalseat=orjinalSeat;

            if(seat==line1.size()) // is seat last seat  send line2 first seat
                control2(line1, line2, 1, 2, type3last, seat2, lineNumber, orjinall);

            else // else seat increase 1
                control1(line1, line2, (seat + 1), 2, type3last, seat2, lineNumber, orjinall);

        }
        else if(line1[seat].type==3) //if is type3
        {
            type3last=line1[seat].type3LastOperation;
            int z= type3last;
            z=line1[seat].seatNumber+z; //of couse  plus now place
            line1[seat].type=type;
            seat2=line1[seat].seatNumber;
            line1[seat].seatNumber=seatnumber;
            line1[seat].type3LastOperation=type3LastOperation;
            lineNumber=line1[seat].line;
            line1[seat].line=lineN;
            orjinall=line1[seat].orjinalseat;
            line1[seat].orjinalseat=orjinalSeat;
            //and for type3 ,type3last increase 1

            int a=line1.size() +line2.size();
            z=z%a;

            if(z>line1.size()) //if z is bigger n and z-n is smaller m  so z dont place line1 but place line2
                control2(line1,line2,z-line1.size(),3,type3last+2,z-line1.size(),lineNumber,orjinall); //so send control 2 with seat is z-n
            else if(z==0)
                control2(line1, line2, line2.size(), 3, type3last + 2, line2.size(),lineNumber,orjinall);
            else
                control1(line1, line2, z - 0, 3, type3last + 2, z-0, lineNumber, orjinall);

        }



    }




}
