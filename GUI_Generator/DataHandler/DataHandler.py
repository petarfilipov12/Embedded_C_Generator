import json
import copy
from common import FileHandler

from DataHandler.data_strucutre_templates.Services.ADC_Data_Structure_Template import ADC_Data_Structure_Template
from DataHandler.data_strucutre_templates.Services.DIO_Data_Structure_Template import DIO_Data_Structure_Template
from DataHandler.data_strucutre_templates.Services.GPT_Data_Structure_Template import GPT_Data_Structure_Template
from DataHandler.data_strucutre_templates.Services.OS_Data_Structure_Template import OS_Data_Structure_Template
from DataHandler.data_strucutre_templates.Services.PWM_Data_Structure_Template import PWM_Data_Structure_Template
from DataHandler.data_strucutre_templates.Services.SPI_Data_Structure_Template import SPI_Data_Structure_Template
from DataHandler.data_strucutre_templates.Services.UART_Data_Structure_Template import UART_Data_Structure_Template
from DataHandler.data_strucutre_templates.Services.WDT_Data_Structure_Template import WDT_Data_Structure_Template

from DataHandler.data_strucutre_templates.SWCs.SWC_Components_Data_Structure_Template import SWC_Components_Data_Structure_Template
from DataHandler.data_strucutre_templates.SWCs.SWC_Connections_Data_Structure_Template import SWC_Connections_Data_Structure_Template

class DataHandler:
    
    data_files = {
        "Services": {
            "ADC": "/Services/ADC_Configuration.json",
            "DIO": "/Services/DIO_Configuration.json",
            "GPT": "/Services/GPT_Configuration.json",
            "UART": "/Services/UART_Configuration.json",
            "SPI": "/Services/SPI_Configuration.json",
            "WDT": "/Services/WDT_Configuration.json",
            "PWM": "/Services/PWM_Configuration.json",
            "OS": "/Services/OS_Configuration.json",
        },
        "SWCs": {
            "Components": "/SWCs/Components_Configuration.json",
            "Connections": "/SWCs/Connections_Configuration.json"
        }
    }

    data_structure_template = {
        "Services": {
            "ADC": ADC_Data_Structure_Template,
            "DIO": DIO_Data_Structure_Template,
            "GPT": GPT_Data_Structure_Template,
            "UART": UART_Data_Structure_Template,
            "SPI": SPI_Data_Structure_Template,
            "WDT": WDT_Data_Structure_Template,
            "PWM": PWM_Data_Structure_Template,
            "OS": OS_Data_Structure_Template,
        },
        "SWCs": {
            "Components": SWC_Components_Data_Structure_Template,
            "Connections": SWC_Connections_Data_Structure_Template,
        }
    }
    
    data = {}
    data_dir = None
    sync_id_count = 0
    
    def __init__(self, data_dir):
        self.data_dir = data_dir

        self.data_structure_template = self.SortData(self.data_structure_template)

        for key in self.data_structure_template.keys():
            self.data[key] = {}

            for data_type in self.data_structure_template[key].keys():
                temp = self._DataHandler_ReadData(
                        self.data_dir + self.data_files[key][data_type])
                if(temp == None):
                    temp = self._DataHandler_InitEmptyData(self.data_structure_template[key][data_type])

                self.data[key][data_type] = temp

        self.data = self.SortData(self.data)

    def _DataHandler_ReadData(self, data_file):
        data = FileHandler.ReadFile(data_file)

        if(data != None):
            data = json.loads(data)

        return data

    def _DataHandler_WriteData(self, data, data_file):
        FileHandler.WriteFile(s=json.dumps(data, indent=2), path_to_file=data_file, create_path_to_file=True)

    def _DataHandler_InitEmptyData_Recursive(self, data_src, data_dest):
        for key, val in data_src.items():
            if (val["metadata"]["mandatory"]):
                data_dest[key] = {
                    "metadata": val["metadata"],
                    "data": {}
                }
                for temp_key in val.keys():
                    if (temp_key != "data"):
                        data_dest[key][temp_key] = copy.deepcopy(val[temp_key])

                data_dest[key]["data"] = {}
                if (isinstance(val["data"], dict)):
                    self._DataHandler_InitEmptyData_Recursive(val["data"], data_dest[key]["data"])

    def _DataHandler_InitEmptyData(self, data_src):
        data_dest = []

        if(isinstance(data_src, dict)):
            data_dest = {}
            self._DataHandler_InitEmptyData_Recursive(data_src, data_dest)

        return data_dest

    def SortData(self, data):
        return {k: self.SortData(v) if isinstance(v, dict) else v for k, v in sorted(data.items())}

    def GetData(self):
        return self.data

    def GetServices(self):
        return list(self.data_structure_template["Services"].keys())

    def GetSWCs(self):
        ret = []
        for component in self.data["SWCs"]["Components"]:
            ret.append(copy.deepcopy(component["Properties"]["Component_Name"]["value"]))

        return sorted(ret)

    def GetDataStructureTemplates(self):
        return self.data_structure_template

    def SaveData(self):
        self.data = self.SortData(self.data)

        for key in self.data_files.keys():
            for data_type in self.data_files[key].keys():
                self._DataHandler_WriteData(self.data[key][data_type], self.data_dir + self.data_files[key][data_type])

    def _Synchronize(self, data):
        if (("leaf" in data["metadata"].keys()) and (data["metadata"]["leaf"] == True)):
            for param in data["parameters"].values():
                if (("id" in param["metadata"].keys()) and (param["metadata"]["id"] == True)):
                    param["metadata"]["changeable"] = False
                    param["value"] = str(self.sync_id_count)
                    self.sync_id_count += 1
        else:
            self.sync_id_count = 0
            for key in data["data"]:
                self._Synchronize(data["data"][key])

    def Synchronize(self, data):
        if("metadata" in data.keys()):
            self.sync_id_count = 0
            self._Synchronize(data)
        else:
            for key in data.keys():
                self.sync_id_count = 0
                self._Synchronize(data[key])
