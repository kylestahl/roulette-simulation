//
//  main.cpp
//  roultte.cpp
//
//  Created by Kyle Stahl, Wyatt Peery, Moira Blodgett and Pratheeksha Mallikarjun on 12/1/14.
//  Copyright (c) 2014 Kyle Stahl. All rights reserved.
//

//This program creates a class called roulette, that simulates a UK style roulette board. Then runs a simulation of the Martingale Roulette strategy until the player runs out of money. Then repeats this multiple time and averages the results.


#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int TRIALS(100);
//////////////////////////////////////////////////////////////////////////////////////////////////
//Roulette class definition
class roulette
{
public:
    
    void assign_number(roulette array[], int n);
    void assign_color(roulette a[], int i);
    int get_number();
    string get_color();
    void assign_board(roulette board[]);
    
private:
    
    int number;
    string color;
    
    
};


//Roulette Class Implentation
void roulette::assign_board(roulette board[])
{
    int i;
    
    // Assigning numbers for board
    for(i=0; i<37; i++)
    {
        board[i].assign_number(board, i);
        board[i].assign_color(board, i);
    }
}

void roulette::assign_number(roulette array[], int i)
{

    array[i].number=i;

}


//Assinging a color
void roulette::assign_color(roulette array[], int i)
{
    switch( i )
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 9:
        case 12:
        case 14:
        case 16:
        case 18:
        case 19:
        case 21:
        case 23:
        case 25:
        case 27:
        case 30:
        case 32:
        case 34:
        case 36:
            array[i].color="red";
            break;
            
        case 2:
        case 4:
        case 6:
        case 8:
        case 10:
        case 11:
        case 13:
        case 15:
        case 17:
        case 20:
        case 22:
        case 24:
        case 26:
        case 28:
        case 29:
        case 31:
        case 33:
        case 35:
            array[i].color="black";
            break;
            
        case 0:
            array[i].color="green";
            break;
            
        default:
            array[i].color="invalid";
            break;
    }
}

//Board Accessor Functions
int roulette::get_number()
{
    return number;
}

string roulette::get_color()
{
    return color;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

//random number generator function
int play(int trial, int round, int x)
{
    int n;
    srand(trial*round*x);
    n = (rand() % 37);
    return n;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

//Martingale Class definition
class Martingale
{
public:
    void assigndata(int initrounds, int initwins, int initloses, int initmaxbet, int inittimes);
    friend Martingale average(Martingale a[]);
    //friend ostream& operator <<(ostream& out, Martingale a);
    int getrounds();
    int getwins();
    int getloses();
    int getmaxbet();
    int gettimes();
    
private:
    int rounds;
    int wins;
    int loses;
    int maxbet;
    int times;
};


//Martingale Class Implementation
void Martingale::assigndata(int initrounds, int initwins, int initloses, int initmaxbet, int inittimes)
{
    rounds=initrounds;
    wins=initwins;
    loses=initloses;
    maxbet=initmaxbet;
    times=inittimes;
}



Martingale average(Martingale a[])
{
    int i;
    Martingale avg;
    avg.assigndata(0, 0, 0, 0, 0);
    
    //loop sums the array of trials
    for(i=0; i<TRIALS; i++)
    {
        avg.rounds = avg.rounds + a[i].rounds;
        avg.wins = avg.wins + a[i].wins;
        avg.loses = avg.loses + a[i].loses;
        avg.maxbet = avg.maxbet + a[i].maxbet;
        avg.times = avg.times + a[i].times;
    }
    
    // divides the sum by the number of trials
    avg.rounds = (avg.rounds/TRIALS);
    avg.wins = (avg.wins/TRIALS);
    avg.loses = (avg.loses/TRIALS);
    avg.maxbet = (avg.maxbet/TRIALS);
    avg.times = (avg.times/TRIALS);
    
    return avg;
}

//Strategy Accessor Functions
int Martingale::getrounds()
{
    return rounds;
}

int Martingale::getwins()
{
    return wins;
}

int Martingale::getloses()
{
    return loses;
}

int Martingale::getmaxbet()
{
    return maxbet;
}

int Martingale::gettimes()
{
    return times;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

/*ostream& operator <<(ostream out, Martingale a)
{
    cout<<"The average number of total rounds = "<<a.rounds<<endl;
    cout<<"Average: Rounds won = "<<a.wins<<" Rounds lost = "<<a.loses<<endl;
    cout<<"The average max bet was "<<a.maxbet<<" happening on average "<<a.times<<" times."<<endl;
    cout<<endl<<"You Lose $0.00"<<endl;
    
    return out;

}*/
//Not working on my machine oh well



////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //initialize variables
    int i;
    roulette board[37];
    Martingale array[TRIALS];
    int money(1000), rounds(1), n(1), bet(1), maxbet(0), happened(0), wins(0), losses(0);
    
    
    // assign baord
    for(i=0; i<37; i++)
    {board[i].assign_board(board);}
    
    
    
    
for(i=0; i<TRIALS; i++)
{
    
    //do while loop: while you still have money
    do
    {   // bet is on 19-36 evertime to make things easy
        n = play(i,rounds,n);
        
        //if win
        if (n > 18)
        {
            /*cout<<"Round "<<rounds<<": "<<board[n].get_number()<<" "<<board[n].get_color()<<" Won $"
            <<bet<<", Total= $"<<money<<endl;*/
            
            
            money++;//make $1.00 when you win and bet goes back to 1.
            bet=1;
            
            wins++;
        }
        
        //if lose
        else if( n <= 18)
        {
            /*cout<<"Round "<<rounds<<": "<<board[n].get_number()<<" "<<board[n].get_color()<<" Lost $"
            <<bet<<", Total= $"<<money<<endl;*/
            
            money = (money - bet);
            bet = (bet * 2);
            
                if(bet > maxbet)
                    maxbet=bet;
                else if(bet == maxbet)
                    happened++;
            
            losses++;
        }
        
        //Thank you!
        else
            cout<<"Hey JGC. Thanks for a great semester!!!"<<endl;
        
        rounds++;
        
    }while(money > 0.0);
    
    rounds--;
    
    //outputing simulation summary
    cout<<endl<<"Trial: "<<(i+1)<<endl;
    cout<<"Total rounds= "<<rounds<<endl;
    cout<<"Rounds won = "<<wins<<endl;
    cout<<"Rounds lost = "<<losses<<endl;
    cout<<"The max bet was "<< maxbet <<" and it happened "<<happened<<" times."<<endl;
    cout<<"Money = $0.00.  You lose"<<endl;

    //Gathering data
    array[i].assigndata(rounds, wins, losses, maxbet, happened);
    
    //Setting Variable back for next trial
    rounds=1;
    wins=0;
    losses=0;
    maxbet=0;
    happened=0;
    money=1000;
    bet=1;
}
    
    //Averaging the array
    Martingale a;
    a = average(array);
    
    //Probably could've overloaded the << operator but this works I guess
    cout<<endl;
    cout<<"The average number of total rounds = "<<a.getrounds()<<endl;
    cout<<"Average: Rounds won = "<<a.getwins()<<" Rounds lost = "<<a.getloses()<<endl;
    cout<<"The average max bet was "<<a.getmaxbet()
    <<" happening on average "<<a.gettimes()<<" times."<<endl;
    cout<<endl<<"Loser: --> $0.00"<<endl;
    
    
    return 0;
}

