#include <stdio.h>

char board[8][8]; // this shouldn't be a globall array, but i can't be expected to do two shits about it

void read_input() {
    for(int i = 0 ; i < 8; i++) {
        for(int j = 0 ; j < 8; j++)
            scanf("%c", &board[i][j]);

        char trash;
        scanf("%c", &trash); // removing char(10) from the stdin
    }
}

int max(int a, int b) {
    return a>b?a:b;
}

/*
 * this funcion, will (if I ever get around to implementing that)
 * return 0 if the move is valid
 * return 1 if the move is invalid
 * return 2 if the move is vaild, but the next move in that direction will not be
 * (a checker has been removed)
*/
int check_board(board_i, board_j, board_res_i, board_res_j) {
    return 0;

}

int parse_king(int board_i, int board_j) {
    int result = 0, ret;
    for(int i = -1; i <= 1; i++)
        for(int j = -1; j <= 1; j++)
            if(j != 0 && i != 0) {
                ret = check_board(board_i, board_j, board_i+2, board_j+1);
                if (ret == 0 || ret == 2) 
                    result++;
            }
    return result;
}

// TODO add pion switching at the last line
int parse_pion(int board_i, int board_j) {
    int ret, result = 0;
    ret = check_board(board_i, board_j, board_i-1, board_j);
    if (ret == 0) {
        if(board_i == 1)
            result += 4;
        else
            result ++;
        
        if(board_i == 6) {
            ret = check_board(board_i, board_j, board_i-2, board_j);
            if(ret == 0)
                result ++;
        }
    }

    ret = check_board(board_i, board_j, board_i-1, board_j-1);
    if (ret == 2)
        if(board_i == 1)
            result += 4;
        else
            result ++;

    ret = check_board(board_i, board_j, board_i-1, board_j+1);
    if (ret == 2)
        if (board_i == 1)
            result += 4;
        else
            result ++;

    return result;
}

//move a tower in four directions, if it hits another checker stop moving it.
int parse_tower(int board_i, int board_j) {
    int result = 0, ret;
    for(int i = board_i-1; i >= 0; i--) {
        ret = check_board(board_i, board_j, i, board_j);
            if (ret == 0)
                result ++;

            if (ret == 1)
                break;

            if (ret == 2) {
                result ++;
                break;
            }
    }

    for(int i = board_i+1; i < 8; i++) {
        ret = check_board(board_i, board_j, i, board_j);
            if(ret == 0)
                result ++;

            if (ret == 1)
                break;

            if(ret == 2) {
                result ++;
                break;
            }
    }

    for(int j = board_j-1; j >= 0; j--) {
        ret = check_board(board_i, board_j, board_i, j);
            if(ret == 0)
                result ++;

            if (ret == 1)
                break;

            if(ret == 2) {
                result ++;
                break;
            }
    }

    for(int j = board_j+1; j < 8; j++) {
        ret = check_board(board_i, board_j, board_i, j);
            if(ret == 0)
                result ++;

            if (ret == 1)
                break;

            if(ret == 2) {
                result ++;
                break;
            }
    }

    return result;
}

// this function is lit af 😂😂😂
int parse_horse_person(int board_i, int board_j) {
    int result = 0, ret;
    ret = check_board(board_i, board_j, board_i+2, board_j+1);
    if (ret == 0 || ret == 2) result++;
    ret = check_board(board_i, board_j, board_i+2, board_j-1);
    if (ret == 0 || ret == 2) result++;
    ret = check_board(board_i, board_j, board_i-2, board_j+1);
    if (ret == 0 || ret == 2) result++;
    ret = check_board(board_i, board_j, board_i-2, board_j-1);
    if (ret == 0 || ret == 2) result++;
    ret = check_board(board_i, board_j, board_i+1, board_j+2);
    if (ret == 0 || ret == 2) result++;
    ret = check_board(board_i, board_j, board_i-1, board_j+2);
    if (ret == 0 || ret == 2) result++;
    ret = check_board(board_i, board_j, board_i+1, board_j-2);
    if (ret == 0 || ret == 2) result++;
    ret = check_board(board_i, board_j, board_i-1, board_j-2);
    if (ret == 0 || ret == 2) result++;

    return result;
}

int solve() { // i honestly prayed to Jesus for this function to be written by himself, however, without success
    int result = 0;
    for(int i = 0 ; i < 8; i++)
        for(int j = 0 ; j < 8; j++)
            switch(board[i][j]) { // everytime a switch statement is used, i shame myself for not knowing the syntax by heart
                case 'P': // pion
                    result += parse_pion(i,j);
                break;

                case 'W': // tower
                    result += parse_tower(i,j);
                break;

                case 'S': // mf horse person 😂😂😂
                    result += parse_horse_person(i,j);
                break;

                case 'G': // goniec (as you can see, i have given up on the english names)
                break;

                case 'H': // the perfect female protagonist

                break;

                case 'K': // king
                    result += parse_king(i, j);
                break;

                default:
                    break;  // empty space or enemie's checker
            }

    return result;
}

int main() {
    read_input();
    printf("%d", solve());
}