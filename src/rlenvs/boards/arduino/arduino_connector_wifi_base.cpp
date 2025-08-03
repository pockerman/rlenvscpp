//
// Created by alex on 8/2/25.
//

#include "rlenvs/boards/arduino/arduino_connector_wifi_base.h"
#include "rlenvs/extern/nlohmann/json/json.hpp"
#include "rlenvs/extern/HTTPRequest.hpp"


#include <string>

namespace rlenvscpp
{
    namespace boards::arduino
    {
        ArduinoConnectorWIFIBase::ArduinoConnectorWIFIBase(const std::string& arduino_url)
            :
        ArduinoConnectorBase(),
        arduino_url_(arduino_url)
        {}

        void
        ArduinoConnectorWIFIBase::connect()
        {}

        void
        ArduinoConnectorWIFIBase::close_connection()
        {}

        std::string
       ArduinoConnectorWIFIBase::send_cmd(const ArduinoCMDBase& cmd)
        {
            http::Request request{arduino_url_};
            std::string body_str = cmd.get_cmd();

            const http::Response response = request.send("POST", body_str);
            auto str_response = std::string(response.body.begin(), response.body.end());
            return str_response;
        }


    }
}

