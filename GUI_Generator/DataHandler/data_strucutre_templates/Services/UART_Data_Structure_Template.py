UART_Data_Structure_Template = {
  "UART_Service_UARTs": {
    "metadata": {
      "type": "Services/UART/UART_Service_UARTs",
      "mandatory": True,
      "deletable": False,
      "duplicable": False,
      "generate_params": False,
      "generate_data_count": True,
      "generate_data_data_files": True,
      "generate_data_data_files_data_type": "UartHwCfg_t",
      "generate_data_data_files_data_name": "UartHwCfg_data",
      "generate_data_data_files_init_func_postfix": "_INIT_FUNC"
    },
    "parameters": {
      "ShortName": {
        "value": "UART_Service_UARTs",
        "metadata": {
          "type": "string",
          "changeable": False
        }
      }
    },
    "data": {
      "UART_Service_UART": {
        "metadata": {
          "type": "Services/UART/UART_Service_UARTs/data/UART_Service_UART",
          "mandatory": False,
          "leaf": True,
          "deletable": True,
          "duplicable": True,
          "generate_params": True
        },
        "parameters": {
          "ShortName": {
            "value": "UART_Service_UART",
            "metadata": {
              "type": "string",
              "changeable": True
            }
          },
          "Id": {
            "value": "0",
            "metadata": {
              "type": "int",
              "id": True,
              "changeable": False
            }
          },
          "Baud": {
            "value": "0",
            "metadata": {
              "type": "int",
              "changeable": True
            }
          },
          "UartTxBufferSize": {
            "value": "0",
            "metadata": {
              "type": "int",
              "changeable": True,
              "gen_buffer": True,
              "gen_buffer_var_name": "uartTxBuffer",
              "gen_buffer_size_var_name": "uartTxBufferSize"
            }
          },
          "UartRxBufferSize": {
            "value": "0",
            "metadata": {
              "type": "int",
              "changeable": True,
              "gen_buffer": True,
              "gen_buffer_var_name": "uartRxBuffer",
              "gen_buffer_size_var_name": "uartRxBufferSize"
            }
          }
        },
        "data": {}
      }
    }
  }
}