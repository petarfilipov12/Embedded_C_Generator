import copy
import re
from common import FileHandler

class Generator:
    _generator_data_handler = None
    _generator_gen_folder = None

    _generator_gen_service_struct_name = None
    _generator_gen_service_current_element = -1

    _generator_gen_include_section_start = "/* DO NOT REMOVE COMMENT - GEN INCLUDE SECTION */"
    _generator_gen_server_ports_vars_section_start = "/* DO NOT REMOVE COMMENT - GEN SERVER PORTS-VARS SECTION */"
    _generator_gen_server_ports_funcs_section_start = "/* DO NOT REMOVE COMMENT - GEN SERVER PORTS-FUNCS SECTION */"
    _generator_gen_runnables_section_start = "/* DO NOT REMOVE COMMENT - GEN RUNNABLES SECTION */"
    _generator_gen_end_section = "/* DO NOT REMOVE COMMENT - GEN END SECTION */"
    _generator_gen_start_func = "/* DO NOT REMOVE COMMENT - GEN START FUNC */"
    _generator_gen_end_func = "/* DO NOT REMOVE COMMENT - GEN END FUNC */"
    _generator_gen_empty_file_s = (_generator_gen_include_section_start + "\n" + _generator_gen_end_section + "\n\n" +
                                   _generator_gen_server_ports_vars_section_start + "\n" + _generator_gen_end_section + "\n\n" +
                                   _generator_gen_server_ports_funcs_section_start + "\n" + _generator_gen_end_section + "\n\n" +
                                   _generator_gen_runnables_section_start + "\n" + _generator_gen_end_section)

    def __init__(self, data_handler, gen_folder):
        self._generator_data_handler = data_handler
        self._generator_gen_folder = gen_folder

    def _Generator_ReadFile(self, path_to_file):
        return FileHandler.ReadFile(path_to_file)

    def _Generator_WriteFile(self, s, path_to_file):
        FileHandler.WriteFile(s=s, path_to_file=path_to_file, create_path_to_file=True)

    def _Generator_DeleteFile(self, path_to_file):
        FileHandler.DeleteFile(path_to_file)

    def _Generator_GenService_GenerateDataCfgCFile(self, prefix, data, data_cfg_c_file_s=None, buffers_s=None):
        for key in data.keys():
            metadata = data[key]["metadata"]

            if ( ("generate_data_data_files" in metadata.keys()) and (metadata["generate_data_data_files"] == True) ):
                self._generator_gen_service_struct_name = prefix + metadata["generate_data_data_files_data_name"]
                self._generator_gen_service_current_element = -1
                if (data_cfg_c_file_s == None):
                    data_cfg_c_file_s = ""
                else:
                    data_cfg_c_file_s = data_cfg_c_file_s.strip() + "\n}\n"

                if(len(data[key]["data"]) > 0):
                    data_cfg_c_file_s = data_cfg_c_file_s.strip() + "\n\n" + prefix + metadata["generate_data_data_files_data_type"] + " " + prefix + metadata["generate_data_data_files_data_name"] + "[" + prefix + key + "_Count];\n\n"
                data_cfg_c_file_s += "inline void " + prefix + metadata["generate_data_data_files_data_name"] + metadata["generate_data_data_files_init_func_postfix"] + "(void)\n{\n"

            if ( (self._generator_gen_service_struct_name != None) and ("generate_params" in metadata.keys()) and (metadata["generate_params"] == True)):
                params = data[key]["parameters"]
                short_name = params.pop("ShortName", None)
                short_name = short_name["value"]
                self._generator_gen_service_current_element += 1

                for param_name in params.keys():
                    if( ("gen_buffer" in params[param_name]["metadata"].keys()) and (params[param_name]["metadata"]["gen_buffer"] == True) ):
                        current_buffer_name = "NULL"
                        if( (params[param_name]["metadata"]["type"] == "int") and (int(params[param_name]["value"]) > 0) ):
                            if(buffers_s == None):
                                buffers_s = ""
                            current_buffer_name = prefix + short_name + "_" + params[param_name]["metadata"]["gen_buffer_var_name"]
                            buffers_s += "uint8 " + current_buffer_name + "[" + prefix + short_name + "_" + param_name + "];\n"

                        data_cfg_c_file_s += ("\t" + self._generator_gen_service_struct_name + "[" + str(
                            self._generator_gen_service_current_element) + "]." + params[param_name]["metadata"]["gen_buffer_var_name"])
                        if(current_buffer_name == "NULL"):
                            data_cfg_c_file_s += " = NULL;\n"
                        else:
                            data_cfg_c_file_s += " = &" + current_buffer_name + "[0];\n"
                        data_cfg_c_file_s += ("\t" + self._generator_gen_service_struct_name + "[" + str(
                            self._generator_gen_service_current_element) + "]." + params[param_name]["metadata"]["gen_buffer_size_var_name"]
                                              + " = " + prefix + short_name + "_" + param_name + ";\n")

                    else:
                        data_cfg_c_file_s += ("\t" + self._generator_gen_service_struct_name + "[" + str(self._generator_gen_service_current_element) + "]." + param_name[0].lower() + param_name[1 :]
                                              + " = " + prefix + short_name + "_" + param_name + ";\n")

                data_cfg_c_file_s += "\t" + self._generator_gen_service_struct_name + "[" + str(
                    self._generator_gen_service_current_element) + "].status = RET_NOT_OK;\n\n"

                if (("generate_data_data_files" in metadata.keys()) and (
                        metadata["generate_data_data_files"] == True) and (len(data[key]["data"]) > 0)):
                    self._generator_gen_service_struct_name = None

            if (("leaf" not in metadata.keys()) or (metadata["leaf"] == False)):
                data_cfg_c_file_s, buffers_s = self._Generator_GenService_GenerateDataCfgCFile(prefix=prefix, data=data[key]["data"],
                                                                               data_cfg_c_file_s=data_cfg_c_file_s,
                                                                               buffers_s=buffers_s)

        return data_cfg_c_file_s, buffers_s


    def _Generator_GenService_GenerateDataCfgHFile(self, prefix, data):
        data_cfg_h_file_s = None

        for key in data.keys():
            metadata = data[key]["metadata"]

            if ( ("generate_data_data_files" in metadata.keys()) and (metadata["generate_data_data_files"] == True) ):
                if (data_cfg_h_file_s == None):
                    data_cfg_h_file_s = ""
                else:
                    data_cfg_h_file_s = data_cfg_h_file_s.strip() + "\n\n"

                if( ("generate_data_data_files_data_type" in metadata.keys()) and (len(data[key]["data"]) > 0) ):
                    data_cfg_h_file_s += "extern " + prefix + metadata["generate_data_data_files_data_type"] + " "

                if( ("generate_data_data_files_data_name" in metadata.keys()) and (len(data[key]["data"]) > 0) ):
                    data_cfg_h_file_s += prefix + metadata["generate_data_data_files_data_name"] + "[" + prefix + key + "_Count];\n\n"

                if("generate_data_data_files_init_func_postfix" in metadata.keys()):
                    data_cfg_h_file_s += "extern inline void " + prefix + metadata["generate_data_data_files_data_name"] + metadata["generate_data_data_files_init_func_postfix"] + "(void);"

        return data_cfg_h_file_s
    def _Generator_GenService_GenerateCfgFile(self, prefix, data, cfg_file_s=None, cfg_file_data_init_s=None):
        if (cfg_file_s == None):
            cfg_file_s = ""

        for key in data.keys():
            metadata = data[key]["metadata"]

            if (("generate_data_count" in metadata.keys()) and (metadata["generate_data_count"] == True)):
                cfg_file_s += "#define " + prefix + key + "_Count " + str(len(data[key]["data"])) + "\n\n"

            if (("generate_data_init_define" in metadata.keys()) and (metadata["generate_data_init_define"] == True)):
                cfg_file_data_init_s = "#define " + prefix + "Data_Init \\\n"

            if( ("generate_params" in metadata.keys()) and (metadata["generate_params"] == True) ):
                params = data[key]["parameters"]
                short_name = params.pop("ShortName", None)
                short_name = short_name["value"]

                if(cfg_file_data_init_s != None):
                    if(short_name != None):
                        cfg_file_data_init_s += "/* " + short_name + " */"
                    cfg_file_data_init_s += "{"

                for param_name in params.keys():
                    define_name = prefix + short_name + "_" + param_name
                    cfg_file_s += "#define " + define_name + " "
                    if(data[key]["parameters"][param_name]["metadata"]["type"] == "reference"):
                        service = data[key]["parameters"][param_name]["value"]
                        service = service[service.find('/') + 1 :]
                        service = service[: service.find("/")]

                        ref_container_shortname = data[key]["parameters"][param_name]["value"]
                        ref_container_shortname = ref_container_shortname[ref_container_shortname.rfind("/") + 1 :]

                        cfg_file_s += service + "_Service_" + ref_container_shortname + "_Id\n"
                    else:
                        cfg_file_s += str(data[key]["parameters"][param_name]["value"]) + "\n"

                    if(cfg_file_data_init_s != None):
                        cfg_file_data_init_s += define_name + ", "
                cfg_file_s += "\n"

                if (cfg_file_data_init_s != None):
                    cfg_file_data_init_s += "RET_NOT_OK}, \\\n"

            if( ("leaf" not in metadata.keys()) or (metadata["leaf"] == False) ):
                cfg_file_s, cfg_file_data_init_s = self._Generator_GenService_GenerateCfgFile(prefix=prefix, data=data[key]["data"], cfg_file_s=cfg_file_s, cfg_file_data_init_s=cfg_file_data_init_s)

            if (("generate_data_init_define" in metadata.keys()) and (metadata["generate_data_init_define"] == True)):
                cfg_file_data_init_s = cfg_file_data_init_s[: cfg_file_data_init_s.rfind("}") + 1]
                cfg_file_s += cfg_file_data_init_s
                cfg_file_data_init_s = None

        cfg_file_s += "\n"

        return cfg_file_s, cfg_file_data_init_s



    def _Generator_GenOs(self, os_data):
        cfg_os_file_s = ""
        tasks_config_s = "#define OS_TASKS_CONFIG()\t\\\n"
        create_tasks_define_s = "#define OS_CREATE_TASKS()\t\\\n"

        if("OS_Tasks" in os_data.keys()):
            for os_task in os_data["OS_Tasks"]["data"].values():
                task_name = os_task["parameters"]["ShortName"]["value"]
                priority = os_task["parameters"]["Priority"]["value"]
                cycle = os_task["parameters"]["Cycle"]["value"]
                stack_size = os_task["parameters"]["StackSize"]["value"]
                init_runnables = os_task["parameters"]["InitRunnables"]["value"]
                cyclic_runnables = os_task["parameters"]["CyclicRunnables"]["value"]

                init_runnables_define_name = task_name + "_InitRunnables"
                runnables_s = "#define " + init_runnables_define_name + "\t\\\n"
                for runnble in init_runnables:
                    runnables_s += runnble + "();\t\\\n"
                runnables_s = runnables_s[: runnables_s.rfind('\\')].strip()
                cfg_os_file_s += runnables_s + "\n\n"

                cyclic_runnables_define_name = task_name + "_CyclicRunnables"
                runnables_s = "#define " + cyclic_runnables_define_name + "\t\\\n"
                for runnble in cyclic_runnables:
                    runnables_s += runnble + "();\t\\\n"
                runnables_s = runnables_s[: runnables_s.rfind('\\')].strip()
                cfg_os_file_s += runnables_s + "\n\n"

                tasks_config_s += ("OS_TASK(" + task_name + ", " + str(cycle) + "u, " + str(stack_size) + "u, " +
                                   str(priority) + "u, " + init_runnables_define_name + ", " + cyclic_runnables_define_name + ")\t\\\n")

                create_tasks_define_s += "OS_CreateTask(" + task_name + ", " + str(cycle) + "u, " + str(stack_size) + "u, " + str(priority) + "u);\t\\\n"


        tasks_config_s = tasks_config_s[: tasks_config_s.rfind('\\')].strip()
        create_tasks_define_s = create_tasks_define_s[: create_tasks_define_s.rfind('\\')].strip()
        cfg_os_file_s = cfg_os_file_s.strip() + "\n\n" + tasks_config_s + "\n\n" + create_tasks_define_s

        return cfg_os_file_s

    def _Generator_WrapFile(self, file_s, file_name, include_libs, ifndef_protection=False):
        if ( isinstance(file_s, str) and file_name ):
            include_s = ""
            if(isinstance(include_libs, list)):
                for lib in include_libs:
                    include_s += "#include \"" + lib + "\"\n"
                if(len(include_libs) > 0):
                    include_s = include_s.strip() + "\n\n"

            ifndef_protection_s = ""
            if(ifndef_protection):
                ifndef_protection_define = file_name.replace('.', '_').upper()
                ifndef_protection_s = "#ifndef " + ifndef_protection_define + "\n"
                ifndef_protection_s += "#define " + ifndef_protection_define + "\n\n"

            file_s = ifndef_protection_s + include_s + file_s.strip()

            if(ifndef_protection):
                file_s = file_s.strip() + "\n\n#endif"

        return file_s

    def GenerateService(self, service_data, service_name):
        prefix = service_name + "_Service_"
        service_h_file_name = service_name + "_Service.h"

        cfg_file_name = "GEN_" + service_name + "_Service_CFG.h"
        self._Generator_DeleteFile(self._generator_gen_folder + "/" + cfg_file_name)
        data_cfg_h_file_name = "GEN_" + service_name + "_Service_DATA_CFG.h"
        self._Generator_DeleteFile(self._generator_gen_folder + "/" + data_cfg_h_file_name)
        data_cfg_c_file_name = "GEN_" + service_name + "_Service_DATA_CFG.c"
        self._Generator_DeleteFile(self._generator_gen_folder + "/" + data_cfg_c_file_name)

        cfg_file_s, cfg_file_data_init_s = self._Generator_GenService_GenerateCfgFile(prefix=prefix, data=copy.deepcopy(service_data))
        if(cfg_file_s != None):
            cfg_file_s = self._Generator_WrapFile(file_s=cfg_file_s, file_name=cfg_file_name, include_libs=["Types.h"],
                                                  ifndef_protection=True)
            self._Generator_WriteFile(cfg_file_s, self._generator_gen_folder + "/" + cfg_file_name)

        data_cfg_h_file_s = self._Generator_GenService_GenerateDataCfgHFile(prefix=prefix, data=copy.deepcopy(service_data))
        if(data_cfg_h_file_s != None):
            data_cfg_h_file_s = self._Generator_WrapFile(file_s=data_cfg_h_file_s, file_name=data_cfg_h_file_name,
                                                         include_libs=["Types.h", "Queue.h", cfg_file_name, service_h_file_name], ifndef_protection=True)
            self._Generator_WriteFile(data_cfg_h_file_s, self._generator_gen_folder + "/" + data_cfg_h_file_name)

        data_cfg_c_file_s, buffers_s = self._Generator_GenService_GenerateDataCfgCFile(prefix=prefix, data=copy.deepcopy(service_data))
        if(data_cfg_c_file_s != None):
            if(buffers_s == None):
                buffers_s = ""

            data_cfg_c_file_s = data_cfg_c_file_s.strip()
            if(data_cfg_c_file_s[len(data_cfg_c_file_s) - 1] != '}'):
                data_cfg_c_file_s = data_cfg_c_file_s.strip() + "\n}"

            data_cfg_c_file_s = buffers_s.strip() + "\n\n" + data_cfg_c_file_s.strip()

            data_cfg_c_file_s = self._Generator_WrapFile(file_s=data_cfg_c_file_s, file_name=data_cfg_c_file_name, include_libs=[data_cfg_h_file_name],
                                                  ifndef_protection=False)
            self._Generator_WriteFile(data_cfg_c_file_s, self._generator_gen_folder + "/" + data_cfg_c_file_name)

    def GenerateOS(self, os_data):
        cfg_file_name = "GEN_OS_CFG.h"
        self._Generator_DeleteFile(self._generator_gen_folder + "/" + cfg_file_name)

        cfg_file_s = self._Generator_GenOs(os_data)
        if (cfg_file_s != None):
            cfg_file_s = self._Generator_WrapFile(file_s=cfg_file_s, file_name=cfg_file_name, include_libs=[],
                                                  ifndef_protection=True)
            self._Generator_WriteFile(cfg_file_s, self._generator_gen_folder + "/" + cfg_file_name)

    def _Generator_GenServicePorts(self, service_ports_data):
        service_ports_s = False

        functions_ports_s = ""
        var_ports_s = ""

        if(len(service_ports_data) > 0):
            service_ports_s = True

        for service_port in service_ports_data:
            service_port_name = service_port["Server_Port_Id"]["value"]

            if(service_port["Port_Type"]["value"] == "FUNCTION"):
                functions_ports_s += "extern Func_ReturnType " + service_port_name + "(" + ", ".join(service_port["Port_Params"]["value"]) + ");\n"
            elif(service_port["Port_Type"]["value"] == "VARIABLE"):
                var_ports_s += "extern " + service_port["Port_Params"]["value"][0] + " " + service_port_name + ";\n"

        if(service_ports_s):
            service_ports_s = var_ports_s.strip() + "\n" + functions_ports_s.strip()
        else:
            service_ports_s = None

        return service_ports_s

    def _Generator_GenClientPorts(self, component_data, connections_data, client_ports_data):
        component_name = component_data["Properties"]["Component_Name"]["value"]
        client_ports_s = None
        includes = None

        for client_port in client_ports_data:
            server_port = None
            server_component = None
            for connection in connections_data:
                if( (connection["Client_Port"] == client_port) and (connection["Client_Component"] == component_name) ):
                    server_port = connection["Server_Port"]
                    server_component = connection["Server_Component"]

            if (client_ports_s == None):
                client_ports_s = ""

            if( (server_port != None) and (server_component != None) ):
                if (includes == None):
                    includes = ""

                server_component_ports_cfg_file_name = "GEN_" + server_component + "_SERVER_PORTS_CFG.h"
                if(server_component_ports_cfg_file_name not in includes):
                    includes += "#include \"" + server_component_ports_cfg_file_name + "\"\n"
                    for component in self._generator_data_handler.GetData()["SWCs"]["Components"]:
                        if (component["Properties"]["Component_Name"]["value"] == server_component):
                            if(component["Properties"]["Component_Type"]["value"] == "SERVICE"):
                                server_component_cfg_file_name = "GEN_" + server_component + "_CFG.h"
                                includes += "#include \"" + server_component_cfg_file_name + "\"\n"

                client_ports_s += "#define " + client_port + "\t" + server_port + "\n"
            else:
                client_ports_s += "#define " + client_port + "\t" + "RET_PORT_UNCONNECTED\n"

        if( (client_ports_s != None) and (includes != None)):
            client_ports_s = includes.strip() + "\n\n" + client_ports_s.strip()

        return client_ports_s

    def _Generator_GenComponentHFile(self, component_name, component_gen_location):
        file_name_h = component_name + ".h"

        file_s = self._Generator_ReadFile(component_gen_location + "/" + file_name_h)
        if ( (file_s == None) or (not file_s.strip()) ):
            file_s = self._Generator_WrapFile(file_s="", file_name=file_name_h, include_libs=["Types.h"], ifndef_protection=True)
        file_s = file_s.strip()

        return file_s

    def _Generator_GetFunctionsInSection(self, section_s):
        funcs_list = []
        temp = section_s
        while (temp.find(self._generator_gen_start_func) != -1):
            temp = temp[temp.find(self._generator_gen_start_func):].strip()

            if (self._generator_gen_end_func in temp):
                func = temp[: temp.find(self._generator_gen_end_func) + len(self._generator_gen_end_func)].strip()
                while (func.count(self._generator_gen_start_func) > 1):
                    func = func[func.find(self._generator_gen_start_func,
                                          func.find(self._generator_gen_start_func) + len(
                                              self._generator_gen_start_func)):]
                funcs_list.append(func)

            temp = temp[temp.find(self._generator_gen_end_func) + len(self._generator_gen_end_func):].strip()

        return funcs_list

    def _Generator_GenComponentCFile(self, server_ports_vars_callouts_list, server_ports_funcs_callouts_list, runnables_list, component_name, component_gen_location, server_ports_cfg_file_name, client_ports_cfg_file_name):
        file_name_c = component_name + ".c"
        file_name_h = component_name + ".h"

        file_s = self._Generator_ReadFile(component_gen_location + "/" + file_name_c)
        if(file_s == None):
            file_s = self._generator_gen_empty_file_s
        file_s = file_s.strip()

        if(self._generator_gen_end_section in file_s):
            if(self._generator_gen_include_section_start in file_s):
                include_section_old = file_s[file_s.find(self._generator_gen_include_section_start) :]
                include_section_old = include_section_old[: include_section_old.find(self._generator_gen_end_section) + len(self._generator_gen_end_section)].strip()

                temp = [self._generator_gen_server_ports_vars_section_start,
                        self._generator_gen_server_ports_funcs_section_start,
                        self._generator_gen_runnables_section_start]

                if(not any(gen_section_start in include_section_old for gen_section_start in temp)):
                    include_section_new = self._generator_gen_include_section_start + "\n"
                    include_section_new += "#include \"" + server_ports_cfg_file_name + "\"\n"
                    include_section_new += "#include \"" + client_ports_cfg_file_name + "\"\n"
                    include_section_new += "#include \"" + file_name_h + "\"\n"
                    include_section_new += self._generator_gen_end_section

                    file_s = file_s.replace(include_section_old, include_section_new.strip())

            if(self._generator_gen_server_ports_vars_section_start in file_s):
                server_ports_vars_section_old = file_s[file_s.find(self._generator_gen_server_ports_vars_section_start) :]
                server_ports_vars_section_old = server_ports_vars_section_old[: server_ports_vars_section_old.find(self._generator_gen_end_section) + len(self._generator_gen_end_section)].strip()

                temp = [self._generator_gen_include_section_start,
                        self._generator_gen_server_ports_funcs_section_start,
                        self._generator_gen_runnables_section_start]

                if (not any(gen_section_start in server_ports_vars_section_old for gen_section_start in temp)):
                    server_ports_vars_section_new = self._generator_gen_server_ports_vars_section_start + "\n"
                    for callout in server_ports_vars_callouts_list:
                        server_ports_vars_section_new += callout + ";\n"
                    server_ports_vars_section_new += self._generator_gen_end_section

                    file_s = file_s.replace(server_ports_vars_section_old, server_ports_vars_section_new.strip())

            if (self._generator_gen_server_ports_funcs_section_start in file_s):
                server_ports_funcs_section_old = file_s[file_s.find(self._generator_gen_server_ports_funcs_section_start):]
                server_ports_funcs_section_old = server_ports_funcs_section_old[: server_ports_funcs_section_old.find(self._generator_gen_end_section) + len(self._generator_gen_end_section)].strip()

                temp = [self._generator_gen_include_section_start,
                        self._generator_gen_server_ports_vars_section_start,
                        self._generator_gen_runnables_section_start]

                if (not any(gen_section_start in server_ports_funcs_section_old for gen_section_start in temp)):
                    funcs_old_list = self._Generator_GetFunctionsInSection(server_ports_funcs_section_old)

                    server_ports_funcs_section_new = self._generator_gen_server_ports_funcs_section_start + "\n"
                    for callout in server_ports_funcs_callouts_list:
                        func_declaration = callout[: callout.find('(')]
                        func_new = None
                        for func in funcs_old_list:
                            if(func_declaration in func):
                                func_params = callout[callout.find('('): callout.find(')') + 1]
                                if(not func_params):
                                    func_params = "(void)"
                                func_new = func.replace(func[func.find('(', func.find(func_declaration)) : func.find(')', func.find(func_declaration)) + 1], func_params)
                                break
                        if(func_new == None):
                            func_new = self._generator_gen_start_func + "\n"
                            func_new += callout + "\n{\n\treturn RET_OK;\n}\n"
                            func_new += self._generator_gen_end_func

                        server_ports_funcs_section_new += func_new.strip() + "\n\n"

                    server_ports_funcs_section_new = server_ports_funcs_section_new.strip() + "\n" + self._generator_gen_end_section
                    file_s = file_s.replace(server_ports_funcs_section_old, server_ports_funcs_section_new.strip())

            if (self._generator_gen_runnables_section_start in file_s):
                runnables_section_old = file_s[file_s.find(self._generator_gen_runnables_section_start):]
                runnables_section_old = runnables_section_old[: runnables_section_old.find(self._generator_gen_end_section) + len(self._generator_gen_end_section)].strip()

                temp = [self._generator_gen_include_section_start,
                        self._generator_gen_server_ports_vars_section_start,
                        self._generator_gen_server_ports_funcs_section_start]

                if (not any(gen_section_start in runnables_section_old for gen_section_start in temp)):
                    funcs_old_list = self._Generator_GetFunctionsInSection(runnables_section_old)

                    runnables_section_new = self._generator_gen_runnables_section_start + "\n"
                    for runnable in runnables_list:
                        func_declaration = "void " + runnable + "(void)"
                        func_new = None
                        for func in funcs_old_list:
                            if (func_declaration in func):
                                func_new = func
                                break
                        if (func_new == None):
                            func_new = self._generator_gen_start_func + "\n"
                            func_new += func_declaration + "\n{\n\n}\n"
                            func_new += self._generator_gen_end_func

                        runnables_section_new += func_new.strip() + "\n\n"

                    runnables_section_new = runnables_section_new.strip() + "\n" + self._generator_gen_end_section
                    file_s = file_s.replace(runnables_section_old, runnables_section_new.strip())

        return file_s

    def _Generator_GenComponentStructure(self, component_data, service_ports_s, server_ports_cfg_file_name, client_ports_cfg_file_name):
        temp = service_ports_s.strip().replace("extern ", "")
        temp = temp.strip().replace("\n", "")
        temp = temp.strip().replace("\r", "")
        temp = temp.strip().replace("\t", "")
        temp = re.sub(" +", " ", temp.strip())
        server_ports_callouts_list = temp.strip().split(";")
        if (server_ports_callouts_list[len(server_ports_callouts_list) - 1] == ""):
            server_ports_callouts_list.pop(len(server_ports_callouts_list) - 1)
        server_ports_vars_callouts_list = []
        server_ports_funcs_callouts_list = []
        for server_port_callout in server_ports_callouts_list:
            if( ('(' in server_port_callout) and (')' in server_port_callout) ):
                server_ports_funcs_callouts_list.append(server_port_callout)
            else:
                server_ports_vars_callouts_list.append(server_port_callout)

        runnables_list = []
        for rennable in component_data["Runnables"]["value"]:
            runnables_list.append(copy.deepcopy(rennable["Runnable_Name"]["value"]))

        component_name = component_data["Properties"]["Component_Name"]["value"]
        component_gen_location = component_data["Properties"]["Component_Gen_Location"]["value"]
        if(not component_gen_location):
            component_gen_location = self._generator_gen_folder + "/Appl/" + component_name

        component_c_file_s = self._Generator_GenComponentCFile(server_ports_vars_callouts_list, server_ports_funcs_callouts_list,
                                                               runnables_list, component_name, component_gen_location, server_ports_cfg_file_name, client_ports_cfg_file_name)
        self._Generator_WriteFile(component_c_file_s, component_gen_location + "/" + component_name + ".c")

        component_h_file_s = self._Generator_GenComponentHFile(component_name, component_gen_location)
        self._Generator_WriteFile(component_h_file_s, component_gen_location + "/" + component_name + ".h")



    def GenerateComponent(self, component_data, connections_data):
        service_ports_s = self._Generator_GenServicePorts(component_data["Server_Ports"]["value"])
        client_ports_s = self._Generator_GenClientPorts(component_data = component_data, connections_data=connections_data,
                                                        client_ports_data=component_data["Client_Ports"]["value"])

        if( (service_ports_s != None) or (client_ports_s != None) ):
            if(service_ports_s == None):
                service_ports_s = ""
            if(client_ports_s == None):
                client_ports_s = ""

            server_ports_cfg_file_name = "GEN_" + component_data["Properties"]["Component_Name"]["value"] + "_SERVER_PORTS_CFG.h"
            self._Generator_DeleteFile(self._generator_gen_folder + "/" + server_ports_cfg_file_name)

            client_ports_cfg_file_name = "GEN_" + component_data["Properties"]["Component_Name"]["value"] + "_CLIENT_PORTS_CFG.h"
            self._Generator_DeleteFile(self._generator_gen_folder + "/" + client_ports_cfg_file_name)

            server_ports_cfg_file_s = self._Generator_WrapFile(file_s=service_ports_s, file_name=server_ports_cfg_file_name, include_libs=["Types.h", "Queue.h"],
                                                  ifndef_protection=True)
            self._Generator_WriteFile(server_ports_cfg_file_s, self._generator_gen_folder + "/" + server_ports_cfg_file_name)

            client_ports_cfg_file_s = self._Generator_WrapFile(file_s=client_ports_s,
                                                               file_name=client_ports_cfg_file_name, include_libs=[],
                                                               ifndef_protection=True)
            self._Generator_WriteFile(client_ports_cfg_file_s,
                                      self._generator_gen_folder + "/" + client_ports_cfg_file_name)

        if(component_data["Properties"]["Gen_Structure"]["value"]):
            self._Generator_GenComponentStructure(component_data=component_data, service_ports_s=service_ports_s, server_ports_cfg_file_name=server_ports_cfg_file_name, client_ports_cfg_file_name=client_ports_cfg_file_name)

    def Generate(self, generation_data):
        for service in generation_data["Services"]:
            if(service == "OS"):
                self.GenerateOS(self._generator_data_handler.GetData()["Services"]["OS"])
            else:
                self.GenerateService(service_data=self._generator_data_handler.GetData()["Services"][service], service_name=service)

        for swc in generation_data["SWCs"]:
            for component in self._generator_data_handler.GetData()["SWCs"]["Components"]:
                if (component["Properties"]["Component_Name"]["value"] == swc):
                    self.GenerateComponent(component, self._generator_data_handler.GetData()["SWCs"]["Connections"])
                    break
