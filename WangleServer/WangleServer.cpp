﻿// WangleTest.cpp : Defines the entry point for the application.
//

#include "WangleServer.h"
#include <folly/portability/GFlags.h>
#include <wangle/bootstrap/ServerBootstrap.h>
#include <wangle/channel/AsyncSocketHandler.h>
#include <wangle/codec/LineBasedFrameDecoder.h>
#include <wangle/codec/StringCodec.h>

using namespace folly;
using namespace wangle;

using namespace std;

DEFINE_int32(port, 8888, "echo server port");
typedef Pipeline<IOBufQueue&, std::string> EchoPipeline;

	class EchoHandler :public HandlerAdapter<std::string> {
	public:
		virtual void read(Context* ctx, std::string msg) override {
			std::cout << "handling " << msg << std::endl;
			write(ctx, msg + "\r\n");
		}
	};
	class EchoPipelineFactory : public PipelineFactory<EchoPipeline> {
	public:
		EchoPipeline::Ptr newPipeline(std::shared_ptr<AsyncTransportWrapper> sock) {
			auto pipeline = EchoPipeline::create();
			pipeline->addBack(AsyncSocketHandler(sock));
			pipeline->addBack(LineBasedFrameDecoder(8192));
			pipeline->addBack(StringCodec());
			pipeline->addBack(EchoHandler());
			pipeline->finalize();
			return pipeline;
		}
	};

int main(int argc, char** argv)
	{
	gflags::ParseCommandLineFlags(&argc, &argv, true);
	ServerBootstrap<EchoPipeline> server;
	server.childPipeline(std::make_shared<EchoPipelineFactory>());
	server.bind(FLAGS_port);
	server.waitForStop();
	return 0;
	}
