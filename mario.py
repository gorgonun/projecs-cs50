from cs50 import get_int

# loop until the number of the pyramidHeight is in the range 0-23
while True:
    pyramidHeight = get_int("Pyramid Height: ")
    if 0 <= pyramidHeight and pyramidHeight <= 23:
        break
base = pyramidHeight + 1
line = 2
for i in range(pyramidHeight):
    text = ' ' * (base - line) + '#' * line
    print(text)
    line += 1