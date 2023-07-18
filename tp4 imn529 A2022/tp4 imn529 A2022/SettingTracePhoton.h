#ifndef _SETTINGTRACEPHOTON

#define _SETTINGTRACEPHOTON


#include "PhotonMap.h"
#include "Definition.h"
#include "Attr.h"


#define NB_PHOTON_CAUSTIQUE     100000
#define NB_PHOTON_ILL_GLOBAL    0




extern float costheta[256];
extern float sintheta[256];
extern float cosphi[256];
extern float sinphi[256];


class SettingTracePhoton
{

protected:


	entier	m_NbPhotonCaustique;	    // indique le nombre de photons pour calculer les caustiques
    entier  m_NbPhotonGlobal;           // indique le nombre de photons pour calculer l'illumination global

    PhotonMap* m_CaustiqueMap;         // photon map pour les caustiques
    PhotonMap* m_GlobalMap;            // photon map pour l'illumination global


public:

	SettingTracePhoton();
	~SettingTracePhoton();


    void EmptyPhotonMaps( void );


	entier NbPhotonCaustique( void )		{ return m_NbPhotonCaustique; }
	entier NbPhotonGlobal( void )		    { return m_NbPhotonGlobal; }

	void NbPhotonCaustique( entier n )		{ m_NbPhotonCaustique = n; }
	void NbPhotonGlobal( entier n )		    { m_NbPhotonGlobal = n; }

    bool CaustiqueMapEmpty( void )          { return m_CaustiqueMap->Empty(); }
    bool GlobalMapEmpty( void )             { return m_GlobalMap->Empty(); }


    PhotonMap* PhotonMapCaustique( void )   { return m_CaustiqueMap; }
    PhotonMap* PhotonMapGlobal( void )      { return m_GlobalMap; }
};



#endif

