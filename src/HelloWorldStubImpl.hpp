#ifndef HELLOWORLDSTUBIMPL_H_
#define HELLOWORLDSTUBIMPL_H_
  
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/HelloWorldStubDefault.hpp>
  
class HelloWorldStubImpl: public v1::commonapi::HelloWorldStubDefault {//HelloWorldStubDefault클래스를 상속 받습니다. 
// HelloWorldStubDefault 클래스에 fidl로 설정한 함수들이 있어서 함수를 상속받으면 클라이언트에서 호출시 현재 클래스의 함수가 출력이 되도록 연결이 됩니다.
public:
    HelloWorldStubImpl();
    virtual ~HelloWorldStubImpl();
    virtual void sayHello(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, sayHelloReply_t _return);//sayHello라는 함수를 상속 받습니다.
 //함수 재정의를 할수 있도록 상속 받습니다.
};
 
#endif /* HELLOWORLDSTUBIMPL_H_ */

