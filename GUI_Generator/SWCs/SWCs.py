import dearpygui.dearpygui as dpg
import copy

class SWCs_GUI_Handler:
    _swc_data_structure_template_files = {
        "components_data_file": "SWCs/SWC_Components_Data_Structure_Template.json",
        "connections_data_file": "SWCs/SWC_Connections_Data_Structure_Template.json"
    }
    _swc_data_files = None

    _swc_edit_window_apply_button_tag = "SWC_EDIT_WINDOW_APPLY_BUTTON"
    _swc_edit_window_edit_params_apply_button_tag = "SWC_EDIT_WINDOW_EDIT_PARAMS_APPLY_BUTTON"

    _swc_node_handler_registry_tag = None

    _swc_data_handler = None
    _swc_components_data = None
    _swc_components_data_structure_template = None
    _swc_connections_data = None
    _swc_connections_data_structure_template = None

    _swc_background_disable_widgets_tags = []
    _swc_enabled_node_editor = True

    _swc_edit_window_selected_buffer = {}
    _swc_selected_nodes_buffer = []
    _swc_selected_node_links_buffer = []

    _swc_edit_window_selected_tab = None

    _swc_edit_window_edit_params_last_args = {}

    def __init__(self, data_handler):
        self._swc_data_handler = data_handler

        self._swc_components_data_structure_template = data_handler.GetDataStructureTemplates()["SWCs"]["Components"]
        self._swc_connections_data_structure_template = data_handler.GetDataStructureTemplates()["SWCs"]["Connections"]

        self._swc_components_data = data_handler.GetData()["SWCs"]["Components"]
        self._swc_connections_data = data_handler.GetData()["SWCs"]["Connections"]

    def _SWC_GetComponentList(self):
        return [d["Properties"]['Component_Name']["value"] for d in self._swc_components_data]

    def _SWC_GetComponentRunnablesList(self, component_data_pointer):
        return [d["Runnable_Name"]["value"] for d in component_data_pointer["Runnables"]["value"]]

    def _SWC_GetComponentServerPortsList(self, component_data_pointer):
        return [d["Server_Port_Id"]["value"] for d in component_data_pointer["Server_Ports"]["value"]]

    def _SWC_StoreCurrentNodesPositions(self):
        for component in self._swc_components_data:
            if( ("SWC_NODE_EDITOR/" + component["Properties"]["Component_Name"]["value"]) in dpg.get_aliases() ):
                component["Component_Metadata"]["node_editor_position"] = dpg.get_item_pos(
                    "SWC_NODE_EDITOR/" + component["Properties"]["Component_Name"]["value"])

    def _SWC_DrawLinkNodesFromConnection(self, connection, parent):
        connection_tag = connection["metadata"]["tag"]
        server_port_tag = connection_tag[connection_tag.find("/CONNECTION/") + len("/CONNECTION/") : connection_tag.find("/TO/")]
        client_port_tag = connection_tag[connection_tag.find("/TO/") + len("/TO/") :]

        dpg.add_node_link(server_port_tag, client_port_tag, tag=connection_tag, parent=parent)

    def _SWC_CreateLinkCallback(self, sender, app_data, user_data):
        #app_data[0] -> output(server) port app_data[1] -> input(client) port
        print("_SWC_CreateLinkCallback:", sender, app_data, user_data)
        for item in app_data:
            print(dpg.get_item_alias(item))

        connection = copy.deepcopy(self._swc_connections_data_structure_template[0])

        temp = dpg.get_item_alias(app_data[0]).split('/')
        connection["Server_Port"] = temp[-1]
        connection["Server_Component"] = temp[-2]

        temp = dpg.get_item_alias(app_data[1]).split('/')
        connection["Client_Port"] = temp[-1]
        connection["Client_Component"] = temp[-2]

        client_port_connected_flag = False
        for connection_data in self._swc_connections_data:
            if( (connection_data["Client_Port"] == connection["Client_Port"]) and
                    (connection_data["Client_Component"] == connection["Client_Component"]) ):
                client_port_connected_flag = True
                break

        if(not client_port_connected_flag):
            connection_tag = dpg.get_item_alias(app_data[0]) + "/TO/" + dpg.get_item_alias(app_data[1])
            connection_tag = "SWC_NODE_EDITOR/CONNECTION/" + connection_tag

            connection["metadata"] = {}
            connection["metadata"]["tag"] = connection_tag

            self._SWC_DrawLinkNodesFromConnection(connection=connection, parent="SWC_NODE_EDITOR")
            self._swc_connections_data.append(connection)

        self._SWC_SyncConnectionsData()

    def _SWC_DeleteLinkCallback(self, sender, app_data, user_data):
        #app_data -> link tag
        print("_SWC_DeleteLinkCallback:", sender, app_data, user_data)

        for connection in copy.deepcopy(self._swc_connections_data):
            if(connection["metadata"]["tag"] == dpg.get_item_alias(app_data)):
                self._swc_connections_data.remove(connection)
                dpg.delete_item(dpg.get_item_alias(app_data))

    def _SWC_EditWindowOnCloseCallback(self, sender, app_data, user_data):
        # diasble window background
        constant_background_disable_widgets = ["ADD_SWC_BUTTON", "SWC_COMPONENT_LIST"]
        for disable_tag in set(self._swc_background_disable_widgets_tags + constant_background_disable_widgets):
            if ("node" in dpg.get_item_type(disable_tag).lower()):
                dpg.configure_item(disable_tag, draggable=True)
                self._swc_enabled_node_editor = False
            else:
                try:
                    dpg.configure_item(disable_tag, enabled=True)
                except:
                    pass

        dpg.delete_item("SWC_EDIT_WINDOW")
        self._SWC_RenderComponentList(parent="SWC_LIST_WINDOW")
        self._SWC_RenderNodeEditor(parent="SWC_NODE_EDITOR_WINDOW")

    def _SWC_EditWindowEditParamApplyButtonCallback(self, sender, app_data, user_data):
        print(sender, app_data, user_data)

        param_tag_list = [alias for alias in dpg.get_aliases() if "SWC_EDIT_WINDOW_EDIT_PARAM/TABLE/" in alias]
        for param_tag in param_tag_list:
            tab_type = param_tag[param_tag.find("SWC_EDIT_WINDOW_EDIT_PARAM/TABLE/") + len("SWC_EDIT_WINDOW_EDIT_PARAM/TABLE/") :]
            tab_type = tab_type[: tab_type.find('/')]

            index = int(param_tag[param_tag.find('[') + 1 : param_tag.find(']')])

            print(param_tag)
            if("/PARAM_NAME/" in param_tag):
                if ( ("/ADD_BUTTON" not in param_tag) and ("/DELETE_BUTTON" not in param_tag) and
                        ("/SELECTABLE/" not in param_tag) ):
                    param_name = param_tag[param_tag.rfind("/") + 1:]
                    if ("TABLE" != param_name):
                        print("TUK")
                        user_data[tab_type]["value"][index][param_name]["value"] = dpg.get_value(param_tag)
            else:
                user_data[tab_type]["value"][index] = dpg.get_value(param_tag)

        dpg.configure_item(sender, enabled=False)

    def _SWC_SyncConnectionsData(self):
        for component in self._swc_components_data:
            component_name = component["Properties"]["Component_Name"]["value"]

            for server_port in component["Server_Ports"]["value"]:
                server_port_id = server_port["Server_Port_Id"]["value"]
                server_port_type = server_port["Port_Type"]["value"]

                for connection in self._swc_connections_data:
                    if( (connection["Server_Component"] == component_name) and (connection["Server_Port"] == server_port_id) ):
                        connection["Port_Type"] = server_port_type

    def _SWC_ApplyButtonCallback(self, sender, app_data, user_data):
        #user_data -> pointer to element in components_data

        old_component_name = user_data["Properties"]["Component_Name"]["value"]

        for tab_tag in dpg.get_item_children("SWC_EDIT_WINDOW_TAB_BAR")[1]:
            tab_tag = dpg.get_item_alias(tab_tag)
            tab_parameters = {}
            for alias in dpg.get_aliases():
                if( (tab_tag in alias) and ("/PARAMETER/" in alias) ):
                    ret = dpg.get_value(alias)
                    # if(not isinstance(ret, str)):
                    #     ret = dpg.get_item_label(alias)
                    tab_parameters[alias] = ret

            if("PROPERTIES_TAB" in tab_tag):
                for tab_parameter_tag in tab_parameters.keys():
                    param_name = tab_parameter_tag[tab_parameter_tag.rfind('/') + 1 :]

                    user_data["Properties"][param_name]["value"] = tab_parameters[tab_parameter_tag]

        new_component_name = user_data["Properties"]["Component_Name"]["value"]
        if(old_component_name != new_component_name):
            for connection in self._swc_connections_data:
                if(connection["Server_Component"] == old_component_name):
                    connection["Server_Component"] = new_component_name
                if (connection["Client_Component"] == old_component_name):
                    connection["Client_Component"] = new_component_name

        self._SWC_SyncConnectionsData()

        #dpg.configure_item(self._swc_edit_window_apply_button_tag, enabled=False)
        self._swc_edit_window_selected_tab = dpg.get_item_alias(dpg.get_value("SWC_EDIT_WINDOW_TAB_BAR"))
        self._SWC_EditWindowOnCloseCallback(sender=None, app_data=None, user_data=None)
        self._SWC_OpenSWCEditWindow(component_name=new_component_name)

    def _SWC_NodeDoubleClickCallback(self, sender, app_data, user_data):
        #caller_tag = app_data[1] -> node tag
        if(self._swc_enabled_node_editor):
            comp_name = dpg.get_item_alias(app_data[1])
            comp_name = comp_name[comp_name.rfind('/') + 1 :]
            self._SWC_OpenSWCEditWindow(component_name=comp_name)

    def _SWC_NodeSelectionCallback(self, sender, app_data, user_data):
        if(dpg.is_item_visible("SWC_NODE_EDITOR")):
            selected_nodes = dpg.get_selected_nodes("SWC_NODE_EDITOR")
            selected_links = dpg.get_selected_links("SWC_NODE_EDITOR")
            if(selected_links or selected_nodes):
                self._swc_selected_nodes_buffer = []
                self._swc_selected_node_links_buffer = []

                for item in selected_nodes:
                    self._swc_selected_nodes_buffer.append(dpg.get_item_alias(item))
                for item in selected_links:
                    self._swc_selected_node_links_buffer.append(dpg.get_item_alias(item))

            if(selected_nodes):
                for child in dpg.get_item_children("SWC_LIST_WINDOW/SWC_BUTTON_GROUP")[1]:
                    if("ADD" not in dpg.get_item_alias(child)):
                        dpg.configure_item(child, enabled=True)
            else:
                for child in dpg.get_item_children("SWC_LIST_WINDOW/SWC_BUTTON_GROUP")[1]:
                    if("ADD" not in dpg.get_item_alias(child)):
                        dpg.configure_item(child, enabled=False)
    def _SWC_ParamChangeCallBack(self, sender, app_data, user_data):
        dpg.configure_item(user_data, enabled=True)

    def _SWC_EditWindowSelectableCallback(self, sender, app_data, user_data):
        #user_data => row_index

        tab_tag = sender[: sender.rfind("_TAB/")]
        tab_tag += "_TAB"
        tab_tag = tab_tag[tab_tag.rfind('/') + 1 :]

        for alias in dpg.get_aliases():
            if(tab_tag in alias):
                if("mvButton" in dpg.get_item_type(alias)):
                    dpg.configure_item(alias, enabled=True)
                elif( ("mvSelectable" in dpg.get_item_type(alias)) and (sender != alias) ):
                    dpg.set_value(alias, False)

        self._swc_edit_window_selected_buffer[tab_tag] = user_data
        print(self._swc_edit_window_selected_buffer)

    def _SWC_EditWindowAddElem(self, tab_tag, component_data_pointer, new_elem_name, new_elem=None):
        param_data_pointer = None
        current_elem_name_list = None
        if ("SERVER_PORTS_TAB" == tab_tag):
            param_data_pointer = component_data_pointer["Server_Ports"]
            current_elem_name_list = self._SWC_GetComponentServerPortsList(component_data_pointer=component_data_pointer)
        elif ("CLIENT_PORTS_TAB" == tab_tag):
            param_data_pointer = component_data_pointer["Client_Ports"]
            current_elem_name_list = param_data_pointer["value"]
        elif ("RUNNABLES_TAB" == tab_tag):
            param_data_pointer = component_data_pointer["Runnables"]
            current_elem_name_list = self._SWC_GetComponentRunnablesList(component_data_pointer=component_data_pointer)

        counter = 1
        temp_new_elem_name = new_elem_name
        print(current_elem_name_list)
        while (temp_new_elem_name in current_elem_name_list):
            temp_new_elem_name = new_elem_name + "_" + str(counter)
            counter += 1
        new_elem_name = temp_new_elem_name

        if ("RUNNABLES_TAB" == tab_tag):
            new_elem["Runnable_Name"]["value"] = new_elem_name
        elif("SERVER_PORTS_TAB" == tab_tag):
            new_elem["Server_Port_Id"]["value"] = new_elem_name
        else:
            new_elem = new_elem_name

        param_data_pointer["value"].append(new_elem)

        if ("SERVER_PORTS_TAB" == tab_tag):
            self._SWC_RnederServerPortsTab(parent="SWC_EDIT_WINDOW_TAB_BAR/SERVER_PORTS_TAB",
                                     component_data_pointer=component_data_pointer)
        elif ("CLIENT_PORTS_TAB" == tab_tag):
            self._SWC_RnederClientsPortsTab(parent="SWC_EDIT_WINDOW_TAB_BAR/CLIENT_PORTS_TAB",
                                     component_data_pointer=component_data_pointer, ports_type="Client_Ports")
        elif ("RUNNABLES_TAB" == tab_tag):
            self._SWC_RenderRunnableTab(parent="SWC_EDIT_WINDOW_TAB_BAR/RUNNABLES_TAB",
                                        component_data_pointer=component_data_pointer)
    def _SWC_EditWindowAddNewButtonCallback(self, sender, app_data, user_data):
        #user_data -> component_data_pointer
        print(sender, app_data, user_data)

        tab_tag = sender[: sender.rfind("_TAB/")]
        tab_tag += "_TAB"
        tab_tag = tab_tag[tab_tag.rfind('/') + 1:]

        new_elem_name = None
        new_elem = None
        if ("SERVER_PORTS_TAB" == tab_tag):
            new_elem = copy.deepcopy(self._swc_components_data_structure_template[0]["Server_Ports"]["value"][0])
            new_elem_name = copy.deepcopy(new_elem["Server_Port_Id"]["value"])
        elif ("CLIENT_PORTS_TAB" == tab_tag):
            new_elem_name = copy.deepcopy(self._swc_components_data_structure_template[0]["Client_Ports"]["value"][0])
        elif ("RUNNABLES_TAB" == tab_tag):
            new_elem = copy.deepcopy(self._swc_components_data_structure_template[0]["Runnables"]["value"][0])
            new_elem_name = copy.deepcopy(new_elem["Runnable_Name"]["value"])

        self._SWC_EditWindowAddElem(tab_tag=tab_tag, component_data_pointer=user_data, new_elem_name=new_elem_name,
                                    new_elem=new_elem)

    def _SWC_EditWindowDuplicateButtonCallback(self, sender, app_data, user_data):
        print(sender, app_data, user_data)

        tab_tag = sender[: sender.rfind("_TAB/")]
        tab_tag += "_TAB"
        tab_tag = tab_tag[tab_tag.rfind('/') + 1:]

        print(self._swc_edit_window_selected_buffer[tab_tag])

        new_elem_name = None
        new_elem = None
        if ("RUNNABLES_TAB" == tab_tag):
            for runnable in user_data["Runnables"]["value"]:
                if(runnable["Runnable_Name"]["value"] == self._swc_edit_window_selected_buffer[tab_tag]):
                    new_elem_name = self._swc_edit_window_selected_buffer[tab_tag]
                    new_elem = copy.deepcopy(runnable)
        elif ("SERVER_PORTS_TAB" == tab_tag):
            for server_port in user_data["Server_Ports"]["value"]:
                if (server_port["Server_Port_Id"]["value"] == self._swc_edit_window_selected_buffer[tab_tag]):
                    new_elem_name = self._swc_edit_window_selected_buffer[tab_tag]
                    new_elem = copy.deepcopy(server_port)
        else:
            new_elem_name = self._swc_edit_window_selected_buffer[tab_tag]

        self._SWC_EditWindowAddElem(tab_tag=tab_tag, component_data_pointer=user_data, new_elem_name=new_elem_name, new_elem=new_elem)

    def _SWC_EditWindowDeleteButtonCallback(self, sender, app_data, user_data):
        #user_data -> component_data_pointer
        print(sender, app_data, user_data)

        tab_tag = sender[: sender.rfind("_TAB/")]
        tab_tag += "_TAB"
        tab_tag = tab_tag[tab_tag.rfind('/') + 1:]

        print(self._swc_edit_window_selected_buffer[tab_tag])

        if ("SERVER_PORTS_TAB" == tab_tag):
            for server_port in copy.deepcopy(user_data["Server_Ports"]["value"]):
                if(server_port["Server_Port_Id"]["value"] == self._swc_edit_window_selected_buffer[tab_tag]):
                    user_data["Server_Ports"]["value"].remove(server_port)
                    break
            self._SWC_RnederServerPortsTab(parent="SWC_EDIT_WINDOW_TAB_BAR/SERVER_PORTS_TAB",
                                     component_data_pointer=user_data)
        elif ("CLIENT_PORTS_TAB" == tab_tag):
            user_data["Client_Ports"]["value"].remove(self._swc_edit_window_selected_buffer[tab_tag])
            self._SWC_RnederClientsPortsTab(parent="SWC_EDIT_WINDOW_TAB_BAR/CLIENT_PORTS_TAB",
                                     component_data_pointer=user_data, ports_type="Client_Ports")
        elif ("RUNNABLES_TAB" == tab_tag):
            for runnable in copy.deepcopy(user_data["Runnables"]["value"]):
                if(runnable["Runnable_Name"]["value"] == self._swc_edit_window_selected_buffer[tab_tag]):
                    user_data["Runnables"]["value"].remove(runnable)
                    break
            self._SWC_RenderRunnableTab(parent="SWC_EDIT_WINDOW_TAB_BAR/RUNNABLES_TAB",
                                        component_data_pointer=user_data)

    def _SWC_ServerPortsDeleteButtonCallback(self, sender, app_data, user_data):
        print(sender, app_data, user_data)

        selectable_tag = sender[: sender.rfind("/DELETE_BUTTON")] + "/SELECTABLE"

        for alias in dpg.get_aliases():
            if( (selectable_tag in alias) and dpg.get_value(alias) ):
                param_index = alias[alias.rfind('/') + 1 :]
                print(user_data["value"])
                print(param_index)
                user_data["value"].pop(int(param_index))
                dpg.delete_item(alias)

    def _SWC_ServerPortsAddButtonCallback(self, sender, app_data, user_data):
        print(sender, app_data, user_data)

        with dpg.window(modal=True, label="Add New", min_size=[320, 70]) as add_new_window:
            new_param_tag = dpg.add_input_text(hint="Parameter (format: param_type param_name)", width=-1)

            def button_callback():
                new_param = dpg.get_value(new_param_tag)
                if(new_param):
                    user_data["value"].append(new_param)
                    dpg.delete_item(add_new_window)
                    self._SWC_EditWindowEditParamWindow(**self._swc_edit_window_edit_params_last_args)

            dpg.add_button(label="Add Parameter", callback=button_callback)

    def _SWC_EditWindowEditParamWindow(self, sender, app_data, user_data):
        print(sender, app_data, user_data)

        if ("SWC_EDIT_WINDOW_EDIT_PARAM" in dpg.get_aliases()):
            dpg.delete_item("SWC_EDIT_WINDOW_EDIT_PARAM", children_only=True)
            dpg.delete_item("SWC_EDIT_WINDOW_EDIT_PARAM")

        dpg.add_window(tag="SWC_EDIT_WINDOW_EDIT_PARAM", label="Edit Param", min_size=[800, 200], no_collapse=True,
                           on_close=self._SWC_ApplyButtonCallback, user_data=user_data, no_focus_on_appearing=False,
                           no_bring_to_front_on_focus=False)

        tab_tag = sender[: sender.rfind("_TAB/")]
        tab_tag += "_TAB"
        tab_tag = tab_tag[tab_tag.rfind('/') + 1:]
        print(self._swc_edit_window_selected_buffer[tab_tag])

        tab_key = None
        if ("SERVER_PORTS_TAB" == tab_tag):
            tab_key = "Server_Ports"
        elif ("CLIENT_PORTS_TAB" == tab_tag):
            tab_key = "Client_Ports"
        elif ("RUNNABLES_TAB" == tab_tag):
            tab_key = "Runnables"
        print(user_data[tab_key])

        with dpg.table(tag="SWC_EDIT_WINDOW_EDIT_PARAM/TABLE", parent="SWC_EDIT_WINDOW_EDIT_PARAM",
                       policy=dpg.mvTable_SizingFixedFit, resizable=True, no_host_extendX=False, borders_innerH=True):
            if(user_data[tab_key]["metadata"]["type"] == "list_dict"):
                for param_name in user_data[tab_key]["value"][0]:
                    dpg.add_table_column(label=param_name, width_stretch=True)

                row_index = 0
                for params in user_data[tab_key]["value"]:
                    with dpg.table_row():
                        for param_name in params.keys():
                            tag = "SWC_EDIT_WINDOW_EDIT_PARAM/TABLE/" + tab_key + "/[" + str(row_index) + "]/PARAM_NAME/" + param_name
                            if (params[param_name]["metadata"]["type"] == "string"):
                                dpg.add_input_text(tag=tag, default_value=params[param_name]["value"], width=-1,
                                                   callback=self._SWC_ParamChangeCallBack,
                                                   user_data=self._swc_edit_window_edit_params_apply_button_tag)
                            elif (params[param_name]["metadata"]["type"] == "selectable"):
                                dpg.add_combo(params[param_name]["metadata"]["selectable_list"], tag=tag,
                                              default_value=params[param_name]["value"], width=-1,
                                              callback=self._SWC_ParamChangeCallBack,
                                              user_data=self._swc_edit_window_edit_params_apply_button_tag)
                            elif (params[param_name]["metadata"]["type"] == "list_string"):
                                with dpg.group(horizontal=True):
                                    with dpg.group(horizontal=False):
                                        dpg.add_button(tag=tag + "/ADD_BUTTON", label="+", callback=self._SWC_ServerPortsAddButtonCallback,
                                                       user_data=params[param_name])
                                        dpg.add_button(tag=tag + "/DELETE_BUTTON", label="x", callback=self._SWC_ServerPortsDeleteButtonCallback,
                                                       user_data=params[param_name])
                                    with dpg.table(tag=tag + "/TABLE", header_row=False):
                                        dpg.add_table_column(no_header_label=True)

                                        selectable_index = 0
                                        for param_value in params[param_name]["value"]:
                                            print(params[param_name])
                                            with dpg.table_row():
                                                selectable_tag = tag + "/SELECTABLE/" + str(selectable_index)
                                                dpg.add_selectable(tag=selectable_tag, label=param_value)
                                            selectable_index += 1
                    row_index += 1
            elif(user_data[tab_key]["metadata"]["type"] == "list_string"):
                dpg.add_table_column(label="Port Name", width_stretch=True)

                row_index = 0
                for param in user_data[tab_key]["value"]:
                    with dpg.table_row():
                        tag = "SWC_EDIT_WINDOW_EDIT_PARAM/TABLE/" + tab_key + "/[" + str(row_index) + "]"
                        dpg.add_input_text(tag=tag, default_value=param, width=-1,
                                           callback=self._SWC_ParamChangeCallBack,
                                           user_data=self._swc_edit_window_edit_params_apply_button_tag)
                    row_index += 1

        dpg.add_button(tag=self._swc_edit_window_edit_params_apply_button_tag, parent="SWC_EDIT_WINDOW_EDIT_PARAM", label="Apply changes",
                       enabled=False, callback=self._SWC_EditWindowEditParamApplyButtonCallback, user_data=user_data)

    def _SWC_EditWindowEditButtonCallback(self, sender, app_data, user_data):
        print(sender, app_data, user_data)

        self._swc_edit_window_edit_params_last_args["sender"] = sender
        self._swc_edit_window_edit_params_last_args["app_data"] = app_data
        self._swc_edit_window_edit_params_last_args["user_data"] = user_data

        self._SWC_EditWindowEditParamWindow(**self._swc_edit_window_edit_params_last_args)

    def _SWC_EditWindowAddToolbarButtons(self, parent, component_data_pointer):
        dpg.add_button(tag=parent + "/ADD_NEW_BUTTON", parent=parent, label="Add New", small=True,
                       callback=self._SWC_EditWindowAddNewButtonCallback, user_data=component_data_pointer)
        dpg.add_button(tag=parent + "/DUPLICATE_BUTTON", parent=parent, label="Duplicate", small=True, enabled=False,
                       callback=self._SWC_EditWindowDuplicateButtonCallback, user_data=component_data_pointer)
        dpg.add_button(tag=parent + "/DELETE_BUTTON", parent=parent, label="Delete", small=True, enabled=False,
                       callback=self._SWC_EditWindowDeleteButtonCallback, user_data=component_data_pointer)

    def _SWC_RenderRunnableTab(self, parent, component_data_pointer):
        dpg.delete_item(parent, children_only=True)
        self._swc_edit_window_selected_buffer[parent[parent.rfind('/') + 1 :]] = None

        parameters_data = component_data_pointer["Runnables"]["value"]
        table_tag = parent + "/RUNNABLE_TABLE_TAG"
        with dpg.group(tag=parent + "/GROUP", parent=parent, horizontal=True):
            toolbar_group_tag = parent + "/GROUP/TOOLBAR_GROUP"
            with dpg.group(tag=toolbar_group_tag, horizontal=False, show=True):
                self._SWC_EditWindowAddToolbarButtons(parent=toolbar_group_tag, component_data_pointer=component_data_pointer)
            with dpg.table(tag=table_tag, parent=parent + "/GROUP",
                           policy=dpg.mvTable_SizingFixedFit, resizable=True, no_host_extendX=False):
                for label in self._swc_components_data_structure_template[0]["Runnables"]["value"][0].keys():
                    dpg.add_table_column(label=label, width_stretch=True)

                row_index = 0
                for parameters_data in parameters_data:
                    with dpg.table_row():
                        for param_name in parameters_data.keys():
                            selectable_tag = table_tag + "/PARAMETER/" + "Runnables[" + str(row_index) + "]/" + param_name
                            dpg.add_selectable(tag=selectable_tag, span_columns=True, label=parameters_data[param_name]["value"],
                                               callback=self._SWC_EditWindowSelectableCallback,
                                               user_data=parameters_data["Runnable_Name"]["value"])
                    row_index += 1
        dpg.add_button(tag=parent + "/EDIT_BUTTON", parent=parent, label="Edit Data",
                       callback=self._SWC_EditWindowEditButtonCallback, user_data=component_data_pointer)

    def _SWC_RnederClientsPortsTab(self, parent, component_data_pointer, ports_type):
        dpg.delete_item(parent, children_only=True)
        self._swc_edit_window_selected_buffer[parent[parent.rfind('/') + 1 :]] = None
        table_tag = parent + "/CLIENT_TABLE_TAG"

        component_name = component_data_pointer["Properties"]["Component_Name"]["value"]
        port_key = "Client_Port"
        component_key = "Client_Component"
        table_header_keys = ["Client_Port", "Server_Port", "Server_Component"]
        ports_data = component_data_pointer["Client_Ports"]

        with dpg.group(tag=parent + "/GROUP", parent=parent, horizontal=True):
            toolbar_group_tag = parent + "/GROUP/TOOLBAR_GROUP"
            with dpg.group(tag=toolbar_group_tag, horizontal=False, show=True):
                self._SWC_EditWindowAddToolbarButtons(parent=toolbar_group_tag, component_data_pointer=component_data_pointer)
            with dpg.table(tag=table_tag, parent=parent + "/GROUP", resizable=True, borders_innerH=True, borders_outerV=True):
                connection_empty_data = copy.deepcopy(self._swc_connections_data_structure_template[0])

                for label in table_header_keys:
                    dpg.add_table_column(label=label)

                row_index = 0
                for port in ports_data["value"]:
                    port_info = connection_empty_data
                    port_info[port_key] = port

                    port_info[component_key] = component_name
                    for connection in self._swc_connections_data:
                        if( (connection[port_key] == port) and (connection[component_key] == component_name)):
                            port_info = copy.deepcopy(connection)
                            break

                    with dpg.table_row():
                        for key in table_header_keys:
                            selectable_tag = table_tag + "/PARAMETER/" + ports_type + '[' + str(row_index) + ']/' + key
                            dpg.add_selectable(tag=selectable_tag, label=port_info[key], span_columns=True,
                                                callback=self._SWC_EditWindowSelectableCallback, user_data=port_info[port_key])
                    row_index += 1
        dpg.add_button(tag=parent + "/EDIT_BUTTON", parent=parent, label="Edit Data",
                       callback=self._SWC_EditWindowEditButtonCallback, user_data=component_data_pointer)

    def _SWC_RnederServerPortsTab(self, parent, component_data_pointer):
        dpg.delete_item(parent, children_only=True)
        self._swc_edit_window_selected_buffer[parent[parent.rfind('/') + 1:]] = None

        parameters_data = component_data_pointer["Server_Ports"]["value"]
        table_tag = parent + "/SERVER_PORTS_TABLE_TAG"
        with dpg.group(tag=parent + "/GROUP", parent=parent, horizontal=True):
            toolbar_group_tag = parent + "/GROUP/TOOLBAR_GROUP"
            with dpg.group(tag=toolbar_group_tag, horizontal=False, show=True):
                self._SWC_EditWindowAddToolbarButtons(parent=toolbar_group_tag,
                                                      component_data_pointer=component_data_pointer)
            with dpg.table(tag=table_tag, parent=parent + "/GROUP",
                           policy=dpg.mvTable_SizingFixedFit, resizable=True, no_host_extendX=False):
                for label in self._swc_components_data_structure_template[0]["Server_Ports"]["value"][0].keys():
                    dpg.add_table_column(label=label, width_stretch=True)

                row_index = 0
                for parameters_data in parameters_data:
                    with dpg.table_row():
                        for param_name in parameters_data.keys():
                            selectable_tag = table_tag + "/PARAMETER/" + "ServerPorts[" + str(
                                row_index) + "]/" + param_name
                            dpg.add_selectable(tag=selectable_tag, span_columns=True,
                                               label=parameters_data[param_name]["value"],
                                               callback=self._SWC_EditWindowSelectableCallback,
                                               user_data=parameters_data["Server_Port_Id"]["value"])
                    row_index += 1
        dpg.add_button(tag=parent + "/EDIT_BUTTON", parent=parent, label="Edit Data",
                       callback=self._SWC_EditWindowEditButtonCallback, user_data=component_data_pointer)
    def _SWC_RenderPropertiesTab(self, parent, component_data_pointer):
        dpg.delete_item(parent, children_only=True)

        param_data_pointer = component_data_pointer["Properties"]
        table_tag = parent + "/TABLE_TAG"
        with dpg.table(tag=table_tag, parent=parent + "/GROUP", resizable=True, borders_innerH=True):
            dpg.configure_item(table_tag, header_row=False)
            dpg.add_table_column()
            dpg.add_table_column()

            for param_name in param_data_pointer.keys():
                with dpg.table_row():
                    dpg.add_text(param_name)

                    param_tag = None
                    if(param_data_pointer[param_name]["metadata"]["type"] == "string"):
                        param_tag = dpg.add_input_text(tag=parent + "/PARAMETER/" + param_name,
                                                    default_value=str(param_data_pointer[param_name]["value"]),
                                                    width=-1, callback=self._SWC_ParamChangeCallBack, user_data=self._swc_edit_window_apply_button_tag)
                    elif(param_data_pointer[param_name]["metadata"]["type"] == "boolean"):
                        param_tag = dpg.add_checkbox(tag=parent + "/PARAMETER/" + param_name, default_value=bool(param_data_pointer[param_name]["value"]),
                                                     callback=self._SWC_ParamChangeCallBack, user_data=self._swc_edit_window_apply_button_tag)
                    elif (param_data_pointer[param_name]["metadata"]["type"] == "selectable"):
                        param_tag = dpg.add_combo(param_data_pointer[param_name]["metadata"]["selectable_list"],
                                                  tag=parent + "/PARAMETER/" + param_name,
                                                     default_value=str(param_data_pointer[param_name]["value"]),
                                                     callback=self._SWC_ParamChangeCallBack,
                                                     user_data=self._swc_edit_window_apply_button_tag)

                    if (not param_data_pointer[param_name]["metadata"]["changeable"]):
                        dpg.configure_item(tag=param_tag, enabled=False)

        dpg.add_button(tag=self._swc_edit_window_apply_button_tag, parent=parent, label="Apply changes",
                       enabled=False, callback=self._SWC_ApplyButtonCallback, user_data=component_data_pointer)

    def _SWC_OpenSWCEditWindow(self, component_name):
        self._swc_edit_window_selected_buffer = {}

        #Store Nodes Positions
        self._SWC_StoreCurrentNodesPositions()

        component_data = None
        for component in self._swc_components_data:
            if(component["Properties"]["Component_Name"]["value"] == component_name):
                component_data = component
                break

        #diasble window background
        constant_background_disable_widgets = ["ADD_SWC_BUTTON", "SWC_COMPONENT_LIST", "DUPLICATE_SWC_BUTTON", "DELETE_SWC_BUTTON"]
        for disable_tag in set(self._swc_background_disable_widgets_tags + constant_background_disable_widgets):
            if("node" in dpg.get_item_type(disable_tag).lower()):
                dpg.configure_item(disable_tag, draggable=False)
                self._swc_enabled_node_editor = False
            else:
                try:
                    dpg.configure_item(disable_tag, enabled=False)
                except:
                    pass

        if("SWC_EDIT_WINDOW" in dpg.get_aliases()):
            dpg.delete_item("SWC_EDIT_WINDOW", children_only=True)
        else:
            dpg.add_window(tag="SWC_EDIT_WINDOW", label="Edit SWC", min_size=[800, 200], no_collapse=True,
                       on_close=self._SWC_EditWindowOnCloseCallback, no_focus_on_appearing=False, no_bring_to_front_on_focus=False)

        with dpg.tab_bar(tag="SWC_EDIT_WINDOW_TAB_BAR", parent="SWC_EDIT_WINDOW"):
            with dpg.tab(tag="SWC_EDIT_WINDOW_TAB_BAR/PROPERTIES_TAB", label="Properties"):
                self._SWC_RenderPropertiesTab(parent="SWC_EDIT_WINDOW_TAB_BAR/PROPERTIES_TAB",
                                       component_data_pointer=component_data)

            with dpg.tab(tag="SWC_EDIT_WINDOW_TAB_BAR/SERVER_PORTS_TAB", label="Server Ports"):
                self._SWC_RnederServerPortsTab(parent="SWC_EDIT_WINDOW_TAB_BAR/SERVER_PORTS_TAB",
                                         component_data_pointer=component_data)

            with dpg.tab(tag="SWC_EDIT_WINDOW_TAB_BAR/CLIENT_PORTS_TAB", label="Client Ports"):
                self._SWC_RnederClientsPortsTab(parent="SWC_EDIT_WINDOW_TAB_BAR/CLIENT_PORTS_TAB",
                                         component_data_pointer=component_data, ports_type="Client_Ports")

            with dpg.tab(tag="SWC_EDIT_WINDOW_TAB_BAR/RUNNABLES_TAB", label="Runnables"):
                self._SWC_RenderRunnableTab(parent="SWC_EDIT_WINDOW_TAB_BAR/RUNNABLES_TAB",
                                            component_data_pointer=component_data)

        if(self._swc_edit_window_selected_tab != None):
            dpg.set_value("SWC_EDIT_WINDOW_TAB_BAR", self._swc_edit_window_selected_tab)
            self._swc_edit_window_selected_tab = None

    def _SWC_AddNewComponent(self, new_component, new_component_position=None):
        count = 1
        new_name = new_component["Properties"]["Component_Name"]["value"]
        component_name_list = self._SWC_GetComponentList()
        while (new_name in component_name_list):
            new_name = new_component["Properties"]["Component_Name"]["value"] + "_" + str(count)
            count += 1

        new_component["Properties"]["Component_Name"]["value"] = new_name
        if(new_component_position != None):
            new_component["Component_Metadata"]["node_editor_position"] = new_component_position

        while(True):
            flag = True
            for component in self._swc_components_data:
                if(component["Component_Metadata"]["node_editor_position"] == new_component["Component_Metadata"]["node_editor_position"]):
                    new_component["Component_Metadata"]["node_editor_position"][0] += 10
                    new_component["Component_Metadata"]["node_editor_position"][1] -= 10
                    flag = False
                    break
            if(flag):
                break

        self._swc_components_data.append(new_component)
        self._SWC_AddComponentToEditor(component=new_component, parent="SWC_NODE_EDITOR")
        self._SWC_StoreCurrentNodesPositions()

    def _SWC_AddNewComponentCallback(self, sender, app_data, user_data):
        new_component = copy.deepcopy(self._swc_components_data_structure_template[0])
        self._SWC_AddNewComponent(new_component=new_component)

        self._SWC_RenderComponentList(parent="SWC_LIST_WINDOW")

    def _SWC_DuplicateComponentCallback(self, sender, app_data, user_data):
        print(sender, app_data, user_data)

        for selected_node in self._swc_selected_nodes_buffer:
            component_name = selected_node[selected_node.rfind('/') + 1 :]
            for component in self._swc_components_data:
                if(component_name == component["Properties"]["Component_Name"]["value"]):
                    new_component = copy.deepcopy(component)

                    new_component_position = dpg.get_item_pos(selected_node)
                    new_component_position[0] = new_component_position[0] + 10
                    new_component_position[1] = new_component_position[1] - 10

                    self._SWC_AddNewComponent(new_component=new_component, new_component_position=new_component_position)

        self._SWC_RenderComponentList(parent="SWC_LIST_WINDOW")

    def DeleteComponent(self, component_to_delete):
        for component_name in component_to_delete:
            for component in self._swc_components_data:
                if(component_name == component["Properties"]["Component_Name"]["value"]):
                    pass
            #self._swc_components_data.remove(component)

        self._SWC_StoreCurrentNodesPositions()
        self._SWC_RenderComponentList(parent="SWC_LIST_WINDOW")


    def _SWC_DeleteComponentCallback(self, sender, app_data, user_data):
        print(sender, app_data, user_data)

        for node_link_tag in self._swc_selected_node_links_buffer:
            self._SWC_DeleteLinkCallback(sender=None, app_data=node_link_tag, user_data=None)

        for component_node_tag in self._swc_selected_nodes_buffer:
            for alias in dpg.get_aliases():
                if( ("CONNECTION" in alias) and ("/TO/" in alias) and (component_node_tag in alias) ):
                    self._SWC_DeleteLinkCallback(sender=None, app_data=alias, user_data=None)

            component_name = component_node_tag.split('/')[-1]
            for component in copy.deepcopy(self._swc_components_data):
                if(component_name == component["Properties"]["Component_Name"]["value"]):
                    self._swc_components_data.remove(component)
                    break

        self._SWC_StoreCurrentNodesPositions()
        self._SWC_RenderComponentList(parent="SWC_LIST_WINDOW")
        self._SWC_RenderNodeEditor(parent="SWC_NODE_EDITOR_WINDOW")

    def _SWC_AddComponentToEditor(self, component, parent):
        component_tag = parent + "/" + component["Properties"]["Component_Name"]["value"]
        with dpg.node(tag=component_tag, parent=parent, label=component["Properties"]["Component_Name"]["value"],
                      pos=component["Component_Metadata"]["node_editor_position"]):
            self._swc_background_disable_widgets_tags.append(component_tag)
            for client_port in component["Client_Ports"]["value"]:
                with dpg.node_attribute(tag=component_tag + "/" + client_port, parent=component_tag):
                    dpg.add_text(client_port)

            for server_port in component["Server_Ports"]["value"]:
                server_port = server_port["Server_Port_Id"]["value"]
                with dpg.node_attribute(tag=component_tag + "/" + server_port, parent=component_tag,
                                        attribute_type=dpg.mvNode_Attr_Output):
                    dpg.add_text(server_port)
        dpg.bind_item_handler_registry(item=component_tag, handler_registry=self._swc_node_handler_registry_tag)

    def _SWC_RenderNodeEditor(self, parent):
        self._swc_background_disable_widgets_tags = []
        dpg.delete_item("SWC_NODE_EDITOR")
        if(self._swc_node_handler_registry_tag != None):
            dpg.delete_item(self._swc_node_handler_registry_tag)

        self._swc_enabled_node_editor = True
        with dpg.item_handler_registry() as node_handler_registry_tag:
            self._swc_node_handler_registry_tag = node_handler_registry_tag
            dpg.add_item_double_clicked_handler(parent=node_handler_registry_tag, callback=self._SWC_NodeDoubleClickCallback,
                                         button=dpg.mvMouseButton_Left)

        dpg.add_node_editor(tag="SWC_NODE_EDITOR", parent=parent,
                            minimap=True, minimap_location=dpg.mvNodeMiniMap_Location_BottomRight,
                            callback=self._SWC_CreateLinkCallback, delink_callback=self._SWC_DeleteLinkCallback)
        for component in self._swc_components_data:
            self._SWC_AddComponentToEditor(component=component, parent="SWC_NODE_EDITOR")

        for connection in self._swc_connections_data:
            self._SWC_DrawLinkNodesFromConnection(connection=connection, parent="SWC_NODE_EDITOR")

    def _SWC_ListCallBack(self, sender, app_data, user_data):
        # comp_name = app_data
        self._SWC_OpenSWCEditWindow(app_data)


    def _SWC_RenderComponentList(self, parent):
        dpg.delete_item("SWC_COMPONENT_LIST")
        component_list = self._SWC_GetComponentList()
        dpg.add_listbox(component_list, tag="SWC_COMPONENT_LIST", parent=parent,
                        callback=self._SWC_ListCallBack, num_items=len(component_list), enabled=True)

    def ShowWindow(self, parent):
        with dpg.handler_registry():
            dpg.add_key_release_handler(key=dpg.mvKey_Delete, callback=self._SWC_DeleteComponentCallback)
            dpg.add_mouse_release_handler(button=dpg.mvMouseButton_Left, callback=self._SWC_NodeSelectionCallback)

        dpg.add_group(horizontal=True, tag="SWC_GROUP", parent=parent)
        dpg.add_child_window(tag="SWC_LIST_WINDOW", width=280, auto_resize_x=False, resizable_x=True,
                             horizontal_scrollbar=True, parent="SWC_GROUP")

        with dpg.group(horizontal=True, tag="SWC_LIST_WINDOW/SWC_BUTTON_GROUP", parent="SWC_LIST_WINDOW"):
            dpg.add_button(tag="ADD_SWC_BUTTON", label="Add SWC", parent="SWC_LIST_WINDOW/SWC_BUTTON_GROUP",
                           callback=self._SWC_AddNewComponentCallback)
            dpg.add_button(tag="DUPLICATE_SWC_BUTTON", label="Duplicate SWC", parent="SWC_LIST_WINDOW/SWC_BUTTON_GROUP",
                           callback=self._SWC_DuplicateComponentCallback, enabled=False)
            dpg.add_button(tag="DELETE_SWC_BUTTON", label="Delete SWC", parent="SWC_LIST_WINDOW/SWC_BUTTON_GROUP",
                           callback=self._SWC_DeleteComponentCallback, enabled=False)
        self._SWC_RenderComponentList(parent="SWC_LIST_WINDOW")

        dpg.add_child_window(tag="SWC_NODE_EDITOR_WINDOW", parent="SWC_GROUP")
        self._SWC_RenderNodeEditor(parent="SWC_NODE_EDITOR_WINDOW")

    def SaveData(self):
        self._SWC_StoreCurrentNodesPositions()
