#include <stdio.h>

#define bool int
#define true 1
#define false 0

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


// blatantly moving away the code i don't want to write
/*
 * 0 for a valid state
 * 1 for invalid
*/

char forbidden[8][8];
void setbad(int i, int j) {
    if(i >= 0 && i <= 7 && j >= 0 && j<= 7)
        forbidden[i][j] = 'X';
}

int check_checker(int board_i, int board_j, int board_res_i, int board_res_j, int debug) {
    char hold_from = board[board_i][board_j];
    char hold_to = board[board_res_i][board_res_j];

    board[board_i][board_j] = '.';
    board[board_res_i][board_res_j] = hold_from;

    for(int i = 0 ; i < 8; i++)
        for(int j = 0 ; j < 8; j++)
            forbidden[i][j] = 'O';

    for(int i = 0 ; i < 8; i++)
        for(int j = 0 ; j < 8; j++)
            if(board[i][j] == 'p') {
                setbad(i+1, j+1);
                setbad(i+1, j-1);
                setbad(i,j);
            }
    
    for(int i = 0 ; i < 8; i++)
        for(int j = 0 ; j < 8; j++)
            if(board[i][j] == 't') {
                setbad(i,j);
                for(int k = 1 ; k < 20; k++)
                    if(board[i+k][j] == '.' || board[i+k][j] == 'K') setbad(i+k, j); else break;
                 for(int k = 1 ; k < 20; k++)
                    if(board[i-k][j] == '.' || board[i-k][j] == 'K') setbad(i-k, j); else break;
                for(int k = 1 ; k < 20; k++)
                    if(board[i][j+k] == '.' || board[i][j+k] == 'K') setbad(i, j+k); else break;
                for(int k = 1 ; k < 20; k++)
                    if(board[i][j-k] == '.' || board[i][j-k] == 'K') setbad(i, j-k); else break;
            }
    

    if (debug)
        for (int i = 0 ; i < 8; i++) {
            for (int j = 0 ; j < 8; j++)
                printf("%c", forbidden[i][j]);
            printf("\n");
        }
    /*code to check if move is valid here*/

    board[board_i][board_j] = hold_from;
    board[board_res_i][board_res_j] = hold_to;
}

/*
 * this funcion, will (if I ever get around to implementing that)
 * return 0 if the move is valid
 * return 1 if the move is invalid
 * return 2 if the move is vaild, but the next move in that direction will not be
 * (a checker has been removed)
*/
int check_board(int board_i, int board_j, int board_res_i, int board_res_j) {
    if (board_res_i < 0 || board_res_j < 0 || board_res_i > 7 || board_res_j > 7)
        return 1; // out of bounds move

    char target = board[board_res_i][board_res_j];

    if (target == '.')
        return check_checker(board_i, board_j, board_res_i, board_res_j, false);

    if (target == 'p' || target == 'w' || target == 's' || \
        target == 'g' || target == 'h')
        if(check_checker(board_i, board_j, board_res_i, board_res_j, false) == 0)
            return 2;
        else
            return 1;

    return 1;
        // for when the player is trying to intersect his own checker
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

int parse_goniec(int board_i, int board_j) {
    int result = 0, ret;
    bool try1 = true, try2 = true, try3 = true, try4 = true;
    for(int i = 1; i < 15; i++) {
        if (try1) {
            ret = check_board(board_i, board_j, board_i+i, board_j+i);
            if (ret == 0 || ret == 2)
                result ++;
            if (ret == 1 || ret == 2)
                try1 = false;
        }
        if (try2) {
            ret = check_board(board_i, board_j, board_i-i, board_j+i);
            if (ret == 0 || ret == 2)
                result ++;
            if (ret == 1 || ret == 2)
                try2 = false;
        }
        if (try3) {
            ret = check_board(board_i, board_j, board_i+i, board_j-i);
            if (ret == 0 || ret == 2)
                result ++;
            if (ret == 1 || ret == 2)
                try3 = false;
        }
        if (try4) {
            ret = check_board(board_i, board_j, board_i-i, board_j-i);
            if (ret == 0 || ret == 2)
                result ++;
            if (ret == 1 || ret == 2)
                try4 = false;
        }
    }

    return result;
}

int parse_perfect_female_protagonist(int board_i, int board_j) {
    int result = 0, ret;
    bool try1 = true, try2 = true, try3 = true, try4 = true;
    bool try5 = true, try6 = true, try7 = true, try8 = true;
    
    for(int i = 1; i < 15; i++) {
        if (try1) {
            ret = check_board(board_i, board_j, board_i+i, board_j+i);
            if (ret == 0 || ret == 2)
                result ++;
            if (ret == 1 || ret == 2)
                try1 = false;
        }
        if (try2) {
            ret = check_board(board_i, board_j, board_i-i, board_j+i);
            if (ret == 0 || ret == 2)
                result ++;
            if (ret == 1 || ret == 2)
                try2 = false;
        }
        if (try3) {
            ret = check_board(board_i, board_j, board_i+i, board_j-i);
            if (ret == 0 || ret == 2)
                result ++;
            if (ret == 1 || ret == 2)
                try3 = false;
        }
        if (try4) {
            ret = check_board(board_i, board_j, board_i-i, board_j-i);
            if (ret == 0 || ret == 2)
                result ++;
            if (ret == 1 || ret == 2)
                try4 = false;
        }

        if (try5) {
            ret = check_board(board_i, board_j, board_i, board_j+i);
            if (ret == 0 || ret == 2)
                result ++;
            if (ret == 1 || ret == 2)
                try5 = false;
        }
        if (try6) {
            ret = check_board(board_i, board_j, board_i, board_j-i);
            if (ret == 0 || ret == 2)
                result ++;
            if (ret == 1 || ret == 2)
                try6 = false;
        }
        if (try7) {
            ret = check_board(board_i, board_j, board_i+i, board_j);
            if (ret == 0 || ret == 2)
                result ++;
            if (ret == 1 || ret == 2)
                try7 = false;
        }
        if (try8) {
            ret = check_board(board_i, board_j, board_i-i, board_j);
            if (ret == 0 || ret == 2)
                result ++;
            if (ret == 1 || ret == 2)
                try8 = false;
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
                    result += parse_goniec(i,j);
                break;

                case 'H': // the perfect female protagonist
                    result += parse_perfect_female_protagonist(i,j);
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
    check_checker(1,1,1,1, true);
    printf("%d", solve());
}