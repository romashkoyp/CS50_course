import os
import re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Find all user's purchases (symbol and symbol's shares)
    stocks = db.execute(
        "SELECT symbol, SUM(share) as all_shares FROM purchases WHERE user_id = :user_id GROUP BY symbol HAVING all_shares > 0",
        user_id=session["user_id"],
    )

    # Find user's cash
    cash = db.execute(
        "SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"]
    )[0]["cash"]

    # Create variables for total values
    total_symbol = cash

    # Iterate through the purchases for summing
    for stock in stocks:
        quote = lookup(stock["symbol"])
        stock["symbol"] = quote["symbol"]
        stock["price"] = quote["price"]
        stock["cost"] = stock["price"] * stock["all_shares"]
        total_symbol += stock["cost"]

    return render_template(
        "index.html", stocks=stocks, cash=cash, total_symbol=total_symbol
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reach buy.html with POST
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        stock_data = lookup(symbol)

        # Check, is symbol field blank or not
        if not symbol:
            return apology("must provide symbol", 400)

        # Check, if symbol has prohibited symbols
        if re.search(r"[';]", symbol):
            return apology(
                "Your symbol must not contain prohibited symbols ' or ; ", 400
            )

        # Check, is symbol exist or not
        if not stock_data:
            return apology("invalid symbol", 400)

        # Check, is quantity of shares blank or not
        share = request.form.get("shares")
        if not share:
            return apology("missing shares", 400)

        # Check, if share has prohibited symbols
        if re.search(r"[';]", share):
            return apology(
                "Your share must not contain prohibited symbols ' or ; ", 400
            )

        # Check, is quantity of shares a positive integer
        try:
            share = int(share)
            if share < 1:
                return apology("shares have to be a positive integer", 400)
        except ValueError:
            return apology("shares must be a valid number", 400)

        # Check, if user has enough money for buying
        price = stock_data["price"]
        cost = price * int(share)
        cash = db.execute(
            "SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"]
        )[0]["cash"]
        if cash < cost:
            return apology("not enough money", 400)

        # Make a purchace and update database
        db.execute(
            "UPDATE users SET cash = cash - :cost WHERE id = :user_id",
            cost=cost,
            user_id=session["user_id"],
        )

        # Add information about current transaction to the table
        db.execute(
            "INSERT INTO purchases (user_id, symbol, share, price, cost) VALUES (:user_id, :symbol, :share, :price, :cost)",
            user_id=session["user_id"],
            symbol=symbol,
            share=int(share),
            price=price,
            cost=cost,
        )

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Find all user's purchases
    stocks = db.execute(
        "SELECT symbol, share, price, cost, timestamp FROM purchases WHERE user_id = :user_id ORDER BY timestamp DESC",
        user_id=session["user_id"],
    )

    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User reached quote via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)

        # Check, if symbol has prohibited symbols
        if re.search(r"[';]", symbol):
            return apology(
                "Your symbol must not contain prohibited symbols ' or ; ", 400
            )

        quote = lookup(symbol)
        if not quote:
            return apology("invalid symbol", 400)
        return render_template("quoted.html", quote=quote)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        password = request.form.get("password")
        # Check, is username blank or not
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Check, if username contains prohibited symbols
        if re.search(r"[';]", request.form.get("username")):
            return apology(
                "Your username must not contain prohibited symbols ' or ; ", 400
            )

        # Check, if password blank or not
        if not password:
            return apology("must provide password", 400)

        # Check, if confirmation blank or not
        if not request.form.get("confirmation"):
            return apology("must provide confirmation", 400)

        # Check, if password has 8 characters
        if len(password) < 8:
            return apology("your password has contain at least 8 characters", 400)

        # Check, if password has 1 upper letter
        if not any(char.isupper() for char in password):
            return apology(
                "Your password must contain at least one uppercase letter", 400
            )

        # Check, if password has 1 lower letter
        if not any(char.islower() for char in password):
            return apology(
                "Your password must contain at least one lowercase letter", 400
            )

        # Check, if password has 1 digit
        if not any(char.isdigit() for char in password):
            return apology("Your password must contain at least one digit", 400)

        # Check, if password has 1 special symbol
        if not re.search(r'[!"#$%&()*+,-./:<=>?@[\]^_`{|}~]', password):
            return apology(
                "Your password must contain at least one special symbol", 400
            )

        # Check, if password has prohibited symbols
        if re.search(r"[';]", password):
            return apology(
                "Your password must not contain prohibited symbols ' or ; ", 400
            )

        # Check, if password and confirmation are the same
        if password != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        # Quary user's name from database
        username_db = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Check, does username exist or not
        if len(username_db) != 0:
            return apology("this username already exists", 400)

        # Create password hash for new user
        hashed_password = generate_password_hash(password)

        # Insert the new user into the database with the hashed password
        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            request.form.get("username"),
            hashed_password,
        )

        # Query database for new user
        username_db = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Remember session for new user
        session["user_id"] = username_db[0]["id"]

        # Redirect user to homepage
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Create variable for extracting user's stocks
    stocks = db.execute(
        "SELECT symbol, SUM(share) as all_shares FROM purchases WHERE user_id = :user_id GROUP BY symbol HAVING all_shares > 0",
        user_id=session["user_id"],
    )

    # User reached sell.html with POST
    if request.method == "POST":
        # Check if symbol is selected
        symbol = request.form.get("symbol").upper()
        if not symbol:
            return apology("must provide symbol", 400)

        # Check, if symbol has prohibited symbols
        if re.search(r"[';]", symbol):
            return apology(
                "Your symbol must not contain prohibited symbols ' or ; ", 400
            )

        # Check if the user owns the selected stock
        owned_stocks = [stock["symbol"] for stock in stocks]
        if symbol not in owned_stocks:
            return apology("you don't own shares of this symbol", 400)

        # Check if the number of shares is a positive integer
        share = request.form.get("shares")
        if not share or not share.isdigit() or int(share) < 1:
            return apology("provide a valid positive number of shares", 400)

        # Check, if share has prohibited symbols
        if re.search(r"[';]", share):
            return apology(
                "Your share must not contain prohibited symbols ' or ; ", 400
            )

        # Check if the user has enough shares to sell
        for stock in stocks:
            if stock["symbol"] == symbol:
                if int(share) > stock["all_shares"]:
                    return apology("not enough shares to sell", 400)
                else:
                    quote = lookup(symbol)
                    if not quote:
                        return apology("symbol not found", 400)
                    price = quote["price"]
                    all_sales = int(share) * price

                    # Update user's cash information
                    db.execute(
                        "UPDATE users SET cash = cash + :all_sales WHERE id = :user_id",
                        all_sales=all_sales,
                        user_id=session["user_id"],
                    )

                    # Add information about the current transaction to the table
                    db.execute(
                        "INSERT INTO purchases (user_id, symbol, share, price, cost) VALUES (:user_id, :symbol, :share, :price, :cost)",
                        user_id=session["user_id"],
                        symbol=symbol,
                        share=-int(share),  # Negative share to represent selling
                        price=price,
                        cost=all_sales,  # Use cost to represent the selling value
                    )

        # Redirect user to the home page
        return redirect("/")

    else:
        return render_template("sell.html", stocks=stocks)
