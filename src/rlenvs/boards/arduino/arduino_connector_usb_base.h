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
            std::string send_cmd(const ArduinoCMDBase& cmd) override;

            ///
            /// @return The port id
            int_t port_id()const noexcept{return port_id_;}

            ///
            /// @return Trur is the port is open
            bool is_port_open()const noexcept{return port_id_ > 0;}

        protected:

            ///
            /// \brief Opens the port
            ///
            virtual void open_port_();

            ///
            /// \brief Configure the serial port
            ///
            virtual void configure_port_();

            void set_port_id_(int_t port_id)noexcept{port_id_ = port_id;}

        private:

            std::string port_name_;
            int_t port_id_{-1};


        };

    }
}
#endif //ARDUINO_ENV_USB_BASE_H
