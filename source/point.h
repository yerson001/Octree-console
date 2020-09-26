#ifndef POINT_H
#define POINT_H

class Point {
  public:
    // puntos del octree
    float x,y,z;
    
    // puntos por defecto vacio
    Point() { 

    }
    
    // puntos por parametro
    Point(float a, float b, float c) {
      x = a;
      y = b;
      z = c;
    }

    // puntos para a , b c = 0,0
    Point(float a,float b) {
      x = a;
      y = b;
      z = 0.0;
    }
};

#endif
