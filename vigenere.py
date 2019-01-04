import sys
import cs50


def main():
    if len(sys.argv) != 2:
        print("Usage python vigenere.py cipher")
        exit(1)
    else:
        for char in sys.argv[1]:
            if char.isalpha() is False:
                print("Is allowed only char to cipher")
                exit(1)
        cipherList = [ord(sys.argv[1][x].upper()) - ord('A') for x in range(0, len(sys.argv[1]))]
        plainText = cs50.get_string("Text: ")
        print("ciphertext:", end="")
        newList = cipherList
        position = 0
        while len(newList) < len(plainText):
            newList.append(cipherList[position])
            position += 1
            if position >= len(plainText):
                position = 0
        position = 0
        for char in plainText:
            if char.isalpha():
                if char.islower():
                    first = ord('a')
                    last = ord('z')
                else:
                    first = ord('A')
                    last = ord('Z')
                between = range(first, last + 1)
                tempChar = ord(char) + newList[position]
                if tempChar not in between:
                    tempChar = first + tempChar - last - 1
                print(chr(tempChar), end="")
                position += 1
            else:
                print(char, end="")
        print()


main()
