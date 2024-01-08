import sys
from random import choice
from pyfiglet import Figlet

figlet = Figlet()

# get 0 argument
if len(sys.argv) == 1:
# get input text
    answer_1 = input("Input: ")
# random style and print the result
    f = choice(figlet.getFonts())
    figlet.setFont(font=f)
    print(figlet.renderText(answer_1))

# get 2 arguments
elif len(sys.argv) == 3 and sys.argv[1] == ("-f") or sys.argv[1] == ("--font"):
    font_name = sys.argv[2]
    if font_name in figlet.getFonts():
        answer_2 = input("Input: ")
        figlet.setFont(font=font_name)
        print(figlet.renderText(answer_2))
    else:
        sys.exit("error")
else:
    sys.exit("error")