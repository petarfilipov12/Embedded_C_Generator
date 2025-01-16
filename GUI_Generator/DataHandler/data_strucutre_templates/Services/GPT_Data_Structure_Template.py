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
          "changeable": False
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
              "changeable": True
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
          "CompareValue": {
            "value": "0",
            "metadata": {
              "type": "int",
              "changeable": True
            }
          },
          "Prescaler": {
            "value": "0",
            "metadata": {
              "type": "int",
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