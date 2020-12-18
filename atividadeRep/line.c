
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

  // Para esse exercício, esta função deve estar em ordem!
  int index;
  float step = 0.05;
  if (pd1->x == pd2->x) // linha vertical
  {
    i = pd1->x;
    if (pd1->y < pd2->y) // do ponto1 ao ponto2
    {
      // para linhas verticais nao ha necessidade de utilizar step
      for (int k = pd1->y; k < pd2->y; k++)
      {
        j = k;
        index = j * dev->MaxX + i;
        dev->buffer[index] = color;
      }
    }
    else if (pd1->y > pd2->y) // do ponto2 ao ponto1
    {
      for (int k = pd2->y; k < pd1->y; k++)
      {
        j = k;
        index = j * dev->MaxX + (i);
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
      index = j * dev->MaxX + i;
      dev->buffer[index] = color;
    }
  }
  return 0;
}

// Retorna a posicao maxima da linha dy que deve ser preenchida
int GetMaxInObject(int dx, int dy, bufferdevice *dev, viewport *port, int color)
{
  int dx_max = dx; // no caso de nao encontrar um ultimo ponto
  int flag = 0;
  int dx_aux = port->xmax - 1; // partindo do fim da viewport
  while (dx_aux > dx && flag == 0) // enquanto nao encontrar o primeiro && nao encontrar o ultimo ponto
  {
    int index = dy * dev->MaxX + dx_aux;

    if (dev->buffer[index] == color) // encontrou o ultimo ponto
    {
      dx_max = dx_aux; 
      flag = 1;
    }
    dx_aux--;
  }

  return dx_max;
}

// Esboço para uma função de preenchimento de polígonos
int RasterFill(bufferdevice *dev, viewport *port, int color)
{
  for (int dy = port->ymin + 1; dy < port->ymax; dy++) // para cada linha da viewport
  {
    int flag = 0;
    int dx = port->xmin + 1;
    int dx_max = dx;
    while (flag == 0 && dx < port->xmax) // enquanto nao encontrou o primeiro ponto && nao chegou no final da viewport
    {
      int index = dy * dev->MaxX + dx;

      if (dev->buffer[index] == color) // encontrou o primeiro ponto do poligono na linha atual
      {
        flag = 1;
        dx_max = GetMaxInObject(dx, dy, dev, port, color); // busca o ultimo ponto do poligono na linha atual
      }
      dx++;
    }
    while (dx < dx_max) // enqaunto o primeiro ponto for menor que o ultimo
    {
      int index = dy * dev->MaxX + (dx++);

      dev->buffer[index] = color;
    }
  }

  return 0;
}
