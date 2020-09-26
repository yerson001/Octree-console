#ifndef OCTREE_H
#define OCTREE_H
#include <iostream>
#include "point.h"
#include <vector>

using namespace std;
class Octree {
private:
    bool parar() {
        if(data.size() > 3) {// si el numero de datos es mayor a 2
            return true;
        }
        return false;

    }
public:
//  Variables del octree
    bool leaf;
    Point dimMax;
    Point dimMin;
    vector<Point*> data;
//  hijos para el arbol
    Octree *hijo1;
    Octree *hijo2;
    Octree *hijo3;
    Octree *hijo4;
    Octree *hijo5;
    Octree *hijo6;
    Octree *hijo7;
    Octree *hijo8;

// constructor por defecto
    Octree() {
        dimMin = Point(-1,-1,-1);
        dimMax = Point(1,1,1);
        leaf = true;
    }
// Constructor con min - max
    Octree(Point min, Point max) {
        dimMax = max;
        dimMin = min;
        leaf = true;
    }


    // funcion para encontrar un punto en nuestro arbol
    // recibe el punto 'a' y un puntero de tipo octree
    bool find(Point *pt, Octree **pOT ){
        if(leaf){ // si es una hoja lo buscamos en data
            *pOT = this; // cout<<"pOT->leaf: "<<*pOT<<endl;
            for(int i=0;i<data.size();i++) {
                if(data[i]->x == pt->x && data[i]->y == pt->y && data[i]->z == pt->z) {
                    return true;
                }
            }
            return false;
        }
        //cout<<"findOctante: "<<findOctant(pt)<<endl;
        return findOctant(pt)->find(pt,pOT);
    }
  // Busca el dato entre dimMAX  y dimMIN
  // y retorna el lugar
    Octree* findOctant(Point *p){
        cout<<"lo busco en octante"<<endl;
        float midX = (dimMax.x + dimMin.x)/2;
        float midY = (dimMax.y + dimMin.y)/2;
        float midZ = (dimMax.z + dimMin.z)/2;

        if(p->x <= midX) {
            if(p->y <= midY) {
                if(p->z <= midZ) {
                    return hijo6;
                } else {
                    return hijo2;
                }
            } else {
                if(p->z <= midZ){
                    return hijo5;
                }else{
                    return hijo1;
                }
            }
        } 
        else {
            if(p->y <= midY){
                if(p->z <= midZ){
                    return hijo8;
                }else{
                    return hijo4;
                }
            } else {
                if(p->z <= midZ){
                    return hijo7;
                }else{
                    return hijo3;
                }
            }

        }
    }
    // funcion insertar un nuevo punto
    bool insert(Point *pt) {
        Octree *pOT = nullptr; //cout<<"qOT: "<<pOT<<endl;
    // verificar si el punto ya existe en el arbol
        if(find(pt,&pOT)){
            cout<< "ya existe! " <<endl;
            return false;
        }
        //cout<<"pOT->after find: "<<pOT<<endl;

        if(pOT==nullptr)
            return false;

        if(pOT->parar()){// si tenemos un cubo con menor a n puntos 
            pOT->leaf = false;
            float midX = (pOT->dimMax.x + pOT->dimMin.x)/2;
            float midY = (pOT->dimMax.y + pOT->dimMin.y)/2;
            float midZ = (pOT->dimMax.z + pOT->dimMin.z)/2;
            //cout<<"midx: "<<midX<<"  midy: "<<midY<<"  midz: "<<midZ<<endl;

            pOT->hijo1 = new Octree(Point(pOT->dimMin.x,midY,midZ),Point(midX,pOT->dimMax.y,pOT->dimMax.z));
            pOT->hijo2 = new Octree(Point(pOT->dimMin.x,pOT->dimMin.y,midZ),Point(midX,midY,pOT->dimMax.z));
            pOT->hijo3 = new Octree(Point(midX,midY,midZ),pOT->dimMax);
            pOT->hijo4 = new Octree(Point(midX,pOT->dimMin.y,midZ),Point(pOT->dimMax.x,midY,pOT->dimMax.z));

            pOT->hijo5 = new Octree(Point(pOT->dimMin.x,midY,pOT->dimMin.z),Point(midX,pOT->dimMax.y,midZ));
            pOT->hijo6 = new Octree(pOT->dimMin,Point(midX,midY,midZ));
            pOT->hijo7 = new Octree(Point(midX,midY,pOT->dimMin.z),Point(pOT->dimMax.x,pOT->dimMax.y,midZ));
            pOT->hijo8 = new Octree(Point(midX,pOT->dimMin.y,pOT->dimMin.z),Point(pOT->dimMax.x,midY,midZ));


            for(int i = 0;i<int(pOT->data.size());i++) {
                (pOT->findOctant(pOT->data[i]))->insert(pOT->data[i]);
                //(findOctant(data[i])->data).push_back(data[i]);
            }
            (pOT->findOctant(pt))->insert(pt);
            (pOT->data).clear();

        } else {
             (pOT->data).push_back(pt);
        }
        return true;
    }

    void printQ() {
        this->data;
        std::cout <<" Numero de datos: " <<data.size() << " puntos"<<endl;
    }
    void PriP(Point *pt){
        cout<<"punto : ("<<pt->x<<", "<<pt->y<<", "<<pt->z<<" )"<<endl;
    }  

    void eliminar(Point *pt) {
        Octree *pOT = nullptr;
        if(find(pt,&pOT)) { 
         cout<<">>>>>>>>>> lo encontramos para eliminar"<<endl;
        for(int i = 0;i<int(pOT->data.size());i++){
            if( pOT->data[i]->x == pt->x and pOT->data[i]->y == pt->y and pOT->data[i]->z == pt->z){
                cout<<"( "<<pOT->data[i]->x<<", "<<pOT->data[i]->y<<", "<<pOT->data[i]->z<<")"<<endl;
                pOT->data[i] = new Point();
            }
        }
         
        }else {
          cout<<"no lo encontro para eliminar"<<endl;
        }
    }

    ~Octree() {
        for(int i = 0;i<data.size();i++)
            delete data[i];
        if(hijo1) {
            delete hijo1;
            delete hijo2;
            delete hijo3;
            delete hijo4;
            delete hijo5;
            delete hijo6;
            delete hijo7;
            delete hijo8;
        }
    }

};

#endif // OCTREE_H
