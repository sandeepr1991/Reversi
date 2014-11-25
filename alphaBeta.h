/* 
 * File:   alphaBeta.h
 * Author: sandeep
 *
 * Created on October 13, 2014, 1:33 PM
 */

#ifndef ALPHABETA_H
#include "main.h"
#define	ALPHABETA_H

class alphaBeta {
public:
    alphaBeta();
    alphaBeta(const alphaBeta& orig);
    virtual ~alphaBeta();    void generate_Children();
    void update_Board(char board[max_Depth][max_Depth]);
    void get_Children();
    void set_Player(char);
    int number_Conquered(int pos_Hor,int pos_Ver,int horizontal, int vertical);
    void check_Directions(int hor,int ver);
    int get_Depth();
    void evaluate();
    void print();
    void set_Evaluation();
    void set_Position();
    bool is_Game_Finished();
private:
    char boardPosition[max_Depth][max_Depth];
    alphaBeta *childern[50];
    int number_Of_Children;
    char player;
    int har_Position;
    int ver_Position;
    int leaf;
    int depth;
    int evaluation_Value;
    int evaluation_Set[50];
    int selected_Move;
    int alpha;
    int alpha_Set[50];
    int beta;
    int beta_Set[25];
    bool end_Game;
    bool pass;
};

#endif	/* ALPHABETA_H */

