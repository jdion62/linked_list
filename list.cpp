#include "list.h"


Node::Node()
{
    x = 0;
    y = 0;
    z = 0;
    chain = 'C';
    next = NULL;
}

Node::Node(double _x, double _y, double _z, char c)
{
    x = _x;
    y = _y;
    z = _z;
    chain = c;
    next = NULL;
}

Node::~Node(){}

Node *Node::get_next()
{
    return next;
}

List::List()
{
    head = tail = new Node();
    size = 0;
}

List::List(double x, double y, double z, char c)
{
    head = tail = new Node(x, y, z, c);
    size = 1;
}

List::~List()
{
    Node *p = head;
    for(int i = 0; i < size; ++i)
    {
        head = head->next;
        delete p;
        p = head;
    }
}

void List::append(Node *n)
{
    if(size == 0)
    {
        head = tail = n;
        ++size;
        return;
    }
    tail->next = n;
    tail = n;
    ++size;
}

void List::prepend(Node *n)
{
    n->next = head;
    head = n;
    ++size;
}

void List::overwrite_head(Node *n)
{
    n->next = head->next;
    head = n;
}

void List::fill(char *fname)
{
    std::ifstream infile(fname);
    std::string line;
    char c;
    std::string x;
    std::string y;
    std::string z;
    while(std::getline(infile, line))
    {
        if(!line.compare(0, 6, "ATOM  "))
            if(!line.compare(13, 3, "CA "))
            {
                c = line[21];
                x = line.substr(31, 7);
                y = line.substr(39, 7);
                z = line.substr(47, 7);
                Node *n = new Node(atof(x.c_str()), atof(y.c_str()), atof(z.c_str()), c);
                this->append(n);
            }
    }
}

int List::get_size()
{
    return size;
}

void List::find_neighbors(Node *n, int idx, std::ofstream& coordsfile, std::ofstream& colorsfile)
{
    double min_dist;
    int idx2 = 0;
    //initialize min_dist without comparing a Node to itself
    if(idx)
        min_dist = distance(*n, *at(0));
    else
    {
        min_dist = distance(*n, *at(1));
        idx2 = 1;
    }
    //will be closest Node
    Node *p = at(idx2);
    //this Node traverses the List
    Node *ntemp = at(0);

    for(int i = 0; i < size; ++i)
    {
        //so we don't calc dist from Node to itself
        if(i == idx)
        {
            ntemp = ntemp->next;
            continue;
        }
        //calc dist
        double temp = distance(*n, *ntemp);
        //switch if found smaller dist
        if(min_dist > temp)
        {
            min_dist = temp;
            p = ntemp;
            //idx2 = i;
        }
        ntemp = ntemp->next;
    }
    //writes coords to file
    coordsfile << n->x << ", " << n->y << ", " << n->z << ", ";
    coordsfile << p->x << ", " << p->y << ", " << p->z << ", " << "\n";
    //finds suposed color for first Node
    int r = 0, b = 0;
    double g = 0;
    switch(n->chain)
    {
        case 'A':
            b = 1;
            break;
        case 'B':
            g = 1;
            break;
        case 'C':
            r = 1;
            break;
        case 'D':
            r = g = 1;
            break;
        case 'E':
            r = g = b = 1;
            break;
        default:
            r = 1;
            g = .5;
    }
    //Writes to colorsfile for first Node
    colorsfile << r << ", " << g << ", " << b << ", ";
    //do it again for Node 2, probably should have written a func instead
    r = b = 0;
    g = 0;
    switch(p->chain)
    {
        case 'A':
            b = 1;
            break;
        case 'B':
            g = 1;
            break;
        case 'C':
            r = 1;
            break;
        case 'D':
            r = g = 1;
            break;
        case 'E':
            r = g = b = 1;
            break;
        default:
            r = 1;
            g = .5;
    }

    colorsfile << r << ", " << g << ", " << b << ", " << "\n";
}

double List::distance(Node n1, Node n2)
{
    double x_diff = n1.x - n2.x;
    double y_diff = n1.y - n2.y;
    double z_diff = n1.z - n2.z;
    return sqrt(pow(x_diff, 2) + pow(y_diff, 2) + pow(z_diff, 2));
}
//pseudo index access
Node *List::at(int idx)
{
    Node *p = head;
    for(int i = idx; i > 0; i--)
        p = p->next;
    return p;
}