import dearpygui.dearpygui as dpg
from common.NavigationWindow import NavigationWindow

class SERVICES_GUI_Handler:
    data_handler = None
    data = None
    data_structure_template = None
    _services_navigation_window = None

    def __init__(self, data_handler):
        self.data_handler = data_handler
        self.data = data_handler.GetData()
        self.data_structure_template = data_handler.GetDataStructureTemplates()

    def _SERVICES_SortData(self, data):
        return self.data_handler.SortData(data)

    def _SERVICES_SortAllData(self):
        for service in self.data["Services"].keys():
            self.data["Services"][service] = self._SERVICES_SortData(self.data["Services"][service])

    def _SERVICES_ListCallback(self, sender, app_data, user_data):
        #print(sender, app_data, user_data)
        if(self._services_navigation_window != None):
            dpg.delete_item("SERVICES_NAVIGATION_WINDOW", children_only=True)
            self._services_navigation_window.ClearAll()

        self.data["Services"][app_data] = self._SERVICES_SortData(self.data["Services"][app_data])
        self._services_navigation_window = NavigationWindow(service=app_data, data_handler=self.data_handler, tab=app_data)
        self._services_navigation_window.ShowNavigationWindow(parent="SERVICES_NAVIGATION_WINDOW")

    def ShowWindow(self, parent):
        dpg.add_group(horizontal=True, tag="SERVICES_GROUP", parent=parent)
        dpg.add_child_window(tag="SERVICES_LIST_WINDOW", auto_resize_x=True, resizable_x=False,
                             horizontal_scrollbar=True, parent="SERVICES_GROUP")

        list_services = list(self.data["Services"].keys())
        dpg.add_listbox(list_services, tag="SERVICES_LIST", parent="SERVICES_LIST_WINDOW", width=100,
                        callback=self._SERVICES_ListCallback, num_items=len(list_services))

        dpg.add_child_window(tag="SERVICES_NAVIGATION_WINDOW", parent="SERVICES_GROUP")
        self._SERVICES_ListCallback(sender=None, app_data=list_services[0], user_data=None)

    def SaveData(self):
        pass
