/* 
 * File:   main.cpp
 * Author: sandeep
 *
 * Created on October 7, 2014, 5:24 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

#include "main.h"
#include "minimax.h"
#include "alphaBeta.h"
#include "greedy.h"

using namespace std;

/*
 * 
 */
int required_Depth;
int evaluation_Board[max_Depth][max_Depth]={
        {99,-8,8,6,6,8,-8,99},
        {-8,-24,-4,-3,-3,-4,-24,-8},
        {8,-4,7,4,4,7,-4,8},
        {6,-3,4,0,0,4,-3,6},
        {6,-3,4,0,0,4,-3,6},
        {8,-4,7,4,4,7,-4,8},
        {-8,-24,-4,-3,-3,-4,-24,-8},
        {99,-8,8,6,6,8,-8,99}
    };

int main(int argc, char** argv) {
    
    fstream in;
    ofstream out;
    string buf_String;
    char buf[500];
    
    char present_Play;    
    int task=1;
    int movements[8][2]={{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};
    
    char board_State[max_Depth][max_Depth];
    int option=1,j=0;
    in.open("/home/sandeep/Desktop/input.txt",ios::in);
    out.open("/home/sandeep/Desktop/output.txt",ios::out);
    while(in.eof()==false){
        in >> buf;
        if(option == 1){
            task=atoi(buf);
            option++;
        }
        else if(option == 2){
            present_Play=(buf[0]);
            option++;
        }
        else if(option == 3){
            required_Depth=atoi(buf);
            option++;
        }
        else{
            for(int i=0;i<max_Depth;i++)
                board_State[j][i]=buf[i];
            j++;
        }
    }
    if(task == 1){
        greedy start;
        start.set_Player('X');
        start.update_Board(board_State);
        start.generate_Children();
        start.print();
        
    }
    else if(task == 2){
        minimax start;
        start.set_Player('X');
        start.update_Board(board_State);
        start.set_Position();
        start.generate_Children();
        start.print();
        
    }
    else if(task == 3){
        alphaBeta start;
        start.set_Player('X');
        start.update_Board(board_State);
        start.set_Evaluation();
        start.set_Position();
        start.generate_Children();
        
        start.print();
        
    }
    return 0;
}

