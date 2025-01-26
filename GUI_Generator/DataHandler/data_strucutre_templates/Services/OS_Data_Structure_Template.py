OS_Data_Structure_Template = {
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
          "changeable": False,
          "description": "Shortname for OS_Tasks container"
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
              "changeable": True,
              "description": "Shortname for OS_Task"
            }
          },
          "Priority": {
            "value": "0",
            "metadata": {
              "type": "int",
              "changeable": True,
              "description": "Priority number of the task. Tasks with higher priority number are prioritized."
            }
          },
          "Cycle": {
            "value": "0",
            "metadata": {
              "type": "int",
              "changeable": True,
              "description": "Cycle time of the task in ms."
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
              "changeable": True,
              "description": "List of runnables to be executed once on task startup."
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
              "changeable": True,
              "description": "List of runnables to be executed every task cycle."
            }
          },
          "StackSize": {
            "value": "0",
            "metadata": {
              "type": "int",
              "changeable": True,
              "description": "Task stacksize in bytes."
            }
          }
        },
        "data": {}
      }
    }
  }
}