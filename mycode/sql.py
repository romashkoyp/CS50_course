import csv
import sqlite3

def main():
    conn = sqlite3.connect('suomi_sanat.db')
    cursor = conn.cursor()

    # Create a table
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS mytable (
            id INT PRIMARY KEY,
            abs INT,
            rel REAL,
            sana TEXT,
            typpi TEXT
        )
    ''')

    conn.commit()

    with open('sanat.csv', 'r') as csvfile:
        csvreader = csv.DictReader(csvfile)
        for row in csvreader:
            cursor.execute('''
                INSERT INTO mytable (id, abs, rel, sana, typpi)
                VALUES (?, ?, ?, ?, ?)
            ''', (row['id'], row['abs'], row['rel'], row['sana'], row['typpi']))

    conn.commit()

if __name__ == "__main__":
    main()