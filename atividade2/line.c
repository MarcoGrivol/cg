
// Esboço para a função DrawLine()
// Esta função faz a conversão matricial de segmento de reta entre os pontos p1 e p2

#include "cg2d.h"

int DrawLine(point *p1, point *p2, window *win, viewport *port, bufferdevice *dev, int color)
{
  float a, b, aux;
  int i, j;
  point *pn1, *pd1, *pn2, *pd2;

  pn1 = Sru2Srn(p1, win);
  pd1 = Srn2Srd(pn1, port);
  pn2 = Sru2Srn(p2, win);
  pd2 = Srn2Srd(pn2, port);

  if (pd1->x > pd2->x)
  { // O swap entre os pontos pode ser necessário. Por quê?
    aux = pd1->x;
    pd1->x = pd2->x;
    pd2->x = aux;
    aux = pd1->y;
    pd1->y = pd2->y;
    pd2->y = aux;
  }

  i = pd1->x;
  j = pd1->y;

  // Agora é com vocês! Completem a função! O resultado deve ser similar ao encontrado quando o programa exemplo1,
  // que está disponível na seção Biblioteca Gráfica, é executado.

  return 0;
}
