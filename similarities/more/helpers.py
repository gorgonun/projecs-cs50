from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""
    # A = rows, B = columns
    def returnFirst(nList): return nList[0]
    a = [None] + list(a)
    b = [None] + list(b)
    matrix = [len(b) * [0] for x in range(len(a))]
    for pI in range(len(a)):
        for pJ in range(len(b)):
            compA = a[:pI + 1]
            compB = b[:pJ + 1]
            if compA[-1] == None and compB[-1] == None:
                matrix[pI][pJ] = (0, None)
            elif compA[-1] == None:
                matrix[0][pJ] = (matrix[0][pJ-1][0] + 1, Operation.SUBSTITUTED)
            elif compB[-1] == None:
                matrix[pI][0] = (matrix[pI-1][0][0] + 1, Operation.DELETED)
            else:
                if compA[pI] == compB[pJ]:
                    x = 0
                else:
                    x = 1
                matrix[pI][pJ] = min((matrix[pI - 1][pJ][0] + 1, Operation.DELETED),
                                     (matrix[pI][pJ - 1][0] + 1, Operation.INSERTED),
                                     (matrix[pI - 1][pJ - 1][0] + x, Operation.SUBSTITUTED),
                                     key=returnFirst)
    return matrix
