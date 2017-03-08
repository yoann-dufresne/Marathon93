#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;


class CrossStitch {
public:
    vector<vector<vector<bool> > > canvas;
    int S;

    CrossStitch () {
        canvas = vector<vector<vector<bool> > >(26, vector<vector<bool> > (100, vector<bool> (100, false)));
    }

    /* To find connex components */
    vector<vector<int> > dijkstra (int color) {
        int s = this->S;
        vector<vector<bool> > & canva = this->canvas[color];

        vector<vector<int> > components = vector<vector<int> > (s, vector<int> (s, 0));

        // Init
        unordered_set<int> tiles;
        for (int r=0 ; r<s; r++) {
            for (int c=0 ; c<s ; c++) {
                if (canva[r][c]) {
                    tiles.insert(r*s + c);
                } else {
                    components[r][c] = -1;
                }
            }
        }

        // Dijkstra
        for (int r=0 ; r<s; r++) {
            for (int c=0 ; c<s ; c++) {
                if (canva[r][c] && components[r][c] == 0) {
                    // Dijkstra
                    vector<int> stack;

                    // TODO
                }
            }
        }

        // TODO
        return vector<vector<int> > ();
    }

    /* Solve the problem for 1 color */
    vector<string> solve (int color) {
        //vector<vector<int> > components = dijkstra(color);
        vector<string> sol;

        // Glouton aller/retour
        for (int r=0 ; r<this->S ; r++) {
            if (r%2 == 0) {
                for (int c=0 ; c<this->S ; c++) {
                    if (this->canvas[color][r][c]) {
                        sol.push_back(to_string(r) + " " + to_string(c));
                        sol.push_back(to_string(r+1) + " " + to_string(c+1));
                        sol.push_back(to_string(r+1) + " " + to_string(c));
                        sol.push_back(to_string(r) + " " + to_string(c+1));
                    }
                }
            } else {
                for (int c=this->S-1 ; c>=0 ; c--) {
                    if (this->canvas[color][r][c]) {
                        sol.push_back(to_string(r) + " " + to_string(c+1));
                        sol.push_back(to_string(r+1) + " " + to_string(c));
                        sol.push_back(to_string(r+1) + " " + to_string(c+1));
                        sol.push_back(to_string(r) + " " + to_string(c));
                    }
                }
            }
        }

        return sol;
    }


    vector<string> embroider(vector<string> pattern) {
        this->S = pattern.size();
        int colMax=2;

        for (int r = 0; r < S; ++r)
            for (int c = 0; c < S; ++c) {
                char col = pattern[r][c];
                if (col != '.') {
                    canvas[col-'a'][r][c] = true;
                    colMax = max(colMax, (col-'a')+1);
                }
            }



        vector<string> ret;
        for (int i=0 ; i<colMax ; i++) {
            ret.push_back(string(1, (char)('a'+i)));
            vector<string> path = solve (i);
            ret.insert(ret.end(), path.begin(), path.end());
        }

        return ret;
    }
};

// -------8<------- end of solution submitted to the website -------8<-------

template<class T> void getVector(vector<T>& v) {
    for (int i = 0; i < v.size(); ++i)
        cin >> v[i];
}

int main() {
    int S;
    cin >> S;
    vector<string> pattern(S);
    getVector(pattern);
    
    CrossStitch cs;
    vector<string> ret = cs.embroider(pattern);
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i)
        cout << ret[i] << endl;
    cout.flush();
}