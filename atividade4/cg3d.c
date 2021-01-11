#include "cg3d.h"

point3d *SetPoint3d(float x, float y, float z, float w, int color)
{
	point3d *pnt;

	pnt = (point3d *)malloc(sizeof(point3d));
	pnt->x = x / w;
	pnt->y = y / w;
	pnt->z = z / w;
	pnt->w = w;
	pnt->color = color;

	return pnt;
}

point3d *VectorProduct3d(point3d *u, point3d *v)
{
	point3d *w;
	w = (point3d *)malloc(sizeof(point3d));

	/* 
 i  j  k
 u1 u2 u3       u2v3i + u3v1j + u1v2k - u2v1k - u3v2i - u1v3j = (u2v3 - u3v2)i + (u3v1 - u1v3)j + (u1v2 - u2v1)k 
 v1 v2 v3
 */

	w->x = (u->y) * (v->z) - (u->z) * (v->y);
	w->y = (u->z) * (v->x) - (u->x) * (v->z);
	w->z = (u->x) * (v->y) - (u->y) * (v->x);

	w->color = 1;

	return w;
}

float Modulo3d(point3d *u)
{
	return (sqrt(((u->x) * (u->x)) + ((u->y) * (u->y)) + ((u->z) * (u->z))));
}

point3d *Versor3d(point3d *u)
{
	point3d *w;
	float modulo = Modulo3d(u);
	w = (point3d *)malloc(sizeof(point3d));

	w->x = (u->x) / modulo;
	w->y = (u->y) / modulo;
	w->z = (u->z) / modulo;

	w->color = 1;

	return w;
}

face *CreateFace(int numbers_of_points)
{
	face *fob;

	fob = (face *)malloc(sizeof(face));
	fob->numbers_of_points = 0;
	fob->points = (point3d *)malloc(numbers_of_points * sizeof(point3d));

	return fob;
}

int SetPointFace(point3d *pnt, face *fc)
{
	fc->points[fc->numbers_of_points] = *pnt;
	fc->numbers_of_points = fc->numbers_of_points + 1;

	return 0;
}

object3d *CreateObject3D(int numbers_of_faces)
{
	object3d *ob;

	ob = (object3d *)malloc(sizeof(object3d));
	ob->numbers_of_faces = 0;
	ob->faces = (face *)malloc(numbers_of_faces * sizeof(face));

	return ob;
}

int SetObject3D(face *fc, object3d *ob)
{
	ob->faces[ob->numbers_of_faces] = *fc;
	ob->numbers_of_faces = ob->numbers_of_faces + 1;

	return 0;
}

matrix3d *SetXRotMatrix3D(float theta)
{
	matrix3d *m;
	m = (matrix3d *)malloc(sizeof(matrix3d));

	m->a11 = 1.0;     
	m->a12 = 0.0;    
	m->a13 = 0.0;
	m->a14 = 0.0;

	m->a21 = 0.0;
	m->a22 = cos((theta * M_PI) / 180.0);
	m->a23 = (-1.0) * sin((theta * M_PI) / 180.0);
	m->a24 = 0.0;

	m->a31 = 0.0;
	m->a32 = sin((theta * M_PI) / 180.0);
	m->a33 = cos((theta * M_PI) / 180.0);
	m->a34 = 0.0;

	m->a41 = 0.0;
	m->a42 = 0.0;
	m->a43 = 0.0;
	m->a44 = 1.0;

	return m;
}

matrix3d *SetYRotMatrix3D(float theta)
{
	matrix3d *m;
	m = (matrix3d *)malloc(sizeof(matrix3d));

	m->a11 = cos((theta * M_PI) / 180.0); 
	m->a12 = 0.0;    
	m->a13 = sin((theta * M_PI) / 180.0);
	m->a14 = 0.0;

	m->a21 = 0.0;
	m->a22 = 1.0;
	m->a23 = 0.0;
	m->a24 = 0.0;

	m->a31 = 0.0;
	m->a32 = (-1.0) * sin((theta * M_PI) / 180.0);
	m->a33 = 0.0;
	m->a34 = cos((theta * M_PI) / 180.0);

	m->a41 = 0.0;
	m->a42 = 0.0;
	m->a43 = 0.0;
	m->a44 = 1.0;

	return m;
}

matrix3d *SetZRotMatrix3D(float theta)
{
	matrix3d *m;
	m = (matrix3d *)malloc(sizeof(matrix3d));

	m->a11 = cos((theta * M_PI) / 180.0);
	m->a12 = (-1.0) * sin((theta * M_PI) / 180.0);
	m->a13 = 0.0;
	m->a14 = 0.0;

	m->a21 = sin((theta * M_PI) / 180.0);
	m->a22 = cos((theta * M_PI) / 180.0);
	m->a23 = 0.0;
	m->a24 = 0.0;

	m->a31 = 0.0;
	m->a32 = 0.0;
	m->a33 = 1.0;
	m->a34 = 0.0;

	m->a41 = 0.0;
	m->a42 = 0.0;
	m->a43 = 0.0;
	m->a44 = 1.0;

	return m;
}

matrix3d *SetSftMatrix3D(float dx, float dy, float dz)
{
	matrix3d *m;
	m = (matrix3d *)malloc(sizeof(matrix3d));

	m->a11 = 1.0; m->a12 = 0.0;	m->a13 = 0.0; m->a14 = dx;
	m->a21 = 0.0; m->a22 = 1.0;	m->a23 = 0.0; m->a24 = dy;
	m->a31 = 0.0; m->a32 = 0.0; m->a33 = 1.0; m->a34 = dz;
	m->a41 = 0.0; m->a42 = 0.0; m->a43 = 0.0; m->a44 = 1.0;

	return m;
}

matrix3d *SetSclMatrix3D(float sx, float sy, float sz)
{
	matrix3d *m;
	m = (matrix3d *)malloc(sizeof(matrix3d));

	m->a11 = sx;  m->a12 = 0.0;	m->a13 = 0.0; m->a14 = 0.0;
	m->a21 = 0.0; m->a22 = sy;	m->a23 = 0.0; m->a24 = 0.0;
	m->a31 = 0.0; m->a32 = 0.0; m->a33 = sz;  m->a34 = 0.0;
	m->a41 = 0.0; m->a42 = 0.0; m->a43 = 0.0; m->a44 = 1.0;

	return m;
}

point3d *LinearTransf3d(matrix3d *W, point3d *u)
{
	point3d *p;

	p = (point3d *)malloc(sizeof(point3d));

	p->x = W->a11 * u->x + W->a12 * u->y + W->a13 * u->z + W->a14 * u->w;
	p->y = W->a21 * u->x + W->a22 * u->y + W->a23 * u->z + W->a24 * u->w;
	p->z = W->a31 * u->x + W->a32 * u->y + W->a33 * u->z + W->a34 * u->w;
	p->w = W->a41 * u->x + W->a42 * u->y + W->a43 * u->z + W->a44 * u->w;

	p->color = u->color;

	return p;
}

object3d *ConvertObjectBase(matrix3d *M, object3d *ob)
{
	object3d *mob;
	point3d *p0, *p1;
	int numbers_of_points, numbers_of_faces;

	p0 = (point3d *)malloc(sizeof(point3d));
	p1 = (point3d *)malloc(sizeof(point3d));

	mob = (object3d *)malloc(sizeof(object3d));
	mob->numbers_of_faces = ob->numbers_of_faces;
	mob->faces = (face *)malloc(ob->numbers_of_faces * sizeof(face));

	for (numbers_of_faces = 0; numbers_of_faces < ob->numbers_of_faces; numbers_of_faces++)
	{
		mob->faces[numbers_of_faces].numbers_of_points = ob->faces[numbers_of_faces].numbers_of_points;
		mob->faces[numbers_of_faces].points = (point3d *)malloc(ob->faces[numbers_of_faces].numbers_of_points * sizeof(point3d));
		for (numbers_of_points = 0; numbers_of_points < ob->faces[numbers_of_faces].numbers_of_points; numbers_of_points++)
		{
			p0->x = ob->faces[numbers_of_faces].points[numbers_of_points].x;
			p0->y = ob->faces[numbers_of_faces].points[numbers_of_points].y;
			p0->z = ob->faces[numbers_of_faces].points[numbers_of_points].z;
			p0->w = ob->faces[numbers_of_faces].points[numbers_of_points].w; // new
			p0->color = ob->faces[numbers_of_faces].points[numbers_of_points].color;
			p1 = LinearTransf3d(M, p0);
			mob->faces[numbers_of_faces].points[numbers_of_points].x = p1->x;
			mob->faces[numbers_of_faces].points[numbers_of_points].y = p1->y;
			mob->faces[numbers_of_faces].points[numbers_of_points].z = p1->z;
			mob->faces[numbers_of_faces].points[numbers_of_points].w = p1->w; //new
			mob->faces[numbers_of_faces].points[numbers_of_points].color = p1->color;
		}
	}

	return mob;
}

matrix3d *SetParalProjMatrix()
{
	matrix3d *m;
	m = (matrix3d *)malloc(sizeof(matrix3d));

	m->a11 = 1.0; m->a12 = 0.0; m->a13 = 0.0; m->a14 = 0.0;
	m->a21 = 0.0; m->a22 = 1.0;	m->a23 = 0.0; m->a24 = 0.0;
	m->a31 = 0.0; m->a32 = 0.0; m->a33 = 0.0; m->a34 = 0.0;
	m->a41 = 0.0; m->a42 = 0.0; m->a43 = 0.0; m->a44 = 1.0;

	return m;
}

object *ParalProjFaces(object3d *ob3d)
{
	object *facelist;
	int numbers_of_points, numbers_of_faces;

	matrix3d *m;
	m = (matrix3d *)malloc(sizeof(matrix3d));

	point3d *p;
	p = (point3d *)malloc(sizeof(point3d));

	facelist = (object *)malloc(ob3d->numbers_of_faces * sizeof(object));
	for (numbers_of_faces = 0; numbers_of_faces < ob3d->numbers_of_faces; numbers_of_faces++)
	{
		facelist[numbers_of_faces].numbers_of_points = ob3d->faces[numbers_of_faces].numbers_of_points;
		facelist[numbers_of_faces].points = (point *)malloc(facelist[numbers_of_faces].numbers_of_points * sizeof(point));
		for (numbers_of_points = 0; numbers_of_points < ob3d->faces[numbers_of_faces].numbers_of_points; numbers_of_points++)
		{
			p->x = ob3d->faces[numbers_of_faces].points[numbers_of_points].x;
			p->y = ob3d->faces[numbers_of_faces].points[numbers_of_points].y;
			p->z = ob3d->faces[numbers_of_faces].points[numbers_of_points].z;
			p->w = ob3d->faces[numbers_of_faces].points[numbers_of_points].w;
			p->color = ob3d->faces[numbers_of_faces].points[numbers_of_points].color;

			m = SetParalProjMatrix();
			p = LinearTransf3d(m, p);

			facelist[numbers_of_faces].points[numbers_of_points].x = p->x;
			facelist[numbers_of_faces].points[numbers_of_points].y = p->y;
			facelist[numbers_of_faces].points[numbers_of_points].w = p->w;
			facelist[numbers_of_faces].points[numbers_of_points].color = p->color;
		}
	}

	return facelist;
}

matrix3d *SetPerspProjMatrix(float zpp, float zcp)
{
	matrix3d *m;
	m = (matrix3d *)malloc(sizeof(matrix3d));

	// m->a11 = (zpp - zcp)/(z - zcp); m->a12 = 0.0;	                m->a13 = 0.0; m->a14 = 0.0;
	// m->a21 = 0.0;                   m->a22 = (zpp - zcp)/(z - zcp);	m->a23 = 0.0; m->a24 = 0.0;
	// m->a31 = 0.0;                   m->a32 = 0.0;                   m->a33 = 0.0; m->a34 = 0.0;
	// m->a41 = 0.0;                   m->a42 = 0.0;                   m->a43 = 0.0; m->a44 = 1.0;

	m->a11 = 1.0; m->a12 = 0.0;	              m->a13 = 0.0;                      m->a14 = 0.0;
	m->a21 = 0.0; m->a22 = 1.0;	              m->a23 = 0.0;                      m->a24 = 0.0;
	m->a31 = 0.0; m->a32 = zpp/(zpp - zcp);   m->a33 = (-zpp * zcp)/(zpp - zcp); m->a34 = 0.0;
	m->a41 = 0.0; m->a42 = 0.0;               m->a43 = 1/(zpp - zcp);            m->a44 = -zcp/(zpp - zcp);

	return m;
}

object *PerspProjFaces(object3d *ob3d, float zpp, float zcp)
{
	object *facelist;
	int numbers_of_points, numbers_of_faces;

	matrix3d *m;
	m = (matrix3d *)malloc(sizeof(matrix3d));

	point3d *p;
	p = (point3d *)malloc(sizeof(point3d));

	facelist = (object *)malloc(ob3d->numbers_of_faces * sizeof(object));
	for (numbers_of_faces = 0; numbers_of_faces < ob3d->numbers_of_faces; numbers_of_faces++)
	{
		facelist[numbers_of_faces].numbers_of_points = ob3d->faces[numbers_of_faces].numbers_of_points;
		facelist[numbers_of_faces].points = (point *)malloc(facelist[numbers_of_faces].numbers_of_points * sizeof(point));
		for (numbers_of_points = 0; numbers_of_points < ob3d->faces[numbers_of_faces].numbers_of_points; numbers_of_points++)
		{
			p->x = ob3d->faces[numbers_of_faces].points[numbers_of_points].x;
			p->y = ob3d->faces[numbers_of_faces].points[numbers_of_points].y;
			p->z = ob3d->faces[numbers_of_faces].points[numbers_of_points].z;
			p->w = ob3d->faces[numbers_of_faces].points[numbers_of_points].w;
			p->color = ob3d->faces[numbers_of_faces].points[numbers_of_points].color;
			
			m = SetPerspProjMatrix(zpp, zcp);
			p = LinearTransf3d(m, p);
			
			facelist[numbers_of_faces].points[numbers_of_points].x = p->x / p->w;
			facelist[numbers_of_faces].points[numbers_of_points].y = p->y / p->w;
			facelist[numbers_of_faces].points[numbers_of_points].w = p->w;
			facelist[numbers_of_faces].points[numbers_of_points].color = p->color;
		}
	}
	return facelist;
}
