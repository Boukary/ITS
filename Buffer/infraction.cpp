#include "infraction.h"

using namespace std;

unsigned long long int Infraction::nbr_tot_infraction_ = 0;

Infraction::Infraction(InfractionType infraction_type)
{
    infraction_id_ = nbr_tot_infraction_++;
    infraction_type_ = infraction_type;
}

unsigned long long Infraction::GetIndexAbsolu()
{
    return index_absolu_;
}

InfractionType Infraction::GetInfractionType()
{
    return infraction_type_;
}

unsigned long long Infraction::GetIdInfraction()
{
    return infraction_id_;
}

void Infraction::SetIndexAbsolu(unsigned long long index_absolu)
{
    index_absolu_ = index_absolu;
}
