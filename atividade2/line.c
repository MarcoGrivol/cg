
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

  j = pd1->y;
  i = pd1->x;

  // Agora é com vocês! Completem a função! O resultado deve ser similar ao encontrado quando o programa exemplo1,
  // que está disponível na seção Biblioteca Gráfica, é executado.
  int index;
  if (pd1->x == pd2->x) // linha vertical
  {
    i = pd1->x;
    if (pd1->y < pd2->y) // do ponto1 ao ponto2
    {
      for (j = pd1->y; j < pd2->y; j++)
      {
        index = (dev->MaxY - j) * dev->MaxX + i;
        dev->buffer[index] = color;
      }
    }
    else if (pd1->y > pd2->y) // do ponto2 ao ponto1
    {
      for (j = pd2->y; j < pd1->y; j++)
      {
        index = (dev->MaxY - j) * dev->MaxX + i;
        dev->buffer[index] = color;
      }
    }
  }
  else // reta inclinacao positiva ou negativa (ponto1 ao ponto2 garantido por swap)
  {
    a = (pd2->y - pd1->y) / (pd2->x - pd1->x);
    b = pd1->y - a * pd1->x; 
    for (i = pd1->x; i < pd2->x; i++)
    {
      j = a * i + b;
      index = (dev->MaxY - j) * dev->MaxX + i;
      dev->buffer[index] = color;
    }
  }
  return 0;
}
