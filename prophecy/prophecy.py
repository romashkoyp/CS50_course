import csv
import sys
import sqlite3


def main():
    # Check for command-line usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python prophecy.py students.csv")

    python_filename = "prophecy.py"
    csv_filename = sys.argv[1]
    if sys.argv[0] != python_filename or not csv_filename.endswith(".csv"):
        sys.exit("Usage: python prophecy.py students.csv")

    # Connect to the SQLite database
    conn = sqlite3.connect("roster.db")
    cursor = conn.cursor()

    # Read database file into a variable
    with open(sys.argv[1], "r") as csv_file:
        csv_reader = csv.DictReader(csv_file)
        for row in csv_reader:
            # Extract data from the CSV row
            student_name = row["student_name"]
            house = row["house"]
            head = row["head"]

            # Check if house exists, insert if not
            cursor.execute("SELECT id FROM houses WHERE house = ?;", (house,))
            house_id = cursor.fetchone()
            if house_id is None:
                cursor.execute("INSERT INTO houses (house) VALUES (?);", (house,))
                house_id = cursor.lastrowid
            else:
                house_id = house_id[0]

            # Check if head exists, insert if not
            cursor.execute("SELECT id FROM heads WHERE head = ?;", (head,))
            head_id = cursor.fetchone()
            if head_id is None:
                cursor.execute("INSERT INTO heads (head) VALUES (?);", (head,))
                head_id = cursor.lastrowid
            else:
                head_id = head_id[0]

            # Insert data into the students table with house_id and head_id
            cursor.execute("INSERT INTO students (student_name, house_id, head_id) VALUES (?, ?, ?);",
                           (student_name, house_id, head_id))

    # Commit changes and close the connection
    conn.commit()
    conn.close()


if __name__ == "__main__":
    main()
