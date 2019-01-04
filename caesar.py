import sys
import cs50


def main():
    if len(sys.argv) != 2:
        print("Usage: python caesar.py number")
        exit(1)
    else:
        k = int(sys.argv[1]) % 26
        plainText = cs50.get_string("Text:")
        print("ciphertext: ", end="")
        for char in plainText:
            if char.isalpha():
                if char.islower():
                    first = ord('a')
                    last = ord('z')
                else:
                    first = ord('A')
                    last = ord('Z')
                between = range(first, last + 1)
                tempChar = ord(char) + k
                if tempChar not in between:
                    tempChar = first + tempChar - last - 1
                print(chr(tempChar), end="")
            else:
                print(char, end="")
        print()


main()
