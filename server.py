from flask import Flask
from flask import request

app = Flask(__name__)

@app.route("/")
def receive_data():
    temp = request.args.get("t")
    humidity = request.args.get("h")
    print(f"Temperature: {temp}, humidity: {humidity}")
    return "OK", 200  
