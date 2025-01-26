WDT_Data_Structure_Template = {
  "WDT_Service_WDTs": {
    "metadata": {
      "type": "Services/WDT/WDT_Service_WDTs",
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
        "value": "WDT_Service_WDTs",
        "metadata": {
          "type": "string",
          "changeable": False,
          "description": "Shortname for WDT_Service_WDTs container"
        }
      }
    },
    "data": {
      "WDT_Service_WDT": {
        "metadata": {
          "type": "Services/WDT/WDT_Service_WDTs/data/WDT_Service_WDT",
          "mandatory": False,
          "leaf": True,
          "deletable": True,
          "duplicable": True,
          "generate_params": True
        },
        "parameters": {
          "ShortName": {
            "value": "WDT_Service_WDT",
            "metadata": {
              "type": "string",
              "changeable": True,
              "description": "Shortname for WDT_Service_WDT"
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