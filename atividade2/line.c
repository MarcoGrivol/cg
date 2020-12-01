
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
  float step = 0.5;
  if (pd1->x == pd2->x) // linha vertical
  {
    i = pd1->x;
    if (pd1->y < pd2->y) // do ponto1 ao ponto2
    {
      // para linhas verticais nao ha necessidade de utilizar step
      for (int k = pd1->y; k < pd2->y; k++)
      {
        j = k;
        index = (dev->MaxY - j - 1) * dev->MaxX + i;
        dev->buffer[index] = color;
      }
    }
    else if (pd1->y > pd2->y) // do ponto2 ao ponto1
    {
      for (int k = pd2->y; k < pd1->y; k++)
      {
        j = k;
        index = (dev->MaxY - j - 1) * dev->MaxX + i;
        dev->buffer[index] = color;
      }
    }
  }
  else // reta inclinacao positiva ou negativa (ponto1 ao ponto2 garantido por swap)
  {
    a = (pd2->y - pd1->y) / (pd2->x - pd1->x);
    b = pd1->y - a * pd1->x;
    for (float k = pd1->x; k < pd2->x; k += step)
    {
      j = a * k + b;
      i = k;
      index = (dev->MaxY - j - 1) * dev->MaxX + i;
      dev->buffer[index] = color;
    }
  }
  return 0;
}
