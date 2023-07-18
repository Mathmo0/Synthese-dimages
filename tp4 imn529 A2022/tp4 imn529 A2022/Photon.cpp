#include "photon.h"
#include "SettingTracePhoton.h"



Photon::Photon( void )
{
    pos[0] = 0.;
    pos[1] = 0.;
    pos[2] = 0.;

    power[0] = 0.;
    power[1] = 0.;
    power[2] = 0.;
} 

Photon::Photon ( reel x, reel y, reel z, reel rouge, reel vert, reel bleu )
{
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;

    power[0] = rouge;
    power[1] = vert;
    power[2] = bleu;
}

Photon::~Photon( void )
{
}


point
Photon::position( void ) const
{
    return point( pos[0], pos[1], pos[2] );
}

Couleur
Photon::energie( void ) const
{
    return Couleur( power[0], power[1], power[2] );
}

vecteur
Photon::PhotonDir( void ) const
{
    return vecteur( sintheta[theta] * cosphi[phi],
                    sintheta[theta] * sinphi[phi],
                    costheta[theta] );
}