#ifndef MDK_OBJECT_H_
#define MDK_OBJECT_H_

#include "Smp/IObject.h"
#include "Smp/Exceptions.h"
#include "Mdk/ObjectImpl.h"

namespace Smp 
{ 
    namespace Mdk
    {
        class Object :
            public virtual Smp::IObject
        {
            public:
                Object(void);
                Object(
                        ::Smp::String8 name, ::Smp::String8 description)
                    throw (::Smp::InvalidObjectName);
                virtual ~Object();

                virtual ::Smp::String8 GetName(void) const;
                virtual ::Smp::String8 GetDescription(void) const;

            private:
                ObjectImpl* _impl;
        };
    }
}

#endif  // MDK_OBJECT_H_
