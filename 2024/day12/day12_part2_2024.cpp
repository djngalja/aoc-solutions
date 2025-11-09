#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Plot { char plant; bool visited; };
struct XY { int x; int y; };

bool y_out_of_bounds(int, const std::vector<std::vector<Plot>>&);
bool x_out_of_bounds(int, const std::vector<std::vector<Plot>>&);
bool find_in_corner(const XY&, const XY&, const std::vector<std::vector<Plot>>&);
bool find_out_corner(const XY&, const XY&, const std::vector<std::vector<Plot>>&);
int calc_price(const std::vector<XY>&, const std::vector<std::vector<Plot>>&);
bool the_same_region(const std::vector<std::vector<Plot>>&, const XY&, const XY&);
void find_region(std::vector<std::vector<Plot>>&, const XY&, std::vector<XY>&);
std::vector<std::vector<XY>> find_regions(std::vector<std::vector<Plot>>&);
bool read_input(const std::string&, std::vector<std::vector<Plot>>&);
void day12_part2();


int main() {
    day12_part2();
    return 0;
}


void day12_part2() {
    std::vector<std::vector<Plot>> garden_map;
    if (read_input("input.txt", garden_map)) {
        const std::vector<std::vector<XY>> regions = find_regions(garden_map);
        int ttl_price {};
        for (const auto& region : regions) {
            ttl_price += calc_price(region, garden_map);
        }
        std::cout << "The new total price of fencing all regions: " << ttl_price << '\n';
    }
}

bool read_input(const std::string& f_name, std::vector<std::vector<Plot>>& garden_map) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found\n";
        return false;
    }
    std::string temp_str;
    while(getline(file, temp_str)) {
        std::vector<Plot> temp_vec;
        for (char c : temp_str) {
            temp_vec.push_back( {c , 0} );
        }
        garden_map.push_back(temp_vec);
    }
    return true;
}

std::vector<std::vector<XY>> find_regions(std::vector<std::vector<Plot>>& garden_map) {
    std::vector<std::vector<XY>> regions;
    int n {}; // region number
    for (std::size_t i=0; i<garden_map.size(); ++i) {
        for (std::size_t j=0; j<garden_map[i].size(); ++j) {
            if (garden_map[i][j].visited == 0) {
                regions.push_back( {} );
                XY plot;
                plot.x = i;
                plot.y = j;
                find_region(garden_map, plot, regions[n++]);
            }
        }
    }
    return regions;
}

void find_region(std::vector<std::vector<Plot>>& garden_map, const XY& plot, std::vector<XY>& region_plots) {
    if (garden_map[plot.x][plot.y].visited == 0) {
        garden_map[plot.x][plot.y].visited = 1;
        const std::vector<XY> directions = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
        for (const XY& dir : directions) {
            if (the_same_region(garden_map, plot, dir) ) {
                find_region(garden_map, {plot.x + dir.x, plot.y + dir.y}, region_plots);
            }
        }
        region_plots.push_back(plot);
    } else { return; }
}

bool the_same_region(const std::vector<std::vector<Plot>>& garden_map, const XY& plot, const XY& dir) {
    int lim_x = garden_map.size();
    int lim_y = garden_map[0].size();
    if ( (plot.x + dir.x >= 0) && (plot.x + dir.x < lim_x)
        && (plot.y + dir.y >= 0) && (plot.y + dir.y < lim_y)
        && (garden_map[plot.x + dir.x][plot.y + dir.y].plant == garden_map[plot.x][plot.y].plant) ) {
            return true;
    }
    return false;
}

int calc_price(const std::vector<XY>& region_plots, const std::vector<std::vector<Plot>>& garden_map) {
    int area = region_plots.size();
    int corners {};
    for (auto plot : region_plots) {
        const std::vector<XY> directions = { {-1, -1}, {-1, 1}, {1, 1}, {1, -1} };
        for (const XY& dir : directions ) {
            corners += find_out_corner(plot, dir, garden_map);
            corners += find_in_corner(plot, dir, garden_map);
        }
    }
    return corners * area;
}

bool find_out_corner(const XY& plot, const XY& dir, const std::vector<std::vector<Plot>>& garden_map) {
    if (x_out_of_bounds(plot.x + dir.x, garden_map) ) {
        if (y_out_of_bounds(plot.y + dir.y, garden_map) ) {
            return true;
        }
        if (garden_map[plot.x][plot.y].plant != garden_map[plot.x][plot.y + dir.y].plant) {
            return true;
        } else { return false; }
    }

    if (y_out_of_bounds(plot.y + dir.y, garden_map) ) {
        if (garden_map[plot.x][plot.y].plant != garden_map[plot.x + dir.x][plot.y].plant) {
            return true;
        } else { return false; }
    }

    if (garden_map[plot.x][plot.y].plant != garden_map[plot.x + dir.x][plot.y].plant
        && garden_map[plot.x][plot.y].plant != garden_map[plot.x][plot.y + dir.y].plant) {
        return true;
    } else { return false; }
}

bool find_in_corner(const XY& plot, const XY& dir, const std::vector<std::vector<Plot>>& garden_map) {
    if (x_out_of_bounds(plot.x + dir.x, garden_map) || y_out_of_bounds(plot.y + dir.y, garden_map) ) {
        return false;
    }
    if (garden_map[plot.x][plot.y].plant == garden_map[plot.x + dir.x][plot.y].plant
    && garden_map[plot.x][plot.y].plant == garden_map[plot.x][plot.y + dir.y].plant
    && garden_map[plot.x][plot.y].plant != garden_map[plot.x + dir.x][plot.y + dir.y].plant) {
        return true;
    }
    return false;
}

bool x_out_of_bounds(int new_x, const std::vector<std::vector<Plot>>& garden_map) {
    int lim_x = garden_map.size();
    return new_x < 0 || new_x >= lim_x;
}

bool y_out_of_bounds(int new_y, const std::vector<std::vector<Plot>>& garden_map) {
    int lim_y = garden_map[0].size();
    return new_y < 0 || new_y >= lim_y;
}
