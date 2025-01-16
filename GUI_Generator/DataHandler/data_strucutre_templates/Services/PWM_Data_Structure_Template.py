PWM_Data_Structure_Template = {
  "PWM_Service_Pins": {
    "metadata": {
      "type": "Services/PWM/PWM_Service_Pins",
      "mandatory": True,
      "deletable": False,
      "duplicable": False,
      "generate_params": False,
      "generate_data_count": True,
      "generate_data_data_files": True,
      "generate_data_data_files_data_name": "PwmCfg_data",
      "generate_data_data_files_data_type": "PwmCfg_t",
      "generate_data_data_files_init_func_postfix": "_INIT_FUNC"
    },
    "parameters": {
      "ShortName": {
        "value": "PWM_Service_Pins",
        "metadata": {
          "type": "string",
          "changeable": False
        }
      }
    },
    "data": {
      "PWM_Service_Pin": {
        "metadata": {
          "type": "Services/PWM/PWM_Service_Pins/data/PWM_Service_Pin",
          "mandatory": False,
          "leaf": True,
          "deletable": True,
          "duplicable": True,
          "generate_params": True
        },
        "parameters": {
          "ShortName": {
            "value": "PWM_Service_Pin",
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
          "GptTimerRef": {
            "value": "",
            "metadata": {
              "type": "reference",
              "reference_targets": [
                "Services/GPT/GPT_Service_GPTs"
              ],
              "changeable": True
            }
          }
        },
        "data": {}
      }
    }
  }
}