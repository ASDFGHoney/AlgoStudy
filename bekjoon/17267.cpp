#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <deque>

using namespace std;

int score = 0;

class spot {
public:
    int x;
    int y;
    bool visited;
    int l;
    int r;

    spot(int x, int y, bool visited, int l, int r) {
        this->x = x;
        this->y = y;
        this->visited = visited;
        this->l = l;
        this->r = r;
    }
};

vector<vector<spot *> > matrix;

void BFS(spot *curV, int N, int M) {
    deque<spot *> Q;
    Q.push_back(curV);

    while (!Q.empty()) {
        curV = Q.front();
        score++;
        Q.pop_front();

        if (curV->r > 0 && curV->y < M) {
            spot *next = matrix[curV->x][curV->y + 1];

            if (!next->visited) {
                next->l = curV->l;
                next->r = curV->r - 1;
                Q.push_back(next);
                next->visited = true;
            }
        }
        if (curV->l > 0 && curV->y > 0) {
            spot *next = matrix[curV->x][curV->y - 1];

            if (!next->visited) {
                next->l = curV->l - 1;
                next->r = curV->r;
                Q.push_back(next);
                next->visited = true;
            }
        }
        if(curV->x < N) {
            spot *next = matrix[curV->x + 1][curV->y];
            if (!next->visited) {
                next->l = curV->l;
                next->r = curV->r;
                Q.push_front(next);
                next->visited = true;
            }
        }
        if(curV->x > 0) {
            spot *next1 = matrix[curV->x - 1][curV->y];
            if (!next1->visited) {
                next1->l = curV->l;
                next1->r = curV->r;
                Q.push_front(next1);
                next1->visited = true;
            }
        }
    }
}

int main() {
    int N, M, L, R;
    cin >> N >> M >> L >> R;
    spot *start;
    for (int i = 0; i < N; i++) {
        vector<spot*> a;
        matrix.push_back(a);
        for (int j = 0; j < M; j++) {
            char da;
            cin >> da;
            if (da == '0') {
                spot *sp = new spot(i, j, false, L, R);
                matrix[i].push_back(sp);
            } else {
                spot *sp = new spot(i, j, true, L, R);
                if (da == '2') {
                    start = sp;
                }
                matrix[i].push_back(sp);
            }
        }
    }
    BFS(start, N-1, M-1);

    cout << score;

    return 0;
}
