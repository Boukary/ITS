#ifndef INFRACTION_H
#define INFRACTION_H

#include <iostream>

typedef enum{
    INFRACTION_REDLIGHT,
    INFRACTION_STOPSIGN,
    INFRACTION_SPEED,
    INFRACTION_DIRECTION,
} InfractionType;

class Infraction
{
public:

    Infraction(InfractionType infraction_type);

    unsigned long long int GetIndexAbsolu();

    InfractionType GetInfractionType();

    unsigned long long int GetIdInfraction();

    void SetIndexAbsolu(unsigned long long int index_absolu);


private :

    static unsigned long long int nbr_tot_infraction_ ;

    unsigned long long int infraction_id_ ;

    InfractionType infraction_type_ ;

    unsigned long long int index_absolu_ ;

};

#endif // INFRACTION_H
