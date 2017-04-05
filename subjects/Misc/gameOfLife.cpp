#include <stdio.h>
#include <deque>
#include <utility>
#include <iostream>
#include <string>
// To refresh
#include <ncurses.h>
#include <unistd.h> 

using namespace std;

class Grid {
  /*
   * Grid of R rows and C columns
   * m[x] holds previous/actual state of grid
   */
  int R, C, st;
  static int mv[8][2];
  deque < deque<int> > m[2];

public:
  /*
   * Default constructor
   * fill each cell with zeros
   * actual state is zero
   */
  Grid(int R, int C):
     R(R), C(C), st(0)
  {
    make_grid();
  }

  /*
   * Constructor with list of location of 1's
   */
  Grid(int R, int C, deque< pair<int,int> > &lst):
     R(R), C(C), st(0)
  {
    make_grid();
    set_ones(lst);
  }

  /*
   * Update to the new state
   */
  void update() {
    int pr = st;
    int cnt, nr, nc;
    st = 1 - pr;
    for(int r=1; r<=R; ++r)
    {
      for(int c=1; c<=C; ++c)
      {
        cnt = 0;
        for(int k=0; k<8; ++k) {
          nr = r + mv[k][0];
          nc = c + mv[k][1];
          cnt += m[pr][nr][nc];
        }
        if (m[pr][r][c]) {
          m[st][r][c] = (cnt==3||cnt==2) ? 1 : 0;
        } else {
          m[st][r][c] = (cnt == 3) ? 1 : 0;
        }
      }
    }
  }

  /*
   * Print the grid
   */
  string print() {
    string ret = "";
    for(int r=1; r<=R; ++r)
    {
      for(int c=1; c<=C; ++c)
      {
        ret += m[st][r][c] ? 'o' : ' '; //"1" : "0";
      }
      ret += "\n";
    }
    return ret;
  }

private:
  /*
   * Allocate memory for the grid
   */
  void make_grid()
  {
    m[0] = deque< deque <int> > (R+2);
    m[1] = deque< deque <int> > (R+2);
    for(int i=0; i<=R+1; ++i)
    {
      m[0][i] = deque <int> (C+2, 0); 
      m[1][i] = deque <int> (C+2, 0);
    }
  }

  /*
   * Set the xi,yi from list to 1
   */
  void set_ones(deque< pair<int,int> > &lst)
  {
    for(int i=0; i<lst.size(); ++i)
    {
      m[st][lst[i].first][lst[i].second] = 1;
    }
  }
};

int Grid::mv[8][2] = { {-1,-1}, {-1,0},
               {-1,1}, {0, -1}, {0, 1},
               {1, -1}, {1, 0}, {1,1}};

/*
 * Main functions
 */
int main() {
  int n, r;
  int t;
  int a, b;
  deque < pair<int, int> > dq;

  cin >> n >> r;

  cin >> t;
  for(int i=0; i<t; ++i) {
    cin >> a >> b;
    dq.push_back(make_pair(a,b));
  }

  Grid gr(n,r, dq);

  /* Init ncurses mode */
  initscr ();
  /* Hide cursor */
  curs_set (0);
  for(int it=0; it < 10000; ++it) {
    string str = gr.print();
    gr.update();
    // Refresh
    /* Print at row 0, col 0 */
    mvprintw (0, 0, "%s", str.c_str());
    refresh ();
    usleep (125000);
  }
  /* End ncurses mode */
  endwin();

  return 0;
}