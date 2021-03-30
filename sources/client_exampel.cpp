// Copyright 2021 lamp

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <cstdlib>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;



int main(int argc, char** argv) {
  try {
    if (argc != 4) {
      std::cerr << "Usage: client <host> <port> <input>\n"
                << "Example:\n"
                << "    client 127.0.0.1 80\n"
                << "    client 127.0.0.1 80\n";
      return EXIT_FAILURE;
    }
    auto const host = argv[1];
    auto const port = argv[2];
    auto const target = "v1/api/suggest";
    int version = 11;
    auto const input = argv[3];

    net::io_context ioc;

    tcp::resolver resolver(ioc);
    beast::tcp_stream stream(ioc);

    auto const results = resolver.resolve(host, port);

    stream.connect(results);

    http::request<http::string_body> req{http::verb::post, target, version};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    json j;
    j["input"] = input;
    req.body() = j.dump();

    http::write(stream, req);

    beast::flat_buffer buffer;

    http::response<http::string_body> res;

    http::read(stream, buffer, res);

    std::cout << res << std::endl;

    beast::error_code ec;
    stream.socket().shutdown(tcp::socket::shutdown_both, ec);

    if (ec && ec != beast::errc::not_connected) throw beast::system_error{ec};

  } catch (std::exception const& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
