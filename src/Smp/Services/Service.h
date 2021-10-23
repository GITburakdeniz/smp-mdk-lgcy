#ifndef SMP_SERVICE_H
#define SMP_SERVICE_H

#include "Smp/IService.h"

namespace Smp {
namespace Services {

class Service: public IService {
public:
    
    Service();
    
    ~Service();
private:
};


} // end namespace Services
} // end namespace Smp

#endif // SMP_SERVICE_H