#include "HelloWorldStubImpl.hpp"
 
HelloWorldStubImpl::HelloWorldStubImpl() { }
HelloWorldStubImpl::~HelloWorldStubImpl() { }
  
void HelloWorldStubImpl::sayHello(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, sayHelloReply_t _reply) {//상속받은 함수를 재정의 한다.
    std::stringstream messageStream;
    messageStream << "Hello " << _name << "!";
    std::cout << "sayHello('" << _name << "'): '" << messageStream.str() << "'\n";
 
    _reply(messageStream.str());//fidl에 정의한대로 문자열을 린턴하기 위해 매개변수에 넣어줌
};
 
