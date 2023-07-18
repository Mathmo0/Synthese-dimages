#include "vision.h"
#include "canon.h"
#include "geo.h"
#include "camera.h"


Transformation  CU_a_CV (const Camera& p)
{
	Transformation  dpo = Translation (vecteur (p.PO(), O));
	Transformation  an = Alignement (p.VN(),Z);

	vecteur h = an.transforme(p.VH());

	reel    x,y,z;
	h.composantes (&x,&y,&z);
	h = vecteur (x,y,0.0);
	h.normalise ();

	Transformation  ah = Alignement (h,Y);
//	Transformation  sx = Homo_X (-1.0);

	return(ah * an * dpo);
//	return(sx * ah * an * dpo);

}


Transformation  CV_a_CVN (const Camera& p)
{
	reel    x = (p.Pmax()+p.Pmin())/2.0;
	reel    y = (p.Hmax()+p.Hmin())/2.0;
	reel    z = p.DV() - p.DO();

	Transformation  cz = Cis_Z (vecteur (-x/z,-y/z,0.0));
	Transformation  hx = Homo_X (0.5/(p.Pmax()-x));
	//Transformation        hy = Homo_Y (0.5/(p.Hmax()-y));
	Transformation  hy = Homo_Y (0.5/(p.Pmax()-x));
	Transformation  hz = Homo_Z (1.0/z);

	return(hz*hy*hx * cz);
}

Transformation  CV_a_CA (const Camera& p)
{
	return N;

	reel    x,y;
	Transformation hy,hx,cz;
	vecteur v;

	x = (p.Xmax()-p.Xmin())/2.0;
	y = (p.Ymax()-p.Ymin())/2.0;
	hx = Homo_X (x);
	hy = Homo_Y (y);
	x = (p.Xmax()+p.Xmin())/2.0;
	y = (p.Ymax()+p.Ymin())/2.0;
	v = vecteur (x,y,0.0);

	if (p.perspective()) 

	{
		cz = Cis_Z (v);
	} 

	else 

	{
		cz = Translation (v);
	}

	return(cz * hy * hx);
}

Transformation  Vision (const Camera& p)
{
	return(CV_a_CA (p) * CV_a_CVN (p) * CU_a_CV (p));
}

Transformation  Vision_Normee (const Camera& p)
/* transformation de vision du livre */
{      
	Transformation	cu_cv = CU_a_CV(p); 
//	Transformation  sx = Homo_X (-1.0);       
	
	reel    x = (p.Pmax()+p.Pmin())/2.0;
	reel    y = (p.Hmax()+p.Hmin())/2.0;
	reel    z = p.DV() - p.DO();

	Transformation  cz = Cis_Z (vecteur (-x/z,-y/z,0.0));
	Transformation  hx = Homo_X (2.0/(p.Pmax()-p.Pmin()));
	Transformation  hy = Homo_Y (2.0/(p.Hmax()-p.Hmin()));
	Transformation  hz = Homo_Z (1.0/z);

//	return(cz * cu_cv);
	return(hz*hy*hx * cz * cu_cv);

}
