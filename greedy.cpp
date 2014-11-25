/* 
 * File:   greedy.cpp
 * Author: sandeep
 * 
 * Created on October 13, 2014, 8:35 PM
 */

#include "greedy.h"
#include "main.h"
#include <iostream>
#include <fstream>
using namespace std;

int movements3[8][2]={{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};

greedy::greedy() {
    this->number_Of_Children=0;
    this->leaf=1;
    this->depth=0;
    this->har_Position=0;
    this->ver_Position=0;
    this->pass=false;
    this->end_Game=false;
}

greedy::greedy(const greedy& orig) {
}

greedy::~greedy() {
}



void greedy::update_Board(char board[max_Depth][max_Depth]){
    int i,j;
    for(i=0;i<max_Depth;i++)
        for(j=0;j<max_Depth;j++)
            this->boardPosition[i][j]=board[i][j];
}

int greedy::number_Conquered(int pos_Hor,int pos_Ver,int horizontal, int vertical){
    int ret_Value=0;
    int move=0;
    char search='X';
    if(this->player == 'X')
        search='O';
    pos_Hor+=horizontal;
    pos_Ver+=vertical;
    while(pos_Hor>=0 && pos_Ver>=0 && pos_Hor<=max_Depth && pos_Ver<=max_Depth){
        if(this->boardPosition[pos_Hor][pos_Ver] == search )
            ret_Value++;
    else if (this->boardPosition[pos_Hor][pos_Ver] == '*'){
            move=1;
            break;
    }
    else
        break;
    pos_Hor+=horizontal;
    pos_Ver+=vertical;
    }
    if(move==0)
        ret_Value=0;
    
    return ret_Value;
}

void greedy::set_Player(char player){
    this->player=player;
}

void greedy::check_Directions(int pos_Hor1,int pos_Ver1){
    int i,j,k;
    char search='X';
    int value=0,value1=0;
    int pos_Hor=pos_Hor1;
    int pos_Ver=pos_Ver1;
    int horizontal,vertical;
    if(this->player == 'X')
        search='O';

    
            
                for(k=0;k<8;k++){
                    value=0;
                    value1=0; 
                    pos_Hor=pos_Hor1;
                    pos_Ver=pos_Ver1;
                    horizontal=movements3[k][0];
                    vertical=movements3[k][1];
                    
                    pos_Hor+=horizontal;
                    pos_Ver+=vertical;
                     while(pos_Hor>=0 && pos_Ver>=0 && pos_Hor<=max_Depth && pos_Ver<=max_Depth){
                        if(this->boardPosition[pos_Hor][pos_Ver] == this->player )
                            value++;
                        else if(this->boardPosition[pos_Hor][pos_Ver] == search){
                            
                            value1++;
                            break;
                        }
                        else
                            break;
                            
                        pos_Hor+=horizontal;
                        pos_Ver+=vertical;
                    }
                    if(value!=0 && value1!=0){
                        for(int m=1;m<=(value);m++)
                        this->boardPosition[pos_Hor1+movements3[k][0]*m][pos_Ver1+movements3[k][1]*m]=search;
                        
                    }
                }
            
        
             
}
/* Function evaluate
   To calculate the evaluation value of leaf nodes 
 */
void greedy::evaluate(){
    int i,j;
    int evaluation_value1=0;
    if(this->leaf==1){
        for(i=0;i<max_Depth;i++)
            for(j=0;j<max_Depth;j++){
                if(this->boardPosition[i][j] == 'X'){
                    evaluation_value1+=evaluation_Board[i][j];
                }
                else if(this->boardPosition[i][j] == 'O'){
                    evaluation_value1-=evaluation_Board[i][j];
                }
            }
    }
    this->evaluation_Value=evaluation_value1;
}


void greedy::generate_Children(){
    int i,j,k,temp_Conquered=0;
    
    for(i=0;i<max_Depth;i++)
        for(j=0;j<max_Depth;j++){
            if(this->boardPosition[i][j]==this->player){
                for(k=0;k<8;k++){
                    temp_Conquered = 0;
                    temp_Conquered = number_Conquered(i,j,movements3[k][0],movements3[k][1]);
                    if(temp_Conquered>0){
                        this->leaf = 0;                        
                        greedy* child = new greedy;
                        child->update_Board(this->boardPosition);
                        
                        child->ver_Position=i+movements3[k][0]*(temp_Conquered+1);
                        child->har_Position=j+movements3[k][1]*(temp_Conquered+1);
                        if(this->player=='X')
                            child->set_Player('O');
                        else
                            child->set_Player('X');
                        int m;
                        for( m=1;m<=(temp_Conquered+1);m++){
                            child->boardPosition[i+movements3[k][0]*m][j+movements3[k][1]*m]=this->player;
                            child->check_Directions(i+movements3[k][0]*m,j+movements3[k][1]*m);
                        }
                        child->check_Directions(i+movements3[k][0]*m,j+movements3[k][1]*m);
                        child->evaluate();
                        this->childern[this->number_Of_Children++]=child;
                        cout << "Parent\n";
                        for(int ii=0;ii<max_Depth;ii++){
                            for(int jj=0;jj<max_Depth;jj++)
                                cout << this->boardPosition[ii][jj]<< "\t";
                            cout << "\n";
                        }
                        
                        
                        cout << "Child\n";
                        for(int ii=0;ii<max_Depth;ii++){
                            for(int jj=0;jj<max_Depth;jj++)
                                cout << child->boardPosition[ii][jj]<< "\t";
                            cout << "\n";
                        }
                        cout <<"step\n";
                    }
                    
                        
                }
            }
        }
   
    if(this->number_Of_Children==0){
        this->pass=true;
        
    }
/*Selecting the next move*/        
    else
        if(this->player == 'X'){ //Maximising player
            
            int max_Position=0;
            int childs=0;
            int max=this->childern[childs]->evaluation_Value;
            childs++;
            while(childs < this->number_Of_Children){
                if(this->childern[childs]->evaluation_Value > max){
                    max=this->childern[childs]->evaluation_Value;
                    max_Position=childs;
                }
                else if(this->childern[childs]->evaluation_Value == max){
                    if(this->childern[childs]->ver_Position < this->childern[max_Position]->ver_Position){
                        max=this->childern[childs]->evaluation_Value;
                    max_Position=childs;
                    }
                }
                childs++;
            }
            this->evaluation_Value=max;
            this->selected_Move=max_Position;
//            this->har_Position=this->childern[max_Position]->har_Position;
  //          this->ver_Position=this->childern[max_Position]->ver_Position;
            cout << "\n" << this->evaluation_Value;
            
        }
        else{
            int childs=0;
            int min=this->childern[childs]->evaluation_Value;
            int min_Position=0;
            childs++;
            while(childs < this->number_Of_Children){
                if(this->childern[childs]->evaluation_Value < min){
                    min=this->childern[childs]->evaluation_Value;
                    min_Position=childs;
                }
                else if(this->childern[childs]->evaluation_Value == min){
                    if(this->childern[childs]->ver_Position < this->childern[min_Position]->ver_Position){
                        min=this->childern[childs]->evaluation_Value;
                        min_Position=childs;
                    }
                }
                childs++;
            }
            this->evaluation_Value=min;
           // this->har_Position=this->childern[min_Position]->har_Position;
           // this->ver_Position=this->childern[min_Position]->ver_Position;
            this->selected_Move = min_Position;
            cout << "\n" << this->evaluation_Value;
            
        }
    
    
        this->print();
    
}

void greedy::print(){
    
    ofstream out;
    if(this->pass==false){
        out.open("/home/sandeep/Desktop/output2.txt",ios::out);
    for(int i=0;i<max_Depth;i++){
        for (int j=0;j<max_Depth;j++){
            out << this->childern[this->selected_Move]->boardPosition[i][j] ;
        }
        out << "\n";
    }
    }
    else{
        out.open("/home/sandeep/Desktop/output2.txt",ios::out);
    for(int i=0;i<max_Depth;i++){
        for (int j=0;j<max_Depth;j++){
            out << this->boardPosition[i][j] ;
            }
        out << "\n";
        }
    }
    
    out.close();
    
}