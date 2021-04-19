#include "list.h"

int main(int argc, char **argv)
{
    List list = List();

    list.fill(argv[1]);

    std::ofstream coordsfile("coords.js");
    std::ofstream colorsfile("colors.js");

    coordsfile << "var coords = [\n";
    colorsfile << "var colors = [\n";
    //Node we'll be finding the distance from
    Node *n = list.at(0);

    for(int i = 0; i < list.get_size(); ++i)
    {
        list.find_neighbors(n, i, coordsfile, colorsfile);
        n = n->get_next();
    }
    coordsfile << "];";
    colorsfile << "];";
}