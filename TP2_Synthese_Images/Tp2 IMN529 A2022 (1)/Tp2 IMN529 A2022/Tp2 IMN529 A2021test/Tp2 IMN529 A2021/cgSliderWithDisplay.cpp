//*******************************************************************
//*																	*
//* Programme: cgSliderWithDisplay.h										*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Implantation de slider avec l'affichage de la valeur		*
//*		permettant de choisir une valeur							*
//*		entière.													*
//*																	*
//*******************************************************************
#pragma warning(disable : 4996)

#include "cgSliderWithDisplay.h"
#include <stdlib.h> 
#include <assert.h>			//assert
#include <math.h>			//pow

#define HEIGHT 30

//+1 pour len est pour les chiffres negatifs
cgSliderWithDisplay::cgSliderWithDisplay(int left, int top, int width, double min, double max, int len, int nbdigit, int interespacement, double step, double value)
	: cgSlider(left,top,width,min,max,interespacement,step,value)
{
	assert(len > 0);

	//Modifie la largeur du controle pour ainsi avoir la bonne grandeur dans cgSlider
	m_nWidth += ((len+nbdigit+1)*8)+10;

	m_nLen = len;
	m_nDigit = nbdigit;
}

cgSliderWithDisplay::~cgSliderWithDisplay()
{
}

void cgSliderWithDisplay::OnDraw()
{
	cgSlider::OnDraw();

	//Dessine le rectangle contenant la valeur
	glColor3f(0,0,0);
	cgRectangle(x+w+5,y+3,m_nLeft+m_nWidth,m_nTop+m_nHeight-5);

	//On affiche le chiffre maintenant
	double v = GetValue();
	long n =(long) (v * pow(10.0,(int) m_nDigit));
	
	char c[20];
	itoa(n,c,10);
	char texte[20];

	//partie entiere
	unsigned int j = 0;
	if ( strlen(c) == m_nLen+m_nDigit )
	{
		for(; j < m_nLen; j++)
			texte[j] = c[j];
	}
	if ( m_nDigit > 0 )
	{
		//ajoute le point
		texte[j] = '.';

		//ajoute les decimales
		unsigned int k;
		for(k = 0; k < m_nDigit; k++)
			texte[j+1+k] = c[j+k];
		texte[j+1+k] = '\0';

		int l = 0;
		while (texte[l] != '\0')
		{
			if ( texte[l] == ' ' ) texte[l] = '0';
			l++;
		}
	}

	cgTexte(m_nLeft+w+8,m_nTop+17,texte);
}
