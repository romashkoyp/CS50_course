CREATE TABLE purchases (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    user_id INTEGER NOT NULL,
    symbol TEXT NOT NULL,
    share NUMERIC NOT NULL,
    price NUMERIC NOT NULL,
    cost NUMERIC NOT NULL,
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users (id),
    UNIQUE (user_id, symbol, timestamp)
);

CREATE INDEX user_id_index ON purchases (user_id);
CREATE INDEX symbol_index ON purchases (symbol);
