from pathlib import Path
import os

def ReadFile(path_to_file):
    s = None
    if (path_to_file != None):
        try:
            f = open(path_to_file, "r")
            s = f.read()
            f.close()
        except FileNotFoundError:
            pass

    return s


def WriteFile(s, path_to_file, create_path_to_file=False):
    if ((s != None) and (path_to_file != None)):
        if(create_path_to_file):
            file_name = path_to_file[path_to_file.rfind("/") + 1:]
            path_to_file = path_to_file[: path_to_file.rfind("/")]
            Path(path_to_file).mkdir(parents=True, exist_ok=True)
            path_to_file = path_to_file + "/" + file_name

        f = open(path_to_file, "w")
        f.write(s)
        f.close()


def DeleteFile(path_to_file):
    if os.path.exists(path_to_file):
        os.remove(path_to_file)
