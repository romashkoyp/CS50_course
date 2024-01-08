from cs50 import get_int
import re


def main():
    # Calculate checksum
    number = get_number()
    a = (number % 100) // 10 * 2
    b = (number % 10000) // 1000 * 2
    c = (number % 1000000) // 100000 * 2
    d = (number % 100000000) // 10000000 * 2
    e = (number % 10000000000) // 1000000000 * 2
    f = (number % 1000000000000) // 100000000000 * 2
    g = (number % 100000000000000) // 10000000000000 * 2
    h = (number % 10000000000000000) // 1000000000000000 * 2

    a1 = (a % 100) // 10 + (a % 10)
    b1 = (b % 100) // 10 + (b % 10)
    c1 = (c % 100) // 10 + (c % 10)
    d1 = (d % 100) // 10 + (d % 10)
    e1 = (e % 100) // 10 + (e % 10)
    f1 = (f % 100) // 10 + (f % 10)
    g1 = (g % 100) // 10 + (g % 10)
    h1 = (h % 100) // 10 + (h % 10)
    sum1 = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1

    a2 = number % 10
    b2 = (number % 1000) // 100
    c2 = (number % 100000) // 10000
    d2 = (number % 10000000) // 1000000
    e2 = (number % 1000000000) // 100000000
    f2 = (number % 100000000000) // 10000000000
    g2 = (number % 10000000000000) // 1000000000000
    h2 = (number % 1000000000000000) // 100000000000000
    sum2 = a2 + b2 + c2 + d2 + e2 + f2 + g2 + h2
    sum3 = sum2 + sum1

    # Check VALID or INVALID card
    if (sum3 % 10) != 0:
        print("INVALID")

    # Check for card length
    digits = len(str(number))

    # Check VISA
    if digits == 16 and h // 2 == 4:
        print("VISA")
    elif digits == 15 and h2 == 4:
        print("VISA")
    elif digits == 14 and g // 2 == 4:
        print("VISA")
    elif digits == 13 and g2 == 4:
        print("VISA")

    # Check American Express
    if digits == 15 and h2 == 3 and (((g // 2) == 4) or ((g // 2) == 7)):
        print("AMEX")

    # Check Master Card
    if (
        digits == 16
        and ((h // 2) == 5)
        and (h2 == 1 or h2 == 2 or h2 == 3 or h2 == 4 or h2 == 5)
    ):
        print("MASTERCARD")
    else:
        print("INVALID")


# Get a positive number in a loop
def get_number():
    while True:
        number = get_int("Number: ")
        if number > 0:
            return number


if __name__ == "__main__":
    main()
