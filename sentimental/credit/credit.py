import cs50
import decimal


def error():
    print("INVALID")
    return 0


def total_exp(number):
    listOfExp = [1e12, 1e14, 1e15]
    if number > 1e13 or number < 56e15:
        for exp in listOfExp:
            if number/exp < 10:
                return exp * 10
    return 0


def owner(size, number):
    ownerList = ["VISA", "AMEX", "MASTERCARD"]
    if size == 1e13:
        if number / 1e12 >= 4 and number / 1e12 < 5:
            return ownerList[0]
    elif size == 1E15:
        if ((number / 1e13 >= 34 and number / 1e13 < 35) or (number / 1e13 >= 37 and number / 1e13 < 38)):
            return ownerList[1]
    elif size == 1e16:
        if number / 1e15 >= 4 and number / 1e15 < 5:
            return ownerList[0]
        elif number / 1e14 >= 50 and number / 1e14 < 56:
            return ownerList[2]
    return 0


def card_sum(size, number):
    sum1 = 0
    sum2 = 0
    number = str(number)
    i = len(number) - 1
    fix = i % 2
    while i >= 0:
        if i % 2 == fix:
            sum2 += int(number[i])
        else:
            sumTemp = int(number[i]) * 2
            if len(str(sumTemp)) == 2:
                sum1 += int(str(sumTemp)[0]) + int(str(sumTemp)[1])
            else:
                sum1 += sumTemp
        i -= 1
    return (sum1 + sum2) % 10


def main():
    while True:
        number = cs50.get_int("Credit card number: ")
        if number > 0:
            break
    size = total_exp(number)
    if size == 0:
        return error()
    cardOwner = owner(size, number)
    if cardOwner == 0:
        return error()
    if card_sum(size, number) != 0:
        return error()
    print(cardOwner)


main()