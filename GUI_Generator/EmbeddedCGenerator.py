import dearpygui.dearpygui as dpg
from Services.Services import SERVICES_GUI_Handler
from SWCs.SWCs import SWCs_GUI_Handler
from DataHandler.DataHandler import DataHandler
from Generator.Generator import Generator
from FooterManager.FooterManager import FooterManager
import time

class EmbeddedCGenerator:
    primary_window_tag = "PRIMARY_WINDOW_TAG"
    
    data_handler = None
    gui_handlers = {}
    generator = None
    footer_manager = None

    proj_title = "Proj_Title"
    data_dir = None
    gen_dir = None
    def __init__(self, proj_title, data_dir, gen_dir):
        self.proj_title = proj_title
        self.data_dir = data_dir
        self.gen_dir = gen_dir

        # self.data_handler = DataHandler(os.path.dirname(os.path.realpath(__file__)))
        self.data_handler = DataHandler(data_dir)
        self.footer_manager = FooterManager(parent=self.primary_window_tag)

        self.gui_handlers["Services"] = SERVICES_GUI_Handler(self.data_handler, self.footer_manager)
        self.gui_handlers["SWCs"] = SWCs_GUI_Handler(self.data_handler, self.footer_manager)

        self.generator = Generator(data_handler=self.data_handler, gen_folder=self.gen_dir)
        # Set disabled theme
        # with dpg.theme() as disabled_theme:
        #     for comp_type in (dpg.mvMenuItem, dpg.mvButton, dpg.mvText, dpg.mvInputText):
        #         with dpg.theme_component(comp_type, enabled_state=False):
        #             dpg.add_theme_color(dpg.mvThemeCol_Text, (0.50 * 255, 0.50 * 255, 0.50 * 255, 1.00 * 255))
        #     dpg.bind_theme(disabled_theme)

    def SaveAll(self):
        with dpg.window(tag="SAVE_ALL_POP_UP", modal=True, no_title_bar=True, autosize=True, min_size=(0, 0)):
            with dpg.group(horizontal=True):
                dpg.add_loading_indicator(style=1)
                dpg.add_text("Saving Data")

            time.sleep(1)

            for key in self.gui_handlers:
                self.gui_handlers[key].SaveData()
            self.data_handler.SaveData()

            dpg.delete_item("SAVE_ALL_POP_UP")

    def MenuBarRefreshButtonCallback(self):
        print("Refresh")
        dpg.delete_item(self.primary_window_tag, children_only=True)
        aliases = dpg.get_aliases()
        aliases.remove(self.primary_window_tag)
        for alias in aliases:
            dpg.remove_alias(alias)
        self.ShowMainWondow()

    def MainWindowMenuBar(self, parent):
        with dpg.menu_bar(tag="MAIN_WINDOW_MENU_BAR", parent=parent):
            with dpg.menu(label="Menu"):
                dpg.add_menu_item(label="Save", tag="MENU_SAVE_BUTTON", callback=self.SaveAll)
                dpg.add_menu_item(label="Refresh", tag="MENU_REFRESH_BUTTON", callback=self.MenuBarRefreshButtonCallback)

    def DesignButtonCallback(self, sender, app_data, user_data):
        #tab -> user_data

        tag = user_data + "_MAIN_WINDOW_TAB"
        if(dpg.does_alias_exist(tag)):
            if(not dpg.is_item_visible(tag)):
                dpg.delete_item(tag)
                dpg.add_tab(parent="MAIN_WINDOW_TAB_BAR_TAG", tag=tag, label=user_data, closable=True)
                self.gui_handlers[user_data].ShowWindow(parent=tag)
        else:
            dpg.add_tab(parent="MAIN_WINDOW_TAB_BAR_TAG", tag=tag, label=user_data, closable=True)
            self.gui_handlers[user_data].ShowWindow(parent=tag)

    def StartGenerationButtonCallback(self, sender, app_data, user_data):
        dpg.delete_item("GENERATION_WINDOW")
        time.sleep(0.05)
        self.SaveAll()
        self.generator.Generate(generation_data=user_data)

    def GenerateButtonCallback(self, sender, app_data, user_data):
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
            for service in self.data_handler.GetServices():
                dpg.add_checkbox(label=service, indent=20, user_data=("Services/" + str(service)), callback=Update_data_to_generate)
            dpg.add_text(default_value="SWCs:")
            for swc in self.data_handler.GetSWCs():
                dpg.add_checkbox(label=swc, indent=20, user_data=("SWCs/" + str(swc)), callback=Update_data_to_generate)

            dpg.add_button(label="Start Generation", callback=self.StartGenerationButtonCallback, user_data=data_to_generate)

    def MainWindowDesignViewButtons(self, parent):
        dpg.add_child_window(tag="DESIGN_BUTTONS_WINDOW", parent=parent, resizable_y=False, resizable_x=False, auto_resize_y=True)
        with dpg.group(tag="DESIGN_BUTTONS_GROUP", parent="DESIGN_BUTTONS_WINDOW", horizontal=True):
            for key in self.gui_handlers.keys():
                dpg.add_button(tag="DESIGN_BUTTON_" + key, label=key, callback=self.DesignButtonCallback, user_data=key)
            dpg.add_button(label="Generate", callback=self.GenerateButtonCallback)
    def MainWindowTabs(self, parent):
        dpg.add_child_window(tag="TABS_WINDOW", parent=parent, resizable_y=True, auto_resize_y=False, height=600)
        dpg.add_tab_bar(tag="MAIN_WINDOW_TAB_BAR_TAG", parent="TABS_WINDOW")

    def ShowMainWondow(self):
        self.MainWindowMenuBar(parent=self.primary_window_tag)
        self.MainWindowDesignViewButtons(parent=self.primary_window_tag)
        self.MainWindowTabs(parent=self.primary_window_tag)
        self.footer_manager.Footer_DisplayWindow()

    def Run(self):
        dpg.create_context()
        dpg.create_viewport(title=self.proj_title)
        dpg.setup_dearpygui()
        # dpg.toggle_viewport_fullscreen()
        # dpg.maximize_viewport()

        dpg.add_window(tag=self.primary_window_tag)
        dpg.show_viewport()
        dpg.set_primary_window(self.primary_window_tag, True)

        # dpg.start_dearpygui()
        first_render = True
        while dpg.is_dearpygui_running():
            dpg.render_dearpygui_frame()

            if (first_render):
                self.ShowMainWondow()
                first_render = False

        dpg.destroy_context()