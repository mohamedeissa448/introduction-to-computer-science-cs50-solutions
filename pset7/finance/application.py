import os
import time
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
    rows=db.execute("SELECT * FROM portofolio WHERE user_id=:s",s=session["user_id"])
    row=db.execute("SELECT * FROM users WHERE id=:s",s=session["user_id"])
    overall=0
    for line in rows:
        overall+=line["total"]
    overall+=row[0]["cash"]
    return render_template("portofolio.html",rows=rows,cash=usd(row[0]["cash"]),overall=usd(overall))



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol") or not lookup(request.form.get("symbol")):
            return apology("must provide valid symbol",400)
        if not request.form.get("shares") or int(request.form.get("shares")) <= 0:
            return apology("shares must be positive integer!",400)
        row=db.execute("SELECT * FROM users WHERE id=:s",s=session["user_id"])
        dict=lookup(request.form.get("symbol"))
        cost=dict["price"]* int(request.form.get("shares"))
        if row[0]["cash"]>cost:
            db.execute("INSERT INTO history(symbol,shares,price,transacted,user_id,status) VALUES (:s,:sh,:p,:t,:u_i,:status)",s=dict["symbol"],sh=int(request.form.get("shares")),p=dict["price"],t=time.asctime( time.localtime(time.time())),u_i=session["user_id"],status='bought')
            row[0]["cash"]=row[0]["cash"]-cost
            db.execute("UPDATE users SET cash = :cash WHERE id=:s",cash=row[0]["cash"],s=session["user_id"])
            exist=db.execute("SELECT * FROM portofolio WHERE symbol=:s AND user_id=:u_i",s=dict["symbol"],u_i=session["user_id"])
            if len(exist) == 0 :
                db.execute("INSERT INTO portofolio(symbol,name,shares,price,total,user_id) VALUES (:s,:n,:sh,:p,:t,:u_i)",s=dict["symbol"],n=dict["name"],sh=int(request.form.get("shares")),p=dict["price"],t=cost,u_i=session["user_id"])
            else:
                db.execute("UPDATE portofolio SET shares =shares+:sh, price=:p, total=total+:t WHERE symbol=:s AND user_id=:u_i",sh=int(request.form.get("shares")),p=dict["price"],t=dict["price"] * int(request.form.get("shares")),s=dict["symbol"],u_i=session["user_id"])
        else:
            return apology("Can't afford!",400)



        return redirect("/")
    else:
         return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_history=db.execute("SELECT * FROM history WHERE user_id=:u_i",u_i=session["user_id"])
    return render_template("history.html",s=user_history)


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
    if request.method == "POST":
        if not request.form.get("symbol") or not lookup(request.form.get("symbol")):
            return apology("must provide valid symbol", 400)
        return render_template("quoted.html", dict=lookup(request.form.get("symbol")) )
    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        if not request.form.get("username"):
            return apology("must provide username", 400)
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                              username=request.form.get("username"))
        if len(rows) !=0:
            return apology("choose another username", 400)
        if not request.form.get("password") or not request.form.get("password")==request.form.get("confirmation"):
            return apology("password must provided and matched",400)
        rows=db.execute("INSERT INTO users(username,hash)VALUES(:username,:hash)",username=request.form.get("username"),hash=generate_password_hash(request.form.get("password")))
        row = db.execute("SELECT * FROM users WHERE username = :username",
                              username=request.form.get("username"))
        session["user_id"]=row[0]["id"]
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        dict=lookup(request.form.get("symbol"))
        if not request.form.get("symbol") or not request.form.get("shares") or not lookup(request.form.get("symbol")):
            return apology("Must provide valid symbol and positive integer",400)
        else:
            row=db.execute("SELECT *FROM portofolio WHERE symbol=:s AND user_id=:u_i",s=request.form.get("symbol"),u_i=session["user_id"])
            if len(row) == 0 or int(request.form.get("shares")) > row[0]["shares"]:
                return apology("you don't have enough shares of this company",400)
            else:
                db.execute("INSERT INTO history(symbol,shares,price,transacted,user_id,status) VALUES (:s,:sh,:p,:t,:u_i,:status)",s=dict["symbol"],sh=int(request.form.get("shares")),p=dict["price"],t=time.asctime( time.localtime(time.time())),u_i=session["user_id"],status='sold')
                db.execute("UPDATE portofolio SET shares =shares-:sh, price=:p, total=total-:t WHERE symbol=:s AND user_id=:u_i",sh=int(request.form.get("shares")),p=dict["price"],t=dict["price"] * int(request.form.get("shares")),s=dict["symbol"],u_i=session["user_id"])
                db.execute("UPDATE users SET cash=cash+:extra WHERE id=:i",extra=int(request.form.get("shares")) * dict["price"],i=session["user_id"])
                db.execute("DELETE FROM portofolio WHERE shares=0")
                return redirect("/")
    else:
        rows=db.execute("SELECT *FROM portofolio where user_id=:u_i ",u_i=session["user_id"])
        arr=[]
        for row in rows:
            arr.append(row['symbol'])
        return render_template("selling.html",arr=arr)



def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
