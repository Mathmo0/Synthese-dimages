//*******************************************************************

//*																	*

//* Programme: DisplayOpenGL.cpp									*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Classe permettant de faire l'affichage des primitives.		*

//*																	*

//*******************************************************************



#include "DisplayOpenGL.h"

#include "glut.h"



Display::Display() 

{

}



Display::~Display()

{

}



void Display::InitDisplay()

{

	glFrontFace(GL_CCW);

	glClearColor(0,0,0,1);



	glEnable(GL_DEPTH_TEST);	//Z-Buffer

	glDepthFunc(GL_LEQUAL);		//Pour afficher les sélections par dessus de la scène

	glEnable(GL_NORMALIZE);		//Normalise les vecteurs normaux

}



void Display::SetupCamera(Camera* pCamera)

{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	Gouraud(Settings()->Gouraud());

	CullingFace(Settings()->CullFace());



	point pr(pCamera->PR());

	vecteur vh(pCamera->VH());

	point po(pCamera->PO());

	double Dh = pCamera->DH();

	double Do = pCamera->DO();



	//Il ne faut pas que le plan soit en arriere de l'observateur

	if ( Dh < Do ) Dh = Do + 0.001;



	double z_m = Dh-Do;

	double z_M = pCamera->DY()-Do;



	vecteur n = pCamera->VN();

	n.normalise();



	double proportion = z_m/(pCamera->DV()-Do);

	double left = proportion * pCamera->Pmin();

	double right = proportion * pCamera->Pmax();

	double top = proportion * pCamera->Hmax();

	double bottom = proportion * pCamera->Hmin();

	double nnear = z_m;

	double nfar = z_M;



	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	if ( pCamera->perspective() )

	{

		glFrustum(left,right,bottom,top,nnear,nfar); 



		glMatrixMode( GL_MODELVIEW );

		glLoadIdentity();



		gluLookAt(	po.x(), po.y(), po.z(), 

					po.x()+n.x(), po.y()+n.y(), po.z()+n.z(), 

					vh.x(), vh.y(), vh.z() );

	}

	else

	{

		glOrtho(pCamera->Pmin(),pCamera->Pmax(),pCamera->Hmin(),pCamera->Hmax(),pCamera->DH(),pCamera->DY());



		glMatrixMode( GL_MODELVIEW );

		glLoadIdentity();



		gluLookAt(	pr.x(), pr.y(), pr.z(), 

					pr.x()+n.x(), pr.y()+n.y(), pr.z()+n.z(), 

					vh.x(), vh.y(), vh.z() );

	}

}



void Display::SetupLighting(Camera* pCamera)

{

	if ( pCamera->AvecLumiere() && pCamera->LumiereActiveScene() && Settings()->PolygoneRemplit() )

	{

		glEnable(GL_LIGHTING);



		GLfloat lmodel_ambient[] = { 0, 0, 0, 1 };

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);



		int nbLum = pCamera->NbLumiere();

		for(int i = 0; i < nbLum ; i++)

		{

			const Lumiere* Lum = pCamera->GetLumiere(i);

			if ( Lum->Active() )

			{

				point p2 = Lum->Position();

				GLfloat lightPos[] = { GLfloat(p2.x()),GLfloat(p2.y()),GLfloat(p2.z()), GLfloat(1.0)};



				Couleur ambiante = Lum->IntensiteAmbiante();

				float ambientLight[] = {float(ambiante.rouge()), float(ambiante.vert()), float(ambiante.bleu()), 1.0f};

				Couleur diffuse = Lum->Intensite();

				float diffuseLight[] = {float(diffuse.rouge()), float(diffuse.vert()), float(diffuse.bleu()), 1.0f};



				glLightfv(GL_LIGHT0+i,GL_AMBIENT,ambientLight);

				glLightfv(GL_LIGHT0+i,GL_DIFFUSE,diffuseLight);

				glLightfv(GL_LIGHT0+i,GL_SPECULAR,diffuseLight);

				glLightfv(GL_LIGHT0+i,GL_POSITION,lightPos);

				

				glEnable(GL_LIGHT0+i);

			}

			else

				glDisable(GL_LIGHT0+i);

		}



		glEnable(GL_COLOR_MATERIAL);

		glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);



		//Set l'exposant de Phong pour le speculaire

		glMateriali(GL_FRONT_AND_BACK,GL_SHININESS, Settings()->ExposantPhong());

	}

	else

		glDisable(GL_LIGHTING);

}



void Display::OnChangeSize(int w, int h)

{

	glViewport(0, 0, h, h); 

}



//----------------------------------------------------------------

//

//Gestion des differents settings d'opengl

//

//----------------------------------------------------------------

void Display::GrosseurTrait(int grosseur)

{

	glLineWidth(grosseur);

}



int Display::GrosseurTrait()

{

	float ancienne[2];

	glGetFloatv(GL_LINE_WIDTH,ancienne );

	return ancienne[0];

}



void Display::Pointille(short pattern, int facteur)

{

	glEnable(GL_LINE_STIPPLE);

	glLineStipple(facteur,pattern);

}



void Display::DesactivePointille()

{

	glDisable(GL_LINE_STIPPLE);

}



void Display::Gouraud(booleen g)

{

	if ( g ) 

		glShadeModel(GL_SMOOTH); 

	else 

		glShadeModel(GL_FLAT); 
}



void Display::CullingFace(booleen c)

{

	if ( c ) 

		glEnable(GL_CULL_FACE); 

	else 

		glDisable(GL_CULL_FACE); 

}



void Display::Speculaire(const Couleur& c)

{

	float v[4] = { float(c.rouge()), float(c.vert()), float(c.bleu()), 1.0f };

	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,v);

}



void Display::Diffus(const Attributs& a)

{

	if ( a.highlight() )

	{

		if ( a.highlight() == OBJET_SELECTION )

			glColor3f(1.0, 0.0, 0.0);

		else

			glColor3f(1.0, 1.0, 0.0);

	}

	else

	{

		Couleur d = a.diffus();

		glColor3f(d.rouge(),d.vert(),d.bleu());

	}

}



void Display::ContourPolygone()

{

	Couleur c = Settings()->CouleurContourPolygone().diffus();

	glColor3f(c.rouge(), c.vert(), c.bleu());

}



//----------------------------------------------------------------

//

//Affichage des primitives dans la fenetre pour dessinner

//

//----------------------------------------------------------------

void Display::Ligne (double x1, double y1, double x2, double y2, const Attributs& a)

{

	unsigned char light;

	glGetBooleanv(GL_LIGHTING,&light);

	glDisable(GL_LIGHTING);



	Diffus(a);

	glBegin(GL_LINES);

		glVertex2f(x1,y1);

		glVertex2f(x2,y2);

	glEnd();



	if ( light )

		glEnable(GL_LIGHTING);

}



void Display::Ligne (double x1, double y1, double z1, double x2, double y2, double z2, const Attributs& a)

{

	unsigned char light;

	glGetBooleanv(GL_LIGHTING,&light);

	glDisable(GL_LIGHTING);



	Diffus(a);

	glBegin(GL_LINES);

		glVertex3f(x1,y1,z1);

		glVertex3f(x2,y2,z2);

	glEnd();

	

	if ( light )

		glEnable(GL_LIGHTING);

}



void Display::Polygone (int n, double x[], double y[], const Attributs& a)

{

	Diffus(a);

	Speculaire(a.speculaire());

	if ( Settings()->PolygoneRemplit() && !a.highlight() ) 

	{

		//Affiche filled

		glBegin(GL_POLYGON);

		for(int i = 0; i < n; i++)

			glVertex2f(x[i], y[i]);

		glEnd();



		//Affiche le contour

		if ( Settings()->ContourPolygone() ) 

		{

			unsigned char light;

			glGetBooleanv(GL_LIGHTING,&light);

			glDisable(GL_LIGHTING);



			ContourPolygone();

			glBegin(GL_LINE_LOOP);

			for(int i = 0; i < n; i++)

				glVertex2f(x[i], y[i]);

			glEnd();



			if ( light )

				glEnable(GL_LIGHTING);

		}

	}

	else

	{

		unsigned char light;

		glGetBooleanv(GL_LIGHTING,&light);

		glDisable(GL_LIGHTING);



		//Affiche en wireframe

		glBegin(GL_LINE_LOOP);

		for(int i = 0; i < n; i++)

			glVertex2f(x[i], y[i]);

		glEnd();



		if ( light )

			glEnable(GL_LIGHTING);

	}

}



void Display::Polygone (int n, double x[], double y[], double z[], const Attributs& a)

{

	Diffus(a);

	Speculaire(a.speculaire());

	if ( Settings()->PolygoneRemplit() && !a.highlight() ) 

	{

		//Affiche filled

		glBegin(GL_POLYGON);

		for(int i = 0; i < n; i++)

			glVertex3f(x[i], y[i], z[i]);

		glEnd();



		//Affiche le contour

		if ( Settings()->ContourPolygone() ) 

		{

			unsigned char light;

			glGetBooleanv(GL_LIGHTING,&light);

			glDisable(GL_LIGHTING);



			ContourPolygone();

			glBegin(GL_LINE_LOOP);

			for(int i = 0; i < n; i++)

				glVertex3f(x[i], y[i], z[i]);

			glEnd();



			if ( light )

				glEnable(GL_LIGHTING);

		}

	}

	else

	{

		unsigned char light;

		glGetBooleanv(GL_LIGHTING,&light);

		glDisable(GL_LIGHTING);



		//Affiche en wireframe

		glBegin(GL_LINE_LOOP);

		for(int i = 0; i < n; i++)

			glVertex3f(x[i], y[i], z[i]);

		glEnd();



		if ( light )

			glEnable(GL_LIGHTING);

	}

}



void Display::Polygone(

			int n, 

			double x[], double y[], double z[],

			double nx[], double ny[], double nz[],

			const Attributs& a)

{

	Diffus(a);

	Speculaire(a.speculaire());

	if ( Settings()->PolygoneRemplit() && !a.highlight() ) 

	{

		//Affiche filled

		glBegin(GL_POLYGON);

		for(int i = 0; i < n; i++)

		{

			glNormal3f(nx[i],ny[i],nz[i]);

			glVertex3f(x[i], y[i], z[i]);

		}

		glEnd();



		//Affiche le contour

		if ( Settings()->ContourPolygone() ) 

		{

			unsigned char light;

			glGetBooleanv(GL_LIGHTING,&light);

			glDisable(GL_LIGHTING);

			

			ContourPolygone();

			glBegin(GL_LINE_LOOP);

			for(int i = 0; i < n; i++)

				glVertex3f(x[i], y[i], z[i]);

			glEnd();



			if ( light )

				glEnable(GL_LIGHTING);

		}

	}

	else

	{

		unsigned char light;

		glGetBooleanv(GL_LIGHTING,&light);

		glDisable(GL_LIGHTING);



		//Affiche en wireframe

		glBegin(GL_LINE_LOOP);

		for(int i = 0; i < n; i++)

			glVertex3f(x[i], y[i], z[i]);

		glEnd();



		if ( light )

			glEnable(GL_LIGHTING);

	}

}
