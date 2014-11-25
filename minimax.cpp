/* 
 * File:   minimax.cpp
 * Author: sandeep
 * 
 * Created on October 11, 2014, 4:19 PM
 */
#include "minimax.h"
#include "main.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int movements1[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
//int minimax::log={};

minimax::minimax() {
    this->number_Of_Children=0;
    this->leaf=1;
    this->depth=0;
    this->har_Position=-1;
    this->ver_Position=-1;
    this->evaluation_Value=-9999;
    this->end_Game=false;
    this->pass=false;
    this->selected_Move=0;
}

void minimax::set_Position(){
    this->har_Position=0;
    this->ver_Position=0;
}

minimax::minimax(const minimax& orig) {
}

minimax::~minimax() {
}
/* get the depth of the tree*/

int minimax::get_Depth(){
    return(this->depth);
}

void minimax::update_Board(char board[max_Depth][max_Depth]){
    int i,j;
    for(i=0;i<max_Depth;i++)
        for(j=0;j<max_Depth;j++)
            this->boardPosition[i][j]=board[i][j];
}
void minimax::generate_Children(){
    int i,j,k,temp_Conquered=0;
    if(this->depth == required_Depth){
        this->evaluate();
        return;
    }
    for(i=0;i<max_Depth;i++)
        for(j=0;j<max_Depth;j++){
            if(this->boardPosition[i][j]==this->player){
                for(k=0;k<8;k++){
                    temp_Conquered = 0;
                    temp_Conquered = number_Conquered(i,j,movements1[k][0],movements1[k][1]);
                    if(temp_Conquered>0){
                        this->leaf = 0;                        
                        minimax* child = new minimax;
                        child->update_Board(this->boardPosition);
                        child->depth=this->get_Depth()+1;
                        child->ver_Position=i+movements1[k][0]*(temp_Conquered+1);
                        child->har_Position=j+movements1[k][1]*(temp_Conquered+1);
                        if(this->player=='X'){
                            child->set_Player('O');
                            child->evaluation_Value=9999;
                        }
                        else{
                            child->set_Player('X');
                            child->evaluation_Value=-9999;
                        }
                        int m;
                        for( m=1;m<=(temp_Conquered+1);m++){
                            child->boardPosition[i+movements1[k][0]*m][j+movements1[k][1]*m]=this->player;
                            child->check_Directions(i+movements1[k][0]*m,j+movements1[k][1]*m);
                        }
                        child->check_Directions(i+movements1[k][0]*m,j+movements1[k][1]*m);
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
          //              cout <<"step\n";
                    }
                    
                        
                }
            }
        }
/* Generating all the possible moves*/ 
    
    if(this->number_Of_Children!=0){
        int childs=0;
        this->evaluation_Set[0]=this->evaluation_Value;
        for(int ii=1;ii<this->number_Of_Children;ii++)
            for(int jj=0;jj<ii;jj++){
               
                    if(this->childern[ii]->ver_Position<this->childern[jj]->ver_Position)
                    {
                        minimax *temp=new minimax;
                        temp=this->childern[ii];
                        this->childern[ii]=this->childern[jj];
                        this->childern[jj]=temp;
                        
                    }
                    else if(this->childern[ii]->ver_Position==this->childern[jj]->ver_Position)
                    {
                        if(this->childern[ii]->har_Position<this->childern[jj]->har_Position){
                            minimax *temp=new minimax;
                            temp=this->childern[ii];
                            this->childern[ii]=this->childern[jj];
                            this->childern[jj]=temp;  
                        }
                    }
                
            }
        while(childs < this->number_Of_Children){
        //    this->childern[childs]->evaluate();
            this->childern[childs]->generate_Children();
            
            childs++;
        }
        
            
            
       /*     log[log_Number][0]=this->har_Position;
            log[log_Number][1]=this->ver_Position;
            log[log_Number][2]=this->depth;
            log[log_Number][3]=this->evaluation_Value;
/*Selecting the next move*/        
        
        if(this->player == 'X'){ //Maximising player
            
            int max_Position=0;
            int maxChilds=0;
            this->evaluation_Set[0]=this->evaluation_Value;
            this->evaluation_Set[1]=this->childern[0]->evaluation_Value;
            int max=this->childern[maxChilds]->evaluation_Value;
            maxChilds++;
            while(maxChilds < this->number_Of_Children){
                if(this->childern[maxChilds]->evaluation_Value > max){
                    max=this->childern[maxChilds]->evaluation_Value;
                    max_Position=maxChilds;
                }
                
                if(this->evaluation_Set[maxChilds]<max)
                    this->evaluation_Set[maxChilds+1]=max;
                else
                    this->evaluation_Set[maxChilds+1]=this->evaluation_Set[maxChilds];
                maxChilds++;
            }
            this->evaluation_Value=max;
            this->evaluation_Set[childs+1]=max;
            this->selected_Move=max_Position;
//            this->har_Position=this->childern[max_Position]->har_Position;
  //          this->ver_Position=this->childern[max_Position]->ver_Position;
       //     cout << "\n" << this->evaluation_Value;
            
        }
        else{
            int minChilds=0;
            this->evaluation_Set[0]=this->evaluation_Value;
            this->evaluation_Set[1]=this->childern[0]->evaluation_Value; 
            int min=this->childern[minChilds]->evaluation_Value;
            int min_Position=0;
            minChilds++;
            while(minChilds < this->number_Of_Children){
                if(this->childern[minChilds]->evaluation_Value < min){
                    min=this->childern[minChilds]->evaluation_Value;
                    min_Position=minChilds;
                }
                
                
                if(this->evaluation_Set[minChilds]>min)
                    this->evaluation_Set[minChilds+1]=min;
                else
                    this->evaluation_Set[minChilds+1]=this->evaluation_Set[minChilds];
                minChilds++;
            }
            this->evaluation_Value=min;
            
           // this->har_Position=this->childern[min_Position]->har_Position;
           // this->ver_Position=this->childern[min_Position]->ver_Position;
            this->selected_Move = min_Position;
     //       cout << "\n" << this->evaluation_Value;
            
        }
            
        
    }
    else{
        if(this->is_Game_Finished()==true){
            this->evaluate();
            
        }
        else
        if(this->ver_Position==-1){
            this->pass=true;
            this->leaf=0;
            minimax *child=new minimax;
            child->update_Board(this->boardPosition);
            child->evaluate();
            child->depth=this->get_Depth()+1;
            child->end_Game=true;
            this->childern[0]=child;
            this->number_Of_Children=1;
            this->evaluation_Set[0]=this->evaluation_Value;
            this->evaluation_Value=child->evaluation_Value;
            this->evaluation_Set[1]=child->evaluation_Value;
        }
        else{
            minimax *child=new minimax;
            this->pass=true;
            this->leaf=0;
            //child->pass=true;
            child->update_Board(this->boardPosition);
            child->evaluate();
            child->depth=this->get_Depth()+1;
            if(this->player=='X'){
               child->set_Player('O');
               child->evaluation_Value=9999;
            }
            else{
               child->set_Player('X');
               child->evaluation_Value=-9999;
            }
            this->childern[0]=child;
            this->number_Of_Children=1;
            this->evaluation_Set[0]=this->evaluation_Value;
            child->generate_Children();
            this->evaluation_Value=child->evaluation_Value;
            this->evaluation_Set[1]=child->evaluation_Value;
            
        }
    }
    
}
void minimax::set_Player(char player){
    this->player=player;
}

int minimax::number_Conquered(int pos_Hor,int pos_Ver,int horizontal, int vertical){
    int ret_Value=0;
    int move=0;
    char search='X';
    if(this->player == 'X')
        search='O';
    pos_Hor+=horizontal;
    pos_Ver+=vertical;
    while(pos_Hor>=0 && pos_Ver>=0 && pos_Hor<max_Depth && pos_Ver<max_Depth){
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

void minimax::check_Directions(int pos_Hor1,int pos_Ver1){
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
                    horizontal=movements1[k][0];
                    vertical=movements1[k][1];
                    
                    pos_Hor+=horizontal;
                    pos_Ver+=vertical;
                     while(pos_Hor>=0 && pos_Ver>=0 && pos_Hor<max_Depth && pos_Ver<max_Depth){
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
                        this->boardPosition[pos_Hor1+movements1[k][0]*m][pos_Ver1+movements1[k][1]*m]=search;
                        
                    }
                }
            
        
             
}
/* Function evaluate
   To calculate the evaluation value of leaf nodes 
 */
void minimax::evaluate(){
    int i,j;
    int evaluation_value1=0;
    if(this->leaf==1){
        for(j=0;j<max_Depth;j++)
            for(i=0;i<max_Depth;i++){
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


void minimax::print(){
    
    char mapping[8]={'a','b','c','d','e','f','g','h'};
    ofstream out;
    
    
    if(this->depth==0)
        remove("/home/sandeep/Desktop/output2.txt");
    out.open("/home/sandeep/Desktop/output2.txt",ios::app);
    if(this->depth==0)
    for(int i=0;i<max_Depth;i++){
        for (int j=0;j<max_Depth;j++){
            if(this->number_Of_Children>0)
                out << this->childern[this->selected_Move]->boardPosition[i][j];
            else
                out << this->boardPosition[i][j];
        }
        out << "\n";
        
    }
    
    
    int childs=0;
    while((this->leaf==1 ||childs < this->number_Of_Children) ){    
        if(this->end_Game==true||(this->ver_Position==-1&&this->depth!=0&&this->number_Of_Children==0))
        {
            
            
                out << "pass,"<<this->depth<<","<<this->evaluation_Value<<"\n";
                out.close();
                
                childs++;
        //        exit(1);
                break;
            
        }
        else{
        if(this->depth == 0){
            if(childs==0){
                out << "Node,Depth,Value\n";
                out << "root," <<this->depth<<","<<"-Infinity"<<"\n";
            }
            if(this->pass==true){
                
                out << "pass,"<<this->childern[childs]->depth<<","<<((this->childern[childs]->evaluation_Set[childs]==9999)?"Infinity":"-Infinity")<<"\n";
                out.close();
                
                
            }
            
            
            
            
            
            
            
        }
        else{
            if(childs==0){
                if(this->leaf == 1)
                        out << mapping[this->har_Position]<<this->ver_Position+1<<","<<this->depth<<","<<this->evaluation_Value<<"\n";
                else if(this->ver_Position!=-1){
                        out << mapping[this->har_Position]<<this->ver_Position+1<<","<<this->depth<<","<<((this->childern[childs]->evaluation_Set[childs]==9999)?"Infinity":"-Infinity")<<"\n";
                        if(this->pass==true){
                
                out << "pass,"<<this->depth<<","<<((this->childern[0]->evaluation_Set[childs]==9999)?"Infinity":"-Infinity") <<"\n";
                        }
                out.close();
                
               
            }
                }
            }
            
               
            if(this->leaf==1)
                break;
            out.close();
            this->childern[childs]->print();
             out.open("/home/sandeep/Desktop/output2.txt",ios::app);
             if(this->depth!=0&& this->ver_Position!=-1)
                out << mapping[this->har_Position]<<this->ver_Position+1<<","<<this->depth<<","<<this->evaluation_Set[childs+1]<<"\n";
             else if(this->depth == 0)
                 out << "root," <<this->depth<<","<<this->evaluation_Set[childs+1]<<"\n";
             else if(this->depth!=0 && this->ver_Position==-1)
                 out << "pass," <<this->depth<<","<<this->evaluation_Set[childs+1]<<"\n";
                
            
            
            
            
            
           
           // out << mapping[this->har_Position]<<this->ver_Position+1<<","<<this->depth<<","<<this->evaluation_Set[childs]<<"\n";
            
        }
        childs++;
        }
        
            
    }

bool minimax::is_Game_Finished(){
    bool ret_Value=false;
    bool cont=true;
    char search;
    int i,j;
    for(i=0;i<max_Depth && cont;i++)
        for(j=0;j<max_Depth;j++){
            if(this->boardPosition[i][j]=='*')
                cont=false;
                break;
        }
    if(i==max_Depth && j==max_Depth){
        ret_Value = true;
    
        
    }
    else{
        cont = true;
        for(i=0;i<max_Depth && cont;i++)
            for(j=0;j<max_Depth;j++){
                if(this->boardPosition[i][j]=='X' || this->boardPosition[i][j]=='O'){
                    search = this->boardPosition[i][j];
                    cont=false;
                    break;
                }
            }
        if(search=='X')
            search='O';
        else
            search='X';
        
        i--;
        cont =  true;
        for(;i<max_Depth && cont;i++)
            for(j=0;j<max_Depth;j++){
                if(this->boardPosition[i][j]== search){
                    cont=false;
                    break;
                }
            }
        if(i==max_Depth && j==max_Depth)
        ret_Value = true;
    }
    return ret_Value;
    
        
}
    
    
    
