#ifndef MDK_OBJECT_IMPL_H_
#define MDK_OBJECT_IMPL_H_

#include "Smp/Exceptions.h"

#include <string>

namespace Smp 
{ 
    namespace Mdk
    {
        class ObjectImpl
        {
            public:
                ObjectImpl(void);
                ObjectImpl(
                        ::Smp::String8 name, ::Smp::String8 description)
                    throw (::Smp::InvalidObjectImplName);
                virtual ~ObjectImpl();

                virtual ::Smp::String8 GetName(void) const;
                virtual ::Smp::String8 GetDescription(void) const;

            private:
                ::std::string _name;
                ::std::string _description;
        };
    }
}

#endif  // MDK_OBJECT_IMPL_H_
