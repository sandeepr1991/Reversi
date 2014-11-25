/* 
 * File:   alphaBeta.cpp
 * Author: sandeep
 * 
 * Created on October 11, 2014, 4:19 PM
 */
#include "alphaBeta.h"
#include "main.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

int movements2[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
alphaBeta::alphaBeta() {
    this->number_Of_Children=0;
    this->leaf=1;
    this->depth=0;
    this->har_Position=-1;
    this->ver_Position=-1;
    this->end_Game=false;
    this->alpha=-9999;
    this->beta=9999;
    this->pass=false;
    this->selected_Move=0;
    for(int i=0;i<25;i++){
        this->alpha_Set[i]=-9999;
        this->beta_Set[i]=9999;
    }
}

alphaBeta::alphaBeta(const alphaBeta& orig) {
}

alphaBeta::~alphaBeta() {
}

void alphaBeta::set_Position(){
    this->har_Position=0;
    this->ver_Position=0;
}

/* get the depth of the tree*/

int alphaBeta::get_Depth(){
    return(this->depth);
}

void alphaBeta::set_Evaluation()
{
    if(this->player=='X')
        this->evaluation_Value=-9999;
    else
        this->evaluation_Value=9999;
}

void alphaBeta::update_Board(char board[max_Depth][max_Depth]){
    int i,j;
    for(i=0;i<max_Depth;i++)
        for(j=0;j<max_Depth;j++)
            this->boardPosition[i][j]=board[i][j];
}
void alphaBeta::generate_Children(){
    int i,j,k,temp_Conquered=0;
    if(this->depth == required_Depth){
        this->evaluate();

        return;
    }
    for(j=0;j<max_Depth;j++)
        for(i=0;i<max_Depth;i++){
            if(this->boardPosition[i][j]==this->player){
                for(k=0;k<8;k++){
                    temp_Conquered = 0;
                    temp_Conquered = number_Conquered(i,j,movements2[k][0],movements2[k][1]);
                    if(temp_Conquered>0){
                        this->leaf = 0;                        
                        alphaBeta* child = new alphaBeta;
                        child->update_Board(this->boardPosition);
                        child->depth=this->get_Depth()+1;
                        child->ver_Position=i+movements2[k][0]*(temp_Conquered+1);
                        child->har_Position=j+movements2[k][1]*(temp_Conquered+1);
                        child->alpha=this->alpha;
                        child->beta=this->beta;
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
                            child->boardPosition[i+movements2[k][0]*m][j+movements2[k][1]*m]=this->player;
                            child->check_Directions(i+movements2[k][0]*m,j+movements2[k][1]*m);
                        }
                        child->check_Directions(i+movements2[k][0]*m,j+movements2[k][1]*m);
                        //child->evaluate();
                        this->childern[this->number_Of_Children++]=child;
                     /*   cout << "Parent\n";
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
                        }*/
                      //  cout <<"step\n";
                    }
                    
                        
                }
            }
        }
/* Generating all the possible moves*/ 
    int max_Position=0;
    int min_Position=0;
    if(this->number_Of_Children!=0){
        int childs=0;
        this->evaluation_Set[0]=this->evaluation_Value;
        this->alpha_Set[0]=this->alpha;
        this->beta_Set[0]=this->beta;
        
        for(int ii=1;ii<this->number_Of_Children;ii++)
            for(int jj=0;jj<ii;jj++){
                
                    if(this->childern[ii]->ver_Position<this->childern[jj]->ver_Position)
                    {
                        alphaBeta *temp=new alphaBeta;
                        temp=this->childern[ii];
                        this->childern[ii]=this->childern[jj];
                        this->childern[jj]=temp;
                        
                    }
                    else if(this->childern[ii]->ver_Position==this->childern[jj]->ver_Position){
                        if(this->childern[ii]->har_Position<this->childern[jj]->har_Position){
                            alphaBeta *temp=new alphaBeta;
                            temp=this->childern[ii];
                            this->childern[ii]=this->childern[jj];
                            this->childern[jj]=temp;
                        }
                    }
                
            }
        
        while(childs < this->number_Of_Children){
            this->childern[childs]->alpha=this->alpha;
            this->childern[childs]->beta=this->beta;
            this->childern[childs]->generate_Children();
            
        
        
/*Selecting the next move*/        
        
        if(this->player == 'X'){ //Maximising player
            
          /*  this->evaluation_Set[1]=this->childern[0]->evaluation_Value; 
            this->beta_Set[1]=this->childern[0]->evaluation_Value;
            this->alpha_Set[1]=this->childern[0]->alpha;
            */
            
            //this->evaluation_Value=this->childern[min_childs]->evaluation_Value;
            
           
            
           
               
                if(this->evaluation_Value<this->childern[childs]->evaluation_Value){
                    this->evaluation_Set[childs+1]=this->childern[childs]->evaluation_Value;
                    if(this->alpha_Set[childs]<this->childern[childs]->evaluation_Value){
                        this->alpha_Set[childs+1]=this->childern[childs]->evaluation_Value;
                        this->alpha=this->childern[childs]->evaluation_Value;
                    }
                    else
                        this->alpha_Set[childs+1]=this->alpha_Set[childs];
                    this->evaluation_Value=this->childern[childs]->evaluation_Value;
                    this->beta_Set[childs+1]=this->beta_Set[childs];
                    
                    max_Position=childs;
                }
                else{
                    this->evaluation_Set[childs+1]=this->evaluation_Set[childs];
                    this->beta_Set[childs+1]=this->beta_Set[childs];
                    this->alpha_Set[childs+1]=this->alpha_Set[childs];
                }
               
                if(this->beta <= this->alpha){
                        childs++;
                        this->number_Of_Children=childs;
                        this->selected_Move = max_Position;
                        break;
                }    
                    
            
           /* this->evaluation_Value=min;
            this->evaluation_Set[childs+1]=min;
            this->beta_Set[childs+1]=this->beta;*/
           // this->har_Position=this->childern[min_Position]->har_Position;
           // this->ver_Position=this->childern[min_Position]->ver_Position;
            this->selected_Move = max_Position;
          //  cout << "\n" << this->evaluation_Value;
           
            
        }
        else{
            
            
            /*this->evaluation_Set[1]=this->childern[0]->evaluation_Value; 
            this->beta_Set[1]=this->childern[0]->evaluation_Value;
            this->alpha_Set[1]=this->childern[0]->alpha;*/
            
            //this->evaluation_Value=this->childern[min_childs]->evaluation_Value;
            
            
            
           
               
                if(this->evaluation_Value>this->childern[childs]->evaluation_Value){
                    
                    min_Position=childs;
                    this->evaluation_Set[childs+1]=this->childern[childs]->evaluation_Value;
                    if(this->beta_Set[childs]>this->childern[childs]->evaluation_Value){
                        this->beta_Set[childs+1]=this->childern[childs]->evaluation_Value;
                        this->beta=this->childern[childs]->evaluation_Value;
                    }
                    else
                        this->beta_Set[childs+1]=this->beta_Set[childs];
                    this->evaluation_Value=this->childern[childs]->evaluation_Value;
                    this->alpha_Set[childs+1]=this->alpha_Set[childs];
                    
                    
                }
                else{
                    this->evaluation_Set[childs+1]=this->evaluation_Set[childs];
                    this->beta_Set[childs+1]=this->beta_Set[childs];
                    this->alpha_Set[childs+1]=this->alpha_Set[childs];
                }
               
                if(this->beta <= this->alpha){
                    
                        
                        childs++;
                        this->number_Of_Children=childs;
                        this->selected_Move = max_Position;
                        break;
                }
            
           /* this->evaluation_Value=min;
            this->evaluation_Set[childs+1]=min;
            this->beta_Set[childs+1]=this->beta;*/
           // this->har_Position=this->childern[min_Position]->har_Position;
           // this->ver_Position=this->childern[min_Position]->ver_Position;
            this->selected_Move = min_Position;
          //  cout << "\n" << this->evaluation_Value;
           
            
        }
            childs++;
    }
    }
    else{
        if(this->is_Game_Finished()==true){
            this->evaluate();
            
        }
        else
        if(this->ver_Position==-1){
            alphaBeta *child=new alphaBeta;
            this->pass=true;
            this->leaf=0;
            child->end_Game=true;
            this->evaluation_Set[0]=this->evaluation_Value;
            child->update_Board(this->boardPosition);
            child->evaluate();
            this->evaluation_Set[1]=child->evaluation_Value;
            this->evaluation_Value=child->evaluation_Value;
            this->number_Of_Children=1;
            child->depth=this->get_Depth()+1;
            child->alpha=this->alpha;
            child->beta=this->beta;
            if(this->player=='X'){
                this->alpha=child->evaluation_Value;
                this->alpha_Set[1]=child->evaluation_Value;
                this->beta_Set[1]=this->beta_Set[0];
            }
            else{
                this->beta=child->evaluation_Value;
                this->beta_Set[1]=child->evaluation_Value;
                this->alpha_Set[1]=this->alpha_Set[0];
            }
            this->childern[0]=child;
        }
        else{
            alphaBeta *child=new alphaBeta;
            this->pass=true;
            this->leaf=0;
           
            child->update_Board(this->boardPosition);
            child->depth=this->get_Depth()+1;

       //     this->evaluate();
            if(this->player=='X'){
                child->set_Player('O');
                child->evaluation_Value=9999;
            }
            else{
                child->set_Player('X');
                child->evaluation_Value=-9999;
            }
            child->alpha=this->alpha;
            child->beta=this->beta;
            
            this->childern[0]=child;
            this->number_Of_Children=1;
            this->evaluation_Set[0]=this->evaluation_Value;
            this->alpha_Set[0]=this->alpha;
            this->beta_Set[0]=this->beta;
            child->generate_Children();

            this->evaluation_Value=child->evaluation_Value;
            this->evaluation_Set[1]=child->evaluation_Value;
            if(this->player=='X'){
                this->alpha=child->evaluation_Value;
                this->alpha_Set[1]=child->evaluation_Value;
                this->beta_Set[1]=this->beta_Set[0];
            }
            else{
                this->beta=child->evaluation_Value;
                this->beta_Set[1]=child->evaluation_Value;
                this->alpha_Set[1]=this->alpha_Set[0];
            }
                
            
            
          //  cout << "here";
        }
    }
    
}
void alphaBeta::set_Player(char player){
    this->player=player;
}

int alphaBeta::number_Conquered(int pos_Hor,int pos_Ver,int horizontal, int vertical){
    int ret_Value=0;
    char search='X';
    int move=0;
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

void alphaBeta::check_Directions(int pos_Hor1,int pos_Ver1){
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
                    horizontal=movements2[k][0];
                    vertical=movements2[k][1];
                    
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
                        this->boardPosition[pos_Hor1+movements2[k][0]*m][pos_Ver1+movements2[k][1]*m]=search;
                        
                    }
                }
            
        
             
}
/* Function evaluate
   To calculate the evaluation value of leaf nodes 
 */
void alphaBeta::evaluate(){
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


void alphaBeta::print(){
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
            
            
                if(this->alpha==-9999&&this->beta==9999)
                        out << "pass"<<","<<this->depth<<","<<this->evaluation_Value<<","<<"-Infinity,"<<"Infinity\n";
                    else if(this->alpha_Set[childs]==-9999&&this->beta!=9999)
                        out << "pass"<<","<<this->depth<<","<<this->evaluation_Value<<","<<"Infinity,"<<this->beta<<"\n";
                    else if(this->alpha!=-9999 && this->beta==9999)
                        out << "pass"<<","<<this->depth<<","<<this->evaluation_Value<<","<<this->alpha<<",Infinity"<<"\n";
                    else
                        out << "pass"<<","<<this->depth<<","<<this->evaluation_Value<<","<<this->alpha<<","<<this->beta<<"\n";
                
                childs++;
                out.close();
                break;
//         /       exit(1);
               
            
        }
        else{
        if(this->depth == 0){
            if(childs==0){
                out <<"Node,Depth,Value,Alpha,Beta\n";
                out << "root," <<this->depth<<","<<((this->evaluation_Set[childs]==9999)?"Infinity,":"-Infinity,")<<"-Infinity,"<<"Infinity\n";
            }
            if(this->pass==true){
                if(this->childern[childs]->alpha_Set[childs]==-9999&&this->childern[childs]->beta_Set[childs]==9999)
                        out << "pass"<<","<<this->childern[childs]->depth<<","<<((this->childern[childs]->evaluation_Set[childs]==9999)?"Infinity":"-Infinity")<<","<<"-Infinity,"<<"Infinity\n";
                    else if(this->childern[childs]->alpha_Set[childs]==-9999&&this->childern[childs]->beta_Set[childs]!=9999)
                        out << "pass"<<","<<this->childern[childs]->depth<<","<<((this->childern[childs]->evaluation_Set[childs]==9999)?"Infinity":"-Infinity")<<","<<"Infinity,"<<this->childern[childs]->beta_Set[childs]<<"\n";
                    else if(this->childern[childs]->alpha_Set[childs]!=-9999 && this->childern[childs]->beta_Set[childs]==9999)
                        out << "pass"<<","<<this->childern[childs]->depth<<","<<((this->childern[childs]->evaluation_Set[childs]==9999)?"Infinity":"-Infinity")<<","<<this->childern[childs]->alpha_Set[childs]<<",Infinity"<<"\n";
                    else
                        out << "pass"<<","<<this->childern[childs]->depth<<","<<((this->childern[childs]->evaluation_Set[childs]==9999)?"Infinity":"-Infinity")<<","<<this->childern[childs]->alpha_Set[childs]<<","<<this->childern[childs]->beta_Set[childs]<<"\n";
                out.close();
                
                
            }
            
        }
        else{
            if(childs==0){
                if(this->leaf == 1){
                    if(this->alpha==-9999&&this->beta==9999)
                        out << mapping[this->har_Position]<<this->ver_Position+1<<","<<this->depth<<","<<this->evaluation_Value<<","<<"-Infinity,"<<"Infinity\n";
                    else if(this->alpha==-9999&&this->beta!=9999)
                        out << mapping[this->har_Position]<<this->ver_Position+1<<","<<this->depth<<","<<this->evaluation_Value<<","<<"-Infinity,"<<this->beta<<"\n";
                    else if(this->alpha!=-9999 && this->beta==9999)
                        out << mapping[this->har_Position]<<this->ver_Position+1<<","<<this->depth<<","<<this->evaluation_Value<<","<<this->alpha<<","<<"Infinity"<<"\n";
                    else
                        out << mapping[this->har_Position]<<this->ver_Position+1<<","<<this->depth<<","<<this->evaluation_Value<<","<<this->alpha<<","<<this->beta<<"\n";
                    }    
                else if(this->ver_Position!=-1){
                    
                    if(this->alpha_Set[childs]==-9999&&this->beta_Set[childs]==9999)
                        out << mapping[this->har_Position]<<this->ver_Position+1<<","<<this->depth<<","<<((this->evaluation_Set[childs]==9999)?"Infinity":"-Infinity")<<","<<"-Infinity,"<<"Infinity\n";
                    else if(this->alpha_Set[childs]==-9999&&this->beta_Set[childs]!=9999)
                        out << mapping[this->har_Position]<<this->ver_Position+1<<","<<this->depth<<","<<((this->evaluation_Set[childs]==9999)?"Infinity":"-Infinity")<<","<<"Infinity,"<<this->beta_Set[childs]<<"\n";
                    else if(this->alpha_Set[childs]!=-9999 && this->beta_Set[childs]==9999)
                        out << mapping[this->har_Position]<<this->ver_Position+1<<","<<this->depth<<","<<((this->evaluation_Set[childs]==9999)?"Infinity":"-Infinity")<<","<<this->alpha_Set[childs]<<",Infinity"<<"\n";
                    else
                        out << mapping[this->har_Position]<<this->ver_Position+1<<","<<this->depth<<","<<((this->evaluation_Set[childs]==9999)?"Infinity":"-Infinity")<<","<<this->alpha_Set[childs]<<","<<this->beta_Set[childs]<<"\n";
                    
                    if(this->pass==true){
                        if(this->childern[childs]->alpha_Set[childs]==-9999&&this->childern[childs]->beta_Set[childs]==9999)
                        out << "pass"<<","<<this->childern[0]->depth<<","<<((this->childern[childs]->evaluation_Set[childs]==9999)?"Infinity":"-Infinity")<<","<<"-Infinity,"<<"Infinity\n";
                    else if(this->childern[childs]->alpha_Set[childs]==-9999&&this->childern[childs]->beta_Set[childs]!=9999)
                        out << "pass"<<","<<this->childern[0]->depth<<","<<((this->childern[childs]->evaluation_Set[childs]==9999)?"Infinity":"-Infinity")<<","<<"Infinity,"<<this->childern[childs]->beta_Set[childs]<<"\n";
                    else if(this->childern[childs]->alpha_Set[childs]!=-9999 && this->childern[childs]->beta_Set[childs]==9999)
                        out << "pass"<<","<<this->childern[0]->depth<<","<<((this->childern[childs]->evaluation_Set[childs]==9999)?"Infinity":"-Infinity")<<","<<this->childern[childs]->alpha_Set[childs]<<",Infinity"<<"\n";
                    else
                        out << "pass"<<","<<this->childern[0]->depth<<","<<((this->childern[childs]->evaluation_Set[childs]==9999)?"Infinity":"-Infinity")<<","<<this->childern[childs]->alpha_Set[childs]<<","<<this->childern[childs]->beta_Set[childs]<<"\n";
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
             if(this->depth!=0 && this->ver_Position!=-1){
            if(this->alpha_Set[childs+1]==-9999&&this->beta_Set[childs+1]==9999)
                        out << mapping[this->har_Position]<<this->ver_Position+1<<","<<this->depth<<","<<this->evaluation_Set[childs+1]<<","<<"-Infinity,"<<"Infinity\n";
                    else if(this->alpha_Set[childs+1]==-9999&&this->beta_Set[childs+1]!=9999)
                        out << mapping[this->har_Position]<<this->ver_Position+1<<","<<this->depth<<","<<this->evaluation_Set[childs+1]<<","<<"-Infinity,"<<this->beta_Set[childs+1]<<"\n";
                    else if(this->alpha_Set[childs+1]!=-9999 && this->beta_Set[childs+1]==9999)
                        out << mapping[this->har_Position]<<this->ver_Position+1<<","<<this->depth<<","<<this->evaluation_Set[childs+1]<<","<<this->alpha_Set[childs+1]<<",Infinity"<<"\n";
                    else
                        out << mapping[this->har_Position]<<this->ver_Position+1<<","<<this->depth<<","<<this->evaluation_Set[childs+1]<<","<<this->alpha_Set[childs+1]<<","<<this->beta_Set[childs+1]<<"\n";
             }
             else if(this->depth==0){
                 if(this->alpha_Set[childs+1]==-9999&&this->beta_Set[childs+1]==9999)
                out << "root," <<this->depth<<","<<this->evaluation_Set[childs+1]<<","<<"-Infinity,"<<"Infinity\n";
            else if(this->alpha_Set[childs+1]==-9999&&this->beta_Set[childs+1]!=9999)
                out << "root," <<this->depth<<","<<this->evaluation_Set[childs+1]<<","<<"-Infinity,"<<this->beta_Set[childs+1]<<"\n";
            else if(this->alpha_Set[childs+1]!=-9999 && this->beta_Set[childs+1]==9999)
                out << "root," <<this->depth<<","<<this->evaluation_Set[childs+1]<<","<<this->alpha_Set[childs+1]<<","<<"Infinity"<<"\n";
            else
                out << "root," <<this->depth<<","<<this->evaluation_Set[childs+1]<<","<<this->alpha_Set[childs+1]<<","<<this->beta_Set[childs+1]<<"\n";
             }
             else if(this->depth!=0 && this->ver_Position==-1){
                        if(this->alpha_Set[childs+1]==-9999&&this->beta_Set[childs+1]==9999)
                        out << "pass"<<","<<this->depth<<","<<this->evaluation_Set[childs+1]<<","<<"-Infinity,"<<"Infinity\n";
                    else if(this->alpha_Set[childs+1]==-9999&&this->beta_Set[childs+1]!=9999)
                        out << "pass"<<","<<this->depth<<","<<this->evaluation_Set[childs+1]<<","<<"Infinity,"<<this->beta_Set[childs+1]<<"\n";
                    else if(this->alpha_Set[childs+1]!=-9999 && this->beta_Set[childs+1]==9999)
                        out << "pass"<<","<<this->depth<<","<<this->evaluation_Set[childs+1]<<","<<this->alpha_Set[childs+1]<<",Infinity"<<"\n";
                    else
                        out << "pass"<<","<<this->depth<<","<<this->evaluation_Set[childs+1]<<","<<this->alpha_Set[childs+1]<<","<<this->beta_Set[childs+1]<<"\n";
                    }
                    cout<<"here";
            
            
            
            
            
           
           // out << mapping[this->har_Position]<<this->ver_Position+1<<","<<this->depth<<","<<this->evaluation_Set[childs]<<"\n";
            
        }
        childs++;
        } 
    
    }
    
    
bool alphaBeta::is_Game_Finished(){
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
        for(i=0;i<max_Depth && cont==true;i++)
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
        for(;i<max_Depth && cont==true;i++)
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