#ifndef __List__
#define __List__

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

class Node
{
    private:
        double x;
        double y;
        double z;
        char chain;

        Node *next;

        //void set_next(Node*);

    public:
        Node();
        Node(double, double, double, char);
        ~Node();
        Node *get_next();

    friend class List;

};

class List
{
    private:
        Node *head;
        Node *tail;

        int size;

    public:
        List();
        List(double, double, double, char);
        ~List();

        void append(Node*);
        void prepend(Node*);
        void overwrite_head(Node*);
        void fill(char *fname);
        int get_size();

        void find_neighbors(Node *, int, std::ofstream&, std::ofstream&);
        double distance(Node, Node);

        Node *at(int);
};

#endif