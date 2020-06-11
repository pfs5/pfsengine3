# -----------------------------------------------------------------------------
# Script parses .cpp and .h files and sorts the #include lines
# -----------------------------------------------------------------------------
import argparse
import re
import os
# -----------------------------------------------------------------------------
def sort_single_file(path):
    print ('sorting file <' + path + '>')

    lines_pre_inc = []
    lines_inc = []
    lines_post_inc = []
    
    with open(path, 'r') as file:
        mode = 'pre'    # pre, def, post        
        pattern = re.compile("^#include.*")
        for line in file:
            if re.match(pattern, line) and mode != 'post':
                mode = 'def'
                lines_inc.append(line)
            elif mode == 'pre':
                lines_pre_inc.append(line)
            elif mode == 'def' or mode == 'post':
                lines_post_inc.append(line)
                mode = 'post'

    lines_inc.sort()

    with open(path + '.tmp', 'w') as file:
        file.writelines(lines_pre_inc)
        file.writelines(lines_inc)
        file.writelines(lines_post_inc)

    os.replace(path + '.tmp', path)

# -----------------------------------------------------------------------------
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Include sorter for .cpp / .h files.')
    parser.add_argument('--file', type=str, help='Sort a single file.')
    
    args = parser.parse_args()
    
    if (args.file is not None):
        sort_single_file(args.file)
# -----------------------------------------------------------------------------