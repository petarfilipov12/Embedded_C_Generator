import dearpygui.dearpygui as dpg
from Services.Services import SERVICES_GUI_Handler
from SWCs.SWCs import SWCs_GUI_Handler
from DataHandler.DataHandler import DataHandler
from Generator.Generator import Generate
import os
import time

GUI_HANDLERS = {}
DATA_HANDLER = None

def SaveAll():
    global GUI_HANDLERS

    with dpg.window(tag="SAVE_ALL_POP_UP", modal=True, no_title_bar=True, autosize=True, min_size=(0, 0)):
        with dpg.group(horizontal=True):
            dpg.add_loading_indicator(style=1)
            dpg.add_text("Saving Data")

        time.sleep(1)

        for key in GUI_HANDLERS:
            GUI_HANDLERS[key].SaveData()
        DATA_HANDLER.SaveData()

        dpg.delete_item("SAVE_ALL_POP_UP")

def MenuBarRefreshButtonCallback():
    print("Refresh")
    dpg.delete_item("PRIMARY_WINDOW_TAG", children_only=True)
    aliases = dpg.get_aliases()
    aliases.remove("PRIMARY_WINDOW_TAG")
    for alias in aliases:
        dpg.remove_alias(alias)
    ShowMainWondow()

def MainWindowMenuBar(parent):
    with dpg.menu_bar(tag="MAIN_WINDOW_MENU_BAR", parent=parent):
        with dpg.menu(label="Menu"):
            dpg.add_text("This menu is just for show!")
            dpg.add_menu_item(label="New")
            dpg.add_menu_item(label="Open")
            dpg.add_menu_item(label="Refresh", tag="MENU_REFRESH_BUTTON", callback=MenuBarRefreshButtonCallback)

        dpg.add_button(label="Save", tag="MENU_SAVE_BUTTON", callback=SaveAll)

def DesignButtonCallback(sender, app_data, user_data):
    #tab -> user_data

    global HANDLER_REGISTRY

    tag = user_data + "_MAIN_WINDOW_TAB"
    if(dpg.does_alias_exist(tag)):
        if(not dpg.is_item_visible(tag)):
            dpg.delete_item(tag)
            dpg.add_tab(parent="MAIN_WINDOW_TAB_BAR_TAG", tag=tag, label=user_data, closable=True)
            GUI_HANDLERS[user_data].ShowWindow(parent=tag)
    else:
        dpg.add_tab(parent="MAIN_WINDOW_TAB_BAR_TAG", tag=tag, label=user_data, closable=True)
        GUI_HANDLERS[user_data].ShowWindow(parent=tag)

def StartGenerationButtonCallback(sender, app_data, user_data):
    global DATA_HANDLER

    dpg.delete_item("GENERATION_WINDOW")
    time.sleep(0.05)
    SaveAll()
    Generate(data_handler=DATA_HANDLER, generation_data=user_data)

def GenerateButtonCallback(sender, app_data, user_data):
    global DATA_HANDLER

    data_to_generate = {
        "Services": [],
        "SWCs": []
    }

    def Update_data_to_generate(sender, app_data, user_data):
        keys = user_data.split("/")
        if(app_data):
            if(keys[1] not in data_to_generate[keys[0]]):
                data_to_generate[keys[0]].append(keys[1])
        else:
            if(keys[1] in data_to_generate[keys[0]]):
                data_to_generate[keys[0]].remove(keys[1])


    with dpg.window(tag="GENERATION_WINDOW", modal=True, on_close=lambda: dpg.delete_item("GENERATION_WINDOW")):
        dpg.add_text(default_value="Services:")
        for service in DATA_HANDLER.GetServices():
            dpg.add_checkbox(label=service, indent=20, user_data=("Services/" + str(service)), callback=Update_data_to_generate)
        dpg.add_text(default_value="SWCs:")
        for swc in DATA_HANDLER.GetSWCs():
            dpg.add_checkbox(label=swc, indent=20, user_data=("SWCs/" + str(swc)), callback=Update_data_to_generate)

        dpg.add_button(label="Start Generation", callback=StartGenerationButtonCallback, user_data=data_to_generate)

def MainWindowDesignViewButtons(parent):
    global GUI_HANDLERS

    dpg.add_child_window(tag="DESIGN_BUTTONS_WINDOW", parent=parent, resizable_y=False, resizable_x=False, auto_resize_y=True)
    with dpg.group(tag="DESIGN_BUTTONS_GROUP", parent="DESIGN_BUTTONS_WINDOW", horizontal=True):
        for key in GUI_HANDLERS.keys():
            dpg.add_button(tag="DESIGN_BUTTON_" + key, label=key, callback=DesignButtonCallback, user_data=key)
        dpg.add_button(label="Generate", callback=GenerateButtonCallback)
def MainWindowTabs(parent):
    global GUI_HANDLERS

    dpg.add_child_window(tag="TABS_WINDOW", parent=parent, resizable_y=True, auto_resize_y=False, height=400)
    dpg.add_tab_bar(tag="MAIN_WINDOW_TAB_BAR_TAG", parent="TABS_WINDOW")

def MainWindowFooter(parent):
    dpg.add_child_window(tag="FOOTER", parent=parent)
    dpg.add_input_text(parent="FOOTER", label="FOOTER")

def ShowMainWondow():
    MainWindowMenuBar(parent="PRIMARY_WINDOW_TAG")
    MainWindowDesignViewButtons(parent="PRIMARY_WINDOW_TAG")
    MainWindowTabs(parent="PRIMARY_WINDOW_TAG")
    MainWindowFooter(parent="PRIMARY_WINDOW_TAG")

def Init():
    global DATA_HANDLER
    global GUI_HANDLERS

    DATA_HANDLER = DataHandler(os.path.dirname(os.path.realpath(__file__)))

    GUI_HANDLERS["Services"] = SERVICES_GUI_Handler(DATA_HANDLER)
    GUI_HANDLERS["SWCs"] = SWCs_GUI_Handler(DATA_HANDLER)

    #Set disabled theme
    with dpg.theme() as disabled_theme:
        for comp_type in (dpg.mvMenuItem, dpg.mvButton, dpg.mvText, dpg.mvInputText):
            with dpg.theme_component(comp_type, enabled_state=False):
                dpg.add_theme_color(dpg.mvThemeCol_Text, (0.50 * 255, 0.50 * 255, 0.50 * 255, 1.00 * 255))
        dpg.bind_theme(disabled_theme)

    dpg.add_window(tag="PRIMARY_WINDOW_TAG")

if __name__ == '__main__':
    dpg.create_context()
    dpg.create_viewport(title='Custom Title')
    dpg.setup_dearpygui()
    # dpg.toggle_viewport_fullscreen()
    # dpg.maximize_viewport()

    Init()

    dpg.show_viewport()
    dpg.set_primary_window("PRIMARY_WINDOW_TAG", True)

    #dpg.start_dearpygui()
    first_render = True
    while dpg.is_dearpygui_running():
        dpg.render_dearpygui_frame()

        if(first_render):
            ShowMainWondow()
            first_render=False

    dpg.destroy_context()