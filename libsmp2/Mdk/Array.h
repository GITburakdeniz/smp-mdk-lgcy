/** This file is part of smp-mdk
 *
 * Copyright (C) 2018 Juan R. Garcia Blanco
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MDK_ARRAY_H_
#define MDK_ARRAY_H_

#include "Smp/SimpleTypes.h"

#include <cstring>

namespace Smp
{
    namespace Mdk
    {
        template< class T, int size>
        struct Array
        {
            T internalArray[size];

            Array(void)
                {
                    ::memset(this->internalArray, 0, size);
                }

            inline const T& operator[] (long index) const
                {
                    return this->internalArray[index];
                }

            inline T& operator[] (long index)
                {
                    return this->internalArray[index];
                }

            inline T* operator& (void)
                {
                    return this->internalArray;
                }
        };
    }
}

#endif  // MDK_ARRAY_H_
