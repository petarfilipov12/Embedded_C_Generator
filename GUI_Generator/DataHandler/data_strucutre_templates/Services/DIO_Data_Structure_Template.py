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
          "changeable": False,
          "description": "Shortname for DIO_Service_Pins container"
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
              "changeable": True,
              "description": "Shortname for DIO_Service_Pin"
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
              "changeable": True,
              "description": "Initial type of DIO_Pin (Input/Output)"
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
          "PinState": {
            "value": "PIN_LOW",
            "metadata": {
              "type": "selectable",
              "selectable_list": [
                "PIN_HIGH",
                "PIN_LOW"
              ],
              "changeable": True,
              "description": "Initial state of DIO_Pin (High/Low). This parameter is ignored if PinType is PIN_INPUT"
            }
          }
        },
        "data": {
        }
      }
    }
  }
}