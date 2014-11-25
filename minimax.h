/* 
 * File:   minimax.h
 * Author: sandeep
 *
 * Created on October 11, 2014, 4:19 PM
 */

#ifndef MINIMAX_H
#define	MINIMAX_H
#include <iostream>
#include "main.h"
class minimax {

public:
    minimax();
    minimax(const minimax& orig);
    virtual ~minimax();
    void generate_Children();
    void update_Board(char board[max_Depth][max_Depth]);
    void get_Children();
    void set_Player(char);
    int number_Conquered(int pos_Hor,int pos_Ver,int horizontal, int vertical);
    void check_Directions(int hor,int ver);
    int get_Depth();
    void evaluate();
    void print();
    void set_Position();
    bool is_Game_Finished();
 
private:
    char boardPosition[max_Depth][max_Depth];
    minimax *childern[50];
    int number_Of_Children;
    char player;
    int har_Position;
    int ver_Position;
    int leaf;
    int depth;
    int evaluation_Value;
    int evaluation_Set[50];
    int selected_Move;
    bool end_Game;
    bool pass;
};

#endif	/* MINIMAX_H */

