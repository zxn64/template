from markdown import markdown
from os import listdir, path


def find_cpp_source(directory):
    source = {}
    for dirname in listdir(directory):
        if path.isdir(dirname):
            for filename in listdir(dirname):
                if filename.endswith('.cpp'):
                    source[dirname] = source.get(dirname, []) + [filename]
    return source


def wirte_cpp_code(mdfile, sourcefile):
    mdfile.write('\n```c++\n')
    cppfile = open(sourcefile, 'r', encoding='utf8')
    mdfile.write(cppfile.read())
    mdfile.write('\n```\n')


source = find_cpp_source('.')
mdfile = open('summary.md', 'w')
mdfile.write('# UESTC_404\'s Template\n')
for dirname, filenames in source.items():
    mdfile.write(f'\n## {dirname}\n')
    for filename in filenames:
        mdfile.write(f"\n### {filename.rstrip('.cpp')}\n")
        wirte_cpp_code(mdfile, path.join(dirname, filename))
mdfile.close()

mdfile = open('summary.md', 'r')
mdstr = mdfile.read()
mdfile.close()

html_body = markdown(text=mdstr, output_format='html', extensions=['extra', 'fenced_code', 'codehilite'])
html_whole = \
    f"""<html lang="zh-cn">
<head>
<meta content="text/html; charset=utf-8" http-equiv="content-type" />
<link href="codecolor.css" rel="stylesheet">
<link href="pagestyle.css" rel="stylesheet">
</head>
<body>
{html_body}
</body>
</html>
"""
html_file = open('summary.html', 'w', encoding='utf8')
html_file.write(html_whole)
html_file.close()
