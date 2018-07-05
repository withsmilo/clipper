
#include <cxxopts.hpp>

#include <clipper/config.hpp>
#include <clipper/constants.hpp>

#include "management_frontend.hpp"

int main(int argc, char* argv[]) {
  cxxopts::Options options("management_frontend",
                           "Clipper management interface");

  // clang-format off
  options.add_options()
    ("redis_ip", "Redis address",
        cxxopts::value<std::string>()->default_value(clipper::DEFAULT_REDIS_ADDRESS))
    ("redis_port", "Redis port",
        cxxopts::value<int>()->default_value(std::to_string(clipper::DEFAULT_REDIS_PORT)))
    ("redis_pw", "Redis password",
        cxxopts::value<std::string>()->default_value(clipper::DEFAULT_REDIS_PW));
  // clang-format on
  options.parse(argc, argv);

  clipper::Config& conf = clipper::get_config();
  conf.set_redis_address(options["redis_ip"].as<std::string>());
  conf.set_redis_port(options["redis_port"].as<int>());
  conf.set_redis_pw(options["redis_pw"].as<std::string>());
  conf.ready();
  management::RequestHandler rh(clipper::MANAGEMENT_FRONTEND_PORT);
  rh.start_listening();
}
