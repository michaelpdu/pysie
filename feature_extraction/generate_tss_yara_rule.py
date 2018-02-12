import os

with open('feature_tss_keywords.yar', 'w') as fh:
    fh.write('''
/*
common TSS keywords, generated by python script
*/
    ''')
    with open('tss_keywords.ini', 'r') as fh2:
        index = 0
        for line in fh2.readlines():
            keyword = line.strip()
            fh.write('\n')
            fh.write('rule tss_keyword_{}\n'.format(keyword))
            fh.write('{\n')
            fh.write('    meta:\n')
            fh.write('        index = {}\n'.format(index))
            fh.write('    strings:\n')
            fh.write('        $a = "{}" nocase\n'.format(keyword))
            fh.write('    condition:\n')
            fh.write('        $a\n')
            fh.write('}\n')
            index += 1