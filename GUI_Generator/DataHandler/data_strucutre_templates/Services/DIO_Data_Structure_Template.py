DIO_Data_Structure_Template = {
  "DIO_Service_Pins": {
    "metadata": {
      "type": "Services/DIO/DIO_Service_Pins",
      "mandatory": True,
      "deletable": False,
      "duplicable": False,
      "generate_params": False,
      "generate_data_count": True,
      "generate_data_data_files": True,
      "generate_data_data_files_data_type": "PinCfg_t",
      "generate_data_data_files_data_name": "PinCfg_data",
      "generate_data_data_files_init_func_postfix": "_INIT_FUNC"
    },
    "parameters": {
      "ShortName": {
        "value": "DIO_Service_Pins",
        "metadata": {
          "type": "string",
          "changeable": False
        }
      }
    },
    "data": {
      "DIO_Service_Pin": {
        "metadata": {
          "type": "Services/DIO/DIO_Service_Pins/data/DIO_Service_Pin",
          "mandatory": False,
          "leaf": True,
          "deletable": True,
          "duplicable": True,
          "generate_params": True
        },
        "parameters": {
          "ShortName": {
            "value": "DIO_Service_Pin",
            "metadata": {
              "type": "string",
              "changeable": True
            }
          },
          "PinType": {
            "value": "PIN_OUTPUT",
            "metadata": {
              "type": "selectable",
              "selectable_list": [
                "PIN_INPUT",
                "PIN_OUTPUT"
              ],
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
          "PinState": {
            "value": "PIN_LOW",
            "metadata": {
              "type": "selectable",
              "selectable_list": [
                "PIN_HIGH",
                "PIN_LOW"
              ],
              "changeable": True
            }
          }
        },
        "data": {
        }
      }
    }
  }
}