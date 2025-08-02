//
// Created by alex on 8/2/25.
//

#ifndef ARDUINO_ENV_USB_BASE_H
#define ARDUINO_ENV_USB_BASE_H

#include "rlenvs/boards/arduino/arduino_connector_base.h"



namespace rlenvscpp
{
    namespace boards::arduino
    {
        class ArduinoConnectorUSBBase: public ArduinoConnectorBase
        {
        public:

            ///
            /// \brief The base type
            ///
            typedef ArduinoConnectorBase base_type;

            /// Constructor
            /// @param port
            /// @param cidx
            /// @param name
            ArduinoConnectorUSBBase(const std::string& port);

            ///
            /// @return string representing the port name
            std::string port_name()const noexcept{return port_name_;}

            ///
            /// \brief Connect to the Arduino board
            ///
            void connect() override;

            ///
            /// \brief Close the connection
            ///
            virtual void close_connection()override;

            ///
            /// \brief Send the command
            ///
            void send_cmd(const ArduinoCMDBase& cmd) override;

        protected:

            ///
            /// \brief Opens the port
            ///
            virtual void open_port_();

            ///
            /// \brief Configure the serial port
            ///
            virtual void configure_port_();

        private:

            std::string port_name_;


        };

    }
}
#endif //ARDUINO_ENV_USB_BASE_H
