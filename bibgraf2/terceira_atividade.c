// Um exemplo utizando as funções da biblioteca implementada

// Para executar:
// gcc -c bibaux.c
// gcc -c cg2d.c
// gcc exemplo1.c -o exemplo1 cg2d.o bibaux.o -lm -lX11
// ./exemplo1

#include "cg2d.h"
/*
typedef struct Casa {
    object *objetos;
} casa;

point *GetPoint( object *obj, int i )
{
    return &obj->points[i];
}

point *GetPoints( object *obj )
{
    point *p = (point *) malloc( sizeof(point) * 3);
    p[0] = GetPoint( obj, 0 );
    p[1] = GetPoint( obj, 1 );
    p[2] = GetPoint( obj, 2 );
    return p;
}
*/


object * OriginScale( object * obj )
{
    matrix *m;
    point *p = obj->points;

    m = SetSftMatrix( -p[0].x, -p[0].y ); // coloca p1 na origem
    obj = TransObj( obj, m );
    p = obj->points;
    m = SetSclMatrix( 1.0/p[1].x, 1.0/p[1].y ); // escala para catetos = 1
    return TransObj( obj, m );
}

void print( object *obj )
{
    point *p = obj->points;
    printf("p1(%.3f, %.3f)\np2(%.3f, %.3f)\np3(%.3f, %.3f)\n", 
        p[0].x, p[0].y, p[1].x, p[1].y, p[2].x, p[2].y );
    return;
}

int main(int argc, char **argv)
{

    palette *palheta;
    bufferdevice *monitor;
    window *janela;
    viewport *porta;
    object *poligono1, *poligono2;

    monitor = CreateBuffer(640, 480); // Cria um monitor virtual

    palheta = CreatePalette(5); // Cria um colormap (lookup table) com 5 cores
    SetColor(0, 0, 0, palheta);
    SetColor(1, 0, 0, palheta);
    SetColor(0, 1, 0, palheta);
    SetColor(0, 0, 1, palheta);
    SetColor(1, 1, 1, palheta);

    point *p1 = SetPoint( 4, -7, 1, 1 );
    point *p2 = SetPoint( 7, -3, 1, 1 );
    point *p3 = SetPoint( 7, -7, 1, 1 );
    
    object *triangulo = CreateObject( 3 ); 
    SetObject( p1, triangulo );
    SetObject( p2, triangulo );
    SetObject( p3, triangulo );

    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    object *c = CreateObject( 3 );
    
    point *p = triangulo->points;
    
    print( triangulo );
    triangulo = OriginScale( triangulo );

    






















    janela = CreateWindow(-20.0, -20.0, 20.0, 20.0); // cria uma janela de visualização (coordenadas no SRU)
    porta = CreateViewPort(0, 0, 639, 479); // Cria uma viewport

    DrawObject( triangulo, janela, porta, monitor, 1 );
    // DrawObject( new_triangulo, janela, porta, monitor, 3 );


    /*
    // cria dois objetos bidimensionais
    poligono1 = CreateObject(5); // polígono fechado com 5 vértices
    poligono2 = CreateObject(4); // polígono fechado com 4 vértices

    // Insere as coordenadas dos pontos representados no SRU em cada objeto
    // O terceiro parâmetro será discutido em aula futura
    // O quarto parâmetro é o indice associado a lookup table (cor)
    SetObject(SetPoint(-9.0, -8.0, 1, 1), poligono1);
    SetObject(SetPoint(-7.0, -3.0, 1, 1), poligono1);
    SetObject(SetPoint(-4.0, -4.0, 1, 1), poligono1);
    SetObject(SetPoint(-3.0, -6.0, 1, 1), poligono1);
    SetObject(SetPoint(-6.0, -9.0, 1, 1), poligono1);

    SetObject(SetPoint(-6.0, -2.0, 1, 3), poligono2);
    SetObject(SetPoint(-1.0, -2.0, 1, 3), poligono2);
    SetObject(SetPoint(-1.0, -6.0, 1, 3), poligono2);
    SetObject(SetPoint(-6.0, -6.0, 1, 3), poligono2);

    janela = CreateWindow(-10.0, -10.0, 0.0, 0.0); // cria uma janela de visualização (coordenadas no SRU)

    porta = CreateViewPort(0, 0, 639, 479); // Cria uma viewport
    // no caso uma única saída para o dispositivo de visualização com 640x480 entradas

    DrawObject(poligono1, janela, porta, monitor, 1);
    DrawObject(poligono2, janela, porta, monitor, 3);
    */
    Dump2X(monitor, palheta);

    return 0;
}
