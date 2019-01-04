import cs50


def calculate_change(coin, money):
    numberOfCoins = 0
    while money >= coin:
        money -= coin
        numberOfCoins += 1
    return numberOfCoins, money


while True:
    change = cs50.get_float("Change owed: ")
    if change > 0:
        break
cents = change * 100
numberOfCoins = 0
listOfCoins = [25, 10, 5, 1]
for coin in listOfCoins:
    tempNofCoins, cents = calculate_change(coin, cents)
    numberOfCoins += tempNofCoins
print(numberOfCoins)
