// C++11
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int nextIdx = 0;

class Tile {
public:
    int row;
    int col;
    int idx;

    Tile * up;
    Tile * down;
    Tile * left;
    Tile * right;

    Tile () {}
    Tile (int row, int col) {
        this->row = row;
        this->col = col;
        this->up = this->right = this->down = this->left = (Tile *)0;
        this->idx = nextIdx++;
    }

    double get_distance (const Tile & t) {
        return sqrt((double)((this->row-t.row)*(this->row-t.row) + (this->col-t.col)*(this->col-t.col)));
    }

    Tile & operator=(const Tile & t) {
        if (this != &t) {
            this->row = t.row;
            this->col = t.col;
            this->idx = t.idx;
        }

        return *this;
    }

    bool operator==(const Tile & tile) const {
        return this->row == tile.row && this->col == tile.col;
    }

    bool operator!=(const Tile & tile) const {
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

int height = 0;
int width = 0;

namespace std {
    template <>
    struct hash<Tile> {
        size_t operator()( const Tile & t ) const {
            return t.row * height + t.col;
        }
    };
}





class Area {
public:
    vector<Tile> tiles;
    vector<Tile> borders;
    int id;

    Area() {
        this->id = -1;
    };
    Area (int id) {
        this->id = id;
    }

    Area & operator=(const Area & a) {
        if (this != &a) {
            for (Tile t : a.tiles)
                this->tiles.push_back(t);
            this->borders = a.borders;
            this->id = a.id;
        }

        return *this;
    }

    bool operator == (const Area & a) const {
        return this->id == a.id;
    }
};

class Distance {
public:
    Tile t1;
    Tile t2;
    vector<Area> areas;
    double dist;

    Distance (){
        double dist = 10000000;
    }

    Distance (Tile t1, Tile t2) {
        this->t1 = t1;
        this->t2 = t2;

        this->dist = t1.get_distance (t2);
    }

    bool operator < (const Distance & d) const {
        return this->dist < d.dist;
    }
};


class CrossStitch {
public:
    vector<vector<vector<bool> > > canvas;
    int S;

    CrossStitch () {
        canvas = vector<vector<vector<bool> > >(26, vector<vector<bool> > (100, vector<bool> (100, false)));
    }


    vector<Area> computeAreas (vector<vector<bool> > canva) {
        vector<Area> areas;
        vector<vector<bool> > computed (canva.size(), vector<bool>(canva[0].size(), false));

        int height = this->S;
        int width = this->S;
        int nextId = 0;

        // All over the canva
        for (int row=0 ; row<height ; row++) {
            for (int col=0 ; col<width ; col++) {
                if (canva[row][col]) {
                    if (!computed[row][col]) {
                        Area area (nextId++);

                        // BFS
                        unordered_set<Tile> to_compute;
                        to_compute.insert(Tile(row, col));
                        computed[row][col] = true;

                        while (to_compute.size() > 0) {
                            Tile t = *(to_compute.begin());
                            to_compute.erase(to_compute.begin());
                            int nb_neighbors = 0;

                            // Up
                            if (t.row > 0 && canva[t.row-1][t.col]) {
                                nb_neighbors++;
                                if (!computed[t.row-1][t.col]) {
                                    to_compute.insert(Tile(t.row-1,t.col));
                                    computed[t.row-1][t.col] = true;
                                }
                            }
                            // Down
                            if (t.row+1 < height && canva[t.row+1][t.col]) {
                                nb_neighbors++;
                                if (!computed[t.row+1][t.col]) {
                                    to_compute.insert(Tile(t.row+1,t.col));
                                    computed[t.row+1][t.col] = true;
                                }
                            }
                            // Left
                            if (t.col > 0 && canva[t.row][t.col-1]) {
                                nb_neighbors++;
                                if (!computed[t.row][t.col-1]) {
                                    to_compute.insert(Tile(t.row,t.col-1));
                                    computed[t.row][t.col-1] = true;
                                }
                            }
                            // Right
                            if (t.col+1 < width && canva[t.row][t.col+1]) {
                                nb_neighbors++;
                                if (!computed[t.row][t.col+1]) {
                                    to_compute.insert(Tile(t.row,t.col+1));
                                    computed[t.row][t.col+1] = true;
                                }
                            }

                            area.tiles.push_back(t);
                            if (nb_neighbors < 4)
                                area.borders.push_back(t);
                        }

                        areas.push_back(area);
                    }
                } else {
                    computed[row][col] = true;
                }
            }
        }

        return areas;
    }

    vector<vector<Distance> > get_distances (vector<Area> areas) {
        vector<vector<Distance> > distances (areas.size(), vector<Distance> (areas.size()));

        for (int a1Idx=0 ; a1Idx<areas.size() ; a1Idx++) {
            Area & a1 = areas[a1Idx];
            for (int a2Idx=a1Idx+1 ; a2Idx<areas.size() ; a2Idx++) {
                Area & a2 = areas[a2Idx];

                Distance min_dist;
                int val_min = 1000000;
                for (Tile & t1 : a1.borders) {
                    for (Tile & t2 : a2.borders) {
                        if (t1.get_distance(t2) < val_min) {
                            min_dist = Distance(t1, t2);
                            val_min = min_dist.dist;
                        }
                    }
                }

                distances[a1Idx][a2Idx] = min_dist;
                distances[a2Idx][a1Idx] = Distance(min_dist.t2, min_dist.t1);
            }
        }

        return distances;
    }


    // Area _hamilton_min (vector<Area> areas, vector<vector<Distance> > & distances,
    //                     vector<Area> & nexts, vector<Area> & prevs, int areaIdx) {
    //     int currIdx = areaIdx;
    //     Area current = areas[currIdx];
    //     double minDist = 1000000;
    //     Area minArea;

    //     // No need to compute already used areas
    //     if (nexts[current.id].id != current.id)
    //         return Area();

    //     // Look for areas in the previous parts of the chain
    //     vector<bool> samePart (areas.size(), false);
    //     Area tmp = current;
    //     while (prevs[tmp.id].id != tmp.id) {
    //         tmp = prevs[tmp.id];
    //         samePart[tmp.id] = true;
    //     }

    //     // Search for the min dist
    //     for (int nextIdx=0 ; nextIdx<areas.size() ; nextIdx++) {
    //         Area next = areas[nextIdx];
    //         // If it's the same: continue
    //         if (current.id == next.id) {
    //             continue;
    //         }

    //         // To avoid cycles
    //         if (samePart[next.id]) {
    //             continue;
    //         }

    //         // Already in the chain
    //         if (prevs[next.id].id != next.id && nexts[next.id].id != next.id) {
    //             continue;
    //         }

    //         // Distance comparison
    //         Distance d = distances[current.id][next.id];
    //         if (d.dist < minDist) {
    //             minDist = d.dist;
    //             minArea = next;
    //         }
    //     }

    //     return minArea;
    // }

    // vector<Area> _hamilton_mins (vector<Area> areas, vector<vector<Distance> > & distances,
    //                             vector<Area> & nexts, vector<Area> & prevs) {
    //     vector<Area> mins (areas.size());

    //     for (int currIdx=0 ; currIdx<areas.size() ; currIdx++) {
    //         mins[currIdx] = _hamilton_min (areas, distances, nexts, prevs, currIdx);
    //     }

    //     return mins;
    // }

    // vector<Area> _update_mins (vector<Area> areas, vector<vector<Distance> > & distances,
    //                             vector<Area> & nexts, vector<Area> & prevs, vector<Area> mins, int addedIdx) {
    //     for (int aIdx=0 ; aIdx<mins.size() ; aIdx++) {
    //         if (mins[aIdx].id == addedIdx)
    //             mins[aIdx] = _hamilton_min(areas, distances, nexts, prevs, aIdx);
    //     }

    //     return mins;
    // }

    // vector<Area> hamiltonian_path (vector<Area> & areas, vector<vector<Distance> > & distances) {
    //     // Only one area
    //     if (areas.size() < 2)
    //         return areas;

    //     // Normal case
    //     vector<Area> nexts (areas.size());
    //     vector<Area> prevs (areas.size());
    //     for (Area a : areas) {
    //         nexts[a.id] = a;
    //         prevs[a.id] = a;
    //     }

    //     int modified = -1;
    //     vector<Area> mins;

    //     for (int n=0 ; n<areas.size()-1 ; n++) {
    //         cout << n << "/" << areas.size() << endl;
    //         if (modified == -1)
    //             mins = _hamilton_mins(areas, distances, nexts, prevs);
    //         else
    //             mins = _update_mins(areas, distances, nexts, prevs, mins, modified);

    //         Area maxArea;
    //         double maxDist = 0;
    //         for (int aIdx=0 ; aIdx<areas.size() ; aIdx++) {
    //             // No need to find the next after a used one.
    //             if (nexts[aIdx].id != aIdx || mins[aIdx].id == -1)
    //                 continue;

    //             // cout << aIdx << "->" << mins[aIdx].id << " : " << distances[aIdx][mins[aIdx].id].dist << endl;

    //             // Select the max of the mins
    //             Distance & d = distances[aIdx][mins[aIdx].id];
    //             if (d.dist > maxDist) {
    //                 maxDist = d.dist;
    //                 maxArea = areas[aIdx];
    //             }
    //         }

    //         // Add the element in the path in the correct direction
    //         Area current = maxArea;
    //         Area next = mins[current.id];
    //         modified = current.id;

    //         // Revert the sub-path
    //         if (prevs[next.id].id != next.id) {
    //             modified = -1;
    //             Area before = prevs[next.id];
    //             Area head = next;
    //             Area save = head;

    //             while (before.id != head.id) {
    //                 prevs[head.id] = nexts[head.id];
    //                 nexts[head.id] = before;

    //                 save = head;
    //                 head = before;
    //                 before = prevs[head.id];
    //             }

    //             nexts[head.id] = head;
    //             prevs[head.id] = save;

    //             // cout << "Reverted from " << next.id << endl;
    //         }

    //         // Add the element
    //         nexts[current.id] = next;
    //         prevs[next.id] = current;

    //         // cout << current.id << "->" << next.id << " added" << endl << endl;
    //     }

    //     // -- Construction of the path ---

    //     vector<Area> path;
    //     // First area in the path
    //     Area current;
    //     for (Area a : areas) {
    //         if (prevs[a.id].id == a.id) {
    //             current = a;
    //             break;
    //         }
    //     }
    //     path.push_back(current);

    //     while (nexts[current.id].id != current.id) {
    //         current = nexts[current.id];
    //         path.push_back(current);
    //     }

    //     return path;
    // }


    vector<Area> hamiltonian_path (vector<Area> areas, vector<vector<Distance> > distances) {
        vector<Area> path;

        // Index the areas
        unordered_map<Tile, Area> area_index;
        for (Area a : areas)
            for (Tile t : a.borders)
                area_index[t] = a;

        // Shuffle and sort the distances
        vector<bool> used (areas.size(), false);
        Area & current = *(areas.begin());
        path.push_back(current);
        used[current.id] = true;


        while (path.size() < areas.size()) {
            vector<Distance> current_distances = distances[current.id];
            current_distances.erase(current_distances.begin() + current.id);

            random_shuffle(current_distances.begin(), current_distances.end());
            sort(current_distances.begin(), current_distances.end());

            
            // Select the smallest dist
            for (Distance & d : current_distances) {
                Area a = area_index[d.t2];

                if (a.id != -1 && !used[a.id]) {
                    current = a;
                    break;
                }
            }

            used[current.id] = true;
            path.push_back(current);
        }

        return path;
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
    vector<int> computeAreaWire (vector<vector<bool> > & canva, Tile & start, Tile & end) {
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

        // BFS to find contiguous areas
        vector<Area> areas = computeAreas(canvas[color]);

        // Compute basic distances
        vector<vector<Distance> > distances = get_distances(areas);

        // Hamilton path between conexa areas
        vector<Area> path = hamiltonian_path (areas, distances);
        cout << path.size() << endl;

        Tile previous = *(path[0].tiles.begin());
        for (int idx=0 ; idx<path.size()-1 ; idx++) {
            Area first = path[idx];
            Area second = path[idx+1];
            Distance link = distances[first.id][second.id];

            vector<int> wirePath = this->computeAreaWire (this->canvas[color], previous, link.t1);
            sol.insert(sol.end(), wirePath.begin(), wirePath.end());
            previous = link.t2;
        }

        vector<int> wirePath = this->computeAreaWire (this->canvas[color], previous, *(path[path.size()-1].borders.begin()));
        sol.insert(sol.end(), wirePath.begin(), wirePath.end());

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
        height = this->S;
        width = this->S;
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

