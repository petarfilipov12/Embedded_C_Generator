GPT_Data_Structure_Template = {
  "GPT_Service_GPTs": {
    "metadata": {
      "type": "Services/GPT/GPT_Service_GPTs",
      "mandatory": True,
      "deletable": False,
      "duplicable": False,
      "generate_params": False,
      "generate_data_count": True,
      "generate_data_data_files": True,
      "generate_data_data_files_data_name": "GptCfg_data",
      "generate_data_data_files_data_type": "GptCfg_t",
      "generate_data_data_files_init_func_postfix": "_INIT_FUNC"
    },
    "parameters": {
      "ShortName": {
        "value": "GPT_Service_GPTs",
        "metadata": {
          "type": "string",
          "changeable": False,
          "description": "Shortname for GPT_Service_GPTs container"
        }
      }
    },
    "data": {
      "GPT_Service_GPT": {
        "metadata": {
          "type": "Services/GPT/GPT_Service_GPTs/data/GPT_Service_GPT",
          "mandatory": False,
          "leaf": True,
          "deletable": True,
          "duplicable": True,
          "generate_params": True
        },
        "parameters": {
          "ShortName": {
            "value": "GPT_Service_GPT",
            "metadata": {
              "type": "string",
              "changeable": True,
              "description": "Shortname for GPT_Service_GPT unit"
            }
          },
          "GptMode": {
            "value": "GPT_MODE_NORMAL",
            "metadata": {
              "type": "selectable",
              "selectable_list": [
                "GPT_MODE_PWM",
                "GPT_MODE_NORMAL"
              ],
              "changeable": True,
              "description": "Mode of the GPT_Service_GPT unit.\nNORMAL - regular timer functionality.\nPWM - pulse width modulation functionality"
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
          "CompareValue": {
            "value": "0",
            "metadata": {
              "type": "int",
              "changeable": True,
              "description": "Value ot which the timer resets and registers 1 tick"
            }
          },
          "Prescaler": {
            "value": "0",
            "metadata": {
              "type": "int",
              "changeable": True,
              "description": "Value by witch the timer frequency is divided, effectively slowing down the tick count."
            }
          }
        },
        "data": {
        }
      }
    }
  }
}