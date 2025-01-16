from EmbeddedCGenerator import EmbeddedCGenerator
import argparse

def ParseArgs():
    parser = argparse.ArgumentParser(description="Embedded C Generator")

    parser.add_argument("--data_dir", type=str, required=True , help="Path to data directory")
    parser.add_argument("--gen_dir", type=str, required=True, help="Path to gen directory")
    parser.add_argument("--proj_title", type=str, required=True, help="Project title")

    args = parser.parse_args()

    args.data_dir = args.data_dir.replace('/', '\\')
    if(args.data_dir[-1] == '\\'):
        args.data_dir = args.data_dir[: -1]

    args.gen_dir = args.gen_dir.replace('/', '\\')
    if (args.gen_dir[-1] == '\\'):
        args.gen_dir = args.gen_dir[: -1]

    return args

def main():
    args = ParseArgs()

    embedded_c_generator = EmbeddedCGenerator(data_dir=args.data_dir, gen_dir=args.gen_dir, proj_title=args.proj_title)
    embedded_c_generator.Run()

if __name__ == "__main__":
    main()