/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v201907221047.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_COMMONAPI_HELLO_WORLD_HPP_
#define V1_COMMONAPI_HELLO_WORLD_HPP_




#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Types.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace commonapi {

class HelloWorld {
public:
    virtual ~HelloWorld() { }

    static inline const char* getInterface();
    static inline CommonAPI::Version getInterfaceVersion();
};

const char* HelloWorld::getInterface() {
    return ("commonapi.HelloWorld:v1_0");
}

CommonAPI::Version HelloWorld::getInterfaceVersion() {
    return CommonAPI::Version(1, 0);
}


} // namespace commonapi
} // namespace v1

namespace CommonAPI {
}


// Compatibility
namespace v1_0 = v1;

#endif // V1_COMMONAPI_HELLO_WORLD_HPP_
