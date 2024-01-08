import csv

# Create an empty set to store unique words
unique_words = set()

# Open and read the CSV file
with open('finnish_nouns_wiki_20.09.2023.csv', 'r', newline='') as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        # Get the word field from each row
        word = row['word']

        # Check if the word ends with "" (case insensitive)
        if word.lower().endswith("i"):
            unique_words.add(word)

# Sort the unique words alphabetically (ASC)
unique_words = sorted(unique_words)

# Sort the unique words by word length
unique_words = sorted(unique_words, key=lambda x: len(x))

# Check if there are words with endings
if unique_words:
    # Define the name of the new CSV file
    output_file = 'unique_i_noun_words.csv'

    # Write the unique words to a new CSV file
    with open(output_file, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['Word'])  # Write the header
        writer.writerows([[word] for word in unique_words])  # Write the data rows
