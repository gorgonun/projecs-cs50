from cs50 import get_int

# loop until the number of the pyramidHeight is in the range 0-23
while True:
    pyramidHeight = get_int("Pyramid Height: ")
    if 0 <= pyramidHeight and pyramidHeight <= 23:
        break
base = pyramidHeight
line = 1
for i in range(pyramidHeight):
    text1 = ' ' * (base - line)
    text2 = '#' * line
    print(text1 + text2, text2, sep="  ")
    line += 1