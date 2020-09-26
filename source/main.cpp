#include <iostream>
#include "octree.h"
#include "point.h"

using namespace std;
Octree tree;
Octree *pQT = nullptr;

int main() {
    
    Point *a = new Point(1,1,4);
    Point *b = new Point(-2,1,-4);
    Point *c = new Point(-1,2,-1);   
    //*****insertamos los puntos****
    tree.insert(a);
    tree.insert(b);
    tree.insert(c);
   //*****verificamos que esten*****
    cout<<(tree.find(a,&pQT)? " Encontrado " : " No encontrado " )<<endl;
    cout<<(tree.find(b,&pQT)? " Encontrado " : " No encontrado " )<<endl;
    cout<<(tree.find(c,&pQT)? " Encontrado " : " No encontrado " )<<endl;
    //*********Eliminamos******a y b***
    tree.eliminar(a);
    tree.eliminar(b);
    //*********Verificamos si se eliminaron
    cout<<(tree.find(a,&pQT)? " Encontrado " : " No encontrado " )<<endl;
    cout<<(tree.find(b,&pQT)? " Encontrado " : " No encontrado " )<<endl;
    cout<<(tree.find(c,&pQT)? " Encontrado " : " No encontrado " )<<endl;


    return 0;
}
