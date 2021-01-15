#include "cg3d.h"

// Aluno: Marco Antonio Bernardi Grivol
// RA: 758619

// gcc -c cg2d.c
// gcc -c cg3d.c
// gcc exemplo_teste_3d.c -o exemplo_teste_3d cg3d.o cg2d.o bibaux.o -lm -lX11
// ./exemplo_teste_3d

int main(void)
{
    point3d *p;
    face *f1, *f2, *f3, *f4, *f5;
    object3d *ob, *cob;
    point3d *u, *v, *vu, *w;
    matrix3d *H;
    object *faces;

    palette *palheta;
    bufferdevice *dispositivo;
    window *janela;
    viewport *porta;

    float zcp, zpp;

    palheta = CreatePalette(6);
    SetColor(0, 0, 0, palheta);
    SetColor(1, 1, 1, palheta);
    SetColor(1, 1, 0, palheta);
    SetColor(1, 0, 0, palheta);
    SetColor(0, 1, 0, palheta);
    SetColor(0, 0, 1, palheta);

    p = (point3d *)malloc(sizeof(point3d));

    f1 = CreateFace(3);
    p = SetPoint3d(10.0, 10.0, 0.0, 1.0, 1);
    SetPointFace(p, f1);
    p = SetPoint3d(10.0, 0.0, 15.0, 1.0, 1);
    SetPointFace(p, f1);
    p = SetPoint3d(10.0, -10.0, 0.0, 1.0, 1);
    SetPointFace(p, f1);

    f2 = CreateFace(3);
    p = SetPoint3d(-10.0, 10.0, 0.0, 1.0, 2);
    SetPointFace(p, f2);
    p = SetPoint3d(-10.0, 0.0, 15.0, 1.0, 2);
    SetPointFace(p, f2);
    p = SetPoint3d(-10.0, -10.0, 0.0, 1.0, 2);
    SetPointFace(p, f2);

    f3 = CreateFace(4);
    p = SetPoint3d(10.0, 10.0, 0.0, 1.0, 3);
    SetPointFace(p, f3);
    p = SetPoint3d(10.0, 0.0, 15.0, 1.0, 3);
    SetPointFace(p, f3);
    p = SetPoint3d(-10.0, 0.0, 15.0, 1.0, 3);
    SetPointFace(p, f3);
    p = SetPoint3d(-10.0, 10.0, 0.0, 1.0, 3);
    SetPointFace(p, f3);

    f4 = CreateFace(4);
    p = SetPoint3d(10.0, 0.0, 15.0, 1.0, 4);
    SetPointFace(p, f4);
    p = SetPoint3d(10.0, -10.0, 0.0, 1.0, 4);
    SetPointFace(p, f4);
    p = SetPoint3d(-10.0, -10.0, 0.0, 1.0, 4);
    SetPointFace(p, f4);
    p = SetPoint3d(-10.0, 0.0, 15.0, 1.0, 4);
    SetPointFace(p, f4);

    f5 = CreateFace(4);
    p = SetPoint3d(10.0, 10.0, 0.0, 1.0, 5);
    SetPointFace(p, f5);
    p = SetPoint3d(10.0, -10.0, 0.0, 1.0, 5);
    SetPointFace(p, f5);
    p = SetPoint3d(-10.0, -10.0, 0.0, 1.0, 5);
    SetPointFace(p, f5);
    p = SetPoint3d(-10.0, 10.0, 0.0, 1.0, 5);
    SetPointFace(p, f5);

    ob = CreateObject3D(5);
    SetObject3D(f1, ob);
    SetObject3D(f2, ob);
    SetObject3D(f3, ob);
    SetObject3D(f4, ob);
    SetObject3D(f5, ob);

    matrix3d *rot;
    rot = (matrix3d *)malloc(sizeof(matrix3d));
    rot = SetZRotMatrix3D( 45.0 );
    ob = ConvertObjectBase(rot, ob);
    rot = SetXRotMatrix3D( 30.0 );
    ob = ConvertObjectBase(rot, ob);
    rot = SetYRotMatrix3D( 30.0 );
    ob = ConvertObjectBase(rot, ob);

    w = (point3d *)malloc(sizeof(point3d)); // vetor normal ao plano de visualização (vetor dado!)
    w->x = 0;
    w->y = 0;
    w->z = -1;

    vu = (point3d *)malloc(sizeof(point3d)); // view-up (vetor dado!)
    vu->x = 0;
    vu->y = 1;
    vu->z = 0;

    u = VectorProduct3d(vu, w);
    v = VectorProduct3d(w, u);

    H = (matrix3d *)malloc(sizeof(matrix3d));
    H->a11 = u->x; H->a12 = u->y; H->a13 = u->z; H->a14 = 0.0;
    H->a21 = v->x; H->a22 = v->y; H->a23 = v->z; H->a24 = 0.0;
    H->a31 = w->x; H->a32 = w->y; H->a33 = w->z; H->a34 = 0.0;
    H->a14 = 0.0;  H->a24 = 0.0;  H->a34 = 0.0;  H->a44 = 1.0;

    cob = ConvertObjectBase(H, ob);

    // faces = ParalProjFaces(cob);
    zpp = 40.0;
    zcp = -45.0;
    faces = PerspProjFaces(cob, zpp, zcp);

    janela = CreateWindow(-80, -80, 80, 80);
    dispositivo = CreateBuffer(640, 480);
    porta = CreateViewPort(0, 0, 639, 479);

    DrawObject(&faces[0], janela, porta, dispositivo, 3);
    DrawObject(&faces[1], janela, porta, dispositivo, 3);
    DrawObject(&faces[2], janela, porta, dispositivo, 3);
    DrawObject(&faces[3], janela, porta, dispositivo, 3);
    DrawObject(&faces[4], janela, porta, dispositivo, 3);

    Dump2X(dispositivo, palheta);

    return 0;
}