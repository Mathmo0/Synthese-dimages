#include "SettingTracePhoton.h"
#include "cmath"




float costheta[256]; 
float sintheta[256];
float cosphi[256];
float sinphi[256];


SettingTracePhoton::SettingTracePhoton( void ) 
{
    // initialize les tables de conversion de direction
    for ( int i = 0; i < 256; i++ )
    {
        double angle = double(i) * (1.0 / 256.0) * PI;
        costheta[i] = (float)cos( angle );
        sintheta[i] = (float)sin( angle );
        cosphi[i] = (float)cos( 2.0*angle );
        sinphi[i] = (float)sin( 2.0*angle );
    }

    
    //Variables des settings
	NbPhotonCaustique( NB_PHOTON_CAUSTIQUE );
    NbPhotonGlobal( NB_PHOTON_ILL_GLOBAL );

    m_CaustiqueMap = new PhotonMap( m_NbPhotonCaustique);
    m_GlobalMap = new PhotonMap( m_NbPhotonGlobal);
}



SettingTracePhoton::~SettingTracePhoton() 
{
    if ( m_CaustiqueMap )
    {
        delete m_CaustiqueMap;
        m_CaustiqueMap = 0;
    }
    
    if ( m_GlobalMap )
    {
        delete m_GlobalMap;
        m_GlobalMap = 0;
    }
}

void 
SettingTracePhoton::EmptyPhotonMaps( void )
{
    if ( m_CaustiqueMap )
    {
        delete m_CaustiqueMap;
        m_CaustiqueMap = new PhotonMap( m_NbPhotonCaustique );
    }
    
    if ( m_GlobalMap )
    {
        delete m_GlobalMap;
        m_GlobalMap = new PhotonMap( m_NbPhotonGlobal);
    }
}
