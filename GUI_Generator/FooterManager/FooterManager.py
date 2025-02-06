import dearpygui.dearpygui as dpg

class FooterManager:
    _footer_window_tag = "FOOTER_WINDOW"
    _footer_window_parent = None
    _footer_handler_registry = None

    def __init__(self, parent):
        self.footer_window_parent = parent

    def _Footer_HandlerRegistryCallback(self, sender, app_data, user_data):
        user_data = dpg.get_item_user_data(app_data[1])
        txt = None

        if(isinstance(user_data, str)):
            txt = user_data
        elif( ("metadata" in user_data.keys()) and ("description" in user_data["metadata"].keys()) ):
            txt = user_data["metadata"]["description"]

        if(txt != None):
            self.Footer_DisplayText(text=txt)
        else:
            self._Footer_DeleteText()

    def _Footer_InitHandlerRegistry(self):
        with dpg.item_handler_registry() as handler_registry_tag:
            self._footer_handler_registry = handler_registry_tag
            dpg.add_item_clicked_handler(parent=handler_registry_tag, callback=self._Footer_HandlerRegistryCallback,
                                         button=dpg.mvMouseButton_Left)

    def _Footer_DeleteText(self):
        if (dpg.does_alias_exist(self._footer_window_tag)):
            dpg.delete_item(self._footer_window_tag, children_only=True)

    def Footer_DisplayWindow(self):
        if(dpg.does_alias_exist(self._footer_window_tag)):
            dpg.delete_item(self._footer_window_tag)

        dpg.add_child_window(tag=self._footer_window_tag, parent=self.footer_window_parent)

    def Footer_DisplayText(self, text, delete_children=True):
        if (not dpg.does_alias_exist(self._footer_window_tag)):
            dpg.add_child_window(tag=self._footer_window_tag, parent=self.footer_window_parent)
        elif(delete_children):
            dpg.delete_item(self._footer_window_tag, children_only=True)

        dpg.add_text(default_value=text, parent=self._footer_window_tag)

    def Footer_GetHandlerRegistry(self):
        if(self._footer_handler_registry == None):
            self._Footer_InitHandlerRegistry()

        return self._footer_handler_registry
