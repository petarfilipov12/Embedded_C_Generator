SPI_Data_Structure_Template = {
  "SPI_Service_SPIs": {
    "metadata": {
      "type": "Services/SPI/SPI_Service_SPIs",
      "mandatory": True,
      "deletable": False,
      "duplicable": False,
      "generate_params": False,
      "generate_data_count": True,
      "generate_data_data_files": True,
      "generate_data_data_files_data_type": "SpiCfg_t",
      "generate_data_data_files_data_name": "SpiHwCfg_data",
      "generate_data_data_files_init_func_postfix": "_INIT_FUNC"
    },
    "parameters": {
      "ShortName": {
        "value": "SPI_Service_SPIs",
        "metadata": {
          "type": "string",
          "changeable": False,
          "description": "Shortname for SPI_Service_SPIs container"
        }
      }
    },
    "data": {
      "SPI_Service_SPI": {
        "metadata": {
          "type": "Services/SPI/SPI_Service_SPIs/data/SPI_Service_SPI",
          "mandatory": False,
          "leaf": True,
          "deletable": True,
          "duplicable": True,
          "generate_params": True
        },
        "parameters": {
          "ShortName": {
            "value": "SPI_Service_SPI",
            "metadata": {
              "type": "string",
              "changeable": True,
              "description": "Shortname for SPI_Service_SPI"
            }
          },
          "Id": {
            "value": "0",
            "metadata": {
              "type": "int",
              "id": True,
              "changeable": False,
              "description": "Unique Id number"
            }
          },
          "SpiRxBufferSize": {
            "value": "0",
            "metadata": {
              "type": "int",
              "gen_buffer": True,
              "gen_buffer_var_name": "spiRxBuffer",
              "gen_buffer_size_var_name": "spiRxBufferSize",
              "changeable": True,
              "description": "Size of SPI Rx buffer in bytes. This parameter is relevant if SPI mode is SPI_MODE_SLAVE"
            }
          },
          "SpiMode": {
            "value": "SPI_MODE_MASTER",
            "metadata": {
              "type": "selectable",
              "selectable_list": [
                "SPI_MODE_MASTER",
                "SPI_MODE_SLAVE"
              ],
              "changeable": True,
              "description": "Mode of the SPI unit (Master/Slave)"
            }
          }
        },
        "data": {}
      }
    }
  }
}