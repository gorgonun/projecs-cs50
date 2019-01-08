from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    listLines = []
    a = set(a.split("\n"))
    b = set(b.split("\n"))
    for line in a:
        if line in b and line not in listLines:
            listLines.append(str(line))
    return listLines


def sentences(a, b):
    """Return sentences in both a and b"""

    finalList = []
    a = sent_tokenize(a)
    b = sent_tokenize(b)
    for sentence in a:
        if sentence in b and sentence not in finalList:
            finalList.append(str(sentence))
    return finalList


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    finalList = []
    a = separate(a, n)
    b = separate(b, n)
    for substring in a:
        if substring in b and substring not in finalList:
            finalList.append(str(substring))
    return finalList


def separate(a, n):
    subs = []
    position = 0
    while position + n <= len(a):
        subs.append(a[position:position + n])
        position += 1
    return subs
