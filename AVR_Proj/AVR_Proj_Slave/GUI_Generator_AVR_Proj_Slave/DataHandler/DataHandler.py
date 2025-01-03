import json
import copy

class DataHandler:
    
    data_files = {
        "Services": {
            "ADC": "/DataHandler/data/Services/ADC_Configuration.json",
            "DIO": "/DataHandler/data/Services/DIO_Configuration.json",
            "GPT": "/DataHandler/data/Services/GPT_Configuration.json",
            "UART": "/DataHandler/data/Services/UART_Configuration.json",
            "SPI": "/DataHandler/data/Services/SPI_Configuration.json",
            "WDT": "/DataHandler/data/Services/WDT_Configuration.json",
            "PWM": "/DataHandler/data/Services/PWM_Configuration.json",
            "OS": "/DataHandler/data/Services/OS_Configuration.json",
        },
        "SWCs": {
            "Components": "/DataHandler/data/SWCs/Components_Configuration.json",
            "Connections": "/DataHandler/data/SWCs/Connections_Configuration.json"
        }
    }
    
    data_structure_template_files = {
        "Services": {
            "ADC": "/DataHandler/data_strucutre_templates/Services/ADC_Data_Structure_Template.json",
            "DIO": "/DataHandler/data_strucutre_templates/Services/DIO_Data_Structure_Template.json",
            "GPT": "/DataHandler/data_strucutre_templates/Services/GPT_Data_Structure_Template.json",
            "UART": "/DataHandler/data_strucutre_templates/Services/UART_Data_Structure_Template.json",
            "SPI": "/DataHandler/data_strucutre_templates/Services/SPI_Data_Structure_Template.json",
            "WDT": "/DataHandler/data_strucutre_templates/Services/WDT_Data_Structure_Template.json",
            "PWM": "/DataHandler/data_strucutre_templates/Services/PWM_Data_Structure_Template.json",
            "OS": "/DataHandler/data_strucutre_templates/Services/OS_Data_Structure_Template.json",
        },
        "SWCs": {
            "Components": "/DataHandler/data_strucutre_templates/SWCs/SWC_Components_Data_Structure_Template.json",
            "Connections": "/DataHandler/data_strucutre_templates/SWCs/SWC_Connections_Data_Structure_Template.json"
        }
    }
    
    data = {}
    data_structure_template = {}
    project_dir = None
    sync_id_count = 0
    
    def __init__(self, project_dir):
        self.project_dir = project_dir

        for key in self.data_structure_template_files.keys():
            self.data_structure_template[key] = {}
            self.data[key] = {}

            for data_type in self.data_structure_template_files[key].keys():
                self.data_structure_template[key][data_type] = self._DataHandler_ReadData(
                    project_dir + self.data_structure_template_files[key][data_type])

                try:
                    self.data[key][data_type] = self._DataHandler_ReadData(
                        project_dir + self.data_files[key][data_type])
                except FileNotFoundError:
                    self.data[key][data_type] = self._DataHandler_InitEmptyData(self.data_structure_template[key][data_type])

        self.data = self.SortData(self.data)
        self.data_structure_template = self.SortData(self.data_structure_template)

    def _DataHandler_ReadData(self, data_file):
        data = None
        with open(data_file, 'r') as file:
            data = json.load(file)
        return data

    def _DataHandler_WriteData(self, data, data_file):
        with open(data_file, 'w') as file:
            json.dump(data, file, indent=2)

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
        return list(self.data_structure_template_files["Services"].keys())

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
                self._DataHandler_WriteData(self.data[key][data_type], self.project_dir + self.data_files[key][data_type])

    def _Synchronize(self, data):
        print(data)
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
