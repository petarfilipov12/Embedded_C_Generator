class DATA_HANDLER:
    data = {}

    def __init__(self):
        pass

    def GetData(self):
        return self.data

class SERVICE:
    data_handler = None
    def __init__(self, data_handler):
        self.data_handler = data_handler

    def AddData(self, key, val):
        self.data_handler.GetData()[key] = val

#main

data_hndler_obj = DATA_HANDLER()
service = SERVICE(data_hndler_obj)

print(data_hndler_obj.GetData())

service.AddData("KEY", "VAL")

print(data_hndler_obj.GetData())
