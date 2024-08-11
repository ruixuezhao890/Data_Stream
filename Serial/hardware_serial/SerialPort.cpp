/**
*********************************************************************
*********
* @project_name :write_demo
* @file : SerialPort.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/8/3
*********************************************************************
*********
*/
//

#include "SerialPort.h"


namespace data_device {
    uint8_t data_cache;

    SerialPort::SerialPort(UART_HandleTypeDef *uart):uart_(uart) {
#if UART_DMA_FLAG

#else
            HAL_UART_Receive_IT(uart_,&data_cache,1);
#endif

    }

    size_t SerialPort::write(uint8_t uint8) {
#if UART_DMA_FLAG
        HAL_UART_Transmit_DMA()
#else
        HAL_UART_Transmit(uart_,&uint8,1,HAL_MAX_DELAY);

        clean_tx_Buff();

#endif
        return 1;
    }

    size_t SerialPort::write(const uint8_t *uint8, size_t size) {
        if (!uint8||size==0){
            return -1;
        }
        auto status=HAL_OK;
#if UART_DMA_FLAG
        HAL_UART_Transmit_DMA()
#else
        status=HAL_UART_Transmit(uart_,uint8,size,HAL_MAX_DELAY);
#endif
        if (status==HAL_OK){
            clean_tx_Buff();
        }
        return size;
    }

} // data_device

extern "C"{
    void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
        if (huart->Instance==USART1){
            if (buf.data_size>256) return;
            buf.buf[buf.write_index++]=data_device::data_cache;
            buf.data_size++;

        }
    #if UART_DMA_FLAG

    #else
        HAL_UART_Receive_IT(huart,&data_device::data_cache,1);
    #endif
    }
}