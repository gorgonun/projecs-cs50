import os
from datetime import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])[0]["cash"]
    result = db.execute("SELECT symbol, sum(quantity) FROM shares WHERE user_id=:id AND owner=1 GROUP BY symbol",
                        id=session["user_id"])
    totalValue = 0
    for item in result:
        l = lookup(item["symbol"])
        item["quantity"] = item["sum(quantity)"]
        item["name"] = l["name"]
        item["current_price"] = usd(l["price"])
        item["total_value"] = usd(l["price"] * item["quantity"])
        totalValue += l["price"] * item["quantity"]
    estimated = usd(cash + totalValue)
    return render_template("index.html", result=result, cash=usd(cash), totalValue=usd(totalValue), estimated=estimated)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    else:
        response = lookup(request.form.get("symbol"))
        if response is None:
            return apology("Invalid symbol")
        else:
            try:
                number = int(request.form.get("shares"))
            except:
                return apology("Invalid number of shares!")
            if number <= 0:
                return apology("Invalid number of shares!")
            cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])[0]["cash"]
            price = number * response["price"]
            if cash > price:
                db.execute("UPDATE users SET cash=:cash WHERE id=:id", cash=round(cash-price, 2), id=session["user_id"])
                date = str(datetime.today().replace(microsecond=0))
                for x in range(0, number):
                    db.execute("INSERT INTO shares (\"user_id\", \"owner\", \"symbol\", \"buy_price\", \"quantity\", \"date\") values (:id, :owner, :symbol, :price, :quantity, :date)",
                               id=session["user_id"], owner=1, symbol=response["symbol"], price=price, quantity=1, date=date)
                return redirect("/")
            else:
                return apology("No enought cash!")
            return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    buy = db.execute(
        "SELECT symbol, buy_price, date, sum(quantity) FROM shares WHERE owner=1 AND user_id=:id GROUP BY date, symbol", id=session["user_id"])
    sell = db.execute(
        "SELECT symbol, sell_price, sell_date, sum(quantity) FROM shares WHERE owner=0 AND user_id=:id GROUP BY date, symbol", id=session["user_id"])
    merge = []
    for item in buy:
        mItem = {}
        mItem["operation"] = "Buy"
        mItem["symbol"] = item["symbol"]
        mItem["price"] = item["buy_price"]
        mItem["quantity"] = item["sum(quantity)"]
        mItem["temp_date"] = item["date"]
        merge.append(mItem)
    for item in sell:
        mItem = {}
        mItem["operation"] = "Sell"
        mItem["symbol"] = item["symbol"]
        mItem["price"] = usd(item["sell_price"])
        mItem["quantity"] = item["sum(quantity)"]
        mItem["temp_date"] = item["sell_date"]
        merge.append(mItem)
    sortedMerge = sorted(merge, key=lambda dictionary: datetime.strptime(dictionary["temp_date"], "%Y-%m-%d  %H:%M:%S"))
    for item in sortedMerge:
        date = datetime.strptime(item["temp_date"], "%Y-%m-%d  %H:%M:%S")
        item["date"] = f"{date.year}-{date.month}-{date.day}"
        item["time"] = "{:.2f}:{:.2f}:{:.2f}".format(date.hour, date.minute, date.second)
    return render_template("history.html", items=sortedMerge)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        page = request.form.get('page')
        if page == None:
            page = "/"
        return redirect(f"{page}")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        page = request.args.get("page")
        return render_template("login.html", page=page)


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
    if request.method == "GET":
        return render_template("quote.html")
    else:
        response = lookup(request.form.get("symbol"))
        if response is None:
            return apology("Invalid symbol")
        response["price"] = usd(response["price"])
        return render_template("quote.html", check=response)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        if len(username) < 1:
            return apology("Missing username!")
        elif len(password) < 1:
            return apology("Missing password!")
        elif password != request.form.get("confirmation"):
            return apology("Passwords doesn't match!")
        else:
            hashPas = generate_password_hash(password)
            result = db.execute("INSERT INTO users (username, hash) VALUES (:u, :h)", u=username, h=hashPas)
            if not result:
                return apology("This username is already in use!")
            result = db.execute("SELECT id FROM users WHERE username = :u", u=username)
            session["user_id"] = result[0]["id"]
            return redirect('/')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stocks = db.execute("SELECT *, sum(quantity) FROM SHARES WHERE user_id=:id AND OWNER=1 GROUP BY symbol", id=session["user_id"])
    if request.method == "GET":
        names = []
        for stock in stocks:
            names.append(stock["symbol"])
        return render_template("sell.html", names=names)
    else:
        for stock in stocks:
            if stock["symbol"] == request.form.get("symbol"):
                try:
                    number = int(request.form.get("shares"))
                except:
                    return apology("Invalid number of shares!")
                if stock["sum(quantity)"] >= number:
                    price = lookup(stock["symbol"])["price"]
                    db.execute("UPDATE shares SET owner=0, sell_price=:price, sell_date=:date WHERE user_id=:id AND symbol=:symbol AND owner=1 ORDER BY symbol LIMIT :n",
                               price=price, date=datetime.today(), id=session["user_id"], symbol=stock["symbol"], n=number)
                    db.execute("UPDATE users SET cash= :price + cash WHERE id=:id", price=price * number, id=session["user_id"])
                    return redirect("/")
                else:
                    return apology("You don't have that many stocks!")


@app.route("/redeem", methods=["GET", "POST"])
@login_required
def redeem():
    if request.method == "GET":
        return render_template("redeem.html")
    gift = request.form.get("giftCard")
    try:
        int(gift[-1])
    except:
        return apology("Invalid gift card!")
    if len(gift) < 5:
        return apology("Invalid gift card!")
    db.execute("UPDATE users SET cash = cash + :gift WHERE id = :id", gift=int(gift[-1]) * 1000, id=session["user_id"])
    return render_template("redeem.html", success=True)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
