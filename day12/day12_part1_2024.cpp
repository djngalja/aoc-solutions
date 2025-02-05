#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Plot { char plant; bool visited; };
struct XY { int x; int y; };

int calc_price(const std::vector<int>&);
bool is_the_same_region(const std::vector<std::vector<Plot>>&, const XY&, const XY&);
void find_region(std::vector<std::vector<Plot>>&, const XY&, std::vector<int>&);
std::vector<std::vector<int>> find_regions(std::vector<std::vector<Plot>>&);
bool read_input(const std::string&, std::vector<std::vector<Plot>>&);
void day12_part1();


int main() {
    day12_part1();
    return 0;
}


void day12_part1() {
    std::vector<std::vector<Plot>> garden_map;
    if (read_input("input.txt", garden_map)) {
        const std::vector<std::vector<int>> regions = find_regions(garden_map);
        int ttl_price {};
        for (const auto& region : regions) {
            ttl_price += calc_price(region);
        }
        std::cout << "The total price of fencing all regions: " << ttl_price << '\n';
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

std::vector<std::vector<int>> find_regions(std::vector<std::vector<Plot>>& garden_map) {
    std::vector<std::vector<int>> regions;
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

void find_region(std::vector<std::vector<Plot>>& garden_map, const XY& plot, std::vector<int>& region_sides) {
    if (garden_map[plot.x][plot.y].visited == 0) {
        garden_map[plot.x][plot.y].visited = 1;
        const std::vector<XY> directions = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
        int plot_sides {4};
        for (const XY& dir : directions) {
            if (is_the_same_region(garden_map, plot, dir) ) {
                plot_sides--;
                find_region(garden_map, {plot.x + dir.x, plot.y + dir.y}, region_sides);
            }
        }
        region_sides.push_back(plot_sides);
    } else { return; }
}

bool is_the_same_region(const std::vector<std::vector<Plot>>& garden_map, const XY& plot, const XY& dir) {
    int lim_x = garden_map.size();
    int lim_y = garden_map[0].size();
    if ( (plot.x + dir.x >= 0) && (plot.x + dir.x < lim_x)
        && (plot.y + dir.y >= 0) && (plot.y + dir.y < lim_y)
        && (garden_map[plot.x + dir.x][plot.y + dir.y].plant == garden_map[plot.x][plot.y].plant) ) {
            return true;
    }
    return false;
}

int calc_price(const std::vector<int>& region_sides) {
    int area = region_sides.size();
    int perimeter {};
    for (auto plot_sides : region_sides) { perimeter += plot_sides; }
    return perimeter * area;
}
