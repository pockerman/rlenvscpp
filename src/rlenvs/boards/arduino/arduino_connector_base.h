//
// Created by alex on 8/2/25.
//

#ifndef ARDUINO_ENV_BASE_H
#define ARDUINO_ENV_BASE_H

#include "rlenvs/rlenvs_consts.h"
#include "rlenvs/rlenvs_types_v2.h"

#include <string>

namespace rlenvscpp
{
    namespace boards::arduino
    {

        struct ArduinoCMDBase
        {

            ArduinoCMDBase() =default;
            virtual ~ArduinoCMDBase() =default;
            virtual std::string get_cmd()const=0;
        };

        class ArduinoConnectorBase
        {
        public:
            ///
            /// \brief Destructor
            ///
            virtual ~ArduinoConnectorBase() =default;

            ///
            /// \brief Connect to the Arduino board
            ///
            virtual void connect()=0;

            ///
            /// \brief Close the connection
            ///
            virtual void close_connection()=0;

            ///
            /// \brief Send the command
            ///
            virtual std::string send_cmd(const ArduinoCMDBase& cmd)=0;



        protected:

            ///
            /// \brief Constructor
            ///
            ArduinoConnectorBase()=default;
        };

    }
}

#endif //ARDUINO_ENV_BASE_H
