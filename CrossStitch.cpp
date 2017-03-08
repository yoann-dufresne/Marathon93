// C++11
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Tile {
public:
    int row;
    int col;

    Tile * up;
    Tile * down;
    Tile * left;
    Tile * right;

    Tile () {}
    Tile (int row, int col) {
        this->row = row;
        this->col = col;
        this->up = this->right = this->down = this->left = (Tile *)0;
    }

    bool operator==(const Tile & tile){
        return this->row == tile.row && this->col == tile.col;
    }

    bool operator!=(const Tile & tile){
        return !(*this == tile);
    }

    virtual vector<int> get_points () {
        return vector<int>();
    }

    virtual void set_identity_neighbors (vector<vector<bool> > & canva) {}

};

class TopLeftTile: public Tile {
public:
    TopLeftTile(int row, int col): Tile (row, col) {}
    vector<int> get_points ();
    void set_identity_neighbors (vector<vector<bool> > & canva);
};

class TopRightTile: public Tile {
public:
    TopRightTile(int row, int col): Tile (row, col) {}
    vector<int> get_points ();
    void set_identity_neighbors (vector<vector<bool> > & canva);
};

class BottomLeftTile: public Tile {
public:
    BottomLeftTile(int row, int col): Tile (row, col) {}
    vector<int> get_points ();
    void set_identity_neighbors (vector<vector<bool> > & canva);
};

class BottomRightTile: public Tile {
public:
    BottomRightTile(int row, int col): Tile (row, col) {}
    vector<int> get_points ();
    void set_identity_neighbors (vector<vector<bool> > & canva);
};



vector<int> TopLeftTile::get_points () {
    vector<int> points;
    // Insertions Top and left
    if (this->up) {
        vector<int> subpoints = this->up->get_points();
        points.insert(points.end(), subpoints.begin(), subpoints.end());
    }
    if (this->left) {
        vector<int> subpoints = this->left->get_points();
        points.insert(points.end(), subpoints.begin(), subpoints.end());
    }
    // First diagonal
    points.push_back (this->row); points.push_back (this->col);
    points.push_back (this->row+1); points.push_back (this->col+1);
    // Insertions Bottom and right
    if (this->down) {
        vector<int> subpoints = this->down->get_points();
        points.insert(points.end(), subpoints.begin(), subpoints.end());
    }
    if (this-> right) {
        vector<int> subpoints = this->right->get_points();
        points.insert(points.end(), subpoints.begin(), subpoints.end());
    }
    // Second diagonal
    points.push_back (this->row); points.push_back (this->col+1);
    points.push_back (this->row+1); points.push_back (this->col);
    return points;
}

void TopLeftTile::set_identity_neighbors (vector<vector<bool> > & canva) {
    int row = this->row;
    int col = this->col;
    canva[row][col] = false;

    int height = canva.size();
    int width = canva[0].size();

    // On the top
    if (row > 0 && canva[row-1][col]) {
        this->up = new BottomLeftTile(row-1, col);
        this->up->set_identity_neighbors(canva);
    }

    // On the left
    if (col > 0 && canva[row][col-1]) {
        this->left = new TopRightTile(row, col-1);
        this->left->set_identity_neighbors(canva);
    }

    // On the bottom
    if (row+1 < height && canva[row+1][col]) {
        this->down = new BottomRightTile(row+1, col);
        this->down->set_identity_neighbors(canva);
    }

    // On the right
    if (col+1 < width && canva[row][col+1]) {
        this->right = new TopLeftTile(row, col+1);
        this->right->set_identity_neighbors(canva);
    }
}

vector<int> TopRightTile::get_points () {
    vector<int> points;
    // Insertions top and right
    if (this->up) {
        vector<int> subpoints = this->up->get_points();
        points.insert(points.end(), subpoints.begin(), subpoints.end());
    }
    if (this->right) {
        vector<int> subpoints = this->right->get_points();
        points.insert(points.end(), subpoints.begin(), subpoints.end());
    }
    // First diagonal
    points.push_back (this->row); points.push_back (this->col+1);
    points.push_back (this->row+1); points.push_back (this->col);
    // Insertions bottom and left
    if (this->down) {
        vector<int> subpoints = this->down->get_points();
        points.insert(points.end(), subpoints.begin(), subpoints.end());
    }
    if (this->left) {
        vector<int> subpoints = this->left->get_points();
        points.insert(points.end(), subpoints.begin(), subpoints.end());
    }
    // Second diagonal
    points.push_back (this->row); points.push_back (this->col);
    points.push_back (this->row+1); points.push_back (this->col+1);
    return points;
}

void TopRightTile::set_identity_neighbors (vector<vector<bool> > & canva) {
    int row = this->row;
    int col = this->col;
    canva[row][col] = false;

    int height = canva.size();
    int width = canva[0].size();

    // On the top
    if (row > 0 && canva[row-1][col]) {
        this->up = new BottomRightTile(row-1, col);
        this->up->set_identity_neighbors(canva);
    }

    // On the left
    if (col > 0 && canva[row][col-1]) {
        this->left = new TopRightTile(row, col-1);
        this->left->set_identity_neighbors(canva);
    }

    // On the bottom
    if (row+1 < height && canva[row+1][col]) {
        this->down = new BottomLeftTile(row+1, col);
        this->down->set_identity_neighbors(canva);
    }

    // On the right
    if (col+1 < width && canva[row][col+1]) {
        this->right = new TopLeftTile(row, col+1);
        this->right->set_identity_neighbors(canva);
    }
}


vector<int> BottomLeftTile::get_points () {
    vector<int> points;
    // Insertions bottom and left
    if (this->down) {
        vector<int> subpoints = this->down->get_points();
        points.insert(points.end(), subpoints.begin(), subpoints.end());
    }
    if (this->left) {
        vector<int> subpoints = this->left->get_points();
        points.insert(points.end(), subpoints.begin(), subpoints.end());
    }
    // First diagonal
    points.push_back (this->row+1); points.push_back (this->col);
    points.push_back (this->row); points.push_back (this->col+1);
    // Insertions top and right
    if (this->up) {
        vector<int> subpoints = this->up->get_points();
        points.insert(points.end(), subpoints.begin(), subpoints.end());
    }
    if (this->right) {
        vector<int> subpoints = this->right->get_points();
        points.insert(points.end(), subpoints.begin(), subpoints.end());
    }
    // First diagonal
    points.push_back (this->row+1); points.push_back (this->col+1);
    points.push_back (this->row); points.push_back (this->col);
    return points;
}

void BottomLeftTile::set_identity_neighbors (vector<vector<bool> > & canva) {
    int row = this->row;
    int col = this->col;
    canva[row][col] = false;

    int height = canva.size();
    int width = canva[0].size();

    // On the top
    if (row > 0 && canva[row-1][col]) {
        this->up = new TopRightTile(row-1, col);
        this->up->set_identity_neighbors(canva);
    }

    // On the left
    if (col > 0 && canva[row][col-1]) {
        this->left = new BottomRightTile(row, col-1);
        this->left->set_identity_neighbors(canva);
    }

    // On the bottom
    if (row+1 < height && canva[row+1][col]) {
        this->down = new TopLeftTile(row+1, col);
        this->down->set_identity_neighbors(canva);
    }

    // On the right
    if (col+1 < width && canva[row][col+1]) {
        this->right = new BottomLeftTile(row, col+1);
        this->right->set_identity_neighbors(canva);
    }
}

vector<int> BottomRightTile::get_points () {
    vector<int> points;
    // Insertions bottom and right
    if (this->down) {
        vector<int> subpoints = this->down->get_points();
        points.insert(points.end(), subpoints.begin(), subpoints.end());
    }
    if (this->right) {
        vector<int> subpoints = this->right->get_points();
        points.insert(points.end(), subpoints.begin(), subpoints.end());
    }
    // First diagonal
    points.push_back (this->row+1); points.push_back (this->col+1);
    points.push_back (this->row); points.push_back (this->col);
    // Insertions top and left
    if (this->up) {
        vector<int> subpoints = this->up->get_points();
        points.insert(points.end(), subpoints.begin(), subpoints.end());
    }
    if (this->left) {
        vector<int> subpoints = this->left->get_points();
        points.insert(points.end(), subpoints.begin(), subpoints.end());
    }
    // Second diagonal
    points.push_back (this->row+1); points.push_back (this->col);
    points.push_back (this->row); points.push_back (this->col+1);
    return points;
}

void BottomRightTile::set_identity_neighbors (vector<vector<bool> > & canva) {
    int row = this->row;
    int col = this->col;
    canva[row][col] = false;

    int height = canva.size();
    int width = canva[0].size();

    // On the top
    if (row > 0 && canva[row-1][col]) {
        this->up = new TopLeftTile(row-1, col);
        this->up->set_identity_neighbors(canva);
    }

    // On the left
    if (col > 0 && canva[row][col-1]) {
        this->left = new BottomRightTile(row, col-1);
        this->left->set_identity_neighbors(canva);
    }

    // On the bottom
    if (row+1 < height && canva[row+1][col]) {
        this->down = new TopRightTile(row+1, col);
        this->down->set_identity_neighbors(canva);
    }

    // On the right
    if (col+1 < width && canva[row][col+1]) {
        this->right = new BottomLeftTile(row, col+1);
        this->right->set_identity_neighbors(canva);
    }
}





class Area {
public:
    vector<Tile> tiles;
    vector<Tile> exterior;

    Area () {}
};


class CrossStitch {
public:
    vector<vector<vector<bool> > > canvas;
    int S;

    CrossStitch () {
        canvas = vector<vector<vector<bool> > >(26, vector<vector<bool> > (100, vector<bool> (100, false)));
    }



    unordered_map<int, int> get_gradient (vector<vector<bool> > & canva, Tile & start) {
        unordered_map<int, int> previous;
        vector<Tile> toCompute;
        toCompute.push_back(start);
        previous[start.row*this->S + start.col] = -1;

        while (toCompute.size() > 0) {
            Tile t = toCompute[0];
            // cout << "Tile : " << t.row << " " << t.col << endl;
            
            // Haut
            if (t.row > 0 && canva[t.row-1][t.col] &&
                    previous.find((t.row-1)*this->S + t.col) == previous.end()) {
                toCompute.push_back(Tile(t.row-1, t.col));
                previous[(t.row-1)*this->S + t.col] = t.row*this->S + t.col;
                // cout << "add top " << ((t.row-1)*this->S + t.col) << " -> " << (t.row*this->S + t.col) << endl;
            }

            // Gauche
            if (t.col > 0 && canva[t.row][t.col-1] &&
                    previous.find(t.row*this->S + t.col-1) == previous.end()) {
                toCompute.push_back(Tile(t.row, t.col-1));
                previous[t.row*this->S + t.col-1] = t.row*this->S + t.col;
                // cout << "add left " << (t.row*this->S + t.col) << " -> " << (t.row*this->S + t.col-1) << endl;
            }

            // Droite
            if (t.col < this->S-1 && canva[t.row][t.col+1] &&
                    previous.find(t.row*this->S + t.col+1) == previous.end()) {
                toCompute.push_back(Tile(t.row, t.col+1));
                previous[t.row*this->S + t.col+1] = t.row*this->S + t.col;
                // cout << "add right " << (t.row*this->S + t.col) << " -> " << (t.row*this->S + t.col+1) << endl;
            }

            // Bas
            if (t.row < this->S-1 && canva[t.row+1][t.col] &&
                    previous.find((t.row+1)*this->S + t.col) == previous.end()) {
                toCompute.push_back(Tile(t.row+1, t.col));
                previous[(t.row+1)*this->S + t.col] = t.row*this->S + t.col;
                // cout << "add bottom " << ((t.row+1)*this->S + t.col) << " -> " << (t.row*this->S + t.col) << endl;
            }

            // Remove from vector
            toCompute.erase(toCompute.begin());
        }

        return previous;
    }

    /* Get a pixel path between start and end pixels following the gradient */
    vector<Tile> get_path (unordered_map<int, int> gradient, Tile & start, Tile & end) {
        Tile current = end;
        int currentValue = current.row * this->S + current.col;
        vector<Tile> path;
        path.push_back(current);

        while (current != start) {
            // cout << current.row << " " << current.col << endl;
            int previousValue = gradient[currentValue];
            int col = previousValue % this->S;
            int row = previousValue / this->S;
            
            current = Tile (row, col);
            path.push_back(current);

            currentValue = previousValue;
        }

        reverse(path.begin(), path.end());
        return path;
    }

    vector<Tile *> path_to_tiles(vector<Tile> path) {
        vector<Tile *> tiles (path.size());

        bool top = true;
        int idx = 0;
        for (Tile t : path) {
            Tile * pt;
            if (top)
                pt = new TopLeftTile(t.row, t.col);
            else
                pt = new BottomLeftTile(t.row, t.col);
            tiles[idx++] = pt;
            top = !top;
        }

        return tiles;
    }

    vector<int> tiles_to_points(vector<Tile *> & path) {
        vector<int> points;

        for (Tile * t : path) {
            vector<int> subpoints = t->get_points();
            points.insert(points.end(), subpoints.begin() , subpoints.end());
        }

        return points;
    }


    /* Get the best string path for a contiguous area */
    vector<int> computeArea (vector<vector<bool> > & canva, Tile & start, Tile & end) {
        // Descente de gradient
        unordered_map<int, int> gradient = this->get_gradient(canva, start);

        // Remontée de gradient
        vector<Tile> path = get_path (gradient, start, end);
        vector<Tile *> tiled = path_to_tiles (path);
        for (Tile * t : tiled)
            canva[t->row][t->col] = false;
        for (Tile * t : tiled)
            t->set_identity_neighbors(canva);

        return tiles_to_points(tiled);
    }


    /* Solve the problem for 1 color */
    vector<int> solve (int color) {
        vector<int> sol;
        if (color != 0)
            return sol;

        // TODO : Parcours en largeur pour trouver les zones
        Area test;
        test.tiles.push_back(Tile(2, 1));
        test.tiles.push_back(Tile(2, 2));
        test.tiles.push_back(Tile(2, 3));
        test.tiles.push_back(Tile(1, 2));
        test.tiles.push_back(Tile(1, 3));
        test.tiles.push_back(Tile(3, 2));
        test.tiles.push_back(Tile(3, 3));
        test.tiles.push_back(Tile(0, 2));
        test.tiles.push_back(Tile(0, 1));

        vector<Area> areas;
        areas.push_back(test);


        // TODO : Trouver les points et distances entre zones

        // TODO : Algo d'optimisation de distances inter zones

        cout << "--- Pavage ---" << endl;
        // Pavage dans chacune des zones
        for (Area & area : areas) {
            vector<int> path = this->computeArea (this->canvas[color], *(area.tiles.begin()), *(area.tiles.end()-1));
            sol.insert(sol.end(), path.begin(), path.end());
        }

        cout << "--- /Pavage ---" << endl;

        return sol;
    }




    vector<string> int_to_strings (vector<int> path) {
        vector<string> sol;
        for (int idx=0 ; idx<path.size() ; idx+=2)
            sol.push_back(to_string(path[idx]) + " " + to_string(path[idx+1]));
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
            vector<string> path = int_to_strings(solve (i));
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

