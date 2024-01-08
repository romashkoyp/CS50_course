from cs50 import get_string


def main():
    # Calculate letters
    text = get_text()
    letters = 0
    for char in text:
        if char.isalpha():
            letters += 1

    # Calculate words
    words = 1
    for char in text:
        if char.isspace():
            words += 1

    # Calculate sentences
    symbols = ".!?"
    sentences = 0
    for char in text:
        if char in symbols:
            sentences += 1

    # Calculate index
    index = (
        0.0588 * ((letters / words) * 100) - 0.296 * ((sentences / words) * 100) - 15.8
    )
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    elif 1 < index < 16:
        print(f"Grade {round(index)}")


def get_text():
    # Get string from user
    text = get_string("Text: ")
    return text


if __name__ == "__main__":
    main()
