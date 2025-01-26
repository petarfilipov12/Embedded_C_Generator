import dearpygui.dearpygui as dpg
from functools import reduce
from operator import getitem
import copy


class NavigationWindow:
    footer_manager = None
    data_handler = None
    _nav_service = None

    _nav_data_param_change_buffer = None

    _nav_navigation_window_tag = "NAV_NAVIGATION_WINDOW"
    _nav_param_window_tag = "NAV_PARAM_WINDOW"
    _nav_apply_button_tag = "NAV_APPLY_BUTTON"
    _nav_handler_registry_tag = "NAV_HANDLER_REGISTRY"
    _nav_main_group_tag = "OS_GROUP"
    _nav_tab = None

    _nav_add_runnables_selected_buffer = []
    _nav_current_param_window_data = {}

    def __init__(self, service, data_handler, footer_manager, tab):
        self.data_handler = data_handler
        self.footer_manager = footer_manager
        self._nav_service = service

        self._nav_tab = tab

        self._nav_navigation_window_tag = tab + "/" + self._nav_navigation_window_tag
        self._nav_param_window_tag = tab + "/" + self._nav_param_window_tag
        self._nav_apply_button_tag = tab + "/" + self._nav_apply_button_tag
        self._nav_handler_registry_tag = tab + "/" + self._nav_handler_registry_tag
        self._nav_main_group_tag = tab + '/' + self._nav_main_group_tag

        self._nav_data_param_change_buffer = {}

    def _NAV_DeletePopupWindows(self, old_tag_name=None):
        while(True):
            all_aliases_deleted = True
            for alias in dpg.get_aliases():
                if("POPUP" in alias):
                    if(old_tag_name):
                        if(old_tag_name in alias.split("/")):
                            dpg.delete_item(alias)
                            all_aliases_deleted = False
                            break
                    else:
                        dpg.delete_item(alias)
                        all_aliases_deleted = False
                        break
            if(all_aliases_deleted):
                break

    def _NAV_RemovePersistentAliases(self):
        aliases = dpg.get_aliases()
        for alias in aliases:
            if ( (self._nav_tab + "_ADD_NEW" in alias) or ("POPUP" in alias) ):
                dpg.remove_alias(alias)

    def _NAV_NavigationButtonCallback(self, sender, app_data, user_data):
        caller = dpg.get_item_alias(app_data[1])
        data = dpg.get_item_user_data(caller)

        #self.footer_manager.Footer_DisplayText(data["metadata"]["description"])
        self._NAV_RenderParamWindow(parameters_data=data["parameters"], parent=caller)

    def _NAV_ShowPopup(self, sender, app_data, user_data):
        caller = dpg.get_item_alias(app_data[1])
        dpg.configure_item(caller + "/POPUP", show=True)

    def _NAV_AddNew(self, caller_tag, new_container, duplicate_flag=False):
        new_container = copy.deepcopy(new_container)
        os_parent_containers = caller_tag.replace("/", "/data/").split("/")

        duplicate_src_container_name = None
        if (duplicate_flag):
            duplicate_src_container_name = os_parent_containers.pop()
            if (os_parent_containers[-1] == "data"):
                os_parent_containers.pop()

        os_data_pointer = reduce(getitem, os_parent_containers, self.data_handler.GetData()["Services"][self._nav_service])

        # pick new shortname
        new_shortname = None
        if (duplicate_flag):
            new_shortname = duplicate_src_container_name
        else:
            new_shortname = new_container["metadata"]["type"].split("/")[-1]

        if (isinstance(os_data_pointer["data"], dict)):
            count = 1
            while (True):
                temp_shortname = new_shortname + "_" + str(count)
                if (temp_shortname not in os_data_pointer["data"].keys()):
                    new_shortname = temp_shortname
                    break
                else:
                    count += 1

        # if child is last in tree set shortname
        new_container["parameters"]["ShortName"]["value"] = new_shortname

        os_data_pointer["data"][new_shortname] = new_container
        parent = "/".join(os_parent_containers).replace("/data/", "/")

        self.data_handler.Synchronize(data=self.data_handler.GetData()["Services"][self._nav_service])
        self._NAV_DisplayNavigation(data={new_shortname: os_data_pointer["data"][new_shortname]},
                                    parent=parent)

    def _NAV_AddNewCallback(self, sender, app_data, user_data):
        caller_tag = sender[: sender.rfind("/" + self._nav_tab + "_ADD_NEW")]
        new_container = copy.deepcopy(user_data)
        if ("data" in new_container.keys()):
            new_container["data"] = {}
        self._NAV_AddNew(caller_tag, new_container)

    def _NAV_DuplicateCallback(self, sender, app_data, user_data):
        caller_tag = sender[: sender.rfind("/" + self._nav_tab + "_DUPLICATE")]
        self._NAV_AddNew(caller_tag, copy.deepcopy(user_data), duplicate_flag=True)

    def _NAV_DeleteCallback(self, sender, app_data, user_data):
        caller_tag = sender[: sender.rfind("/" + self._nav_tab + "_DELETE")]
        os_parent_containers = caller_tag.replace("/", "/data/").split("/")

        delete_container = os_parent_containers.pop()
        os_data_pointer = reduce(getitem, os_parent_containers, self.data_handler.GetData()["Services"][self._nav_service])
        os_data_pointer.pop(delete_container)

        dpg.delete_item(caller_tag)
        dpg.delete_item(self._nav_param_window_tag, children_only=True)

        self._NAV_DeletePopupWindows(old_tag_name=delete_container)

        self.data_handler.Synchronize(data=self.data_handler.GetData()["Services"][self._nav_service])
        #self._NAV_DisplayNavigation(data=self.data_handler.GetData()["Services"][self._nav_service], parent=self._nav_navigation_window_tag)

    def _NAV_DisplayNavigation(self, data, parent):
        print("parent:", parent)
        for key in data.keys():
            tag = key
            if (parent != self._nav_navigation_window_tag):
                tag = parent + "/" + key

            dpg.add_tree_node(tag=tag, label=key, parent=parent, user_data=data[key], span_text_width=True)
            dpg.bind_item_handler_registry(item=tag, handler_registry=self._nav_handler_registry_tag)

            dpg.add_window(popup=True, show=False, tag=tag + "/POPUP", autosize=True, min_size=[0, 0],
                       no_move=False, no_background=False)

            if (("leaf" in data[key]["metadata"].keys()) and (data[key]["metadata"]["leaf"])):
                dpg.configure_item(tag, leaf=True)
            else:
                dpg.configure_item(tag, open_on_arrow=True)

                template_containers = data[key]["metadata"]["type"].split("/")
                os_data_structure_template_pointer = reduce(getitem, template_containers,
                                                            self.data_handler.GetDataStructureTemplates())

                for template_key in os_data_structure_template_pointer["data"].keys():
                    dpg.add_selectable(tag=tag + "/" + self._nav_tab + "_ADD_NEW/" + template_key, label="Add New " + template_key,
                                       parent=tag + "/POPUP", callback=self._NAV_AddNewCallback,
                                       user_data=os_data_structure_template_pointer["data"][template_key])

            if(data[key]["metadata"]["duplicable"]):
                dpg.add_selectable(tag=tag + "/" + self._nav_tab + "_DUPLICATE", label="Duplicate", parent=tag + "/POPUP",
                                   callback=self._NAV_DuplicateCallback, user_data=data[key])
            if(data[key]["metadata"]["deletable"]):
                dpg.add_selectable(tag=tag + "/" + self._nav_tab + "_DELETE", label="Delete", parent=tag + "/POPUP",
                                   callback=self._NAV_DeleteCallback)

            if (("data" in data[key]) and (data[key]["data"])):
                self._NAV_DisplayNavigation(data=data[key]["data"], parent=tag)

    def _NAV_RenderNavigationWindow(self):
        dpg.delete_item(self._nav_navigation_window_tag, children_only=True)
        self.ClearAll()

        with dpg.item_handler_registry() as handler_registry_tag:
            self._nav_handler_registry_tag = handler_registry_tag
            dpg.add_item_clicked_handler(parent=handler_registry_tag, callback=self._NAV_NavigationButtonCallback,
                                         button=dpg.mvMouseButton_Left)
            dpg.add_item_clicked_handler(parent=handler_registry_tag, callback=self._NAV_ShowPopup,
                                         button=dpg.mvMouseButton_Right)

        self._NAV_DisplayNavigation(data=self.data_handler.GetData()["Services"][self._nav_service], parent=self._nav_navigation_window_tag)

    def _NAV_ParamChangeCallBack(self, sender, app_data, user_data):
        self._nav_data_param_change_buffer[sender[sender.rfind("/") + 1:]] = app_data
        dpg.configure_item(self._nav_apply_button_tag, enabled=True)

    def _NAV_ApplyButtonCallback(self, sender, app_data, user_data):
        print("_NAV_ApplyButtonCallback")
        print(user_data)
        # parent = user_data
        containers = user_data.replace("/", "/data/").split("/")
        print(containers)
        data_pointer = reduce(getitem, containers[:-1], self.data_handler.GetData()["Services"][self._nav_service])
        print(data_pointer)

        for param_name in self._nav_data_param_change_buffer.keys():
            data_pointer[containers[-1]]["parameters"][param_name]["value"] = self._nav_data_param_change_buffer[
                param_name]

        if ("ShortName" in self._nav_data_param_change_buffer.keys()):
            data_pointer[self._nav_data_param_change_buffer["ShortName"]] = data_pointer.pop(containers[-1])
            dpg.delete_item(user_data)

            new_parent = user_data[: user_data.rfind("/")]
            data = copy.deepcopy(data_pointer[self._nav_data_param_change_buffer["ShortName"]])
            data = {self._nav_data_param_change_buffer["ShortName"]: data}

            self._NAV_DeletePopupWindows(old_tag_name=containers[-1])

            self._NAV_DisplayNavigation(data=data, parent=new_parent)

            self._NAV_RenderParamWindow(
                parameters_data=data_pointer[self._nav_data_param_change_buffer["ShortName"]]["parameters"],
                parent=new_parent + "/" + self._nav_data_param_change_buffer["ShortName"])
        else:
            dpg.configure_item(self._nav_apply_button_tag, enabled=False)

        self._nav_data_param_change_buffer = {}

    def _NAV_ReferenceGetSelectableList(self, reference_targets):
        selectable_list = []
        for reference_target in reference_targets:
            data_key = reference_target[: reference_target.find("/")]
            reference_target_temp = reference_target[reference_target.find("/") + 1 :]

            containers = reference_target_temp.split("/")
            data_pointer = reduce(getitem, containers, self.data_handler.GetData()[data_key])
            data = copy.deepcopy(data_pointer)

            temp = list(data["data"].keys())
            for index in range(len(temp)):
                temp[index] = reference_target + "/" + temp[index]
            selectable_list += temp

        return selectable_list

    def _NAV_GetReferenceListRecursive(self, data, keys):
        l = []

        if (len(keys) == 1):
            print("END DATA:", data)
            l.append(data[keys[0]])
        else:
            key = keys.pop(0)
            if (isinstance(data[key], list)):
                for elem in data[key]:
                    l = l + self._NAV_GetReferenceListRecursive(data=elem, keys=copy.deepcopy(keys))
            else:
                data = copy.deepcopy(data[key])
                l = l + self._NAV_GetReferenceListRecursive(data=data, keys=copy.deepcopy(keys))

        return l

    def _NAV_AddNewWindow_SelectableCallback(self, sender, app_data, user_data):
        print(sender, app_data, user_data)

        if(app_data == True):
            if(user_data not in self._nav_add_runnables_selected_buffer):
                self._nav_add_runnables_selected_buffer.append(user_data)
        else:
            if (user_data in self._nav_add_runnables_selected_buffer):
                self._nav_add_runnables_selected_buffer.remove(user_data)

        self._nav_add_runnables_selected_buffer = list(set(self._nav_add_runnables_selected_buffer))

        if(len(self._nav_add_runnables_selected_buffer) > 0):
            dpg.configure_item("ADD_NEW_WINDOW/ADD_RUNNABLES_BUTTON", enabled=True)
        else:
            dpg.configure_item("ADD_NEW_WINDOW/ADD_RUNNABLES_BUTTON", enabled=False)

    def _NAV_AddNewWindow_AddRunnablesButtonCallback(self, sender, app_data, user_data):
        print(sender, app_data, user_data)

        self._nav_add_runnables_selected_buffer = list(set(self._nav_add_runnables_selected_buffer))
        user_data["value"] = user_data["value"] + copy.deepcopy(self._nav_add_runnables_selected_buffer)

        dpg.delete_item("ADD_NEW_WINDOW")

        self._NAV_RenderParamWindow(self._nav_current_param_window_data["parameters_data"], self._nav_current_param_window_data["parent"])

    def _NAV_OpenAddNewWindow(self, sender, app_data, user_data):
        print(sender, app_data, user_data)

        self._nav_add_runnables_selected_buffer = []
        if("ADD_NEW_WINDOW" in dpg.get_aliases()):
            dpg.delete_item("ADD_NEW_WINDOW")

        param_name = sender[sender.rfind('/') + 1 :]

        dpg.add_window(tag="ADD_NEW_WINDOW", label="Add new " + param_name, min_size=[800, 200], no_collapse=True,
                       no_focus_on_appearing=False, no_bring_to_front_on_focus=False)

        table_tag = "ADD_NEW_WINDOW/TABLE"
        dpg.add_input_text(hint="Filter", parent="ADD_NEW_WINDOW",
                           user_data=table_tag, callback=lambda s, a, u: dpg.set_value(u, dpg.get_value(s)))
        with dpg.table(tag=table_tag, parent= "ADD_NEW_WINDOW", policy=dpg.mvTable_SizingFixedFit, resizable=False,
                       no_host_extendX=False,header_row=False, borders_outerV=True, borders_outerH=True):
            dpg.add_table_column(width_stretch=True)

            selectable_list = []
            for reference_target in user_data["metadata"]["reference_targets"]:
                containers = reference_target.split("/")
                selectable_list = selectable_list + self._NAV_GetReferenceListRecursive(data=copy.deepcopy(self.data_handler.GetData()), keys=containers)
            print("TUK")
            print(selectable_list)

            for value in user_data["value"]:
                if(value in selectable_list):
                    selectable_list.remove(value)

            for selectable_text in selectable_list:
                with dpg.table_row(filter_key=selectable_text):
                    dpg.add_selectable(label=selectable_text, callback=self._NAV_AddNewWindow_SelectableCallback, user_data=selectable_text)

        parent = "ADD_NEW_WINDOW"
        dpg.add_button(tag= parent + "/ADD_RUNNABLES_BUTTON", label="Add Runnables", parent=parent, enabled=False,
                       callback=self._NAV_AddNewWindow_AddRunnablesButtonCallback, user_data=user_data)

    def _NAV_RenderParamWindow(self, parameters_data, parent):
        #parameters_data = copy.deepcopy(parameters_data)

        self._nav_current_param_window_data["parameters_data"] = parameters_data
        self._nav_current_param_window_data["parent"] = parent


        dpg.delete_item(self._nav_param_window_tag, children_only=True)
        with dpg.table(header_row=False, parent=self._nav_param_window_tag, borders_innerH=True):
            dpg.add_table_column()
            dpg.add_table_column()

            # Set shortname param to be first
            other_params = parameters_data.copy()
            parameters_data = {}
            parameters_data["ShortName"] = other_params.pop("ShortName")
            parameters_data.update(other_params)

            temp_reference_list_data = {}

            for param_name in parameters_data.keys():
                tag = parent + "/parameters/" + param_name

                with dpg.table_row():
                    txt = dpg.add_text(param_name, user_data=parameters_data[param_name])
                    dpg.bind_item_handler_registry(item=txt, handler_registry=self.footer_manager.Footer_GetHandlerRegistry())

                    temp_reference_list_data[param_name] = {}
                    temp_reference_list_data[param_name]["data_pointer"] = parameters_data[param_name]
                    temp_reference_list_data[param_name]["selected_buffer"] = []

                    if(parameters_data[param_name]["metadata"]["type"] == "string"):
                        dpg.add_input_text(tag=tag, default_value=parameters_data[param_name]["value"],
                                           callback=self._NAV_ParamChangeCallBack, width=-1)
                    elif(parameters_data[param_name]["metadata"]["type"] == "int"):
                        dpg.add_input_int(tag=tag, default_value=int(parameters_data[param_name]["value"]),
                                           callback=self._NAV_ParamChangeCallBack, width=-1)
                    elif(parameters_data[param_name]["metadata"]["type"] == "selectable"):
                        dpg.add_combo(parameters_data[param_name]["metadata"]["selectable_list"], tag=tag,
                                      default_value=parameters_data[param_name]["value"],
                                      callback=self._NAV_ParamChangeCallBack, width=-1)
                    elif(parameters_data[param_name]["metadata"]["type"] == "reference"):
                        selectable_list = self._NAV_ReferenceGetSelectableList(parameters_data[param_name]["metadata"]["reference_targets"])
                        dpg.add_combo(selectable_list, tag=tag,
                                      default_value=parameters_data[param_name]["value"],
                                      callback=self._NAV_ParamChangeCallBack, width=-1)
                    elif (parameters_data[param_name]["metadata"]["type"] == "reference_list"):
                        with dpg.group(horizontal=True):
                            with dpg.group(horizontal=False):
                                delete_button = dpg.add_button(label="x", enabled=False, user_data=param_name,
                                    callback=lambda sender, app_data, user_data: (
                                        [temp_reference_list_data[user_data]["data_pointer"]["value"].remove(elem) for elem in
                                         temp_reference_list_data[user_data]["selected_buffer"]],

                                        self._NAV_RenderParamWindow(
                                            self._nav_current_param_window_data["parameters_data"],
                                            self._nav_current_param_window_data["parent"])
                                    ))
                                temp_reference_list_data[param_name]["delete_button"] = delete_button

                                dpg.add_button(tag="ADD_NEW_BUTTON/" + param_name, label="+",
                                                            callback=self._NAV_OpenAddNewWindow, user_data=parameters_data[param_name])
                            with dpg.table(policy=dpg.mvTable_SizingFixedFit, resizable=False, no_host_extendX=False,
                                           header_row=False):
                                dpg.add_table_column(width_stretch=True)

                                for elem in parameters_data[param_name]["value"]:
                                    with dpg.table_row():
                                        dpg.add_selectable(span_columns=True, label=elem, user_data=(elem,param_name),
                                                           callback=lambda sender, app_data, user_data: (
                                            temp_reference_list_data[user_data[1]]["selected_buffer"].append(user_data[0]) if user_data[0] not in temp_reference_list_data[user_data[1]]["selected_buffer"] else temp_reference_list_data[user_data[1]]["selected_buffer"].remove(user_data[0]),
                                            dpg.configure_item(temp_reference_list_data[user_data[1]]["delete_button"], enabled=(len(temp_reference_list_data[user_data[1]]["selected_buffer"]) > 0))
                                        ))
                    elif (parameters_data[param_name]["metadata"]["type"] == "bool"):
                        dpg.add_checkbox(tag=tag, default_value=parameters_data[param_name]["value"],
                                          callback=self._NAV_ParamChangeCallBack)

                    if (not parameters_data[param_name]["metadata"]["changeable"]):
                        dpg.configure_item(tag, enabled=False)
            with dpg.table_row():
                dpg.add_button(tag=self._nav_apply_button_tag, label="Apply Changes",
                               callback=self._NAV_ApplyButtonCallback, user_data=parent, enabled=False)

    def ShowNavigationWindow(self, parent):
        dpg.add_group(horizontal=True, tag=self._nav_main_group_tag, parent=parent)
        dpg.add_child_window(tag=self._nav_navigation_window_tag, width=200, auto_resize_x=False, resizable_x=True,
                             horizontal_scrollbar=True, parent=self._nav_main_group_tag)

        dpg.add_child_window(tag=self._nav_param_window_tag, parent=self._nav_main_group_tag, )

        self._NAV_RenderNavigationWindow()

    def ClearAll(self):
        self._NAV_DeletePopupWindows()
        self._NAV_RemovePersistentAliases()
