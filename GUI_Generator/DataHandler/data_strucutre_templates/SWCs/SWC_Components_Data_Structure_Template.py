SWC_Components_Data_Structure_Template = [
  {
    "Properties": {
      "Component_Name": {
        "metadata": {
          "changeable": True,
          "type": "string"
        },
        "value": "Component_name"
      },
      "Component_Type": {
        "metadata": {
          "changeable": True,
          "type": "selectable",
          "selectable_list": [
            "SERVICE",
            "APPLICATION"
          ]
        },
        "value": "APPLICATION"
      },
      "Gen_Structure": {
        "metadata": {
          "changeable": True,
          "type": "boolean"
        },
        "value": True
      },
      "Component_Gen_Location": {
        "metadata": {
          "changeable": True,
          "type": "string"
        },
        "value": ""
      }
    },
    "Component_Metadata": {
      "node_editor_position": [10, 10]
    },
    "Server_Ports": {
      "value": [
        {
          "Server_Port_Id": {
            "metadata": {
            "changeable": True,
            "type": "string"
            },
              "value": "Server_Port_id"
          },
          "Port_Type": {
            "metadata": {
            "changeable": True,
            "type": "selectable",
              "selectable_list": [
                "FUNCTION",
                "VARIABLE"
              ]
            },
            "value": "FUNCTION"
          },
          "Port_Params": {
            "metadata": {
              "changeable": True,
              "type": "list_string"
            },
            "value": []
          }
        }
      ],
      "metadata": {
        "changeable": True,
        "type": "list_dict"
      }
    },
    "Client_Ports": {
      "value": [
        "Client_Port_id"
      ],
      "metadata": {
        "changeable": True,
        "type": "list_string"
      }
    },
    "Runnables": {
      "metadata": {
        "changeable": True,
        "type": "list_dict"
      },
      "value": [
        {
          "Runnable_Name": {
            "metadata": {
            "changeable": True,
            "type": "string"
          },
            "value": "Runnable_Name"
          },
          "Runnable_Type": {
            "metadata": {
            "changeable": True,
            "type": "selectable",
              "selectable_list": [
                "Init",
                "Cyclic"
              ]
          },
            "value": "Init"
          }
        }
      ]
    }
  }
]