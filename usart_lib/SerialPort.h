/**
*********************************************************************
*********
* @project_name :write_demo
* @file : SerialPort.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/8/3
*********************************************************************
*********
*/
//

#ifndef SERIALPORT_H
#define SERIALPORT_H

#include "stream_lib/OutputStream.h"
#include "stream_lib/InputStream.h"
#include "usart.h"

#define UART_DMA_FLAG 0



namespace data_device {
    extern    uint8_t data_cache;
    class SerialPort: public OutputStream,public InputStream{
    private:
        UART_HandleTypeDef * uart_;

        inline void clean_tx_Buff(){
            memset(this->tx_Buff,0,256);
        }
    public:
        explicit SerialPort(UART_HandleTypeDef * uart);

        inline void begin_receive(){
            HAL_UART_Receive_IT(uart_,&data_cache,1);
        }

        inline void set_uart_ptr(UART_HandleTypeDef * set_ptr){
            uart_= set_ptr;
        }

        size_t write(uint8_t uint8) override;

        size_t write(const uint8_t *uint8, size_t size) override;
    };

} // data_device

#endif //SERIALPORT_H
