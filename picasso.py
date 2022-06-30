#!/usr/bin/env python3
import argparse
from picasso_helper import PicassoTool

def main():
    parser = argparse.ArgumentParser(description='Evolution based image generator')
    parser.add_argument('-i', '--iterations',type=int, nargs='+', required=True, default=50, help = "Number of iterations evolution to go through", metavar='')
    parser.add_argument('-d', '--data', type=str, required=True, help = "Path to target image")
    args = parser.parse_args()
    img_path = args.data
    iterations = args.iterations

    pic = PicassoTool(img_path)

    pic.generate_imge(iterations)

    pic.export_gif()

    pic.export_frame()

    pic.export_frame()

if __name__ == "__main__":
    main()