import os

def copy_files(filenames, output_file):
  with open(output_file, "w") as outfile:
    for filename in filenames:
      with open(filename, "r") as infile:
        for line in infile:
          if not line.startswith('#include"') and not line.startswith('#include "') and not line.startswith('#pragma once'):
            outfile.write(line)
      outfile.write('\n')


def main():
    files_to_copy_file_name = "FilesToCopy.txt"

    with open(files_to_copy_file_name, "r") as infile:
        filenames = [line.strip() for line in infile]

    copy_files(filenames, "new_main.cpp")

    print("Файлы успешно скопированы в new_main.cpp")


if __name__ == "__main__":
    main()