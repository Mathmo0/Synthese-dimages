//*******************************************************************

//*																	*

//* Programme: cgLabel.cpp											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation d'étiquettes. Les étiquettes sont simplement	*

//*		la représentation graphique de textes.						*

//*																	*

//*******************************************************************



#include "cgLabel.h"



cgLabel::cgLabel(int left, int top, cgcString texte, booleen transparent)

	: cgControl(left,top,texte.Len()*8,13)

{

	x = left;

	y = top;

	h = 13;				//heuteur de la police

	w = texte.Len()*8;	//longueur du texte * 8 qui est la longueur d'un caractere

	

	m_texte = texte;

	

	Transparent(transparent);

}



cgLabel::~cgLabel()

{

}



cgcString cgLabel::GetCaption()

{

	return m_texte;

}



void cgLabel::SetCaption(cgcString texte)

{

	m_texte = texte;

}



void cgLabel::OnDraw()

{

	//Rempli le fond si le fond n'est pas transparent

	if ( !Transparent() )

	{

		glColor3f(0.75,0.75,0.75);

		glRecti(x,y,x+w,y+h);

	}



	//Affichage du texte

	glColor3f(0,0,0);

	cgTexte(x,y,m_texte);

}

