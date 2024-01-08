from cs50 import get_int


def main():
    height = get_height()
    for line in range(height):
        for dots in range(height - line - 1):
            print(" ", end="")  # Print ' ' without new line in the end
        for hash in range(line + 1):
            print("#", end="")  # Print '#' without new line in the end
        print("  ", end="")
        for hash2 in range(line + 1):
            print("#", end="")  # Print '#' without new line in the end
        print()  # Print new line


# Get a positive integer between 1 and 8 from user in a loop
def get_height():
    while True:
        n = get_int("Enter a positive integer between 1 and 8 inclusive: ")
        if 1 <= n <= 8:
            return n


if __name__ == "__main__":
    main()
