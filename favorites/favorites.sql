Open database
sqlite3 file_name.db

Open structure of database
.schema

View data in the db file
SELECT * FROM column_name or table_name;



sqlite> UPDATE shows
   ...> SET title = "Brooklyn Nine-Nine"
   ...> WHERE title LIKE "%99%" OR "Brooklyn%";
sqlite> SELECT * FROM shows ORDER BY title ASC;

sqlite> UPDATE shows
   ...> SET title = "Game of Thrones"
   ...> WHERE title = "GoT";

sqlite> UPDATE shows
   ...> SET title = "Game of Thrones"
   ...> WHERE title LIKE "Game%";

sqlite> UPDATE shows
   ...> SET title = "Grey’s Anatomy"
   ...> WHERE title LIKE "Grey's%";

sqlite> UPDATE shows
   ...> SET title = "The Office"
   ...> WHERE title LIKE "Office%" OR title = "Thevoffice";

sqlite> UPDATE shows
   ...> SET title = "The Office"
   ...> WHERE UPPER(title) LIKE UPPER("the office");
