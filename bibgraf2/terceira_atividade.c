#include "cg2d.h"

#define n 12

object *OriginScale(object *obj)
{
    matrix *m;
    point *p = obj->points;

    m = SetSftMatrix(-p[0].x, -p[0].y); // coloca p1 na origem
    obj = TransObj(obj, m);
    p = obj->points;
    m = SetSclMatrix(1.0 / p[1].x, 1.0 / p[1].y); // deixa os catetos = 1
    return TransObj(obj, m);
}

int main(int argc, char **argv)
{
    // definicao das informacoes
    palette *palheta;
    bufferdevice *monitor;
    window *janela;
    viewport *porta;
    object *poligono1, *poligono2;

    monitor = CreateBuffer(640, 480);

    palheta = CreatePalette(9); 
    SetColor(0, 0, 0, palheta); // 0 preto
    SetColor(1, 0, 0, palheta); // 1 vermelho
    SetColor(0, 1, 0, palheta); // 2 verde
    SetColor(0, 0, 1, palheta); // 3 azul
    SetColor(1, 1, 1, palheta); // 4 branco
    SetColor(0.45, 0.5, 0.46, palheta); // 5 fumaca
    SetColor(0.62, 0.40, 0.2, palheta); // 6 marrom 
    SetColor(0.2, 0.81, 1, palheta); // 7 azul claro
    SetColor(1, 1, 0.61, palheta); // 8 amarelo

    point *p1 = SetPoint(4, -7, 1, 1);
    point *p2 = SetPoint(7, -3, 1, 1);
    point *p3 = SetPoint(7, -7, 1, 1);

    object *triangulo = CreateObject(3);
    SetObject(p1, triangulo);
    SetObject(p2, triangulo);
    SetObject(p3, triangulo);

    // Criacao da casa
    object *contorno = CreateObject(5);
    object *door = CreateObject(4);
    object *janelaDir = CreateObject(4);
    object *janelaEsq = CreateObject(4);
    object *janelaUp = CreateObject(4);
    object *telhadoDir = CreateObject(2);
    object *telhadoEsq = CreateObject(2);
    object *chamine = CreateObject(4);
    object *fumaca[n];

    matrix *m, *m1, *m2;
    point *p;

    // coloca p1 origem e altera a escala do triangulo
    triangulo = OriginScale(triangulo);

    //cria o contorno da casa
    m1 = SetSclMatrix( 10.0, 5.5 );
    m2 = SetSftMatrix( -5.0, 0.0 );
    m = ComposeMatrix( m2, m1 );
    triangulo = TransObj( triangulo, m );
    p = triangulo->points;
    SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), contorno );
    SetObject( SetPoint( p[2].x, p[2].y, 1, 1 ), contorno );
    SetObject( SetPoint( p[1].x, p[1].y, 1, 1 ), contorno );

    triangulo = OriginScale( triangulo );

    m1 = SetSclMatrix( 5.0, (0.6 * 5.5) );
    m2 = SetSftMatrix( -5.0, 5.5 );
    m = ComposeMatrix( m2, m1 );
    triangulo = TransObj( triangulo, m );
    p = triangulo->points;
    SetObject( SetPoint( p[1].x, p[1].y, 1, 1 ), contorno );
    SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), contorno );
    
    // reset
    triangulo = OriginScale( triangulo );

    // cria a porta
    m1 = SetSclMatrix( 2, 4.0);
    m2 = SetSftMatrix( -1.0, 0.0 );
    m = ComposeMatrix( m2, m1 );
    triangulo = TransObj( triangulo, m );
    p = triangulo->points;
    SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), door );
    SetObject( SetPoint( p[2].x, p[2].y, 1, 1 ), door );
    SetObject( SetPoint( p[1].x, p[1].y, 1, 1 ), door );

    m = SetSftMatrix( 0.0, 4.0 );
    triangulo = TransObj( triangulo, m );
    p = triangulo->points;
    SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), door );

    // reset
    triangulo = OriginScale( triangulo );

    // cria a janela direita
    m1 = SetSclMatrix( 2.0, 2.0 );
    m2 = SetSftMatrix( 2.25, 2.0 );
    m = ComposeMatrix( m2, m1 );
    triangulo = TransObj( triangulo, m );
    p = triangulo->points;
    SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), janelaDir );
    SetObject( SetPoint( p[2].x, p[2].y, 1, 1 ), janelaDir );
    SetObject( SetPoint( p[1].x, p[1].y, 1, 1 ), janelaDir );

    m = SetSftMatrix( 0.0, 2.0 );
    triangulo = TransObj( triangulo, m );
    p = triangulo->points;
    SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), janelaDir );

    // reset
    triangulo = OriginScale( triangulo );

    // cria a janela esquerda
    m1 = SetSclMatrix( 2.0, 2.0 );
    m2 = SetSftMatrix( -4.25, 2.0 );
    m = ComposeMatrix( m2, m1 );
    triangulo = TransObj( triangulo, m );
    p = triangulo->points;
    SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), janelaEsq );
    SetObject( SetPoint( p[2].x, p[2].y, 1, 1 ), janelaEsq );
    SetObject( SetPoint( p[1].x, p[1].y, 1, 1 ), janelaEsq );

    m = SetSftMatrix( 0.0, 2.0 );
    triangulo = TransObj( triangulo, m );
    p = triangulo->points;
    SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), janelaEsq );

    // reset
    triangulo = OriginScale( triangulo );

    // cria a janela superior
    m1 = SetSclMatrix( 2.0, 2.0 );
    m2 = SetSftMatrix( -1.0 , 5.0 );
    m = ComposeMatrix( m2, m1 );
    triangulo = TransObj( triangulo, m );
    p = triangulo->points;
    SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), janelaUp );
    SetObject( SetPoint( p[2].x, p[2].y, 1, 1 ), janelaUp );
    SetObject( SetPoint( p[1].x, p[1].y, 1, 1 ), janelaUp );

    m = SetSftMatrix( 0.0, 2.0 );
    triangulo = TransObj( triangulo, m );
    p = triangulo->points;
    SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), janelaUp );

    // reset
    triangulo = OriginScale( triangulo );

    // cria telhado
    m = SetSftMatrix( 5.5, 6 );
    triangulo = TransObj( triangulo, m );
    p = triangulo->points;
    SetObject( SetPoint( p[2].x, p[2].y, 1, 1 ), telhadoDir );

    m = SetSftMatrix( -5.5, 4.35 );
    triangulo = TransObj( triangulo, m );
    p = triangulo->points;
    SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), telhadoDir );
    SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), telhadoEsq );

    m = SetSftMatrix( -6.5, -4.35 );
    triangulo = TransObj( triangulo, m );
    p = triangulo->points;
    SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), telhadoEsq );

    // reset
    triangulo = OriginScale( triangulo );

    // cria a chamine
    m = SetSftMatrix( 1.5, 9.35 );
    triangulo = TransObj( triangulo, m );
    p = triangulo->points;
    SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), chamine );

    m = SetSftMatrix( 0.0, 0.85 );
    triangulo = TransObj( triangulo, m );
    p = triangulo->points;
    SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), chamine );
    SetObject( SetPoint( p[2].x, p[2].y, 1, 1 ), chamine );

    m = SetSftMatrix( 0.0, -1.5 );
    triangulo = TransObj( triangulo, m );
    p = triangulo->points;
    SetObject( SetPoint( p[2].x, p[2].y, 1, 1 ), chamine );

    // reset
    triangulo = OriginScale( triangulo );
    
    // cria a fumaca
    m1 = SetSclMatrix( 0.7, 1.0 );
    m2 = SetSftMatrix( -0.7, 0.0 );
    m1 = ComposeMatrix( m2, m1 );
    m2 = SetRotMatrix( 90.0 );
    m = ComposeMatrix( m2, m1 );
    triangulo = TransObj( triangulo, m );
    p = triangulo->points;

    for (int i = 0; i < n/2; i++)
    {
        fumaca[i] = CreateObject(2);
        SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), fumaca[i] );
        m = SetRotMatrix( -180 / (n / 2.0) );
        triangulo = TransObj( triangulo, m );
        p = triangulo->points;
        SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), fumaca[i] );

        m = SetSftMatrix( 2.0, 12.0 );
        fumaca[i] = TransObj( fumaca[i], m );
    }   

    // reset
    triangulo = OriginScale( triangulo );
    m1 = SetSclMatrix( 0.7, 1.0 );
    m2 = SetSftMatrix( -0.7, 0.0 );
    m1 = ComposeMatrix( m2, m1 );
    m2 = SetRotMatrix( 90.0 );
    m = ComposeMatrix( m2, m1 );
    triangulo = TransObj( triangulo, m );
    p = triangulo->points;

    for (int i = n/2; i < n; i++)
    {
        fumaca[i] = CreateObject(2);
        SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), fumaca[i] );
        m = SetRotMatrix( 180.0 / (n / 2.0) );
        triangulo = TransObj( triangulo, m );
        p = triangulo->points;
        SetObject( SetPoint( p[0].x, p[0].y, 1, 1 ), fumaca[i] );

        m = SetSftMatrix( 2.0, 13.4 );
        fumaca[i] = TransObj( fumaca[i], m );
    }

    m = SetSftMatrix( 0.0, -14.8/2.0 ); // os objetos comecam em y=0 com maximo em 14.8 (fumaca)
    contorno = TransObj( contorno, m );
    door = TransObj( door, m );
    janelaDir = TransObj( janelaDir, m );
    janelaEsq = TransObj( janelaEsq, m );
    janelaUp = TransObj( janelaUp, m );
    telhadoDir = TransObj( telhadoDir, m );
    telhadoEsq = TransObj( telhadoEsq, m );
    chamine = TransObj( chamine, m );

    janela = CreateWindow(-20.0, -20.0, 20.0, 20.0); // cria uma janela de visualização (coordenadas no SRU)
    porta = CreateViewPort(79, 0, 559, 479);          // Cria uma viewport

    DrawObject( contorno, janela, porta, monitor, 7 );
    DrawObject( door, janela, porta, monitor, 7 );
    DrawObject( janelaDir, janela, porta, monitor, 8 );
    DrawObject( janelaEsq, janela, porta, monitor, 8 );
    DrawObject( janelaUp, janela, porta, monitor, 8 );
    DrawObject( telhadoDir, janela, porta, monitor, 6 );
    DrawObject( telhadoEsq, janela, porta, monitor, 6 );
    DrawObject( chamine, janela, porta, monitor, 6 );
    for (int i = 0; i < n; i++) 
    {
        fumaca[i] = TransObj( fumaca[i], m );
        DrawObject( fumaca[i], janela, porta, monitor, 5 );
    }

    Dump2X(monitor, palheta);
    return 0;
}
