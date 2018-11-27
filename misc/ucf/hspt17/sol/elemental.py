i = 1
numElements = int(input())


# Check if each word is elemental: ~O(n^2)
def isElemental(word: str, table: list):
    if len(word) == 0:
        return True

    anyTrue = False

    for element in table:
        if word.startswith(element):
            anyTrue = anyTrue or isElemental(word[len(element):], table)

    return anyTrue

while numElements != 0:
    elements = input().split()
    words = input().split()
    allTrue = True

    for nextWord in words:
        allTrue = allTrue and isElemental(nextWord, elements)

    if allTrue:
        print("Phrase #", i, ": Elemental", sep='')
    else:
        print("Phrase #", i, ": Not Elemental", sep='')
    print()

    numElements = int(input())
    i += 1
