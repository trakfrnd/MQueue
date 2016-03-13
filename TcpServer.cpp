#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>

#include <arpa/inet.h>

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <errno.h>
#include "Message.h"
#include "ThreadPool.h"

class TcpServer {
public:
	TcpServer(int port):
		port(port),
		base(event_base_new(), &event_base_free),
		listener(nullptr, &evconnlistener_free) {

	}

private:
	int port;
	std::unique_ptr<event_base, decltype(&event_base_free)> base;
	std::unique_ptr<evconnlistener, decltype(&evconnlistener_free)> listener;
	sockaddr_in sin;

	bool checkPort() {
		if (port<=0 || port>65535) {
            std::cout << "Erorr opening event base";
            return false;
        }
        return true;
	}

	bool initSocket() {
        memset(&sin, 0, sizeof(sin));
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = htonl(0);
        sin.sin_port = htons(port);		
        std::cout << "Erorr opening event base";
	}


	static void readMessage(struct bufferevent *bev, void *ctx)
	{
        char buffer[1024];
        struct evbuffer *input = bufferevent_get_input(bev);
        evbuffer_copyout(input, (void *)buffer, 1024);
        std::cout << "Input " << buffer;
        ThreadPool::getThreadPool()->enqueue(new Message(buffer));
	}

	static void acceptConnection(struct evconnlistener *listener, evutil_socket_t fd,
		struct sockaddr *address, int socklen, void *ctx)
	{
        struct event_base *base = evconnlistener_get_base(listener);
        struct bufferevent *bev = bufferevent_socket_new(
                base, fd, BEV_OPT_CLOSE_ON_FREE);

        bufferevent_setcb(bev, readMessage, NULL, NULL, NULL);
        bufferevent_enable(bev, EV_READ|EV_WRITE);

	}

public:
	bool createListener() {
		if(!checkPort()) {
			return false;
		}

		initSocket();
		listener.reset(evconnlistener_new_bind(base.get(), acceptConnection, NULL,
            LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE, -1,
            (struct sockaddr*)&sin, sizeof(sin)));

        if (!listener) {
                perror("Couldn't create listener");
                return 1;
        }
        event_base_dispatch(base.get());
	}
};

int main()
{
  std::unique_ptr<TcpServer> server(new TcpServer(2222));
  server->createListener();
  return 0;
}
