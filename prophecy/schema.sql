CREATE TABLE students (
    id INTEGER NOT NULL,
    student_name TEXT NOT NULL,
    house_id INTEGER NOT NULL,
    head_id INTEGER NOT NULL,
    PRIMARY KEY(id),
    FOREIGN KEY(house_id) REFERENCES houses(id),
    FOREIGN KEY(head_id) REFERENCES heads(id)
);

CREATE TABLE houses (
    id INTEGER NOT NULL,
    house TEXT NOT NULL,
    PRIMARY KEY(id)
);

CREATE TABLE heads (
    id INTEGER NOT NULL,
    head TEXT NOT NULL,
    PRIMARY KEY(id)
);

SELECT students.id, students.student_name, houses.house, heads.head
FROM students
JOIN houses ON students.house_id = houses.id
JOIN heads ON students.head_id = heads.id;
