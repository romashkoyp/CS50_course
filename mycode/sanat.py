import csv
import sys

def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python sanat.py sanat.csv")

    # Read CSV file into memory
    try:
        with open(sys.argv[1], "r", newline='') as file:
            reader = csv.reader(file)
            next(reader)  # Skip the header row
            data = []
            for row in reader:
                id_value = int(row[1])
                abs_value = int(row[2])
                rel_value = float(row[3])
                sana = row[4]
                typpi = row[5]
                data.append([id_value, abs_value, rel_value, sana, typpi])
    except FileNotFoundError:
        sys.exit("File not found")

    with open('sanat.csv', 'w', newline='') as csvfile:
        csvwriter = csv.writer(csvfile)
        csvwriter.writerow(['id', 'Abs', 'Rel', 'Sana', 'Typpi'])  # Write the header
        csvwriter.writerows(data)  # Write the data rows

if __name__ == "__main__":
    main()

