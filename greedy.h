/* 
 * File:   greedy.h
 * Author: sandeep
 *
 * Created on October 13, 2014, 8:35 PM
 */

#ifndef GREEDY_H
#define	GREEDY_H
#include "main.h"
class greedy {
public:
    greedy();
    greedy(const greedy& orig);
    virtual ~greedy();
    void generate_Children();
    void update_Board(char board[max_Depth][max_Depth]);
    void set_Player(char);
    int number_Conquered(int pos_Hor,int pos_Ver,int horizontal, int vertical);
    void check_Directions(int hor,int ver);
    void evaluate();
    void print();
private:
    char boardPosition[max_Depth][max_Depth];
    greedy *childern[25];
    int number_Of_Children;
    char player;
    int har_Position;
    int ver_Position;
    int leaf;
    int depth;
    int evaluation_Value;
    int selected_Move;
    bool pass;
    bool end_Game;
};

#endif	/* GREEDY_H */

