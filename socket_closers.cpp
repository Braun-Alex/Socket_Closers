#include <memory>
#include <functional>
#include <windows.h>
class functor_based_deleter
{
public:
void operator()(SOCKET* the_socket)
{
closesocket(*the_socket);
}
};
void pointer_based_deleter(SOCKET* the_socket)
{
closesocket(*the_socket);
}
int main()
{
std::function<void(SOCKET*)> function_based_deleter=[](SOCKET* the_socket)
{
closesocket(*the_socket);
};
SOCKET the_first_socket=socket(3,3,3),
       the_second_socket=socket(11,11,11),
       the_thirst_socket=socket(33,33,33);
if (the_first_socket!=INVALID_SOCKET)
std::unique_ptr<SOCKET,functor_based_deleter>
        the_first_pointer(&the_first_socket);
if (the_second_socket!=INVALID_SOCKET)
std::unique_ptr<SOCKET,void(*)(SOCKET*)>
        the_second_pointer(&the_second_socket,pointer_based_deleter);
if (the_thirst_socket!=INVALID_SOCKET)
std::unique_ptr<SOCKET,decltype(function_based_deleter)>
        the_thirst_pointer(&the_thirst_socket,function_based_deleter);
return 0;
}