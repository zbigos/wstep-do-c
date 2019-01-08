#include <stdio.h>
char tabG[100][100]; //w,h
char tab[100][100]; //w,h

int glob_path, glob_city, glob_elect, glob_mine;
int glob_city_yeet, glob_elect_yeet, glob_mine_yeet;
int yeet_tgt[100][2];
int yeet_pt = 0;

int min(int a, int b) {
    return a>b?b:a;
}

void dfs(int j, int i, int path, int w, int h, int yeet) {
    if(yeet == 1) {
        if(glob_city_yeet > 0 && tab[j][i] == 'O') {
            tabG[j][i] = '.';
            glob_city_yeet --;
            yeet_tgt[yeet_pt][0] = j;
            yeet_tgt[yeet_pt][1] = i;
            yeet_pt++;
        }
        if(glob_elect_yeet > 0 && tab[j][i] == 'E') {
            tabG[j][i] = '.';
            glob_elect_yeet --;
            yeet_tgt[yeet_pt][0] = j;
            yeet_tgt[yeet_pt][1] = i;
            yeet_pt++;
        }
        if(glob_mine_yeet > 0 && tab[j][i] == 'K') {
            tabG[j][i] = '.';
            glob_mine_yeet --;
            yeet_tgt[yeet_pt][0] = j;
            yeet_tgt[yeet_pt][1] = i;
            yeet_pt++;
        }
    } else {
        if(tab[j][i] == '#') glob_path++;
        if(tab[j][i] == 'O') glob_city++;
        if(tab[j][i] == 'K') glob_elect++;
        if(tab[j][i] == 'E') glob_mine++;
    }
    
    tab[j][i] = '.';

    if(path == 2) {
        if(j+1 <= h)
            if(tab[j+1][i] == '#') dfs(j+1, i, 2, w, h, yeet);
        if(j-1 >= 0)
            if(tab[j-1][i] == '#') dfs(j-1, i, 2, w, h, yeet);
        if(i+1 <= w)
            if(tab[j][i+1] == '#') dfs(j, i+1, 2, w, h, yeet);
        if(i-1 >= 0)
            if(tab[j][i-1] == '#') dfs(j, i-1, 2, w, h, yeet);
        if(j+1 <= h)
            if(tab[j+1][i] != '#') dfs(j+1, i, 1, w, h, yeet);
        if(j-1 >= 0)
            if(tab[j-1][i] != '#') dfs(j-1, i, 1, w, h, yeet);
        if(i+1 <= w)
            if(tab[j][i+1] != '#') dfs(j, i+1, 1, w, h, yeet);
        if(i-1 >= 0)
            if(tab[j][i-1] != '#') dfs(j, i-1, 1, w, h, yeet);

   }

    if(path == 1) {
        if(j+1 <= h)
            if(tab[j+1][i] != '#') dfs(j+1, i, 0, w, h, yeet);
        if(j-1 >= 0)
            if(tab[j-1][i] != '#') dfs(j-1, i, 0, w, h, yeet);
        if(i+1 <= w)
            if(tab[j][i+1] != '#') dfs(j, i+1, 0, w, h, yeet);
        if(i-1 >= 0)
            if(tab[j][i-1] != '#') dfs(j, i-1, 0, w, h, yeet);
    }

}

int main() {
    int w, h;
    scanf("%d%d", &h, &w);
    

    for(int i = 0 ; i < w; i++) {
        char trash;
        scanf("%c", &trash);
        for(int j = 0 ; j < h; j++) {
            char dupa = 0;
            scanf("%c", &dupa);
            tabG[j][i] = '.';       

            if(dupa == 'O')
                tabG[j][i] = 'O';
            if(dupa == '#')
                tabG[j][i] = '#';
            if(dupa == 'K')
                tabG[j][i] = 'K';
            if(dupa == 'E')
                tabG[j][i] = 'E';
        }
    }
    
    for(int j = 0 ; j < h; j++) {
        for(int i = 0 ; i < w; i++) {
            printf("%c", tabG[j][i]);
        }
    printf("\n");
    }

    for(int j = 0 ; j < h; j++) {
        for(int i = 0 ; i < w; i++) {
            if(tab[j][i] != '.') {
                printf("path found!\n");

                //make copy of a board;
                for(int ii = 0 ; ii < w; ii++)
                for(int jj = 0 ; jj < h; jj++)            
                    tab[jj][ii] = tabG[jj][ii];

                if(tab[j][i] == '#')
                    dfs(j, i, 2, w, h, 0);
                else if(tab[j][i] != '.')
                    dfs(j, i, 1, w, h, 0);

                int tris = min((glob_city, glob_elect), glob_mine);
                glob_city_yeet = tris;
                glob_elect_yeet = tris;
                glob_mine_yeet = tris;
                glob_city -= glob_city_yeet;
                glob_elect -= glob_elect_yeet;
                glob_mine -= glob_mine_yeet;
                printf("TRIS %d\n", tris);
                if(glob_city > 0) {
                    if(glob_elect > 0) {
                        int diff = min(glob_city, glob_elect);
                        glob_city -= diff;
                        glob_elect -= diff;
                        glob_city_yeet += diff;
                        glob_elect_yeet += diff;
                    }
                }

                if(glob_city > 0) {
                    if(glob_mine > 0) {
                        int diff = min(glob_city, glob_mine);
                        glob_city -= diff;
                        glob_mine -= diff;
                        glob_city_yeet += diff;
                        glob_mine_yeet += diff;
                    }
                }
            
                for(int ii = 0 ; ii < w; ii++)
                for(int jj = 0 ; jj < h; jj++)            
                    tab[jj][ii] = tabG[jj][ii]; 

                if(tabG[j][i] == '#')
                    dfs(j, i, 2, w, h, 1);
                else if(tabG[j][i] != '.')
                    dfs(j, i, 1, w, h, 1);
                
                for(int W = yeet_pt; W > 0; W--) {
                    tabG[yeet_tgt[W][0]][yeet_tgt[W][1]] = '.';
                }

                yeet_pt = 0;

                glob_city = 0;
                glob_elect = 0;
                glob_mine = 0;
                glob_path = 0;
            }
        }
    }

        for(int j = 0 ; j < h; j++) {
        for(int i = 0 ; i < w; i++) {
            printf("%c", tabG[j][i]);
        }
    printf("\n");
    }
}