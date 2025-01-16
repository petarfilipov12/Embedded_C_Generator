OS_Data_Structure_Template = {
  "OS_Configuration": {
    "metadata": {
      "type": "Services/OS/OS_Configuration",
      "mandatory": True,
      "deletable": False,
      "duplicable": False,
      "leaf": True
    },
    "parameters": {
      "ShortName": {
        "value": "OS_Configuration",
        "metadata": {
          "type": "string",
          "changeable": False
        }
      },
      "CpuClock": {
        "value": "0",
        "metadata": {
          "type": "int",
          "changeable": True
        }
      }
    },
    "data": {}
  },
  "OS_Tasks": {
    "metadata": {
      "type": "Services/OS/OS_Tasks",
      "mandatory": True,
      "deletable": False,
      "duplicable": False
    },
    "parameters": {
      "ShortName": {
        "value": "OS_Tasks",
        "metadata": {
          "type": "string",
          "changeable": False
        }
      }
    },
    "data": {
      "OS_Task": {
        "metadata": {
          "type": "Services/OS/OS_Tasks/data/OS_Task",
          "mandatory": False,
          "leaf": True,
          "deletable": True,
          "duplicable": True
        },
        "parameters": {
          "ShortName": {
            "value": "OS_Task",
            "metadata": {
              "type": "string",
              "changeable": True
            }
          },
          "Priority": {
            "value": "0",
            "metadata": {
              "type": "int",
              "changeable": True
            }
          },
          "Cycle": {
            "value": "0",
            "metadata": {
              "type": "int",
              "changeable": True
            }
          },
          "InitRunnables": {
            "value": [],
            "metadata": {
              "type": "reference_list",
              "reference_targets": [
                "SWCs/Components/Runnables/value/Runnable_Name/value"
              ],
              "reference_target_keys": "Runnables/*/Runnable_Name",
              "changeable": True
            }
          },
          "CyclicRunnables": {
            "value": [],
            "metadata": {
              "type": "reference_list",
              "reference_targets": [
                "SWCs/Components/Runnables/value/Runnable_Name/value"
              ],
              "reference_target_keys": "Runnables/*/Runnable_Name",
              "changeable": True
            }
          },
          "StackSize": {
            "value": "0",
            "metadata": {
              "type": "int",
              "changeable": True
            }
          }
        },
        "data": {}
      }
    }
  }
}